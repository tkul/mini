/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thisfilewilldeleted.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkul <tkul@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/09 21:44:54 by tkul              #+#    #+#             */
/*   Updated: 2024/09/01 14:08:56 by tkul             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_print_tokens(t_token **token)
{
	t_token	**tmp;
	t_token	*next;
	int		i;

	if (!token || !*token)
		return ;
	tmp = token;
	i = 0;
	while (tmp[i])
	{
		next = tmp[i];
		while (next)
		{
			printf("Token %d: type:%d, %s\n", i, next->type, next->value);
			next = next->next;
		}
		i++;
	}
}

void	ft_print_token_buffer(t_token *token)
{
	t_token	*tmp;

	if (!token)
		return ;
	tmp = token;
	while (tmp)
	{
		printf("type:%d, %s, index: %d\n", tmp->type, tmp->value, tmp->index);
		tmp = tmp->next;
	}
}

void	ft_print_exec(t_exec **exec)
{
	int	i;

	i = 0;
	while (exec[i])
	{
		printf("exec[%d]->is_without_cmd: %d\n", i, exec[i]->is_without_cmd);
		printf("exec[%d]->is_here_doc: %s\n", i, exec[i]->is_here_doc);
		printf("exec[%d]->count_heredocs: %d\n", i, exec[i]->count_heredocs);
		printf("exec[%d]->type: %d\n", i, exec[i]->type);
		printf("exec[%d]->in_fd: %d\n", i, exec[i]->in_fd);
		printf("exec[%d]->out_fd: %d\n", i, exec[i]->out_fd);
		printf("exec[%d]->should_run: %d\n", i, exec[i]->should_run);
		printf("exec[%d]->in_type: %d\n", i, exec[i]->in_type);
		printf("exec[%d]->out_type: %d\n", i, exec[i]->out_type);
		printf("exec[%d]->in_file: %s\n", i, exec[i]->in_file);
		printf("exec[%d]->out_file: %s\n", i, exec[i]->out_file);
		printf("exec[%d]->err_no: %d\n", i, exec[i]->err_no);
		printf("exec[%d]->err_value: %s\n", i, exec[i]->err_value);
		i++;
	}
}
