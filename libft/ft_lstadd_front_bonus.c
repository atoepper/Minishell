/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_front_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atoepper <atoepper@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/18 15:32:34 by alexander         #+#    #+#             */
/*   Updated: 2023/11/27 13:11:27 by atoepper         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_front(t_list **lst, t_list *new)
{
	new->next = *lst;
	*lst = new;
}

// int	main(void)
// {
// 	char 	elem1[] = "first element";
// 	char 	elem2[] = "second element";
// 	char 	elem3[] = "third element";
// 	t_list	*node1;
// 	t_list	*node2;
// 	t_list	*node3;

// 	node1 = ft_lstnew(elem1);
// 	node2 = ft_lstnew(elem2);
// 	node3 = ft_lstnew(elem3);
// 	ft_lstadd_front(&node2, node1);
// 	return (0);
// }
