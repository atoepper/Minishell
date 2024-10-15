/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env2.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jweingar <jweingar@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 17:14:23 by atoepper          #+#    #+#             */
/*   Updated: 2024/10/15 11:05:52 by jweingar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/minishell.h"


char	*ft_find_key(t_env *list, char *keyword)
{
	while (list)
	{
		if (!ft_strncmp(list->key, keyword, ft_strlen(keyword)))
			return (list->key);
		else
			list = list->next;
	}
	return (NULL);
}
