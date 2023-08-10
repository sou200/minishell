/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenization.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fel-hazz <fel-hazz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/11 00:26:51 by serhouni          #+#    #+#             */
/*   Updated: 2023/08/09 12:09:44 by fel-hazz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*space_type(char *line, int *i)
{
	int		x;
	char	*str;

	x = 0;
	while (line[*i + x] == ' ' || line[*i + x] == '\t')
		x++;
	str = malloc(x + 1);
	if (!str)
		exit(-1);
	ft_memmove(str, line + *i, x);
	*i += x;
	str[x] = '\0';
	return (str);
}

enum t_tokentype	find_type2(char *line, int *i)
{
	if (line[*i] == '|')
		return (*i += 1, TYPE_PIPE);
	if (line[*i] == '<' && line[*i + 1] != '<')
		return (*i += 1, TYPE_RD_L);
	else if (line[*i] == '<')
		return (*i += 2, TYPE_HERE_DOC);
	if (line[*i] == '>' && line[*i + 1] != '>')
		return (*i += 1, TYPE_RD_R);
	else if (line[*i] == '>')
		return (*i += 2, TYPE_APPEND);
	exit(-1);
}

enum t_tokentype	find_type(char *line, int *i)
{
	if (line[*i] == '$')
		return (*i += 1, TYPE_DOLLAR);
	if (line[*i] == '\'')
		return (*i += 1, TYPE_QUOTE);
	if (line[*i] == '\"')
		return (*i += 1, TYPE_D_QUOTE);
	if (line[*i] == '*')
		return (*i += 1, TYPE_STAR);
		
	return (find_type2(line, i));
}

token_t	*create_token(enum t_tokentype type, void *content)
{
	token_t	*token;

	token = malloc(sizeof(token_t));
	if (!token)
		ft_exit(ENOMEM);
	token->type = type;
	token->value = content;
	return (token);
}
