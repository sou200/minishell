/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes_handler.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: serhouni <serhouni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/13 15:53:19 by serhouni          #+#    #+#             */
/*   Updated: 2023/07/14 17:15:54 by serhouni         ###   ########.fr       */
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

t_list* remove_quotes(t_list* tokens)
{
    int open_q;
    t_list* new_token_lst;
    char *quote_content;

    open_q = 0;
    new_token_lst = NULL;
    quote_content = NULL;
    while (tokens != NULL)
    {
        if(((token_t *)tokens->content)->type == TYPE_QUOTE && open_q != 2)
            in_qoete_handler(&open_q, &quote_content, &new_token_lst, 1);
        else if(((token_t *)tokens->content)->type == TYPE_D_QUOTE && open_q != 1)
            in_qoete_handler(&open_q, &quote_content, &new_token_lst, 2);
        else if(open_q)
            quote_content = ft_strjoin(quote_content, ((token_t *)tokens->content)->value);
        else
            ft_lstadd_back(&new_token_lst, ft_lstnew(new_token(((token_t *)tokens->content)->type, ((token_t *)tokens->content)->value)));
        tokens = tokens->next;
    }
    return new_token_lst;
}