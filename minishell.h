/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: serhouni <serhouni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/09 23:31:05 by serhouni          #+#    #+#             */
/*   Updated: 2023/08/12 23:41:20 by serhouni         ###   ########.fr       */
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
    TYPE_P_WORD,
    TYPE_QUOTE,
    TYPE_D_QUOTE,
    TYPE_RD_R,
    TYPE_RD_L,
    TYPE_PIPE,
    TYPE_DOLLAR,
    TYPE_HERE_DOC,
    TYPE_HERE_DOC_NX,
    TYPE_APPEND,
    TYPE_STAR,
    TYPE_SPC
};

typedef struct s_global
{
    int exit_status;
    char	return_value;
    t_list	*garbage;
	char	error;
}t_global;

t_global	global;

typedef struct token_s
{
    enum token_type type;
    char *value;
} token_t;

typedef struct s_rd
{
    enum token_type type;
    char *value;
    int is_pseudo;
} t_rd;

typedef struct smpl_cmnd_s
{
   	char **cmnd;
	t_list *left_red;//void * = {< | << ; char *}
	t_list *right_red;//void * = {> | >> ; char *}
} smpl_cmnd_t;

t_list *lexer(char *line);
char	*space_type(char *line, int *i);
enum token_type	find_type2(char *line, int *i);
enum token_type	find_type(char *line, int *i);
token_t	*create_token(enum token_type type, void *content);
int	check_word(char c);
t_list* to_expanded_tokens(t_list* tokens, char **env);
int is_valid_syntax(t_list *token_lst);

void expand_env(t_list **tokens, char **env, int lex_flag);
int is_valid_env(t_list* tokens, int open_q);
t_list* parce_line(char *line, char **env);
int in_quote_handler(int *open_q, char **quote_content, t_list** new_token_lst, int q_case);
t_list *tokens_without_spc(t_list *token_lst);
t_list *token_lst_dup(token_t *token);
void ft_free_token(void *token);
char *ft_strjoin_free(char *a, char *b, int i, int j);
t_list *env_lexer(char *env);
int env_name_len(char *var);
int is_redirection(token_t *token);
t_list *generate_cmnds(t_list *tokens);
t_list *get_matched_files(char *pattern, int *flags);
int is_wildcard(t_list *tokens, int *is_lex);
void yes_it_is_wild(t_list **new_token_list, t_list **tokens, int is_lex);
char *get_pattern(t_list **tokens, int **p_flags);
void check_quote(int *q_type, enum token_type cas);
int	is_lexable(t_list *tokens, int open_q);
t_list	*wildcard_it(t_list *tokens);
void	costum_env_expand(t_list **tokens, char **env, int q_open);
void	f(t_list **new_token_lst, t_list *tokens);
t_list	*join_and_clean_tokens(t_list *tokens);
void	build_smpl_cmnd(t_list **tokens, t_list **smpl_cmnds);


// tmp
void print_tokens(t_list *head);

#endif