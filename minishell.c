/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fel-hazz <fel-hazz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/09 23:19:53 by serhouni          #+#    #+#             */
/*   Updated: 2023/07/26 01:49:17 by fel-hazz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char *get_type(enum t_tokenype type)
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

// int cmnd_arg_count(t_list *tokens)
// {
//     int count;

//     count = 0;
//     while (tokens != NULL && ((t_token*)tokens->content)->type != TYPE_PIPE)
//     {
//         if(is_redirection((t_token*)tokens->content))
//             tokens = tokens->next;
//         else
//             count++;
//         tokens = tokens->next;
//     }
//     return count;
// }

void print_cmnds(t_list *cmnds)
{
    t_prototype *cmnd;
    t_list *left_red;
    t_list *right_red;
    int i;
    while (cmnds != NULL)
    {
        i = 0;
        cmnd = ((t_prototype*)cmnds->content);
        left_red = cmnd->left_red;
        right_red = cmnd->right_red;
        while(cmnd->cmnd[i] != NULL)
            printf("%s\n", cmnd->cmnd[i++]);
        printf("------------------------------\n");
        while (left_red != NULL)
        {
            printf("%s {%s}\n", get_type(((t_token *)left_red->content)->type), ((t_token *)left_red->content)->value);
            left_red = left_red->next;
        }
        printf("-------------------------------\n");
        while (right_red != NULL)
        {
            printf("%s {%s}\n", get_type(((t_token *)right_red->content)->type), ((t_token *)right_red->content)->value);
            right_red = right_red->next;
        }
        printf("================================\n");
        cmnds = cmnds->next;
    }
}
int main(int argc, char const *argv[], char **en)
{
    char *line;
    
    t_list *head;
	initialise_env((const char **)en);             
    while(1)
    {
        line = readline("\033[0;32mminishell: $->\033[0;37m ");
        if (!line)
            break;
        head = parce_line(line, env);
        // if(head != NULL)
        //     print_tokens(head);
        // print_cmnds(head);
		// printf("eee %s\n",((t_token *)(((t_prototype *)(head->content))->left_red->content))->value);
       if (head && head->content && !ft_strncmp(*(((t_prototype *)head->content)->cmnd), "env",4))
	   		ft_env();
	  if (head && head->content && !ft_strncmp(*(((t_prototype *)head->content)->cmnd), "getenv",7))
	   		ft_printenv((((t_prototype *)head->content)->cmnd)[1]);
	 else   if (head && head->content && !ft_strncmp(*(((t_prototype *)head->content)->cmnd), "unset",6))
	   		remove_var((((t_prototype *)head->content)->cmnd)[1]);
	 else   if (head && head->content && !ft_strncmp(*(((t_prototype *)head->content)->cmnd), "set",4))
	   		add_var((((t_prototype *)head->content)->cmnd)[1]);
	
	// else
		
		// ft_execute(head);'
		add_history(line);
	    ft_lstclear(&head, ft_free_token);
        free(line);
    }
    return 0;
}
// int main(int argc, char const *argv[], char **en)
// { 
//     t_list *head;
//     struct stat p;

// 	// env = en;
//     //     lstat("/tmp/ee",&p);
//     //     printf("%d \n",S_ISLNK(p.st_mode));
//     //     lstat("/tmp/ff",&p);
//     //     printf("%d \n",S_ISLNK(p.st_mode));
//     // // printf("%s\n",getcwd(0,0));
//     // // printf("%s\n",getenv("PWD"));
//     // ft_pwd();
// 	int i = 0;

// 	initialise_env((const char **)en);
// 	// while(en[i])
// 	// {
// 	// 	printf("%s\n",en[i]);
// 	// 	i++;
// 	// }
// 	// exit(0);
//    rl_line_buffer = readline("\033[0;32mminishell: $->\033[0;37m");
//     while( rl_line_buffer != NULL)
//     {  
//         head = lexer(rl_line_buffer);
//         if(head == NULL || !is_valid_syntax(head))
//             printf("syntax error !\n");
// 			// print_tokens(head);
//         // if (head && !ft_strncmp(((t_token *)head->content)->value, "pwd",4))
//         //    ft_pwd();
// 		// printf("%s %s\n",((t_token *)head->content)->value,((t_token *)head->next->content)->value);
//         // if (head && !ft_strncmp(((t_token *)head->content)->value, "cd",3))
// 		// { 
// 		// 	if ((t_token *)head->next)
//         //    		ft_cd(((t_token *)head->next->content)->value);
// 		// 	else
// 		// 		ft_cd(0);
// 		// }
// 		t_prototype a;
// 		a.cmnd = malloc(sizeof(char *) * 2);
// 		a.cmnd[0] = ((t_token *)head->content)->value;
// 		a.cmnd[1] = 0;
// 		a.left_red = 0;
// 		a.right_red = 0;
// 		a.next = 0;
// 		ft_execute(&a);
// 	//    if (head && !ft_strncmp(((t_token *)head->content)->value, "clear",6))
//     //     {
//     //         int i  = 0;
//     //         i = fork();
//     //         if (!i)
//     //             execve("/usr/bin/clear", 0 , en);
//     //         else
//     //             usleep(10000);
//     //     }
//     //    if (head && !ft_strncmp(((t_token *)head->content)->value, "env",4))
// 	//    		ft_env();
// 	//     if (head && !ft_strncmp(((t_token *)head->content)->value, "getenv",7))
// 	// 		if(head->next)
// 	//    		ft_printenv((char *)((t_token *)head->next->content)->value);
// 	//     if (head && !ft_strncmp(((t_token *)head->content)->value, "unset",6))
// 	// 		if(head->next)
// 	//    		remove_var((char *)((t_token *)head->next->content)->value);
// 	//     if (head && !ft_strncmp(((t_token *)head->content)->value, "set",4))
// 	// 		if(head->next)
// 	//    		add_var((char *)((t_token *)head->next->content)->value);
//         add_history(rl_line_buffer);
//         rl_line_buffer = readline("\033[0;32mminishell: $->\033[0;37m");
//     }
//     // system("leaks minishell");
//     return 0;
// }
