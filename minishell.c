/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fel-hazz <fel-hazz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/09 23:19:53 by serhouni          #+#    #+#             */
/*   Updated: 2023/08/06 06:23:15 by fel-hazz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_type(enum t_tokenype type)
{
	if (type == TYPE_WORD)
		return ("word");
	if (type == TYPE_QUOTE)
		return ("\'");
	if (type == TYPE_D_QUOTE)
		return ("\"");
	if (type == TYPE_RD_R)
		return (">");
	if (type == TYPE_RD_L)
		return ("<");
	if (type == TYPE_PIPE)
		return ("|");
	if (type == TYPE_DOLLAR)
		return ("$");
	if (type == TYPE_HERE_DOC)
		return ("<<");
	if (type == TYPE_APPEND)
		return (">>");
	if (type == TYPE_STAR)
		return ("*");
	if (type == TYPE_SPC)
		return ("Space");
	return (NULL);
}

// void	print_tokens(t_list *head)
// {
//     t_token *token;
//     while(head != NULL)
//     {
//         token = head->content;
//         // printf("%s\n",token);
//         // if(token->type == 0 || token->type == 15)
//             printf("word ={%s}\n", token->value);
//         printf("token type = %s\n", get_type(token->type));
//         printf("-----------------------\n");
//         head = head->next;
//     }
// }

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

// void print_cmnds(t_list *cmnds)
// {
//     t_prototype *cmnd;
//     t_list *left_red;
//     t_list *right_red;
//     int i;
//     while (cmnds != NULL)
//     {
//         i = 0;
//         cmnd = ((t_prototype*)cmnds->content);
//         left_red = cmnd->left_red;
//         right_red = cmnd->right_red;
//         while(cmnd->cmnd[i] != NULL)
//             printf("%s\n", cmnd->cmnd[i++]);
//         printf("------------------------------\n");
//         while (left_red != NULL)
//         {
//             printf("%s {%s}\n", get_type(((t_token *)left_red->content)->type), ((t_token *)left_red->content)->value);
//             left_red = left_red->next;
//         }
//         printf("-------------------------------\n");
//         while (right_red != NULL)
//         {
//             printf("%s {%s}\n",get_type(((t_token *)right_red->content)->type), ((t_token *)right_red->content)->value);
//             right_red = right_red->next;
//         }
//         printf("================================\n");
//         cmnds = cmnds->next;
//     }
// }
void	controlec(int c)
{
	(void ) c;
	write(1, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
	return_value = 1;
}

// void lk()
// {
// 	system("leaks a.out");
// }

void	initialise_default(void)
{
	char	*pwd;

	default_env = malloc(sizeof(char *) * 3);
	if (!default_env)
		ft_exit(ENOMEM);
	pwd = getcwd(0, 0);
	if (!pwd)
	{
		error_write(MINISHELL_INIT);
		default_env[0] = ft_strdup("");
	}
	else
		default_env[0] = pwd;
	default_env[1] = ft_strdup(DEFAULT_PATH);
	default_env[2] = 0;
}
//find a way to launch builtins in parent
//to handle signals better sleep doesnt stop

int	main(int argc, char const *argv[], char **en)
{
	t_list	*head;
	char	*line;

	init (argc, argv, en);
	while (1)
	{
		line = readline("minishell$ ");
		if (!line)
			return (printf("\x1b[Fminishell$  exit\n"), ft_exit(1));
		if (line)
			head = parce_line(line, env);
		if (head && ft_sortir(head))
			ft_execute(head, (t_var){0, 0, 0, 0, 0, 0});
		add_history(line);
		ft_lstclear(&head, ft_free_protoype);
		free(line);
	}
	return (ft_exit(0));
}
