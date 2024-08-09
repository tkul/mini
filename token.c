/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tugcekul <tugcekul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/09 02:11:20 by tugcekul          #+#    #+#             */
/*   Updated: 2024/08/09 17:39:35 by tugcekul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


void token_add_back(t_token **token, t_token *new)
{
    t_token *current;

    if (!token)
        return ;
    if (!*token)
    {
        *token = new;
        return ;
    }
    current = *token;
    while (current->next)
        current = current->next;
    current->next = new;
    new->prev = current;
}

t_token *new_token(char *value, int type)
{
    t_token *new;

    new = malloc(sizeof(t_token));
    if (!new)
        return (NULL);
    new->value = value;
    new->type = type;
    new->next = NULL;
    new->prev = NULL;
    return (new);
}

void ft_create_token(t_data *data, char *str, int j)
{
    t_token *new;
    
    if (j == 0)
    {
        new = new_token(ft_strdup(str[j]), CMD);
        token_add_back(data->tokens, new);
    }
    else
    {
        new = new_token(ft_strdup(str[j]), ARG);
        token_add_back(data->tokens, new);
    }
    
}