/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: serhouni <serhouni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/13 11:43:01 by serhouni          #+#    #+#             */
/*   Updated: 2023/07/23 01:04:10 by serhouni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int is_redirection(token_t *token)
{
    return token->type == TYPE_HERE_DOC || token->type == TYPE_APPEND || token->type == TYPE_RD_L || token->type == TYPE_RD_R;
}

t_list *to_expanded_tokens(t_list *tokens, char **env)
{
    int open_q;
    t_list *new_token_lst;
    char *quote_content;

    open_q = 0;
    new_token_lst = NULL;
    quote_content = NULL;
    while (tokens != NULL)
    {
        if (((token_t *)tokens->content)->type == TYPE_QUOTE && open_q != 2)
            in_quote_handler(&open_q, &quote_content, &new_token_lst, 1);
        else if (((token_t *)tokens->content)->type == TYPE_D_QUOTE && open_q != 1)
            in_quote_handler(&open_q, &quote_content, &new_token_lst, 2);
        else if (((token_t *)tokens->content)->type == TYPE_DOLLAR && is_valid_env(tokens, open_q))
            expand_env(&tokens, env);
        else if (open_q)
            quote_content = ft_strjoin_free(quote_content, ((token_t *)tokens->content)->value, 1, 0);
        else
            ft_lstadd_back(&new_token_lst, token_lst_dup((token_t *)tokens->content));
        tokens = tokens->next;
    }
    return new_token_lst;
}

int is_valid_to_join(t_list *tokens)
{
    token_t *token;

    token = (token_t *)tokens->content;
    if (token->type == TYPE_WORD)
        return 1;
    if (token->type == TYPE_DOLLAR)
        return 1;
    return 0;
}

t_list *join_and_clean_tokens(t_list *tokens)
{
    t_list *new_tokens;
    token_t *token;
    char *joined;
    int j_flag;

    new_tokens = NULL;
    joined = NULL;
    j_flag = 0;
    while (tokens != NULL)
    {
        token = (token_t *)tokens->content;
        if (is_valid_to_join(tokens))
            joined = ft_strjoin_free(joined, token->value, 1, 0) + 0 * j_flag++;
        else if (token->type != TYPE_WORD)
        {
            if(j_flag)
                ft_lstadd_back(&new_tokens, ft_lstnew(create_token(TYPE_WORD, joined)));
            joined = NULL;
            j_flag = 0;
            if (token->type != TYPE_SPC)
                ft_lstadd_back(&new_tokens, token_lst_dup(token));
        }
        tokens = tokens->next;
    }
    if(j_flag)
        ft_lstadd_back(&new_tokens, ft_lstnew(create_token(TYPE_WORD, joined)));
    return new_tokens;
}

t_list *parce_line(char *line, char **env)
{
    t_list *tokens;
    t_list *expanded_tokens;
    t_list *final_tokens;

    tokens = lexer(line);
    if (!is_valid_syntax(tokens))
        return printf("syntax error !\n"), NULL;
    expanded_tokens = to_expanded_tokens(tokens, env);
    ft_lstclear(&tokens, ft_free_token);
    final_tokens = join_and_clean_tokens(expanded_tokens);
    ft_lstclear(&expanded_tokens, ft_free_token);
    return final_tokens;
}