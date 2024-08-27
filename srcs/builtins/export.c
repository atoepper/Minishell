/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jweingar <jweingar@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 15:53:41 by jweingar          #+#    #+#             */
/*   Updated: 2024/08/27 10:51:16 by jweingar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/minishell.h"

int	ft_export(char **argv, t_env *envlst)
{
	int		i;
	char	*key;
	char	*value;

	i = 1;
	while (argv[i] != NULL)
	{
		if (ft_strchr(argv[i], '=') != NULL)
		{
			key = ft_getkeyword(argv[i]);
			value = ft_getvalue(argv[i]);
			printf("key:%s, value:%s\n", key, value);
			if (key == NULL || value == NULL)
				return (1);
			printf("search:%p, value:%s\n", ft_find_value_by_key(envlst, key), ft_find_value_by_key(envlst, key));
			if (ft_find_value_by_key(envlst, key) != NULL)
			{
				ft_change_envvalue(envlst, key, value);
				free(key);
			}
			else
				ft_add_env(&envlst, ft_new_env(key, value));
		}
		i++;
	}
	return (0);
}