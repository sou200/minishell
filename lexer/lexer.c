/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: serhouni <serhouni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/10 20:19:56 by serhouni          #+#    #+#             */
/*   Updated: 2023/06/11 00:57:01 by serhouni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	check_word(char c)
{
	if (c == ')' || c == '(' || c == '\'' || c == '\"' || c == '|' || c == '&'
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
	char	*word;

	x = 0;
	i = 0;
	head = NULL;
	while (line[i])
	{
		x = i;
		while (line[i] && check_word(line[i]))
			i++;
		if (x != i)
			token = ft_lstnew(new_token(0, ft_substr(line, x, i - x)));
		else if (line[i] == ' ')
			token = ft_lstnew(new_token(TYPE_SPC, space_type(line, &i)));
		else
			token = ft_lstnew(new_token(find_type(line, &i), NULL));
		if (!token)
			exit(-1);
		ft_lstadd_back(&head, token);
	}
	return (head);
}
