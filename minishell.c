/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: serhouni <serhouni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/09 23:19:53 by serhouni          #+#    #+#             */
/*   Updated: 2023/06/11 00:30:29 by serhouni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char *get_type(enum token_type type)
{
    if(type == TYPE_WORD)
        return "word";
    if(type == TYPE_QUOTE)
        return "\'";
    if(type == TYPE_D_QUOTE)
        return "\"";
    if(type == TYPE_RD_R)
        return ">";
    if(type == TYPE_RD_L)
        return "<";
    if(type == TYPE_PIPE)
        return "|";
    if(type == TYPE_DOLLAR)
        return "$";
    if(type == TYPE_HERE_DOC)
        return "<<";
    if(type == TYPE_APPEND)
        return ">>";
    if(type == TYPE_R_BR)
        return ")";
    if(type == TYPE_L_BR)
        return "(";
    if(type == TYPE_OR)
        return "||";
    if(type == TYPE_AND)
        return "&&";
    if(type == TYPE_STAR)
        return "*";
    if(type == TYPE_S_AND)
        return "&&";
    if(type == TYPE_SPC)
        return "Space";
    return NULL;
}

void print_tokens(t_list *head)
{
    token_t *token;
    while(head != NULL)
    {
        token = head->content;
        if(token->type == 0 || token->type == 15)
            printf("word =\"%s\"\n", token->value);
        printf("token type = %s\n", get_type(token->type));
        printf("-----------------------\n");
        head = head->next;
    }
}

int main(int argc, char const *argv[])
{
    char *line = (void *)1;
    
    t_list *head;
    while(line != NULL)
    {   
        line = readline("minishell:");
        head = lexer(line);
        print_tokens(head);
        
        add_history(line);
        free(line);
    }
    system("leaks minishell");
    return 0;
}
