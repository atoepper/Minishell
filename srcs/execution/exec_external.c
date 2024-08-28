/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_external.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jweingar <jweingar@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 10:38:05 by jweingar          #+#    #+#             */
/*   Updated: 2024/08/27 14:43:36 by jweingar         ###   ########.fr       */
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
		return (NULL);
	str = ft_join_path_and_name(lst_path[i], name);
	if (str == NULL)
		return (perror("ft_join_path_and_name"), NULL);
	return (str);
}

char	*ft_join_path_and_name(char *path, char *name)
{
	char	*path_new;
	char	*path_full;

	path_new = ft_strjoin(path, "/");
	free(path);
	if (path_new == NULL)
		return (perror("ft_strjoin"), NULL);
	path_full = ft_strjoin(path_new, name);
	free(path_new);
	if (path_full == NULL)
		return (NULL);
	return (path_full);
}

int	exec_external(char **argv, t_env *envlst)
{
	char	*path;
	int		exit_status;
	char *env[] = { NULL };

	(void)envlst;
	exit_status = 0;
	path = search_function_in_path(argv[0]);
	if (path == NULL)
		return (1);
	if (execve(path, argv, env) == -1)
		exit(EXIT_FAILURE);
	free(path);
	return (exit_status);
}