/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstiter_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atoepper <atoepper@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/27 10:41:38 by atoepper          #+#    #+#             */
/*   Updated: 2023/11/27 11:12:15 by atoepper         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "libft.h"

void	ft_lstiter(t_list *lst, void (*f)(void *))
{
	t_list	*pt;

	pt = lst;
	if (lst == NULL)
		return ;
	while (pt != NULL)
	{
		f(pt->content);
		pt = pt->next;
	}
}
