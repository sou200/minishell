/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fel-hazz <fel-hazz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/10 20:19:56 by serhouni          #+#    #+#             */
/*   Updated: 2023/07/19 17:40:20 by fel-hazz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	check_word(char c)
{
	if (c == '\'' || c == '\"' || c == '|' || c == '&'
		|| c == '*' || c == '<' || c == '>' || c == '$' || c == ' ')
		return (0);
	return (1);
}

t_list	*lexer(char *line)
{
	t_list	*head;
	t_list	*token;
	int		i;
	int		x;

	x = 0;
	i = 0;
	head = NULL;
	while (line[i])
	{
		x = i;
		while (line[i] && check_word(line[i]))
			i++;
		if (x != i)
			token = ft_lstnew1(new_token(0, ft_substr1(line, x, i - x)));
		else if (line[i] == ' ')
		{
			// token = ft_lstnew1(new_token(TYPE_SPC, space_type(line, &i)));
			while(line[i] == ' ')
				i++;
				continue ;
		}
		else
			token = ft_lstnew1(new_token(find_type(line, &i), ft_substr1(line, x, i - x)));
		ft_lstadd_back(&head, token);
	}
	return (head);
}

// char *get_val_by_type()
// {
	
// }
