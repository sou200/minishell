/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: serhouni <serhouni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/14 17:50:04 by serhouni          #+#    #+#             */
/*   Updated: 2023/07/16 17:23:51 by serhouni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int env_name_len(char *var)
{
    int i;

    i = 0;
    while(var[i] != '\0' && (ft_isalnum(var[i]) || var[i] == '_'))
        i++;
    return i;
}

char *get_env_var(char **env, char *var)
{
    int i;

    i = env_name_len(var);
    if(ft_strlen(*env) <= i)
        return NULL;
    while (*env != NULL)
    {
        if(ft_strlen(*env) > i && !ft_strncmp(*env, var, i) && (*env)[i] == '=')
            return ft_substr(*env, i + 1, ft_strlen(*env) - i);
        env++;
    }
    return NULL;
}

void expand_env(t_list *tokens, char **env)
{
    char *env_word = ((t_token *)tokens->next->content)->value;
    char *env_val = get_env_var(env, env_word);
    char *rest_word = ft_substr(env_word, env_name_len(env_word), ft_strlen(env_word) - env_name_len(env_word));
    char *result = ft_strjoin(env_val, rest_word);
    ((t_token *)tokens->next->content)->value = result;
}