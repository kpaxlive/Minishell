/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dayan <42istanbul.com.tr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/21 15:02:44 by dayan             #+#    #+#             */
/*   Updated: 2022/01/21 15:02:45 by dayan            ###   ########.tr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*tmp;
	t_list	*tmp2;

	if (!del || !*lst)
		return ;
	tmp = *lst;
	while (tmp)
	{
		tmp2 = (tmp)->next;
		(*del)((tmp)->content);
		free(tmp);
		tmp = tmp2;
	}
	*lst = NULL;
}
