/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fel-hazz <fel-hazz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/19 07:15:38 by fel-hazz          #+#    #+#             */
/*   Updated: 2023/08/06 02:43:21 by fel-hazz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_free(int number, ...)
{
	va_list	va;

	va_start(va, number);
	while (number-- > 0)
		free(va_arg(va, void *));
	va_end(va);
}

int	ft_exit(int error)
{
	free_table(env);
	free_table(default_env);
	ft_lstclear(&export_list, free);
	exit(error);
}

int	ft_sortir(t_list *head)
{
	if (head && head->content
		&& !ft_strrcmp(((t_prototype *)(head->content))->cmnd[0]
		, "exit"))
	{
		error_write("exit\n");
		ft_exit(0);
	}
	if (head && head->content && !head->next
		&& !ft_strrcmp(((t_prototype *)(head->content))->cmnd[0]
		, "export"))
	{
		ft_export(((t_prototype *)(head->content))->cmnd + 1);
		return (0);
	}
	return (1);
}

void	init(int argc, char const *argv[], char **en)
{
	if (argc > 2 || argv[1])
		print_error(7, 2, "minishell: ", ": too many arguments\n");
	initialise_default();
	initialise_env((const char **)en);
	rl_catch_signals = 0;
	signal(SIGINT, controlec);
	signal(SIGQUIT, SIG_IGN);
}

void	error_write(const char *s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		write(2, &s[i], 1);
		i++;
	}
}
