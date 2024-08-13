/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atoepper <atoepper@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/18 16:04:57 by alexander         #+#    #+#             */
/*   Updated: 2023/11/27 10:27:13 by atoepper         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void*))
{
	t_list	*pt;

	if (lst == NULL || *lst == NULL)
		return ;
	while ((*lst)->next != NULL)
	{
		pt = *lst;
		*lst = (*lst)->next;
		del(pt->content);
		free(pt);
	}
	pt = *lst;
	*lst = (*lst)->next;
	del(pt->content);
	free(pt);
}
