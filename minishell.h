/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fel-hazz <fel-hazz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/09 23:31:05 by serhouni          #+#    #+#             */
/*   Updated: 2023/07/19 16:56:52 by fel-hazz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
#define MINISHELL_H

#include <sys/stat.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <signal.h>
#include <sys/wait.h>
#include "./libft/libft.h"
#include <readline/readline.h>
#include <readline/history.h>
#include <errno.h>
#include <limits.h>
#include <string.h>

// char *env[ARG_MAX];
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
    TYPE_R_BR,
    TYPE_L_BR,
    TYPE_STAR,
    TYPE_SPC
};

typedef struct token_s
{
    enum token_type type;
    char *value;
} token_t;

typedef struct smpl_cmnd_s
{
    char **cmnd;
    int built_in;
} smpl_cmnd_t;

char **env;

const char *ft_getenv(const char *var);
char	**cd_path(char **env);
int		get_sizeslach(char *s);
char	*trim_backslash(char *s);
char	*cd_pathcheck(const char *dirname);
int abs_path (const char *dirname);
void	ft_cd(const char *dirname);

void	ft_pwd(void);
void	ft_echo(char **cmd);
t_list *lexer(char *line);
char	*space_type(char *line, int *i);
enum token_type	find_type2(char *line, int *i);
enum token_type	find_type(char *line, int *i);
token_t	*new_token(enum token_type type, void *content);
int	check_word(char c);
t_list* remove_quotes(t_list* tokens);
int is_valid_syntax(t_list *token_lst);

#endif