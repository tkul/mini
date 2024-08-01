/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tugcekul <tugcekul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/01 16:51:11 by tugcekul          #+#    #+#             */
/*   Updated: 2024/08/01 23:19:06 by tugcekul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int count_word(char *str, char c)
{
    int i;
    int count;
    int quote;
    
    i = -1;
    count = 0;
    quote = -1;
    while(str[++i])
    {
        if (quote == -1 && (str[i] == '\'' || str[i] == '\"'))
			quote = str[i];
		else if (quote == str[i])
			quote = -1;
        if (quote == -1 && str[i] == c)
            count++;
        while (str[i] == c)
            i++;
    }
    return (count);
}

char **ft_split_by_quote(char *str, char c)
{
    char **cmds;
    int i;
    int j;
    int k;
    int quote;
    int len;
    
    i = -1;
    j = 0;
    k = 0;
    quote = -1;
    len = count_word(str, c);
    cmds = (char **)malloc(sizeof(char *) * (len + 2));
    if (!cmds)
        return (NULL);
    while (str[++i])
    {
        if (quote == -1 && (str[i] == '\'' || str[i] == '\"'))
            quote = str[i];
        else if (quote == str[i])
            quote = -1;
        if (quote == -1 && str[i] == c)
        {
            cmds[j] = (char *)malloc(sizeof(char) * (i - k + 1));
            if (!cmds[j])
                return (NULL);
            ft_strlcpy(cmds[j], str + k, i - k + 1);
            k = i + 1;
            j++;
        }
    }
    cmds[j] = (char *)malloc(sizeof(char) * (i - k + 1));
    if (!cmds[j])
        return (NULL);
    ft_strlcpy(cmds[j], str + k, i - k + 1);
    cmds[j + 1] = NULL;
    return (cmds);
}

int ft_lexer(t_data *data)
{
    t_lexer *lexer;
    char **cmds;

    lexer = malloc(sizeof(t_lexer));
    if (!lexer)
        return (-1);
    lexer->pipe_count = ft_count_pipes(data->cmd);
    if (lexer->pipe_count == -1)
        return (free(lexer), -1);
    printf("%d\n", count_word(data->cmd, '|'));
    cmds = ft_split_by_quote(data->cmd, '|');
    if (!cmds)
        return (free(lexer), -1);
    cmds = ft_split_by_quote(data->cmd, ' ');
    if (!cmds)
        return (free(lexer), -1);
    
    return (0);
    
    
    
    
}