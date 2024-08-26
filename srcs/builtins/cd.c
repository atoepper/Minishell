/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jweingar <jweingar@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 16:57:51 by atoepper          #+#    #+#             */
/*   Updated: 2024/08/26 15:41:02 by jweingar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/minishell.h"

int	ft_cd_relativ(char **argv)
{
	int				return_value;
	DIR				*dir;
	char			*path;
	struct dirent	*entry;

	path = NULL;
	return_value = 0;
	path = getcwd(path, 0);
	if (path == NULL)
		return (1);
	dir = opendir(path);
	entry = readdir(dir);
	while (entry != NULL)
	{
		if (ft_strncmp(entry->d_name, argv[1], 1024) == 0)
		{
			path = ft_join_path_and_name(path, argv[1]);
			if (path == NULL)
				return (closedir(dir), 1);
			return_value = chdir(path);
			return (free(path), closedir(dir), return_value);
		}
		entry = readdir(dir);
	}
	return (closedir(dir), free(path), 1);
}

int	ft_cd(char **argv, char **envp)
{
	int				return_value;

	(void)envp;
	if (argv == NULL || argv[1] == NULL)
		return (1);
	return_value = ft_cd_relativ(argv);
	if (return_value == EXIT_SUCCESS)
		return (return_value);
	else
	{
		return_value = chdir(argv[1]);
		if (return_value != EXIT_SUCCESS)
			return (perror("cd"), return_value);
		return (return_value);
	}
}
