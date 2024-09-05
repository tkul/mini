/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_heredoc.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkul <tkul@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 21:45:08 by tkul              #+#    #+#             */
/*   Updated: 2024/09/05 11:43:39 by tkul             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_heredoc(t_data *data, t_token *token, t_exec **exec, int j)
{
	int	pipe_fd[2];

	if (pipe(pipe_fd) == -1)
		return ;
	ft_heredoc_loop(data, token, exec[j], pipe_fd);
	close(pipe_fd[1]);
	exec[j]->in_fd = pipe_fd[0];
}

void	ft_init_here_docs(t_data *data, t_exec **exec, int i, t_token *token)
{
	if (exec[i]->is_here_doc || data->cmd_amount == 0)
		ft_heredoc(data, token, exec, i);
}
