/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_builtin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkul <tkul@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/13 00:00:31 by tkul              #+#    #+#             */
/*   Updated: 2024/09/02 17:39:16 by tkul             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_is_builtins(char *cmd)
{
	if (ft_strncmp(cmd, "echo", 5) == 0)
		return (1);
	if (ft_strncmp(cmd, "cd", 3) == 0)
		return (2);
	if (ft_strncmp(cmd, "pwd", 4) == 0)
		return (3);
	if (ft_strncmp(cmd, "export", 7) == 0)
		return (4);
	if (ft_strncmp(cmd, "unset", 6) == 0)
		return (5);
	if (ft_strncmp(cmd, "env", 4) == 0)
		return (6);
	if (ft_strncmp(cmd, "exit", 5) == 0)
		return (7);
	return (0);
}

void	ft_run_builtin(t_data *data, int i, t_token *token, t_exec *exec)
{
	if (data->cmd_amount == 1 && ft_dup_redictions(exec, data))
		return ;
	if (ft_strcmp(token->value, "echo") == 0)
		ft_echo(data, &i);
	else if (ft_strcmp(token->value, "pwd") == 0)
		ft_pwd(data);
	else if (ft_strcmp(token->value, "env") == 0)
		ft_env(data);
	else if (ft_strcmp(token->value, "cd") == 0)
		ft_cd(data, &i);
	else if (ft_strcmp(token->value, "export") == 0)
		ft_export(data, &i);
	else if (ft_strcmp(token->value, "unset") == 0)
		ft_unset(data, &i);
	else if (ft_strcmp(token->value, "exit") == 0)
		ft_exit(data, &i);
}
