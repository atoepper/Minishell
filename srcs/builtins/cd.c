/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jweingar <jweingar@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 16:57:51 by atoepper          #+#    #+#             */
/*   Updated: 2024/08/26 12:20:18 by jweingar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/minishell.h"

int	ft_cd_relativ(char **argv)
{
	int				return_value;
	DIR				*dir;
	char			*pwd;
	struct dirent	*entry;
	char			*path;

	pwd = NULL;
	return_value = 0;
	pwd = getcwd(pwd, 0);
	if (!pwd)
		return (1);
	dir = opendir(pwd);
	entry = readdir(dir);
	while (entry != NULL)
	{
		if (ft_strncmp(entry->d_name, argv[1], 1024) == 0)
		{
			path = ft_join_path_and_name(pwd, argv[1]);
			if (path == NULL)
				return (1);
			return_value = chdir(path);
			if (return_value != EXIT_SUCCESS)
				return(perror("cd"), free(path), return_value);
			return(free(path), return_value);
		}
		entry = readdir(dir);
	}
	return (1);
}

int	ft_cd(char **argv)
{
	int				return_value;

	if (argv == NULL || argv[1] == NULL)
		return (1);
	return_value = ft_cd_relativ(argv);
	if (return_value == EXIT_SUCCESS)
		return (return_value);
	else
	{
		return_value = chdir(argv[1]);
		if (return_value != EXIT_SUCCESS)
			return(perror("cd absolute"), return_value);
		return(return_value);
	}
}
