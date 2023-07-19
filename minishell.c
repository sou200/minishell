/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fel-hazz <fel-hazz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/09 23:19:53 by serhouni          #+#    #+#             */
/*   Updated: 2023/07/19 08:46:57 by fel-hazz         ###   ########.fr       */
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
    if(type == TYPE_STAR)
        return "*";
    if(type == TYPE_SPC)
        return "Space";
    return NULL;
}

void print_tokens(t_list *head)
{
    t_token *token;
    while(head != NULL)
    {
        token = head->content;
        if(token->type == 0 || token->type == 15)
            printf("word ={%s}\n", token->value);
        printf("token type = %s\n", get_type(token->type));
        printf("-----------------------\n");
        head = head->next;
    }
}

void lk(void)
{
	system("leaks minishell");
}

int main(int argc, char const *argv[], char **env)
{
	atexit(lk);
    char *line;
    
    t_list *head;
    line = readline("\033[0;32mminishell: $->\033[0;37m");
    while(line != NULL)
    {   
        head = lexer(line);
        if(!is_valid_syntax(head))
            printf("syntax error !\n");
        head = remove_quotes(head, env);
        if(head != NULL)
            print_tokens(head);
        add_history(line);
        line = readline("\033[0;32mminishell: $->\033[0;37m");
    }
    system("leaks minishell");
    return 0;
}
