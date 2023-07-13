/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes_handler.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: serhouni <serhouni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/13 15:53:19 by serhouni          #+#    #+#             */
/*   Updated: 2023/07/13 18:12:03 by serhouni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_list* remove_quotes(t_list* tokens)
{
    int open_q;
    t_list* new_tokens;
    char *quote_content;

    open_q = 0;
    new_tokens = NULL;
    quote_content = NULL;
    while (tokens != NULL)
    {
        if(((token_t *)tokens->content)->type == TYPE_QUOTE)
        {
            if(open_q == 1)
            {
                ft_lstadd_back(&new_tokens, ft_lstnew(new_token(TYPE_WORD, quote_content)));
                quote_content = NULL;
                open_q = 0;
            } else
                open_q = 1;
        }
        else if(((token_t *)tokens->content)->type == TYPE_D_QUOTE)
        {
            if(open_q == 2)
            {
                ft_lstadd_back(&new_tokens, ft_lstnew(new_token(TYPE_WORD, quote_content)));
                quote_content = NULL;
                open_q = 0;
            } else
                open_q = 2;
        }
        else if(open_q)
        {
            quote_content = ft_strjoin(quote_content, ((token_t *)tokens->content)->value);
        }
        else if(((token_t *)tokens->content)->type != TYPE_SPC)
        {
            ft_lstadd_back(&new_tokens, ft_lstnew(new_token(((token_t *)tokens->content)->type, ((token_t *)tokens->content)->value)));
        }
        tokens = tokens->next;
    }
    return new_tokens;
}