/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: serhouni <serhouni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/14 00:21:55 by serhouni          #+#    #+#             */
/*   Updated: 2023/07/13 14:51:38 by serhouni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*lastnode;

	if (lst == 0)
		return ;
	if (*lst == 0)
		*lst = new;
	else
	{
		lastnode = ft_lstlast(*lst);
		new->prev = lastnode;
		lastnode->next = new;
	}
}
