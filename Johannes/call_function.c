/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   call_function.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jweingar <jweingar@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 15:55:26 by jweingar          #+#    #+#             */
/*   Updated: 2024/08/19 15:55:27 by jweingar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/minishell.h"

void	free_lst_builtin(t_builtin	**lst_builtins)
{
	int	i;

	i = 0;
	if (lst_builtins == NULL)
		return ;
	while (lst_builtins[i] != NULL)
	{
		free(lst_builtins[i]);
		i++;
	}
	free(lst_builtins);
}

t_builtin	**alloc_lst_builtins(void)
{
	t_builtin	**lst_builtins;
	int			i;

	lst_builtins = malloc(sizeof(t_builtin *) * 8);
	if (lst_builtins == NULL)
		return (perror("malloc"), NULL);
	i = 0;
	while (i < 7)
	{
		lst_builtins[i] = malloc(sizeof(t_builtin));
		if (lst_builtins[i] == NULL)
			return (perror("malloc"), NULL);
		i++;
	}
	lst_builtins[7] = NULL;
	return (lst_builtins);
}

t_builtin	**fill_lst_builtins(void)
{
	t_builtin	**lst_builtins;

	lst_builtins = alloc_lst_builtins();
	if (lst_builtins == NULL)
		return (perror("malloc"), NULL);
	lst_builtins[0]->name = "echo\0";
	lst_builtins[0]->func = ft_echo;
	lst_builtins[1]->name = NULL;
	lst_builtins[1]->func = NULL;
	// lst_builtins[1]->name = "cd\0";
	// lst_builtins[1]->func = &ft_cd;
	// lst_builtins[2]->name = "pwd\0";
	// lst_builtins[2]->func = &ft_pwd;
	// lst_builtins[3]->name = "export\0";
	// lst_builtins[3]->func = &ft_export;
	// lst_builtins[4]->name = "unset\0";
	// lst_builtins[4]->func = &ft_unset;
	// lst_builtins[5]->name = "env\0";
	// lst_builtins[5]->func = &ft_env;
	// lst_builtins[6]->name = "exit\0";
	// lst_builtins[6]->func = &ft_exit;
	// lst_builtins[7]->name = NULL;
	// lst_builtins[7]->func = NULL;
	return (lst_builtins);
}

t_function_ptr functionpath_builtins(char *name)
{
	t_builtin		**lst_builtins;
	int				i;
	t_function_ptr	func;

	lst_builtins = fill_lst_builtins();
	i = 0;
	while (lst_builtins[i]->name != NULL)
	{
		if (ft_strncmp(lst_builtins[i]->name, name, ft_strlen(name) + 1) == 0)
		{
			func = lst_builtins[i]->func;
			return (free_lst_builtin(lst_builtins), func);
		}
		i++;
	}
	free_lst_builtin(lst_builtins);
	return (0);
}


// void exec_funtion(char **argv)
// {
// 	if (is_function_builtin(argv[0])
// }

int	search_file_in_directory(const char *directory, char *name)
{
	struct dirent	*entry;
	DIR				*dp;

	dp = opendir(directory);
	if (dp == NULL)
		return (-1);
	entry = readdir(dp);
	while (entry != NULL)
	{
		if (ft_strncmp(entry->d_name, name, ft_strlen(name) + 1) == 0)
		{
			closedir(dp);
			return (1);
		}
		entry = readdir(dp);
	}
	closedir(dp);
	return (0);
}

char	*search_function_in_path(char *name)
{
	char	*path;
	char	**lst_path;
	int		i;
	char	*str;

	path = getenv("PATH");
	if (path == NULL)
		return (perror("getenv"), NULL);
	lst_path = ft_split(path, ':');
	i = 0;
	while (lst_path[i] != NULL)
	{
		if (search_file_in_directory(lst_path[i], name) == 1)
			break ;
		i++;
	}
	if (lst_path[i] == NULL)
		return (perror("not found in PATH"), NULL);
	str = ft_strjoin(lst_path[i], "/");
	if (str == NULL)
		return (perror("ft_strjoin"), NULL);
	return (str);
}

int exec_builtin(int argc, char **argv)
{
	t_function_ptr	func;

	func = functionpath_builtins(argv[0]);
	if (func != NULL)
	{
		func(argc, argv);
		return (0);
	}
	return (1);
}

char *ft_join_path_and_name(char *path, char *name)
{
	char	*path_full;

	path_full = ft_strjoin(path, name);
	if (path_full == NULL)
		return (NULL);
	free(path);
	return (path_full);
}

int	exec_external(char **argv)
{
	char	*path;
	char	*path_full;
	pid_t	pid;
	int		exit_status;
	char	*envp[1];

	envp[0] = NULL;
	exit_status = 0;
	path = search_function_in_path(argv[0]);
	if (path == NULL)
		return (perror("PATH"), 1);
	pid = fork();
	if (pid < 0)
	{
		perror("fork");
		exit(EXIT_FAILURE);
	}
	if (pid == 0)
	{
		path_full = ft_join_path_and_name(path, argv[0]);
		if (execve(path_full, argv, envp) == -1)
		{
			perror("execve");
			exit(EXIT_FAILURE);
		}
		free(path_full);
	}
	else
		wait(&exit_status);
	return (exit_status);
}

int	main(void)
{
	char			*argv[] = {"echo", "-n", "hellorrrrr world"};
	int				argc = 3;

	if (exec_builtin(argc, argv))
		exec_external(argv);
	return (0);
}
