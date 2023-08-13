/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmnd_builder.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: serhouni <serhouni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/23 22:04:17 by serhouni          #+#    #+#             */
/*   Updated: 2023/08/12 23:43:19 by serhouni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_list	*generate_cmnds(t_list *tokens)
{
	t_list	*smpl_cmnds;

	smpl_cmnds = NULL;
	while (tokens != NULL)
	{
		if (((token_t *)tokens->content)->type == TYPE_PIPE)
			tokens = tokens->next;
		build_smpl_cmnd(&tokens, &smpl_cmnds);
	}
	return (smpl_cmnds);
}
