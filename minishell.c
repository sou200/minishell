/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fel-hazz <fel-hazz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/09 23:19:53 by serhouni          #+#    #+#             */
/*   Updated: 2023/07/22 13:36:33 by fel-hazz         ###   ########.fr       */
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
        // printf("%s\n",token);
        // if(token->type == 0 || token->type == 15)
            printf("word ={%s}\n", token->value);
        printf("token type = %s\n", get_type(token->type));
        printf("-----------------------\n");
        head = head->next;
    }
}

// void sigint_handler(int sig)
// {
//     int pid = fork();
//     char *p[3];

//         if (!pid)
//             execve("/usr/bin/clear",0,0);
//     // system("clear");
//     // write(1, "\n", 1);
//     // rl_on_new_line();
//     // rl_replace_line("", 0);
//     // rl_redisplay();
//     // // printf("SIGINT\n");
// }


int main(int argc, char const *argv[], char **en)
{ 
    t_list *head;
    struct stat p;

	// env = en;
    //     lstat("/tmp/ee",&p);
    //     printf("%d \n",S_ISLNK(p.st_mode));
    //     lstat("/tmp/ff",&p);
    //     printf("%d \n",S_ISLNK(p.st_mode));
    // // printf("%s\n",getcwd(0,0));
    // // printf("%s\n",getenv("PWD"));
    // ft_pwd();
	int i = 0;

	initialise_env((const char **)en);
	// while(en[i])
	// {
	// 	printf("%s\n",en[i]);
	// 	i++;
	// }
	// exit(0);
   rl_line_buffer = readline("\033[0;32mminishell: $->\033[0;37m");
    while( rl_line_buffer != NULL)
    {  
        head = lexer(rl_line_buffer);
        if(head == NULL || !is_valid_syntax(head))
            printf("syntax error !\n");
        head = remove_quotes(head, en);
			print_tokens(head);
        // if (head && !ft_strncmp(((t_token *)head->content)->value, "pwd",4))
        //    ft_pwd();
		// printf("%s %s\n",((t_token *)head->content)->value,((t_token *)head->next->content)->value);
        // if (head && !ft_strncmp(((t_token *)head->content)->value, "cd",3))
		// { 
		// 	if ((t_token *)head->next)
        //    		ft_cd(((t_token *)head->next->content)->value);
		// 	else
		// 		ft_cd(0);
		// }
       if (head && !ft_strncmp(((t_token *)head->content)->value, "clear",6))
        {
            int i  = 0;
            i = fork();
            if (!i)
                execve("/usr/bin/clear", 0 , en);
            else
                usleep(10000);
        }
       if (head && !ft_strncmp(((t_token *)head->content)->value, "env",4))
	   		ft_env();
	    if (head && !ft_strncmp(((t_token *)head->content)->value, "getenv",7))
			if(head->next)
	   		ft_printenv((char *)((t_token *)head->next->content)->value);
	    if (head && !ft_strncmp(((t_token *)head->content)->value, "unset",6))
			if(head->next)
	   		remove_var((char *)((t_token *)head->next->content)->value);
	    if (head && !ft_strncmp(((t_token *)head->content)->value, "set",4))
			if(head->next)
	   		add_var((char *)((t_token *)head->next->content)->value);
        add_history(rl_line_buffer);
        rl_line_buffer = readline("\033[0;32mminishell: $->\033[0;37m");
    }
    // system("leaks minishell");
    return 0;
}
