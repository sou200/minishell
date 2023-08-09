/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcards.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: serhouni <serhouni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/27 19:04:42 by serhouni          #+#    #+#             */
/*   Updated: 2023/08/08 18:00:43 by serhouni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include <dirent.h>

int pattern_match(char *pattern, char *text, int i, int *flags)
{
    if (pattern[i] == '\0' && *text == '\0')
        return 1;
    if (pattern[i] == '\0')
        return 0;
    if (pattern[i] == '*' && flags[i]) {
        while (pattern[i + 1] == '*' && flags[i + 1])
            i++;
        return pattern_match(pattern, text, i + 1, flags) || (*text != '\0' && pattern_match(pattern, text + 1, i, flags));
    } else if (pattern[i] == *text && !flags[i])
        return pattern_match(pattern, text + 1, i + 1, flags);
    return 0;
}

int get_pattern_len(t_list *tokens)
{
    int len;

    len = 0;
    while (tokens != NULL && ((token_t *)tokens->content)->type != TYPE_SPC)
    {
        len += !((token_t *)tokens->content)->value?0:ft_strlen(((token_t *)tokens->content)->value);
        tokens = tokens->next;
    }
    return len;
}

char *get_pattern(t_list **tokens, int **p_flags)
{
    int *flags;
    int i;
    char *pattern;

    flags = ft_calloc(get_pattern_len(*tokens), sizeof(int));
    i = 0;
    pattern = NULL;
    while ((*tokens) != NULL && ((token_t *)(*tokens)->content)->type != TYPE_SPC)
    {
        if (((token_t *)(*tokens)->content)->type == TYPE_STAR)
            flags[i] = 1;
        pattern = ft_strjoin_free(pattern, ((token_t *)(*tokens)->content)->value, 1, 0);
        i += !((token_t *)(*tokens)->content)->value?0:ft_strlen(((token_t *)(*tokens)->content)->value);
        (*tokens) = (*tokens)->next;
    }
    *p_flags = flags;
    return pattern;
}

// void listFilesAndDirectories(const char *path) {
//     struct dirent *entry;
//     struct stat fileStat;
//     DIR *dir = opendir(path);

//     if (dir == NULL) {
//         perror("Unable to open directory");
//         return;
//     }

//     while ((entry = readdir(dir)) != NULL) {
//         char fullpath[PATH_MAX];
//         snprintf(fullpath, PATH_MAX, "%s/%s", path, entry->d_name);
//         printf("%s\n", fullpath);
//         if (lstat(fullpath, &fileStat) == -1) {
//             perror("lstat");
//             continue;
//         }

//         if (S_ISDIR(fileStat.st_mode)) {
//             printf("[Directory] %s\n", entry->d_name);
//         } else if (S_ISREG(fileStat.st_mode)) {
//             printf("[File] %s\n", entry->d_name);
//         }
//     }

//     closedir(dir);
// }

void add_file_to_lst(t_list **lst, char *name, int is_space)
{
    token_t *word;
    token_t *spc;

    word = create_token(TYPE_WORD, ft_strdup(name));
    ft_lstadd_back(lst, ft_lstnew(word));
    if(is_space)
    {
        spc = create_token(TYPE_SPC, ft_strdup(" "));
        ft_lstadd_back(lst, ft_lstnew(spc));
    }
}

t_list *get_matched_files(char *pattern, int *flags)
{
    struct dirent *entry;
    struct dirent *next_entry;
    DIR *dir = opendir(".");
    t_list *matched_files;

    matched_files = NULL;
    entry = readdir(dir);
    while (entry != NULL)
    {
        next_entry = readdir(dir);
        if(entry->d_name[0] != '.' && pattern_match(pattern, entry->d_name, 0, flags))
            add_file_to_lst(&matched_files, entry->d_name, next_entry != NULL);
        entry = next_entry;
    }
    closedir(dir);
    return matched_files;
}