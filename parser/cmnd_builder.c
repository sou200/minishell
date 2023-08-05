/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmnd_builder.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fel-hazz <fel-hazz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/23 22:04:17 by serhouni          #+#    #+#             */
/*   Updated: 2023/08/05 06:46:21 by fel-hazz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int cmnd_arg_count(t_list *tokens)
{
    int count;

    count = 0;
    while (tokens != NULL && ((t_token*)tokens->content)->type != TYPE_PIPE)
    {
        if(is_redirection((t_token*)tokens->content))
            tokens = tokens->next;
        else
            count++;
        tokens = tokens->next;
    }
    return count;
}

void add_smpl_cmnd(t_list **cmnd_lst, char **cmnds, t_list *left_red , t_list *right_red)
{
        t_prototype* smpl_cmnd;

        smpl_cmnd = malloc(sizeof(t_prototype));
        smpl_cmnd->cmnd = cmnds;
        smpl_cmnd->left_red = left_red;
        smpl_cmnd->right_red = right_red;
        ft_lstadd_back(cmnd_lst, ft_lstnew(smpl_cmnd));
}

void build_smpl_cmnd(t_list **tokens, t_list** smpl_cmnds)
{
    t_list *left_red;
    t_list *right_red;
    t_token *token;
    char **cmnds;
    int cmd_index;

    cmnds = malloc((cmnd_arg_count(*tokens) + 1)*sizeof(char *));
    cmd_index = 0;
    left_red = NULL;
    right_red = NULL;
    while (*tokens != NULL && ((t_token*)(*tokens)->content)->type != TYPE_PIPE)
    {
        token = (t_token*)(*tokens)->content;
        if(is_redirection(token))
        {
            if(token->type == TYPE_RD_L || token->type == TYPE_HERE_DOC)
                ft_lstadd_back(&left_red, ft_lstnew(create_token(token->type, ft_strdup(((t_token*)(*tokens)->next->content)->value))));
            else
                ft_lstadd_back(&right_red, ft_lstnew(create_token(token->type, ft_strdup(((t_token*)(*tokens)->next->content)->value))));
            *tokens = (*tokens)->next;
        }
        else
            cmnds[cmd_index++] = ft_strdup(token->value);
        *tokens = (*tokens)->next;
    }
    cmnds[cmd_index] = NULL;
    add_smpl_cmnd(smpl_cmnds, cmnds, left_red, right_red);
}

t_list *generate_cmnds(t_list *tokens)
{
    t_list *smpl_cmnds;

    smpl_cmnds = NULL;
    while(tokens != NULL)
    {
        if(((t_token*)tokens->content)->type == TYPE_PIPE)
            tokens = tokens->next;
        build_smpl_cmnd(&tokens, &smpl_cmnds);
    }
    return smpl_cmnds;
}