/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkul <tkul@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/24 23:54:42 by tkul              #+#    #+#             */
/*   Updated: 2024/09/05 11:51:23 by tkul             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_find_exec_type(t_exec **exec, t_token *token, int i)
{
	if (exec[i]->is_without_cmd)
		return (CMD_WITHOUT_CMD);
	else if (ft_is_builtins(token->value))
		return (CMD_BUILTIN);
	return (CMD_PATH);
}

void	ft_init_exec(t_data *data, t_exec *exec, t_token *token)
{
	exec->err_no = 0;
	exec->err_value = NULL;
	exec->is_without_cmd = isredwocmd(token);
	exec->out_type = 0;
	exec->out_file = NULL;
	exec->in_file = NULL;
	exec->should_run = 0;
	exec->in_type = 0;
	ft_is_without_cmd(exec, data);
	exec->is_here_doc = ft_is_here_doc(token);
	exec->in_fd = 0;
	exec->out_fd = 0;
	exec->count_heredocs = ft_count_heredocs(token);
	exec->type = 0;
}

int	ft_is_redirection(t_token *token)
{
	while (token)
	{
		if (token->type == IN_RED || token->type == OUT_RED
			|| token->type == APP_RED || token->type == HER_DOC)
			return (1);
		token = token->next;
	}
	return (0);
}

char	*ft_is_here_doc(t_token *token)
{
	while (token)
	{
		if (token->type == DELIMETER)
			return (ft_strdup(token->value));
		token = token->next;
	}
	return (NULL);
}

char	*ft_is_here_doc2(t_exec *exec, t_token *token)
{
	while (token)
	{
		if (!(ft_strcmp(token->value, exec->is_here_doc)))
			token = token->next;
		if (token->type == DELIMETER)
		{
			if (exec->is_here_doc)
				free(exec->is_here_doc);
			return (ft_strdup(token->value));
		}
		token = token->next;
	}
	return (NULL);
}
