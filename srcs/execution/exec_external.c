/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_external.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jweingar <jweingar@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 10:38:05 by jweingar          #+#    #+#             */
/*   Updated: 2024/09/23 16:15:16 by jweingar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/minishell.h"

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

char	*search_function_in_path(char *name, t_shell *mshell)
{
	char	*path;
	char	**lst_path;
	int		i;
	char	*str;

	(void)mshell;
	if (!access(name, F_OK))
		return (ft_strdup(name));
	path = ft_find_value_by_key(mshell->envlst, "PATH");
	if (path == NULL)
		return (NULL);
	lst_path = ft_split(path, ':');
	i = -1;
	while (lst_path[++i] != NULL)
		if (search_file_in_directory(lst_path[i], name) == 1)
			break ;
	if (lst_path[i] == NULL)
		return (free_array(lst_path), NULL);
	str = ft_join_path_and_name(lst_path[i], name);
	free_array(lst_path);
	if (str == NULL)
		return (perror("ft_join_path_and_name"), NULL);
	return (str);
}

char	*ft_join_path_and_name(char *path, char *name)
{
	char	*path_new;
	char	*path_full;

	path_new = ft_strjoin(path, "/");
	if (path_new == NULL)
		return (perror("ft_strjoin"), NULL);
	path_full = ft_strjoin(path_new, name);
	free(path_new);
	if (path_full == NULL)
		return (NULL);
	return (path_full);
}

int	exec_external(char **argv, t_shell *mshell, int *pipefd_in, int *pipefd_out)
{
	char			*path;
	int				exit_status;
	char			*env[1];
	int				pid;
	struct termios	oldt;

	(void)mshell;
	tcgetattr(STDIN_FILENO, &oldt);
	env[0] = NULL;
	exit_status = 0;
	path = search_function_in_path(argv[0], mshell);
	if (path == NULL)
		return (127);
	pid = fork();
	if (pid == 0)
	{
		if (isatty(STDIN_FILENO) && isatty(STDOUT_FILENO)) {
			tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
		}
		else
		{
			close(pipefd_in[1]);
			close(pipefd_out[0]);
			dup2(pipefd_in[0], 0);
			close(pipefd_in[0]);
			dup2(pipefd_out[1], 1);
			close(pipefd_out[1]);
		}
		exit_status = execve(path, argv, env);
		perror("execvp");
		free(path);
		exit(exit_status);
	}
	else
	{
		close(pipefd_in[0]);
		close(pipefd_in[1]);
		close(pipefd_out[1]);
		wait(&exit_status);
		free(path);
	}
	return (exit_status);
}
