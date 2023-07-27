/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fel-hazz <fel-hazz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/09 23:19:53 by serhouni          #+#    #+#             */
/*   Updated: 2023/07/27 18:23:01 by fel-hazz         ###   ########.fr       */
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
void controlec(int c)
{
	(void ) c;
	write(1,"\n",1);
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();

}

void lk()
{
	system("leaks a.out");
}

int main(int argc, char const *argv[], char **en)
{
    t_list *head;
	char *line;
	line = NULL;
	if (argc > 2 || argv[1])
		{
			printf("wa bzaf azbi\n");
			ft_exit(0);
		}
	initialise_env((const char **)en);
	rl_catch_signals = 0;
	signal(SIGINT,controlec);
	signal(SIGQUIT,SIG_IGN);
    while(1)
    {
        line = readline("minishell$ ");
        if (!line)
		{
			printf("\x1b[Fminishell$  exit\n");
			ft_exit(0);//return value attention dyal akhir command
		}
		head = parce_line(line, env);
		if (!ft_strrcmp((((t_prototype *)head->content)->cmnd)[0],"exit") && !head->next)
		{
			printf("exit\n");
			ft_exit(0);
		}
		ft_execute(head);
		add_history(line);
	    ft_lstclear(&head, ft_free_protoype);
        free(line);
    }
	ft_exit(0);
    return 0;
}