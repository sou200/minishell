/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmds.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fel-hazz <fel-hazz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/22 16:07:23 by fel-hazz          #+#    #+#             */
/*   Updated: 2023/08/19 21:52:14 by fel-hazz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_builtins(t_prototype *cmd)
{
	if (!ft_strrcmp(cmd->cmnd[0], "echo"))
		ft_exit(ft_echo(cmd->cmnd + 1));
	else if (!ft_strrcmp(cmd->cmnd[0], "export"))
		ft_exit(ft_export(cmd->cmnd + 1));
	else if (!ft_strrcmp(cmd->cmnd[0], "unset"))
		ft_exit(ft_export(cmd->cmnd + 1));
	else if (!ft_strrcmp(cmd->cmnd[0], "env"))
		ft_exit(ft_env());
	else if (!ft_strrcmp(cmd->cmnd[0], "getenv"))
		ft_exit(ft_printenv(cmd->cmnd[1]));
	else if (!ft_strrcmp(cmd->cmnd[0], "pwd"))
		ft_exit(ft_pwd());
	else if (!ft_strrcmp(cmd->cmnd[0], "cd"))
		ft_exit(ft_cd(cmd->cmnd[1]));
	else if (!ft_strrcmp(cmd->cmnd[0], "exit"))
		ft_exit(ft_exit1(cmd->cmnd + 1));
	return (0);
}

void	print_error(int x, int d, ...)
{
	va_list	ap;
	int		i;
	char	*str;
	char	*tmp;

	i = 0;
	tmp = 0;
	va_start(ap, d);
	while (i < d)
	{
		str = ft_strjoin(tmp, va_arg(ap, char *));
		free(tmp);
		tmp = str;
		i++;
	}
	write(2, str, ft_strlen(str));
	free(str);
	va_end(ap);
	ft_exit(x);
}

void	failed_cmd(char *cmd, char *cmdd, char **path)
{
	struct stat	buf;

	if (!cmdd && access(cmd, F_OK) && (!path || ft_strchr(cmd, '/')))
		print_error(127, 3, "minishell: ", cmd, ": No such file or directory\n");
	if ((!cmdd && access(cmd, F_OK)) || !ft_strrcmp("..", cmd)
		|| (!cmdd && !ft_strchr(cmd, '/')) || !cmd[0])
		print_error(127, 3, "minishell: ", cmd, ": command not found\n");
	lstat(cmd, &buf);
	if (S_ISDIR(buf.st_mode))
		print_error(126, 3, "minishell: ", cmd, ": is a directory\n");
	if (access(cmdd, F_OK))
		print_error(127, 3, "minishell: ", cmd, ": No such file or directory\n");
	if (access(cmdd, X_OK) || access(cmdd, R_OK))
		print_error(126, 3, "minishell: ", cmd, ": Permission denied\n");
}

void	simple_cmd(t_var *p, t_prototype *cmd, char *cmdd)
{
	p->pid = fork();
	if (!p->pid)
	{
		p->paths = path();
		if (p->infile != p->fd[0])
			close(p->fd[0]);
		signal(SIGINT, SIG_DFL);
		redirection(cmd, &p->infile, &p->outfile, 0);
		if (p->infile != 0)
			dup2(p->infile, 0);
		signal(SIGQUIT, SIG_DFL);
		p->infile += (p->infile != 0 && close(p->infile) && 0);
		p->outfile += (p->outfile != 1 && close(p->outfile) && 0);
		if (!(cmd->cmnd)[0])
			return (free_table(p->paths), ft_exit(0), free(0));
		ft_builtins(cmd);
		if (!*gl.default_env[0] && !ft_getenv("PWD"))
			error_write(PWD_ENV);
		cmdd = cmd_path(p->paths, cmd->cmnd[0], 0, 0);
		failed_cmd(cmd->cmnd[0], cmdd, p->paths);
		free_table(p->paths);
		if (execve(cmdd, cmd->cmnd, gl.env) == -1)
			return (free(cmdd), cmdd = 0, ft_exit(0), free(0));
	}
}

void	ft_execute(t_list *cmd, t_var p)
{
	initialise_var(&p);
	while (cmd && ++p.i >= 0)
	{
		if (p.i != 0)
		{
			if (p.i >= 2)
				close(p.infile);
			p.infile = p.fd[0];
			close(p.fd[1]);
		}
		if (cmd->next)
		{
			if (pipe(p.fd) == -1)
				ft_error(errno, "pipe: ");
			p.outfile = p.fd[1];
		}
		else
			p.outfile = (p.outfile != 1 && close(p.outfile) && 0) + 1;
		heredocsigs(cmd, &p, 0, 0);
		if (gl.return_value == 400)
			break ;
		simple_cmd(&p, (t_prototype *)(cmd->content), 0);
		cmd = cmd->next;
	}
	waitandreturn(p);
}
