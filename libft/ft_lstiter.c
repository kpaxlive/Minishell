/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstiter.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dayan <42istanbul.com.tr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/21 15:04:43 by dayan             #+#    #+#             */
/*   Updated: 2022/02/03 17:06:34 by dayan            ###   ########.tr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"
#include <stdio.h>

void	ft_lstiter(t_list *lst, void (*f)(void *))
{
	t_list	*node;

	node = lst;
	while (node)
	{
		(*f)(node->content);
		node = node->next;
	}
}

/*void f(void *x)
{
	int i = 0;
	int z = ft_strlen((char *)x);
	while(*((char *)x) != '\0' && z--)
	{
		if(i % 2 == 0)
			*((char *)x + i) = 'x';
		i++;
		
	}
	
}

int main()
{
	t_list *x, *y;
	x = ft_lstnew(ft_strdup("duhan"));
	y =ft_lstnew(ft_strdup("furkan"));
	x -> next = y;
	
	ft_lstiter(x, f);
	while(x)
	{
		printf("%s\n", x->content);
		x = x->next;
	}
	
}*/
