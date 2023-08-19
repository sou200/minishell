/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fel-hazz <fel-hazz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/09 23:31:05 by serhouni          #+#    #+#             */
/*   Updated: 2023/08/19 15:45:19 by fel-hazz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
#define MINISHELL_H

#include <sys/stat.h>
#include <sys/types.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <signal.h>
#include <sys/wait.h>
#include "./libft/libft.h"
#include <readline/readline.h>
#include<fcntl.h>
#include <readline/history.h>
#include <errno.h>
#include <limits.h>
#include <string.h>
#include <stdarg.h>
// char *env[ARG_MAX];
# define MINISHELL_INIT "minishell-init: error retrieving current directory: getcwd: cannot access parent directories: "
# define PWD_ENV "job-working-directory: error retrieving current directory: getcwd: cannot access parent directories: No such file or directory\n"
# define PWD_ERROR "pwd: error retrieving current directory: getcwd: cannot access parent directories: "
# define CD_ERROR "cd: error retrieving current directory: getcwd: cannot access parent directories: "
# define DEFAULT_PATH "PATH=/usr/gnu/bin:/usr/local/bin:/bin:/usr/bin:."

enum e_tokentype
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
//look in default too!!
typedef struct s_var
{
	int		fd[2];
	int		pid;
	char	**paths;
	int		infile;
	int		outfile;
	int		i;
	int		y;
}	t_var;

// typedef struct s_global
// {
//     char	return_value;
//     t_list	*garbage;
// 	char	error;
// }t_global;

// t_global	global;

typedef struct s_token
{
    enum e_tokentype type;
    char *value;
	int is_pseudo;
} t_token;

typedef struct s_helper
{
	int		i;
	int		env_n_l;
	char	*env_val;
	char	*result;
	char	*before;
	char	*after;
}	t_helper;

typedef struct s_prototype
{
   	char **cmnd;
	t_list *left_red;//void * = {< | << ; char *}
	t_list *right_red;//void * = {> | >> ; char *}
	t_list *redire;
} t_prototype;

typedef struct s_global
{
	char **env;
	t_list *export_list;
	int	return_value;
	char **default_env;
}t_global ;

t_global gl;
	// char **env;
	// t_list *export_list;
	// int	return_value;

void	big_error(char *s);
void	controlec2(int c);
void	holder(int c);
void	holder1(int c);
void	redirection(t_prototype *cmd, int *infile
	, int *outfile, t_token *holder);
void	holder(int c);
void	heredocsigs(t_list *cmd, t_var *p, int save, t_list	*j);
const char	*ft_getenv1(const char *var);
void	ft_cd_1(char *str);
// void	controlec1(int c);
const char	*ft_getenv3(const char *var);
int	ft_exit1(char **cmd);
int	ft_atoi1(const char *str);
int	ft_cd_succes(char *dirname, char *str);
void	print_error1(int d, ...);
const char	*ft_getenv2(const char *var);
int	valid_unset(const char *var);
void	remove_var1(const char *var);
void	remove_export(const char *var);
int		ft_unset(char **cmd);
void	initialise_env3(int i, char *s, char *tmp);
void	initialise_env2(void);
int	is_num(char *s);
int	env_append_find(char *var);
void	empty_var(char *var);
void	*ft_malloc(size_t size);
void	error_malloc(int condition);
void	initialise_default(void);
void	error_write(const char *s);
void	env_append(char *str, char *var);
char	*join_export(char *old, char *var);
void	init(int argc, char const *argv[], char **en);
int		ft_sortir(t_list *head);
void	print_error(int x, int d, ...);
void	failed_cmd(char *cmd, char *cmdd, char **path);
void error_write(const char *s);
void	initialise_var(t_var *p);
void waitandreturn(t_var p);
char *ft_exportage3(char *s);
char *ft_exportage(char *s);
char *ft_exportage1(char *s);
void	initialise_export(void);
void	print_export(void);
t_list	*export_exists(char *value);
void replace_value(char *var, t_list *tmp);
int which_export(char *var);
void add_value(char *var);
int ft_export(char **args);
void env_append(char *str, char *var);
void	ft_open(char *str, int *fd, int flag);
void	ft_lstaddandsort(t_list **lst, t_list *new);
int	ft_strcmp(const char *s1, const char *s2);
int  ft_builtins(t_prototype *cmd);
int	check_n(char *s);
int	ft_strrcmp(const char *s1, const char *s2);
void	ft_error(int erno, const char *msg);
char	**path(void);
char	*generate_name(void);
int	ft_input(char *stop, enum e_tokentype type, int fd, int tmp);
int redirect_input(t_list *left_red, int pipe);
int redirect_output(t_list *right_red, int pipe);
char	*cmd_path(char **paths, char *cmd, char *tmp, char *str);
void	simple_cmd(t_var *p, t_prototype *cmd, char *cmdd);
void	ft_execute(t_list *cmd, t_var p);

int add_var1(const char *var);
int	check_var1(const char *var);
int	ft_pathcmp(const char *s1, const char *PATH);
int	check_var(const char *var);
void add_var(const char *var);
void	initialise_export(void);
void remove_var(const char *var);
char *ft_exportage1(char *s);
char *ft_exportage(char *s);
// t_env env;
int ft_env(void);
int	size_double(char **str);
void	initialise_env(const char **en);
char	**realloc_env(int n);
void free_table(char **str);
// char	*ft_strdup1(const char *s);
// char	*ft_strdupenv(const char *s);
void ft_free_protoype(void *content);
const char *ft_getenv(const char *var);
char * expand_heredoc_line(char *line);
char	**cd_path(char **env);
int		get_sizeslach(char *s);
char	*trim_backslash(char *s);
char	*cd_pathcheck(const char *dirname);
int abs_path (const char *dirname);
int	ft_cd(const char *dirname);
void controlec(int c);
int ft_printenv(const char *var);
int is_valid_to_expand(char *s, int i);
int	ft_pwd(void);
int		ft_echo(char **cmd);
// t_list	*ft_lstnew1(void *content);
// char	*ft_substr1(char const *s, unsigned int start, size_t len);
void	ft_free(int number, ...);
int		ft_exit(int	error);
// void recycle(int n, ...);
t_list *lexer(char *line);
char	*space_type(char *line, int *i);
enum e_tokentype	find_type2(char *line, int *i);
enum e_tokentype	find_type(char *line, int *i);
t_token	*create_token(enum e_tokentype type, void *content);
int	check_word(char c);
t_list* to_expanded_tokens(t_list* tokens, char **env);
int is_valid_syntax(t_list *token_lst);

void	expand_env(t_list **tokens,t_list **new_tokens, char **env, int lex_flag);
int is_valid_env(t_list* tokens, int open_q);
t_list* parce_line(char *line, char **env);
int in_quote_handler(int *open_q, char **quote_content, t_list** new_token_lst, int q_case);
t_list *tokens_without_spc(t_list *token_lst);
t_list *token_lst_dup(t_token *token);
void ft_free_token(void *token);
char *ft_strjoin_free(char *a, char *b, int i, int j);
t_list *env_lexer(char *env);
int env_name_len(char *var);
int is_redirection(t_token *token);
t_list *generate_cmnds(t_list *tokens);
t_list *get_matched_files(char *pattern, int *flags);
int is_wildcard(t_list *tokens, int *is_lex);
void yes_it_is_wild(t_list **new_token_list, t_list **tokens, int is_lex);
char *get_pattern(t_list **tokens, int **p_flags);
void check_quote(int *q_type, enum e_tokentype  cas);
int	is_lexable(t_list *tokens, int open_q);
t_list	*wildcard_it(t_list *tokens);
void	costum_env_expand(t_list **tokens, t_list **new_tokens, char **env, int q_open);
void	f(t_list **new_token_lst, t_list *tokens);
t_list	*join_and_clean_tokens(t_list *tokens);
void	build_smpl_cmnd(t_list **tokens, t_list **smpl_cmnds);

char	*get_env_var(char **env, char *var);
// tmp
void print_tokens(t_list *head);

#endif