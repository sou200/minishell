/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmnd_builder.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fel-hazz <fel-hazz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/23 22:04:17 by serhouni          #+#    #+#             */
/*   Updated: 2023/08/13 07:53:12 by fel-hazz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_list	*generate_cmnds(t_list *tokens)
{
	t_list	*smpl_cmnds;

	smpl_cmnds = NULL;
	while (tokens != NULL)
	{
		if (((t_token *)tokens->content)->type == TYPE_PIPE)
			tokens = tokens->next;
		build_smpl_cmnd(&tokens, &smpl_cmnds);
	}
	return (smpl_cmnds);
}
