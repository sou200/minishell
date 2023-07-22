/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmds.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fel-hazz <fel-hazz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/22 16:07:23 by fel-hazz          #+#    #+#             */
/*   Updated: 2023/07/22 18:42:38 by fel-hazz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../minishell.h"
#include"get_next_line_bonus.h"
typedef struct s_var
{
	int		fd[2];
	int		pid1;
	int		pid2;
	char	**paths;
	int		infile;
	int		outfile;
	int		i;
}	t_var;

int return_value;
void	ft_error(int erno, const char *msg)
{
	if (errno == 0)
		errno = erno;
	perror(msg);
	exit(errno);
}

char	**path(void)
{
	const char	*path;
	char	**paths;

	path=ft_getenv("PATH");
	if (!path)
		ft_error(1, "PATH environment not found ");
	paths = ft_split(path, ':');
	if (!paths)
		ft_error(1, "malloc ");
	return (paths);
}
#include<fcntl.h>
void	ft_close(int n, ...)
{
	va_list	t;
	int		i;

	i = 0;
	va_start(t, n);
	while (i < n)
	{
		if (close(va_arg(t, int)) == -1)
			ft_error(1, "close ");
		i++;
	}
	va_end(t);
}

char	*generate_name(void)
{
	int		i;
	char	*str;

	i = 987654321;
	str = ft_itoa(i);
	if (!str)
		ft_error(1, "malloc ");
	while (access(str, F_OK) == 0 && i > 0)
	{
		free(str);
		i++;
		str = ft_itoa(i);
		if (!str)
			ft_error(1, "malloc ");
	}
	if (i < 0 || access(str, F_OK) == 0)
		return (free(str), NULL);
	return (str);
}
void	ft_open(char *str, int *fd, int flag)
{
	if (flag == -1)
		*fd = open(str, O_RDWR | O_TRUNC | O_CREAT, 0666);
	else if (flag == -2)
		*fd = open(str, O_RDWR | O_APPEND | O_CREAT, 0666);
	else
		*fd = open(str, O_RDONLY);
	if (*fd == -1)
		ft_error(1, "open ");
}

int	ft_input(char *stop)
{
	int		fd;
	char	*str;
	int		tmp;

	str = generate_name();
	if (!str)
		ft_error(1, "here_doc ");
	ft_open(str, &fd, -1);
	ft_open(str, &tmp, -1);
	unlink(str);
	free(str);
	write(1, "> ", 2);
	str = get_next_line(0);
	while (str && ft_strncmp(stop, str, ft_strlen(stop) + 1))
	{
		write(fd, str, ft_strlen(str));
		write(1, "> ", 2);
		free(str);
		str = get_next_line(0);
	}
	free(str);
	str = NULL;
	ft_close(1, fd);
	return (tmp);
}

int redirect_input(t_list *left_red)
{
	t_token *holder;
	int	fd;

	fd = 0;
	while(left_red)
	{
		holder = (t_token *)left_red->content;
		if (holder->type =  TYPE_RD_L)
		fd = open(holder->value, O_RDONLY);
		else
		fd = ft_input(holder->value);
		if (fd == -1)
			printf("erroor\n");
		if (left_red->next)
			close(fd);
		left_red = left_red->next;
	}
	return(fd);
}
// void	ft_open(char *str, int *fd, int flag)
// {
// 	if (flag == -1)
// 		*fd = open(str, O_RDWR | O_TRUNC | O_CREAT, 0666);
// 	else if (flag == -2)
// 		*fd = open(str, O_RDWR | O_APPEND | O_CREAT, 0666);
// 	else
// 		*fd = open(str, O_RDONLY);
// 	if (*fd == -1)
// 		ft_error(1, "open ");
// }
int redirect_output(t_list *right_red)
{
	t_token *holder;
	int	fd;

	fd = 1;
	while(right_red)
	{
		holder = (t_token *)right_red->content;
		if (holder->type =  TYPE_RD_R)
		fd = open(holder->value, O_WRONLY | O_TRUNC | O_CREAT, 0666);
		else
		fd = fd = open(holder->value, O_WRONLY | O_APPEND | O_CREAT, 0666);
		if (fd == -1)
			printf("erroor\n");
		if (right_red->next)
			close(fd);
		right_red = right_red->next;
	}
	return(fd);
}
char	*cmd_path(char **paths, char *cmd)
{
	char	*tmp;
	char	*str;
	int		i;

	i = 0;
	if (!access(cmd, X_OK) || cmd[0] == '/')
		return (cmd);
	while (paths[i])
	{
		tmp = ft_strjoin(paths[i], "/");
		if (!tmp)
			return (0);
		str = ft_strjoin(tmp, cmd);
		free(tmp);
		tmp = 0;
		if (!str)
			return (0);
		if (!access(str, X_OK))
			return (str);
		free(str);
		i++;
	}
	return (0);
}

void simple_cmd(t_var *p, t_prototype *cmd)
{
	p->pid1= fork();
	if (!p->pid1)
	{
		p->infile = redirect_input(cmd->left_red);
		p->outfile = redirect_output(cmd->right_red);
		ft_dup2(p->infile, 0);//dup in same file
		ft_dup2(p->outfile, 0);
		if (p->infile != 0)
			close(p->infile);
		if (p->outfile != 1)
			close(p->outfile);
	cmd = cmd_path(p->paths, cmd->cmnd[0]);
	if (!cmd || access(cmd, X_OK))
		return (ft_error(1, "command not found "));
	if (execve(cmd, cmd->cmnd, env) == -1)
		return (free(cmd), cmd = 0, ft_error(1, "execve "));
	}
	else
		waitpid(p->pid1,&return_value, 0);
}
void ft_execute(t_prototype *cmd)
{
	t_var	p;

	p.i = 0;
	p.infile = -1337;
	p.paths = path();
	if (cmd && !cmd->next)
		simple_cmd();
	while (cmd)
	{
		
	}
}