/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: serhouni <serhouni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/23 01:24:45 by serhouni          #+#    #+#             */
/*   Updated: 2023/08/02 01:19:40 by serhouni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_list *token_lst_dup(token_t *token)
{
    t_list *dup;
    token_t *new_token;

    new_token = create_token(token->type, ft_strdup(token->value));
    dup = ft_lstnew(new_token);
    return dup;
}

t_list *tokens_without_spc(t_list *token_lst)
{
    t_list* new_token_lst;

    new_token_lst = NULL;
    while (token_lst != NULL)
    {
        if(((token_t *)token_lst->content)->type != TYPE_SPC)
            ft_lstadd_back(&new_token_lst, token_lst_dup((token_t *)token_lst->content));
        token_lst = token_lst->next;
    }
    return new_token_lst;
}