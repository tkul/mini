/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tugcekul <tugcekul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/06 22:26:00 by tugcekul          #+#    #+#             */
/*   Updated: 2024/08/07 04:25:31 by tugcekul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void add_by_index(char **str, char c, int start)
{
    char *new_str;
    int i;
    int j;

    i = 0;
    j = 0;
    new_str = (char *)malloc(sizeof(char) * (ft_strlen(*str) + 2));
    if (!new_str)
        return ;
    while ((*str)[i])
    {
        if (i == start)
        {
            new_str[j] = c;
            j++;
        }
        new_str[j] = (*str)[i];
        i++;
        j++;
    }
    new_str[j] = c;
    new_str[j + 1] = '\0';
    free(*str);
    *str = new_str;
}
static int control_error(char **str, int quote, int i)
{
    ft_set_quote_type(&quote, (*str)[i]);
    if ((*str)[i] == '>' && (*str)[i + 1] == '>' && (*str)[i + 2] == '>' && quote == -1)
    {
        printf("Error: syntax error near unexpected token `>>>'\n");
        return (-1);
    }
    if ((*str)[i] == '<' && (*str)[i + 1] == '<' && (*str)[i + 2] == '<' && quote == -1)
    {
        printf("Error: syntax error near unexpected token `<<<'\n");
        return (-1);
    }
    if ((*str)[i] == '>' && (*str)[i + 1] == '>' && (*str)[i + 2] == '\0' && quote == -1)
    {
        printf("Error: syntax error near unexpected token `newline'\n");
        return (-1);
    }
    if ((*str)[i] == '<' && (*str)[i + 1] == '<' && (*str)[i + 2] == '\0' && quote == -1)
    {
        printf("Error: syntax error near unexpected token `newline'\n");
        return (-1);
    }
    if ((*str)[i] == '>' && (*str)[i + 1] == '\0' && quote == -1)
    {
        printf("Error: syntax error near unexpected token `newline'\n");
        return (-1);
    }
    if ((*str)[i] == '<' && (*str)[i + 1] == '\0' && quote == -1)
    {
        printf("Error: syntax error near unexpected token `newline'\n");
        return (-1);
    }
    return (0);
}

int ft_init_redirections(char *str)
{
    int i;
    int quote;

    i = -1;
    quote = -1;
    while (str[++i])
    {
        if (control_error(&str, quote, i) == -1)
            return (-1);
        ft_set_quote_type(&quote, str[i]);
        if (str[i] == '<' && str[i + 1] == '<' && quote == -1)
        {
            add_by_index(&str, ' ', i);
            add_by_index(&str, ' ', i + 3);
            i += 3;
        }
        if (str[i] == '<' && quote == -1)
        {
            add_by_index(&str, ' ', i);
            add_by_index(&str, ' ', i + 2);
            i += 2;
        }
        if (str[i] == '>' && str[i + 1] == '>' && quote == -1)
        {
            add_by_index(&str, ' ', i);
            add_by_index(&str, ' ', i + 3);
            i += 3;
        }
        if (str[i] == '>' && quote == -1)
        {
            add_by_index(&str, ' ', i);
            add_by_index(&str, ' ', i + 2);
            i += 2;
        }
    }
    return (0);
}
