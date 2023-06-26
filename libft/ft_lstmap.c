/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dayan <42istanbul.com.tr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/21 15:05:50 by dayan             #+#    #+#             */
/*   Updated: 2022/02/03 17:07:27 by dayan            ###   ########.tr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*node;
	t_list	*new;
	t_list	*tmp;

	tmp = NULL;
	node = lst;
	while (node)
	{
		new = ft_lstnew((*f)(node->content));
		if (!new)
		{
			ft_lstclear(&new, del);
			return (0);
		}
		ft_lstadd_back(&tmp, new);
		node = node->next;
	}
	return (tmp);
}
