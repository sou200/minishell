/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenization.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: serhouni <serhouni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/11 00:26:51 by serhouni          #+#    #+#             */
/*   Updated: 2023/07/14 17:12:57 by serhouni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*space_type(char *line, int *i)
{
	int		x;
	char	*str;

	x = 0;
	while (line[*i] == ' ')
	{
		*i += 1;
		x++;
	}
	str = malloc(x + 1);
	if (!str)
		exit(-1);
	ft_memset(str, ' ', x);
	str[x] = '\0';
	return (str);
}

enum token_type	find_type2(char *line, int *i)
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

enum token_type	find_type(char *line, int *i)
{
	if (line[*i] == '$')
		return (*i += 1, TYPE_DOLLAR);
	if (line[*i] == '(')
		return (*i += 1, TYPE_L_BR);
	if (line[*i] == ')')
		return (*i += 1, TYPE_R_BR);
	if (line[*i] == '*')
		return (*i += 1, TYPE_STAR);
	if (line[*i] == '\'')
		return (*i += 1, TYPE_QUOTE);
	if (line[*i] == '\"')
		return (*i += 1, TYPE_D_QUOTE);
	return (find_type2(line, i));
}

token_t	*new_token(enum token_type type, void *content)
{
	token_t	*token;

	token = malloc(sizeof(token_t));
	if (!token)
		exit(-1);
	token->type = type;
	token->value = content;
	return (token);
}
