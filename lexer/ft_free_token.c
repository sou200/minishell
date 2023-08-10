/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_token.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fel-hazz <fel-hazz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/21 00:40:28 by serhouni          #+#    #+#             */
/*   Updated: 2023/08/09 12:02:22 by fel-hazz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void ft_free_token(void *content)
{
    token_t *token;
    token = (token_t *)content;
    if(token != NULL)
        free(token->value);
    free(token);
}
void ft_free_protoype(void *content)
{
    t_prototype *token;

	token = (t_prototype *)content;
	if(token)
	{
		ft_lstclear(&token->left_red,ft_free_token);
		free(token->left_red);
		ft_lstclear(&token->right_red,ft_free_token);
		free(token->right_red);
		free_table(token->cmnd);
	}
    free(token);
}