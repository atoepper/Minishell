/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envlist.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jweingar <jweingar@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/22 12:08:38 by atoepper          #+#    #+#             */
/*   Updated: 2024/09/23 16:42:35 by jweingar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/minishell.h"

t_env	*ft_new_env(char *key, char *value)
{
	t_env	*new;

	new = (t_env*)malloc(sizeof(t_env));
	if (!new)
		return (NULL);
	new->key = key;
	new->value = value;
	new->next = NULL;
	return (new);
}

void	ft_add_env(t_env **envlist, t_env *new_env)
{
	t_env	*current;

	if (!*envlist)
		*envlist = new_env;
	else
	{
		current = *envlist;
		while (current && current->next)
			current = current->next;
		current->next = new_env;
	}
}

void	ft_del_env(t_env *env)
{
	free(env->key);
	free(env->value);
	free(env);
	env = NULL;
}

void	ft_clear_envlist(t_env **envlist)
{
	t_env	*current;
	t_env	*tmp;

	current = *envlist;
	if (!current)
		return ;
	while (current)
	{
		tmp = current->next;
		ft_del_env(current);
		current = tmp;
	}
	*envlist = NULL;
}

void	ft_printenvlist(t_shell *mshell)
{
	t_env	*current;

	current = mshell->envlst;
	if (!current)
	{
		printf("list is empty\n");
		return ;
	}
	printf("env list: \n");
	while (current)
	{
		printf("key: %s, value: %s\n", current->key, current->value);
		current = current->next;
	}
}
