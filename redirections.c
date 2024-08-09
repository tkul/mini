/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tugcekul <tugcekul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/06 22:26:00 by tugcekul          #+#    #+#             */
/*   Updated: 2024/08/09 02:56:56 by tugcekul         ###   ########.fr       */
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
    new_str[j] = '\0';
    free(*str);
    *str = new_str;
}

// char *ft_split_join(char **arr)
// {
//     int i;
//     char *new_str;
//     int len;
//     int j;
//     int k;

//     i = -1;
//     len = 0;
//     k = 0;
//     while (arr[++i])
//         len += ft_strlen(arr[i]);
//     new_str = (char *)malloc(sizeof(char) * (len + 1));
//     if (!new_str)
//         return (NULL);
//     i = -1;
//     j = 0;
//     while (arr[++i])
//     {
//         while (arr[i][j])
//         {
//             new_str[k] = arr[i][j];
//             j++;
//             k++;
//         }
//         j = 0;
//     }
//     new_str[k] = '\0';
//     return (new_str);
// }

int ft_init_redirections(t_data *data)
{
    int i;
    int quote;

    i = -1;
    quote = -1;
    while ((data->cmd)[++i])
    {
        ft_set_quote_type(&quote, (data->cmd)[i]);
        if ((data->cmd)[i] == '<' && (data->cmd)[i + 1] == '<' && quote == -1)
        {
            add_by_index(&(data->cmd), ' ', i);
            add_by_index(&(data->cmd), ' ', i + 3);
            i += 3;
        }
        else if ((data->cmd)[i] == '<' && quote == -1)
        {
            add_by_index(&(data->cmd), ' ', i);
            add_by_index(&(data->cmd), ' ', i + 2);
            i += 2;
        }
        else if ((data->cmd)[i] == '>' && (data->cmd)[i + 1] == '>' && quote == -1)
        {
            add_by_index(&(data->cmd), ' ', i);
            add_by_index(&(data->cmd), ' ', i + 3);
            i += 3;
        }
        else if ((data->cmd)[i] == '>' && quote == -1)
        {
            add_by_index(&(data->cmd), ' ', i);
            add_by_index(&(data->cmd), ' ', i + 2);
            i += 2;
        }
    }
    return (0);
}

// int is_redirection(char *str)
// {
//     int i;

//     i = -1;
//     while (str[++i])
//     {
        
//     }
// }