/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jweingar <jweingar@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 15:53:41 by jweingar          #+#    #+#             */
/*   Updated: 2024/08/27 11:37:00 by jweingar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/minishell.h"

int	ft_unset(char **argv, t_env *envlst)
{
	int	i;

	i = 1;
	if (argv == NULL)
		return (1);
	if (argv[1] == NULL)
		return (printf("unset: not enough arguments\n"), 1);
	while (argv[i] != NULL)
	{
		if (ft_find_value_by_key(envlst, argv[i]) != NULL)
			ft_remove_env(&envlst, argv[i]);
		i++;
	}
	return (0);
}
