/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: serhouni <serhouni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/09 23:19:53 by serhouni          #+#    #+#             */
/*   Updated: 2023/08/08 17:08:43 by serhouni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char *get_type(enum token_type type)
{
    if (type == TYPE_WORD)
        return "word";
    if (type == TYPE_QUOTE)
        return "\'";
    if (type == TYPE_D_QUOTE)
        return "\"";
    if (type == TYPE_RD_R)
        return ">";
    if (type == TYPE_RD_L)
        return "<";
    if (type == TYPE_PIPE)
        return "|";
    if (type == TYPE_DOLLAR)
        return "$";
    if (type == TYPE_HERE_DOC)
        return "<<";
    if (type == TYPE_HERE_DOC_NX)
        return "<<<";
    if (type == TYPE_APPEND)
        return ">>";
    if (type == TYPE_STAR)
        return "*";
    if (type == TYPE_SPC)
        return "Space";
    return NULL;
}

void print_tokens(t_list *head)
{
    token_t *token;
    while (head != NULL)
    {
        token = head->content;
        if (token->type == TYPE_WORD || token->type == TYPE_P_WORD)
            printf("word ={%d:%s}\n", token->type, token->value);
        printf("token type = %s\n", get_type(token->type));
        printf("-----------------------\n");
        head = head->next;
    }
}

// int cmnd_arg_count(t_list *tokens)
// {
//     int count;

//     count = 0;
//     while (tokens != NULL && ((token_t*)tokens->content)->type != TYPE_PIPE)
//     {
//         if(is_redirection((token_t*)tokens->content))
//             tokens = tokens->next;
//         else
//             count++;
//         tokens = tokens->next;
//     }
//     return count;
// }

void print_cmnds(t_list *cmnds)
{
    smpl_cmnd_t *cmnd;
    t_list *left_red;
    t_list *right_red;
    int i;
    while (cmnds != NULL)
    {
        i = 0;
        cmnd = ((smpl_cmnd_t *)cmnds->content);
        left_red = cmnd->left_red;
        right_red = cmnd->right_red;
        while (cmnd->cmnd[i] != NULL)
            printf("%s\n", cmnd->cmnd[i++]);
        printf("------------------------------\n");
        while (left_red != NULL)
        {
            printf("%s {%s} p:%d\n", get_type(((t_rd *)left_red->content)->type), ((t_rd *)left_red->content)->value, ((t_rd *)left_red->content)->is_pseudo);
            left_red = left_red->next;
        }
        printf("-------------------------------\n");
        while (right_red != NULL)
        {
            printf("%s {%s} p:%d\n", get_type(((t_rd *)right_red->content)->type), ((t_rd *)right_red->content)->value, ((t_rd *)right_red->content)->is_pseudo);
            right_red = right_red->next;
        }
        printf("================================\n");
        cmnds = cmnds->next;
    }
}

int main(int argc, char const *argv[], char **env)
{
    char *line;

    t_list *head;
    global.exit_status = 0;
    while (1)
    {
        line = readline("\033[0;32mminishell: $->\033[0;37m ");
        if (!line)
            continue;
        add_history(line);
        head = parce_line(line, env);
        // if(head != NULL)
        //     print_tokens(head);
        free(line);
        print_cmnds(head);
        ft_lstclear(&head, ft_free_token);
    }
    // clear_history();
    // system("leaks minishell");
    return 0;
}
