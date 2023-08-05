/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmds2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fel-hazz <fel-hazz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/05 01:35:13 by fel-hazz          #+#    #+#             */
/*   Updated: 2023/08/05 02:40:09 by fel-hazz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	**path(void)
{
	const char	*path;
	char		**paths;

	path = ft_getenv("PATH");
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
	int	return_value;

	return_value = 0;
	waitpid(p.pid, &return_value, 0);
	while (waitpid(-1, 0, 0) != -1)
		;
	printf("%d\n", WEXITSTATUS(return_value));
}
