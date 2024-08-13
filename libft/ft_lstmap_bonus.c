/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atoepper <atoepper@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/27 10:42:07 by atoepper          #+#    #+#             */
/*   Updated: 2023/11/28 17:29:17 by atoepper         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*pt;
	t_list	*newlst;
	t_list	*new_node;
	void	*content;

	if (lst == NULL)
		return (lst);
	pt = lst;
	newlst = NULL;
	while (pt != NULL)
	{
		content = f(pt->content);
		new_node = ft_lstnew(content);
		if (new_node == NULL)
		{
			if (content)
				del(content);
			ft_lstclear(&newlst, del);
			return (NULL);
		}
		ft_lstadd_back(&newlst, new_node);
		pt = pt->next;
	}
	return (newlst);
}
