/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstlast_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atoepper <atoepper@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/18 15:44:12 by alexander         #+#    #+#             */
/*   Updated: 2023/11/28 12:02:56 by atoepper         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "libft.h"

t_list	*ft_lstlast(t_list *lst)
{
	t_list	*pt;

	if (lst == NULL)
		return (lst);
	pt = lst;
	while (pt->next != NULL)
		pt = pt->next;
	return (pt);
}
