/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fel-hazz <fel-hazz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/09 23:31:05 by serhouni          #+#    #+#             */
/*   Updated: 2023/07/19 08:32:27 by fel-hazz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
#define MINISHELL_H

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include "./libft/libft.h"
#include <readline/readline.h>
#include <readline/history.h>
#include <stdarg.h>
#include <string.h>
#include <errno.h>

enum token_type
{
    TYPE_WORD,
    TYPE_QUOTE,
    TYPE_D_QUOTE,
    TYPE_RD_R,
    TYPE_RD_L,
    TYPE_PIPE,
    TYPE_DOLLAR,
    TYPE_HERE_DOC,
    TYPE_APPEND,
    TYPE_STAR,
    TYPE_SPC
};

typedef struct s_global
{
    char	return_value;
    t_list	*garbage;
	char	error;
}t_global;

t_global	global;

typedef struct s_token
{
    enum token_type type;
    char *value;
}t_token;

// typedef struct smpl_cmnd_s
// {
//     char **cmnd;
//     int built_in;
// } smpl_cmnd_t;

t_list	*ft_lstnew1(void *content);
char	*ft_substr1(char const *s, unsigned int start, size_t len);
void	ft_free(int number, ...);
void	ft_exit(int	error);
void recycle(int n, ...);
t_list *lexer(char *line);
char	*space_type(char *line, int *i);
enum token_type	find_type2(char *line, int *i);
enum token_type	find_type(char *line, int *i);
t_token	*new_token(enum token_type type, void *content);
int	check_word(char c);
t_list* remove_quotes(t_list* tokens, char **env);
int is_valid_syntax(t_list *token_lst);

void expand_env(t_list *tokens, char **env);

#endif