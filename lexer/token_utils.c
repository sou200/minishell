/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fel-hazz <fel-hazz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/23 01:24:45 by serhouni          #+#    #+#             */
/*   Updated: 2023/07/25 20:50:49 by fel-hazz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_list *token_lst_dup(t_token *token)
{
    t_list *dup;
    t_token *new_token;

    new_token = create_token(token->type, ft_strdup(token->value));
    dup = ft_lstnew(new_token);
    return dup;
}

t_list *tokens_without_spc(t_list *token_lst)
{
    int open_q;
    t_list* new_token_lst;

    open_q = 0;
    new_token_lst = NULL;
    while (token_lst != NULL)
    {
        if(((t_token *)token_lst->content)->type != TYPE_SPC)
            ft_lstadd_back(&new_token_lst, token_lst_dup((t_token *)token_lst->content));
        token_lst = token_lst->next;
    }
    return new_token_lst;
}