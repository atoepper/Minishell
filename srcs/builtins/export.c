/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jweingar <jweingar@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 15:53:41 by jweingar          #+#    #+#             */
/*   Updated: 2024/10/11 10:15:55 by jweingar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/minishell.h"

int	print_env_with_empty(char **argv, t_shell *mshell, int fd)
{
	t_env	*envlst;
	int		return_val;

	if (argv[1] != NULL)
		return (ft_putstr_fd("env: too many arguments\n", 2), 1);
	envlst = mshell->envlst;
	if (envlst == NULL)
		return (1);
	while (envlst != NULL)
	{
		return_val = write(fd, envlst->key, ft_strlen(envlst->key));
		return_val = write(fd, "=", 1);
		return_val = write(fd, envlst->value, ft_strlen(envlst->value));
		return_val = write(fd, "\n", 1);
		envlst = envlst->next;
		return_val++;
	}
	return (0);
}

void	change_or_create(char *arg, char *key, t_shell *mshell)
{
	if (ft_find_value_by_key(mshell->envlst, key) != NULL)
	{
		ft_change_envvalue(mshell->envlst, key, ft_getvalue(arg));
		free(key);
	}
	else
		ft_add_env(&(mshell->envlst), ft_new_env(key,
				ft_getvalue(arg)));
}

int	ft_export(char **argv, t_shell *mshell, int fd)
{
	int		i;
	char	*key;

	if (argv == NULL)
		return (1);
	if (argv[1] == NULL)
		return (print_env_with_empty(argv, mshell, fd), 0);
	i = 0;
	while (argv[++i] != NULL)
	{
		if (ft_strchr(argv[i], '=') != NULL)
		{
			key = ft_getkeyword(argv[i]);
			if (key == NULL)
				return (1);
			change_or_create(argv[i], key, mshell);
		}
		else if (ft_find_value_by_key(mshell->envlst, argv[i]) == NULL)
			ft_add_env(&(mshell->envlst),
				ft_new_env(ft_strdup(argv[i]), ft_strdup("''")));
	}
	return (0);
}
