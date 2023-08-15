/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fel-hazz <fel-hazz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/09 23:19:53 by serhouni          #+#    #+#             */
/*   Updated: 2023/08/15 17:15:15 by fel-hazz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_type(enum t_tokentype type)
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
	if (type == TYPE_HERE_DOC_NX)
		return ("<<<");
	if (type == TYPE_APPEND)
		return (">>");
	if (type == TYPE_STAR)
		return ("*");
	if (type == TYPE_SPC)
		return ("Space");
	return (NULL);
}

void	print_tokens(t_list *head)
{
	t_token	*token;

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

void	controlec(int c)
{
	(void ) c;
	write(1, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
	gl.return_value = 1;
}


void	initialise_default(void)
{
	char	*pwd;

	gl.default_env = malloc(sizeof(char *) * 5);
	if (!gl.default_env)
		ft_exit(ENOMEM);
	pwd = getcwd(0, 0);
	if (!pwd)
	{
		error_write(MINISHELL_INIT);
		gl.default_env[0] = ft_strdup("");
	}
	else
		gl.default_env[0] = pwd;
	gl.default_env[1] = ft_strdup(DEFAULT_PATH);
	gl.default_env[2] = ft_strdup("");
	gl.default_env[3] = ft_strdup("");
	gl.default_env[4] = 0;
}

int	main(int argc, char const *argv[], char **en)
{
	t_list	*head;
	char	*line;

	init (argc, argv, en);
	while (1)
	{
		line = readline("minishell$ ");
		if (!line)
			return (controlec1(1),
				printf("\x1b[Fminishell$ exit\n"), ft_exit(gl.return_value));
		if (line)
			head = parce_line(line, gl.env);
		if (head && ft_sortir(head))
			ft_execute(head, (t_var){{0, 0}, 0, 0, 0, 0, 0, 0});
		add_history(line);
		ft_lstclear(&head, ft_free_protoype);
		free(line);
	}
	return (ft_exit(0));
}
