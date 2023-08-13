/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fel-hazz <fel-hazz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/10 20:19:56 by serhouni          #+#    #+#             */
/*   Updated: 2023/08/13 19:19:15 by fel-hazz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	check_word(char c)
{
	if (c == '\'' || c == '\"' || c == '|' || c == '*' || c == '<' || c == '>'
		|| c == '$' || c == ' ' || c == '\t')
		return (0);
	return (1);
}

t_list	*lexer(char *line)
{
	t_list	*head;
	t_list	*token;
	int		i;
	int		x;

	i = 0;
	head = NULL;
	while (line[i])
	{
		x = i;
		while (line[i] && check_word(line[i]))
			i++;
		if (x != i)
			token = ft_lstnew(create_token(0, ft_substr(line, x, i - x)));
		else if (line[i] == ' ' || line[i] == '\t')
			token = ft_lstnew(create_token(TYPE_SPC, space_type(line, &i)));
		else
			token = ft_lstnew(create_token(find_type(line, &i), ft_substr(line,
							x, i - x)));
		if (!token)
			ft_exit(ENOMEM);
		ft_lstadd_back(&head, token);
	}
	return (head);
}
