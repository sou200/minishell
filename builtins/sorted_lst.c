/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sorted_lst.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fel-hazz <fel-hazz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/28 01:12:44 by fel-hazz          #+#    #+#             */
/*   Updated: 2023/07/28 01:25:31 by fel-hazz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../minishell.h"

int	ft_strcmp(const char *s1, const char *s2)
{
	size_t	i;

	i = 0;
	if (!s1 && !s2)
		return (0);
	if (!s1 || !s2)
		return (1);
	while (s1[i] && s2[i])
	{
		if (s1[i] != s2[i])
			return ((unsigned char)s1[i] - (unsigned char)s2[i]);
		i++;
	}
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}

void	ft_lstaddandsort(t_list **lst, t_list *new)
{
	void	*holder;
	t_list	*traveler;

	if (lst == 0 || new == 0)
		return ;
	if (*lst == 0)
		*lst = new;
	else
	{
		traveler = *lst;
		while (traveler)
		{
			if (ft_strcmp((const char *)(traveler)->content, (const char *)new->content) > 0)
			{
				holder = (traveler)->content;
				(traveler)->content = new->content;
				new->content = holder;
			}
			if (!traveler->next)
				break ;
			traveler = traveler->next;
		}
		new->prev = traveler;
		traveler->next = new;
	}
}