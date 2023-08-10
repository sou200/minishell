/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: serhouni <serhouni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/10 16:30:57 by serhouni          #+#    #+#             */
/*   Updated: 2023/08/10 16:31:20 by serhouni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	is_redirection(token_t *token)
{
	return (token->type == TYPE_HERE_DOC || token->type == TYPE_APPEND
		|| token->type == TYPE_RD_L || token->type == TYPE_RD_R
		|| token->type == TYPE_HERE_DOC_NX);
}