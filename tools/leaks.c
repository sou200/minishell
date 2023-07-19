/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   leaks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fel-hazz <fel-hazz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/19 07:15:38 by fel-hazz          #+#    #+#             */
/*   Updated: 2023/07/19 08:25:23 by fel-hazz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../minishell.h"

//number==number of addresses to freee
//hadi hia lfonction lit9der tfreeyi biha dakchi li allocated w mahadich t7tajo mn b3d
void	ft_free(int number, ...)
{
	va_list	va;

	va_start(va, number);
	while (number-- > 0)
		free(va_arg(va, void *));
	va_end(va);
}

//had lfonction kat exiti ela 7sab error, ila bghina nkhrjo wsafi error = 0m sinon error = ERRor code
void	ft_exit(int	error)
{
	int		i;
	t_list	*lst;

	i = ft_lstsize(global.garbage);
	while (i-- > 0)
	{
		lst = global.garbage->next;
		free(global.garbage->content);
		free(global.garbage);
		global.garbage = lst;
	}
	if (error == ENOMEM)
		perror("malloc: ");
	else if (error != 0)
		perror("");
	else
		exit(error);
}

//had lfonction hia bach t9der t ajouti chi address; garbage collector
void recycle(int n, ...)
{
	t_list	*lst;
	va_list	va;

	va_start(va, n);
	while (n-- > 0)
	{
		lst = ft_lstnew(va_arg(va, void *));
		if (!lst)
			ft_exit(ENOMEM);
		ft_lstadd_back(&global.garbage, lst);
	}
	va_end(va);
}
