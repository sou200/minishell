/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcards.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: serhouni <serhouni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/27 19:04:42 by serhouni          #+#    #+#             */
/*   Updated: 2023/08/19 22:01:42 by serhouni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include <dirent.h>

int	pattern_match(char *pattern, char *text, int i, int *flags)
{
	if (pattern[i] == '\0' && *text == '\0')
		return (1);
	if (pattern[i] == '\0')
		return (0);
	if (pattern[i] == '*' && flags[i])
	{
		while (pattern[i + 1] == '*' && flags[i + 1])
			i++;
		return (pattern_match(pattern, text, i + 1, flags) || (*text != '\0'
				&& pattern_match(pattern, text + 1, i, flags)));
	}
	else if (pattern[i] == *text && !flags[i])
		return (pattern_match(pattern, text + 1, i + 1, flags));
	return (0);
}

int	get_pattern_len(t_list *tokens)
{
	int	len;

	len = 0;
	while (tokens != NULL && ((t_token *)tokens->content)->type != TYPE_SPC)
	{
		len += ft_strlen(((t_token *)tokens->content)->value);
		tokens = tokens->next;
	}
	return (len);
}

char	*get_pattern(t_list **tokens, int **p_flags)
{
	int		*flags;
	int		i;
	char	*pattern;

	flags = ft_calloc(get_pattern_len(*tokens), sizeof(int));
	i = 0;
	pattern = NULL;
	while ((*tokens) != NULL
		&& ((t_token *)(*tokens)->content)->type != TYPE_SPC)
	{
		if (((t_token *)(*tokens)->content)->type == TYPE_STAR)
			flags[i] = 1;
		pattern = ft_strjoin_free(pattern,
				((t_token *)(*tokens)->content)->value, 1, 0);
		i += ft_strlen(((t_token *)(*tokens)->content)->value);
		(*tokens) = (*tokens)->next;
	}
	*p_flags = flags;
	return (pattern);
}

void	add_file_to_lst(t_list **lst, char *name, int is_space)
{
	t_token	*word;
	t_token	*spc;

	word = create_token(TYPE_WORD, ft_strdup(name));
	ft_lstadd_back(lst, ft_lstnew(word));
	if (is_space)
	{
		spc = create_token(TYPE_SPC, ft_strdup(" "));
		ft_lstadd_back(lst, ft_lstnew(spc));
	}
}

t_list	*get_matched_files(char *pattern, int *flags)
{
	struct dirent	*entry;
	struct dirent	*next_entry;
	DIR				*dir;
	t_list			*matched_files;

	matched_files = NULL;
	dir = opendir(".");
	entry = readdir(dir);
	while (entry != NULL)
	{
		next_entry = readdir(dir);
		if (pattern_match(pattern, entry->d_name, 0, flags)
			&& !((*pattern == '.') ^ (*entry->d_name == '.')))
			add_file_to_lst(&matched_files, entry->d_name, next_entry != NULL);
		entry = next_entry;
	}
	closedir(dir);
	return (matched_files);
}
