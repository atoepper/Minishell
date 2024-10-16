/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atoepper <atoepper@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 15:53:41 by jweingar          #+#    #+#             */
/*   Updated: 2024/10/16 13:26:30 by atoepper         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/minishell.h"

int	print_env_with_empty(char **argv, t_shell *mshell, int fd)
{
	t_env	*envlst;

	if (argv[1] != NULL)
		return (ft_putstr_fd("env: too many arguments\n", 2), 1);
	envlst = mshell->envlst;
	if (envlst == NULL)
		return (1);
	while (envlst != NULL)
	{
		write(fd, "declare -x ", 11);
		write(fd, envlst->key, ft_strlen(envlst->key));
		if (envlst->value != NULL)
		{
			write(fd, "=\"", 2);
			write(fd, envlst->value, ft_strlen(envlst->value));
			write(fd, "\"\n", 2);
		}
		else
			write(fd, "\n", 1);
		envlst = envlst->next;
	}
	return (0);
}

void	change_or_create(char *arg, char *key, t_shell *mshell)
{
	if (ft_find_key(mshell->envlst, key) != NULL)
	{
		print2errorfile("1");
		print2errorfile(key);
		if (ft_getvalue(arg) != NULL)
			ft_change_envvalue(mshell->envlst, key, ft_getvalue(arg));
		free(key);
	}
	else
	{
		print2errorfile("2");
		print2errorfile(key);
		ft_add_env(&(mshell->envlst), ft_new_env(key,
				ft_getvalue(arg)));
	}
}

void	ft_export_error(char *key, int *errno)
{
	ft_putstr_fd("minishell: export: \'", 2);
	ft_putstr_fd(key, 2);
	ft_putstr_fd("\': not a valid identifier\n", 2);
	*errno = 1;
}

int	ft_export(char **argv, t_shell *mshell, int fd)
{
	int		i;
	int		errno;
	char	*key;

	if (argv == NULL)
		return (1);
	if (argv[1] == NULL)
		return (print_env_with_empty(argv, mshell, fd), 0);
	i = 0;
	errno = 0;
	while (argv[++i] != NULL)
	{
		key = ft_getkeyword(argv[i]);
		if (key == NULL)
			return (ft_set_error(mshell, 1, MALLOC), 1);
		if (!ft_iskeyword(key))
			ft_export_error(key, &errno);
		else
			change_or_create(argv[i], key, mshell);
	}
	mshell->env = ft_remake_env(mshell);
	return (errno);
}
