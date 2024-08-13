/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsize_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atoepper <atoepper@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/18 15:34:57 by alexander         #+#    #+#             */
/*   Updated: 2023/11/28 11:52:47 by atoepper         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "libft.h"

int	ft_lstsize(t_list *lst)
{
	unsigned int	count;
	t_list			*pt;

	pt = lst;
	if (!lst)
		return (0);
	count = 1;
	while (pt->next != NULL)
	{
		count++;
		pt = pt->next;
	}
	return (count);
}
