/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes_handler.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fel-hazz <fel-hazz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/13 15:53:19 by serhouni          #+#    #+#             */
/*   Updated: 2023/07/25 20:39:34 by fel-hazz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int in_quote_handler(int *open_q, char **quote_content, t_list** new_token_lst, int q_case)
{
    if(*open_q == q_case)
    {
        if(*quote_content == NULL)
            *quote_content = ft_strdup("");
        ft_lstadd_back(new_token_lst, ft_lstnew(create_token(TYPE_WORD, *quote_content)));
        *quote_content = NULL;
        *open_q = 0;
    } else
        *open_q = q_case;
    return 0;
}