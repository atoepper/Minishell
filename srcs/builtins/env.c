/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jweingar <jweingar@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 14:58:04 by atoepper          #+#    #+#             */
/*   Updated: 2024/09/10 16:56:58 by jweingar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/minishell.h"

int	ft_print_env(char **envp)
{
	int	i;

	i = 0;
	while (envp[i])
		ft_printf("%s\n", envp[i++]);
	return (0);
}

int	ft_env(char **argv, t_shell *mshell)
{
	t_env	*envlst;

	(void)argv;
	envlst = mshell->envlst;
	if (envlst == NULL)
		return (0);
	while (envlst != NULL)
	{
		printf("%s=%s\n", envlst->key, envlst->value);
		envlst = envlst->next;
	}
	return (0);
}