/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tugcekul <tugcekul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/01 16:51:11 by tugcekul          #+#    #+#             */
/*   Updated: 2024/08/03 20:29:28 by tugcekul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int count_word(const char *str, char c)
{
    int i;
    int count;
    int quote;
    int toggle;

    i = -1;
    count = 0;
    quote = -1;
    toggle = 0;
    while(str[++i])
    {
        if (quote == -1 && (str[i] == '\'' || str[i] == '\"'))
			quote = str[i];
		else if (quote == str[i])
			quote = -1;
        if (quote == -1 && str[i] == c)
            count++;
        else
            toggle = 1;
        while (str[i] == c)
            i++;
    }
    if (toggle)
        count++;
    return (count);
}

// char **ft_split_by_quote(const char *str, char c)
// {
//     char **cmds;
//     int i;
//     int j;
//     int k;
//     int quote;
//     int len;
    
//     i = -1;
//     j = 0;
//     k = 0;
//     quote = -1;
//     len = count_word(str, c);
//     cmds = (char **)malloc(sizeof(char *) * (len + 2));
//     if (!cmds)
//         return (NULL);
//     while (str[++i])
//     {
//         if (quote == -1 && (str[i] == '\'' || str[i] == '\"'))
//             quote = str[i];
//         else if (quote == str[i])
//             quote = -1;
//         if (quote == -1 && str[i] == c)
//         {
//             cmds[j] = (char *)malloc(sizeof(char) * (i - k + 1));
//             if (!cmds[j])
//                 return (NULL);
//             ft_strlcpy(cmds[j], str + k, i - k + 1);
//             cmds[j++][i - k] = '\0';
//             k = i + 1;
//         }
//     }
//     cmds[j] = (char *)malloc(sizeof(char) * (i - k + 1));
//     if (!cmds[j])
//         return (NULL);
//     ft_strlcpy(cmds[j], str + k, i - k + 1);
//     cmds[j + 1] = NULL;
//     return (cmds);
// }



char **ft_split_by_quote(const char *str, char c)
{
   t_split *s;
   int i;
   int j;
   int k;
    
    i = -1;
    j = 0;
    k = 0;
    s = malloc(sizeof(t_split));
    if (!s)
        return (NULL);
    s->quote = -1;
    s->len = count_word(str, c);
    s->cmds = (char **)malloc(sizeof(char *) * (s->len + 2));
    if (!s->cmds)
        return (NULL);
    while (str[++i])
    {
        if (s->quote == -1 && (str[i] == '\'' || str[i] == '\"'))
            s->quote = str[i];
        else if (s->quote == str[i])
            s->quote = -1;
        if (s->quote == -1 && str[i] == c)
        {
            while (k < i && str[k] == ' ')
                k++;
            s->cmds[j] = (char *)malloc(sizeof(char) * (i - k + 1));
            if (!s->cmds[j])
                return (NULL);
            ft_strlcpy(s->cmds[j], str + k, i - k + 1);
            s->cmds[j++][i - k] = '\0';
            while (str[i + 1] == ' ')
                i++;
            k = i + 1;
        }
    }
    while (k < i && str[k] == ' ')
        k++;
    s->cmds[j] = (char *)malloc(sizeof(char) * (i - k + 1));
    if (!s->cmds[j])
        return (NULL);
    ft_strlcpy(s->cmds[j], str + k, i - k + 1);
    s->cmds[j + 1] = NULL;
    return (s->cmds);
}

int ft_lexer(t_data *data)
{
    t_lexer *lexer;
    char **cmds;
    char **new;
    int i;
    
    i = -1;
    lexer = malloc(sizeof(t_lexer));
    if (!lexer)
        return (-1);
    lexer->pipe_count = ft_count_pipes(data->cmd);
    if (lexer->pipe_count == -1)
        return (free(lexer), -1);
    cmds = ft_split_by_quote(data->cmd, '|');
    if (!cmds)
        return (free(lexer), -1);
    while (cmds[++i])
    {
        new = ft_split_by_quote(cmds[i], ' ');
        if (!new)
            return (free(lexer), -1);
        for (int j = 0; new[j]; j++)
            printf("%s\n", new[j]);
    }
    return (0); 
}