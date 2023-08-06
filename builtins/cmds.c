/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmds.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fel-hazz <fel-hazz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/22 16:07:23 by fel-hazz          #+#    #+#             */
/*   Updated: 2023/08/06 00:52:08 by fel-hazz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_builtins(t_prototype *cmd)
{
	if (!ft_strrcmp(cmd->cmnd[0], "echo"))
		ft_exit(ft_echo(cmd->cmnd + 1));
	else if (!ft_strrcmp(cmd->cmnd[0], "export"))
		ft_exit(ft_export(cmd->cmnd + 1));
	else if (!ft_strrcmp(cmd->cmnd[0], "env"))
		ft_exit(ft_env());
	else if (!ft_strrcmp(cmd->cmnd[0], "getenv"))
		ft_exit(ft_printenv(cmd->cmnd[1]));
	else if (!ft_strrcmp(cmd->cmnd[0], "pwd"))
		ft_exit(ft_pwd());
	else if (!ft_strrcmp(cmd->cmnd[0], "cd"))
		ft_exit(ft_cd(cmd->cmnd[1]));
	return (0);
}
// printf("eqwe\n");
// signal(SIGQUIT,SIG_DFL);
// signal(SIGINT,SIG_DFL);

void	print_error(int x, int d, ...)
{
	va_list	ap;
	int		i;

	i = 0;
	va_start(ap, d);
	while (i < d)
	{
		error_write(va_arg(ap, char *));
		i++;
	}
	va_end(ap);
	ft_exit(x);
}

void	failed_cmd(char *cmd, char *cmdd)
{
	struct stat	buf;

	if (ft_strchr(cmd, '/') && !cmdd || cmd[0] == '/' && access(cmd, F_OK))
		print_error(127, 3, "minishell: ", cmd, ": No such file or directory\n");
	else if (!cmdd)
		print_error(127, 3, "minishell: ", cmd, ": command not found\n");
	lstat(cmd, &buf);
	if (S_ISDIR(buf.st_mode))
		print_error(126, 3, "minishell: ", cmd, ": is a directory\n");
	if (access(cmdd, X_OK) || access(cmdd, R_OK))
		print_error(126, 3, "minishell: ", cmd, ": Permission denied\n");
}

int	simple_cmd(t_var *p, t_prototype *cmd, char *cmdd)
{
	p->pid = fork();
	if (!p->pid)
	{
		p->paths = path();
		if (!p->paths)
			ft_error(ENOMEM, "malloc: ");
		if (p->infile != p->fd[0])
			close(p->fd[0]);
		p->infile = redirect_input(cmd->left_red, p->infile);
		p->outfile = redirect_output(cmd->right_red, p->outfile);
		p->infile += (p->infile != 0 && close(p->infile) && 0);
		p->outfile += (p->outfile != 1 && close(p->outfile) && 0);
		if (!(cmd->cmnd)[0])
			return (free_table(p->paths), ft_exit(0), 0);
		ft_builtins(cmd);
		if (!*default_env[0] && !ft_getenv("PWD"))
			error_write(PWD_ENV);
		cmdd = cmd_path(p->paths, cmd->cmnd[0]);
		free_table(p->paths);
		failed_cmd(cmd->cmnd[0], cmdd);
		if (execve(cmdd, cmd->cmnd, env) == -1)
			return (free(cmdd), cmdd = 0, ft_exit(0), 0);
	}
	return (0);
}
// else
// {
// 	if(!ft_strncmp("./minishell",cmd->cmnd[0],12))
// 		signal(SIGINT,SIG_IGN);
// 	waitpid(p->pid1,&return_value, 0);
// 	signal(SIGINT,controlec);
// }

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
		simple_cmd(&p, (t_prototype *)(cmd->content), 0);
		cmd = cmd->next;
	}
	p.infile = (p.infile != 0 && close(p.infile));
	waitandreturn(p);
}
