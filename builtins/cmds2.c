/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmds2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fel-hazz <fel-hazz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/05 01:35:13 by fel-hazz          #+#    #+#             */
/*   Updated: 2023/08/18 11:47:59 by fel-hazz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	**path(void)
{
	const char	*path;
	char		**paths;

	path = ft_getenv("PATH");
	if (!path)
		path = gl.default_env[1];
	if (!path || !*gl.default_env[1])
		return (0);
	paths = ft_split(path + 5, ':');
	if (!paths)
		ft_error(1, "malloc ");
	return (paths);
}

char	*cmd_path(char **paths, char *cmd, char *tmp, char *str)
{
	int		i;

	i = -1;
	if (!paths && cmd && cmd[0] == '/')
		return (cmd);
	if (!paths || !cmd || (ft_strchr(cmd, '/') && access(cmd, F_OK)))
		return (0);
	if ((ft_strchr(cmd, '/') && !access(cmd, F_OK)))
		return (cmd);
	while (paths[++i])
	{
		tmp = ft_strjoin(paths[i], "/");
		if (!tmp)
			return (0);
		str = ft_strjoin(tmp, cmd);
		free(tmp);
		tmp = 0;
		if (!str)
			return (0);
		if (!access(str, F_OK))
			return (str);
		free(str);
	}
	return (0);
}

void	initialise_var(t_var *p)
{
	p->i = -1;
	p->y = 0;
	p->infile = 0;
	p->outfile = 1;
	p->paths = 0;
	p->fd[0] = -1;
	p->fd[1] = -1;
	signal(SIGINT, SIG_IGN);
	rl_catch_signals = 1;
}

void	waitandreturn(t_var p)
{
	int	x;

	p.infile = (p.infile != 0 && close(p.infile));
	x = gl.return_value;
	gl.return_value = 0;
	waitpid(p.pid, &gl.return_value, 0);
	while (waitpid(-1, 0, 0) != -1)
		;
	signal(SIGINT, controlec);
	rl_catch_signals = 0;
	if (x == 400)
		return (gl.return_value = 1, free(0));
	if (WIFSIGNALED(gl.return_value))
	{
		if (WTERMSIG(gl.return_value) == 3)
			printf("Quit: 3\n");
		gl.return_value = WTERMSIG(gl.return_value) + 128;
	}
	else
		gl.return_value = WEXITSTATUS(gl.return_value);
}
