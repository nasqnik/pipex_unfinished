/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anikitin <anikitin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 11:20:30 by anikitin          #+#    #+#             */
/*   Updated: 2024/07/10 13:02:01 by anikitin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*new_list;
	t_list	*node;

	if (!lst)
		return (NULL);
	new_list = NULL;
	while (lst)
	{
		node = malloc(sizeof(t_list));
		if (!node)
		{
			ft_lstclear(&new_list, (*del));
			return (NULL);
		}
		node->content = f(lst->content);
		node->next = NULL;
		ft_lstadd_back(&new_list, node);
		lst = lst->next;
	}
	return (new_list);
}
