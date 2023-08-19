/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: serhouni <serhouni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/13 11:43:01 by serhouni          #+#    #+#             */
/*   Updated: 2023/08/18 22:20:09 by serhouni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

#include "../minishell.h"

t_list	*to_expanded_tokens(t_list *tokens, char **env)
{
	int		open_q;
	t_list	*new_token_lst;
	char	*quote_content;

	open_q = 0;
	new_token_lst = NULL;
	quote_content = NULL;
	while (tokens != NULL)
	{
		if (((t_token *)tokens->content)->type == TYPE_QUOTE && open_q != 2)
			in_quote_handler(&open_q, &quote_content, &new_token_lst, 1);
		else if (((t_token *)tokens->content)->type == TYPE_D_QUOTE
			&& open_q != 1)
			in_quote_handler(&open_q, &quote_content, &new_token_lst, 2);
		else if (((t_token *)tokens->content)->type == TYPE_DOLLAR
			&& is_valid_env(tokens, open_q))
			costum_env_expand(&tokens, &new_token_lst, env, open_q);
		else if (open_q)
			quote_content = ft_strjoin_free(quote_content,
					((t_token *)tokens->content)->value, 1, 0);
		else
			f(&new_token_lst, tokens);
		tokens = tokens->next;
	}
	return (new_token_lst);
}

t_list	*parce_line(char *line, char **env)
{
	t_list	*tokens;
	t_list	*expanded_tokens;
	t_list	*wildcarded_tokens;
	t_list	*final_tokens;
	t_list	*smpl_cmnds;

	tokens = lexer(line);
	if (!is_valid_syntax(tokens))
		return (ft_lstclear(&tokens, ft_free_token)
			, printf("syntax error !\n"), gl.return_value = 258, NULL);
	expanded_tokens = to_expanded_tokens(tokens, env);
	wildcarded_tokens = wildcard_it(expanded_tokens);
	final_tokens = join_and_clean_tokens(wildcarded_tokens);
	smpl_cmnds = generate_cmnds(final_tokens);
	ft_lstclear(&tokens, ft_free_token);
	ft_lstclear(&expanded_tokens, ft_free_token);
	ft_lstclear(&wildcarded_tokens, ft_free_token);
	ft_lstclear(&final_tokens, ft_free_token);
	return (smpl_cmnds);
}
