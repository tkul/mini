/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils3.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkul <tkul@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 17:41:31 by tkul              #+#    #+#             */
/*   Updated: 2024/09/05 12:36:58 by tkul             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	isredwocmd_helper(t_token *tokens, int i, t_token *tmp)
{
	if (i == 0)
	{
		tmp = tokens;
		while (tmp)
		{
			if (ft_is_redirection(tmp))
				return (1);
			tmp = tmp->next;
		}
	}
	return (0);
}

int	isredwocmd(t_token *tokens)
{
	int		i;
	t_token	*tmp;

	i = 0;
	tmp = tokens;
	while (tmp)
	{
		if (tmp->type == CMD)
			i++;
		if (i != 0)
			return (0);
		tmp = tmp->next;
	}
	return (isredwocmd_helper(tokens, i, tmp));
}

void	ft_is_without_cmd(t_exec *exec, t_data *data)
{
	if (exec->is_without_cmd)
	{
		exec->type = CMD_WITHOUT_CMD;
		if (data->path)
			free(data->path);
		data->path = NULL;
		data->control = 0;
	}
}
