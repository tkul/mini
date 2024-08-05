/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tugcekul <tugcekul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/05 00:13:08 by tugcekul          #+#    #+#             */
/*   Updated: 2024/08/05 18:06:22 by tugcekul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char *remove_by_index(char *str, int start, int end)
{
    char *new_str;
    int i;
    int j;

    i = 0;
    j = 0;
    new_str = malloc(sizeof(char) * (ft_strlen(str) - end + 1));
    while (str[i])
    {
        if (i < start || i > start + end)
        {
            new_str[j] = str[i];
            j++;
        }
        i++;
    }
    new_str[j] = '\0';
    return (new_str);
}

// int handle_dollar(t_data *data, char *str)
// {
//     int i;
//     int j;
//     int quote;

//     i = -1;
//     quote = -1;
//     while (str[++i])
//     {
//         if (quote == -1 && (str[i] == '\'' || str[i] == '\"'))
// 			quote = str[i];
// 		else if (quote == str[i])
// 			quote = -1;
//         if (quote != '\'' && str[i] == '$')
//         {
//             if (str[i] == '$' && str[i + 1] == '?')
//                 printf("%s\n", ft_itoa(data->status));
//             else if (str[i] == '$' && ft_isalpha(str[i + 1]))
//             { 
//                 j = i + 1;
//                 while(ft_isalpha(str[j]))
//                     j++;
//                 data->lexer->key = ft_substr(str, i + 1 , j - i - 1);
//                 printf("%s\n", data->lexer->key);
//                 data->lexer->value = ft_getenv_by_key(data->lexer->key, data->env);
//                 if (!data->lexer->value)
//                     return (-1);
//                 if (data->lexer->value)
//                     printf("%s\n", data->lexer->value);
//                 str = remove_by_index(str, i, j - i);
//                 if (!str)
//                     return (-1);
//                 str = ft_joinstr_index(str, data->lexer->value, i);
//                 if (!str)
//                     return (-1);
//                 //i += ft_strlen(data->lexer->value);
//                 printf("%s\n", str);
//                 free(data->lexer->key);
//                 free(data->lexer->value);
//             }
//         } 
//     }
//     return (0);
// }


int process_dollar_variable(t_data *data, char *str, int i)
{
    int j;

    j = i + 1;
    while (ft_isalpha(str[j]))
        j++;
    data->lexer->key = ft_substr(str, i + 1, j - i - 1);
    if (!data->lexer->key)
        return (-1);
    data->lexer->value = ft_getenv_by_key(data->lexer->key, data->env);
    if (!data->lexer->value)
        return (-1);
    //printf("%s\n", data->lexer->value);
    //printf("%s\n", data->lexer->key);
    str = remove_by_index(str, i, j - i);
    str = ft_joinstr_index(str, data->lexer->value, i);
    if (!str)
        return (-1);
    //printf("%s\n", str);
    free(data->lexer->key);
    free(data->lexer->value);
    return (0);
}

int handle_dollar(t_data *data, char *str)
{
    int i;
    int quote;

    i = -1;
    quote = -1;
    while (str[++i])
    {
        if (quote == -1 && (str[i] == '\'' || str[i] == '\"'))
            quote = str[i];
        else if (quote == str[i])
            quote = -1;
        if (quote != '\'' && str[i] == '$')
        {
            if (str[i] == '$' && str[i + 1] == '?')
                printf("%s\n", ft_itoa(data->status));
            else if (str[i] == '$' && ft_isalpha(str[i + 1]))
            {
                if (process_dollar_variable(data, str, i) == -1)
                    return (-1);
            }
        }
    }
    return (0);
}
