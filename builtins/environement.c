/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environement.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fel-hazz <fel-hazz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/05 17:00:38 by fel-hazz          #+#    #+#             */
/*   Updated: 2023/08/19 20:41:36 by fel-hazz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	initialise_env3(int i, char *s, char *tmp)
{
	char	*two[2];

	two[0] = "SHLVL=1";
	two[1] = 0;
	s = (char *)ft_getenv("SHLVL");
	if (s)
	{
		s += 6;
		if (is_num(s))
		{
			i = (ft_atoi(s) + 1) % 1000;
			if (i != 0)
				s = ft_itoa(i);
			else
				s = 0;
			tmp = ft_strjoin("SHLVL=", s);
			return (free(s), two[0] = tmp, two[1] = 0
				, ft_export(two), free (tmp));
		}
		else
			ft_export(two);
	}
	else
		ft_export(two);
}

void	initialise_env2(void)
{
	char	*tmp;
	char	*two[2];

	initialise_env3(0, 0, 0);
	remove_var("OLDPWD");
	if (*gl.default_env[0])
	{
		tmp = ft_strjoin("PWD=", gl.default_env[0]);
		two[0] = tmp;
		two[1] = 0;
		ft_export(two);
		free(tmp);
	}
}

void	initialise_env(const char **en)
{
	int	x;
	int	y;

	x = 0;
	y = 0;
	if (!en)
		return ;
	while (en[y])
		y++;
	gl.env = malloc((y + 1) * sizeof(char *));
	if (!gl.env)
		ft_error(ENOMEM, "malloc: ");
	y = -1;
	while (en[++y])
	{
		gl.env[y] = ft_strdup(en[y]);
		if (!gl.env[y])
			ft_error(ENOMEM, "malloc: ");
	}
	gl.env[y] = 0;
	initialise_export();
	initialise_env2();
}

void	initialise_export(void)
{
	int		x;
	int		y;
	t_list	*t;

	x = 0;
	y = 0;
	while (gl.env[y])
	{
		t = ft_lstnew(ft_exportage(gl.env[y]));
		if (!t)
			ft_error(ENOMEM, "malloc: ");
		ft_lstaddandsort(&gl.export_list, t);
		y++;
	}
	if (!ft_getenv("OLDPWD"))
	{
		t = ft_lstnew(ft_exportage1("OLDPWD"));
		if (!t)
			ft_error(ENOMEM, "malloc: ");
		ft_lstaddandsort(&gl.export_list, t);
	}
}
