/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: serhouni <serhouni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/09 23:31:05 by serhouni          #+#    #+#             */
/*   Updated: 2023/07/19 01:04:36 by serhouni         ###   ########.fr       */
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

t_list *lexer(char *line);
char	*space_type(char *line, int *i);
enum token_type	find_type2(char *line, int *i);
enum token_type	find_type(char *line, int *i);
token_t	*new_token(enum token_type type, void *content);
int	check_word(char c);
t_list* to_expanded_tokens(t_list* tokens, char **env);
int is_valid_syntax(t_list *token_lst);

void expand_env(t_list **tokens, char **env);
int is_valid_env(t_list* tokens, int open_q);
t_list* parce_line(char *line, char **env);
int in_quote_handler(int *open_q, char **quote_content, t_list** new_token_lst, int q_case);


// tmp
void print_tokens(t_list *head);

#endif