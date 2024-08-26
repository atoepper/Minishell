/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   search_function_in_path.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jweingar <jweingar@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 12:15:37 by jweingar          #+#    #+#             */
/*   Updated: 2024/08/19 12:15:40 by jweingar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/minishell.h"

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
	str = ft_strdup(lst_path[i]);
	if (str == NULL)
		return (perror("ft_strdup"), NULL);
	return (str);
}

int	main(void)
{
	char	*path;
	char	*filename = "echo";

	path = search_function_in_path(filename);
	if (path == NULL)
		return (1);
	printf("path: %s", path);
	free(path);
	return (0);
}
