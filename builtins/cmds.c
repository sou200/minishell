/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmds.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fel-hazz <fel-hazz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/22 16:07:23 by fel-hazz          #+#    #+#             */
/*   Updated: 2023/07/26 01:43:18 by fel-hazz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../minishell.h"



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

int	ft_strrcmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n && (s1[i] != '\0' || s2[i] != '\0'))
	{
		if (s1[i] != s2[i] && s1[i] && s2[i] != '\n')
			return ((unsigned char)s1[i] - (unsigned char)s2[i]);
		i++;
	}
	return (0);
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
	str = get_next_line(0);//read;ome
	while (str && ft_strrcmp(stop, str, ft_strlen(stop) + 1))
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

int redirect_input(t_list *left_red, int pipe)
{
	t_token *holder;
	int	fd;

	fd = pipe;
	while(left_red)
	{
		holder = (t_token *)left_red->content;
		if (holder->type ==  TYPE_RD_L)
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

void	ft_dup2(int x, int y)
{
	if (dup2(x, y) == -1)
		ft_error(1, "dup2 ");
}

int redirect_output(t_list *right_red, int pipe)
{
	t_token *holder;
	int	fd;

	fd = pipe;
	while(right_red)
	{
		holder = (t_token *)right_red->content;
		if (holder->type ==  TYPE_RD_R)
		fd = open(holder->value, O_WRONLY | O_TRUNC | O_CREAT, 0666);
		else
		fd = open(holder->value, O_WRONLY | O_APPEND | O_CREAT, 0666);
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
	char *cmdd;

	p->pid1= fork();
	if (!p->pid1)
	{
		p->infile = redirect_input(cmd->left_red,p->infile);
		p->outfile = redirect_output(cmd->right_red,p->outfile);
		if (p->infile != 0)
			ft_dup2(p->infile, 0);
		if (p->outfile != 1)
			ft_dup2(p->outfile, 1);
		if (p->infile != 0)
			close(p->infile);
		if (p->outfile != 1)
			close(p->outfile);
	cmdd = cmd_path(p->paths, cmd->cmnd[0]);
	if (!cmdd || access(cmdd, X_OK))
		return (ft_error(1, "command not found "));
	if (execve(cmdd, cmd->cmnd, env) == -1)
		return (free(cmdd), cmdd = 0, ft_error(1, "execve "));
	}
	else
		waitpid(p->pid1,&return_value, 0);
}
void ft_execute(t_list *cmd)
{
	t_var	p;

	p.i = -1;
	p.infile = 0;
	p.outfile = 1;
	p.paths = path();
	int i = 0;
	// while (p.paths[i])
	// 	printf("%s\n",p.paths[i++]);
	if (cmd && !cmd->next)
		simple_cmd(&p,(t_prototype *)(cmd->content));
	else if (cmd && cmd->next)
	{
		while (cmd  && ++p.i >= 0)
		{
			if (p.i != 0)
			{
				if (p.i > 2)
					close(p.infile);
				p.infile = p.fd[0];
				close(p.fd[1]);
			}
			if (cmd->next)
			{
				if (pipe(p.fd) == -1)
					ft_error(1, "pipe ");
				p.outfile = p.fd[1];
			}
			else
			{
				close(p.outfile);
				p.outfile = 1;
			}
			simple_cmd(&p,(t_prototype *)(cmd->content));
			p.i++;
			cmd = cmd->next;
		}
		close(p.infile);
		while (waitpid(-1,0,0) != -1)
			;
	}
	// if (cmd && !cmd->next)
	// 	simple_cmd(&p,(t_prototype *)(cmd->content));
	// else
	// 	piped_cmd(&p,(t_prototype *)(cmd->content));
}