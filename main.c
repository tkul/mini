/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkul <tkul@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/07 12:35:45 by tkul              #+#    #+#             */
/*   Updated: 2024/07/07 15:10:32 by tkul             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int main()
{
	while (1)
	{
		char *cmd = readline(BHWHT"⭐ MINISHELL> "COLOR_RESET);
		cmd = ft_remove_quote(cmd);
		printf("%s\n", cmd);
	}
}