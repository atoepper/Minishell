/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jweingar <jweingar@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 17:14:23 by atoepper          #+#    #+#             */
/*   Updated: 2024/08/27 09:57:51 by jweingar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/minishell.h"

char	*ft_getvalue(char *str)
{
	char	*value;

	value = ft_strchr(str, '=');
	if (value == NULL)
		return (NULL);
	value++;
	return (value);
}

char	*ft_getkeyword(char *str)
{
	char	*key;

	key = ft_substr(str, 0, ft_nextchar(str, '='));
	return (key);
}

char	*ft_find_value_by_key(t_env *list, char *keyword)
{
	while (list)
	{
		if (!ft_strncmp(list->key, keyword, ft_strlen(keyword)))
			return (list->value);
		else
			list = list->next;
	}
	return (NULL);
}


void	ft_change_envvalue(t_env *envlist, char *key, char *new_value)
{
	while (envlist)
	{
		if (!ft_strncmp(envlist->key, key, ft_strlen(key) + 1))
		{
			free(envlist->value);
			envlist->value = new_value;
			return ;
		}
		envlist = envlist->next;
	}
}

void	ft_remove_env(t_env **envlist, char *key)
{
	t_env	*tmp;
	t_env	*current;

	if (!envlist || !*envlist)
		return ;
	if (!ft_strncmp((*envlist)->key, key, ft_strlen(key) + 1))
	{
		tmp = *envlist;
		*envlist = (*envlist)->next;
		ft_del_env(tmp);
		return ;
	}
	current = *envlist;
	while (current->next)
	{
		if (!ft_strncmp(current->next->key, key, ft_strlen(key) + 1))
		{
			tmp = current->next;
			current->next = tmp->next;
			ft_del_env(tmp);
			return ;
		}
		current = current->next;
	}
}
