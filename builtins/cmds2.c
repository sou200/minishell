/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmds2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fel-hazz <fel-hazz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/05 01:35:13 by fel-hazz          #+#    #+#             */
/*   Updated: 2023/08/05 17:19:01 by fel-hazz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	**path(void)
{
	const char	*path;
	char		**paths;

	path = ft_getenv("PATH");
	if (!path)
		path = default_env[1];
	if (!path)
		return (0);
	paths = ft_split(path + 5, ':');
	if (!paths)
		ft_error(1, "malloc ");
	return (paths);
}

char	*cmd_path(char **paths, char *cmd)
{
	char	*tmp;
	char	*str;
	int		i;

	i = 0;
	if (!access(cmd, F_OK) || cmd[0] == '/')
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
		if (!access(str, F_OK))
			return (str);
		free(str);
		i++;
	}
	return (0);
}

void	initialise_var(t_var *p)
{
	p->i = -1;
	p->infile = 0;
	p->outfile = 1;
	p->paths = 0;
	p->fd[0] = -1;
	p->fd[1] = -1;
}

void	waitandreturn(t_var p)
{
	waitpid(p.pid, &return_value, 0);
	while (waitpid(-1, 0, 0) != -1)
		;
	if (WIFSIGNALED(return_value))
	{
		return_value = WTERMSIG(return_value) + 128;
		printf("%d\n", return_value);
	}
	else
		printf("%d\n", WEXITSTATUS(return_value));
}
