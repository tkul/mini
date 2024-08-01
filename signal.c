/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tugcekul <tugcekul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/31 18:21:35 by tugcekul          #+#    #+#             */
/*   Updated: 2024/07/31 22:52:25 by tugcekul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_qsignal = 0;

void	coix(int sig)
{
	(void)sig;
	rl_on_new_line();
	printf("\033[K");
	rl_redisplay();
	g_qsignal = 0;
}

void	ctrl_c(int sig)
{
	(void)sig;
	if (!g_qsignal)
	{
		printf("\n");
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
	}
	else
		printf("\n");
}

void	tcsa(void)
{
	struct termios	term1;

	if (tcgetattr(STDIN_FILENO, &term1) != 0)
		exit((perror("error"), -1));
	else
	{
		term1.c_cc[VQUIT] = _POSIX_VDISABLE;
		term1.c_lflag |= ECHOE | ICANON;
		if (tcsetattr(STDIN_FILENO, TCSANOW, &term1) != 0)
			exit((perror("error"), -1));
		if (tcgetattr(STDIN_FILENO, &term1) != 0)
			exit((perror("error"), -1));
	}
}

void	ft_signals(void)
{
	tcsa();
	signal(SIGINT, ctrl_c);
	signal(SIGQUIT, coix);
	return ;
}