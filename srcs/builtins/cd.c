/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jweingar <jweingar@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 16:57:51 by atoepper          #+#    #+#             */
/*   Updated: 2024/10/08 11:20:26 by jweingar         ###   ########.fr       */
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

int	go_to_home(t_shell *mshell)
{
	int		return_value;
	char	*ptr_home;

	ptr_home = ft_find_value_by_key(mshell->envlst, "HOME");
	if (ptr_home == NULL)
		return (1);
	return_value = chdir(ptr_home);
	return (return_value);
}

int	ft_cd(char **argv, t_shell *mshell, int fd)
{
	int		return_value;

	(void)fd;
	if (argv == NULL)
		return (1);
	if (argv[1] == NULL)
		return_value = go_to_home(mshell);
	else
	{
		if (!access(argv[1], F_OK))
			return_value = chdir(argv[1]);
		else
			return_value = ft_cd_relativ(argv);
	}
	if (return_value != EXIT_SUCCESS)
		ft_set_error(mshell, return_value,
			"cd: no such directory or file\n");
	return (return_value);
}
