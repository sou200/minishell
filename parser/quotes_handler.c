/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes_handler.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: serhouni <serhouni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/13 15:53:19 by serhouni          #+#    #+#             */
/*   Updated: 2023/07/16 17:23:51 by serhouni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int in_qoete_handler(int *open_q, char **quote_content, t_list** new_token_lst, int q_case)
{
    if(*open_q == q_case)
    {
        ft_lstadd_back(new_token_lst, ft_lstnew(new_token(TYPE_WORD, *quote_content)));
        *quote_content = NULL;
        *open_q = 0;
    } else
        *open_q = q_case;
    return 0;
}

int is_valid_env(t_list* tokens, int open_q)
{
    t_token * token;

    if(tokens->next == NULL || open_q == 1)
        return 0;
    token = (t_token *)tokens->next->content;
    if(token->type == TYPE_WORD && (ft_isalpha(*token->value) || *token->value == '_'))
        return 1;
    return (token->type == TYPE_QUOTE || token->type == TYPE_D_QUOTE) && open_q == 0; 
}

t_list* remove_quotes(t_list* tokens, char **env)
{
    int open_q;
    t_list* new_token_lst;
    char *quote_content;

    open_q = 0;
    new_token_lst = NULL;
    quote_content = NULL;
    while (tokens != NULL)
    {
        if(((t_token *)tokens->content)->type == TYPE_QUOTE && open_q != 2)
            in_qoete_handler(&open_q, &quote_content, &new_token_lst, 1);
        else if(((t_token *)tokens->content)->type == TYPE_D_QUOTE && open_q != 1)
            in_qoete_handler(&open_q, &quote_content, &new_token_lst, 2);
        else if(((t_token *)tokens->content)->type == TYPE_DOLLAR && is_valid_env(tokens, open_q))
            expand_env(tokens, env);
        else if(open_q)
            quote_content = ft_strjoin(quote_content, ((t_token *)tokens->content)->value);
        else
            ft_lstadd_back(&new_token_lst, ft_lstnew(new_token(((t_token *)tokens->content)->type, ((t_token *)tokens->content)->value)));
        tokens = tokens->next;
    }
    return new_token_lst;
}