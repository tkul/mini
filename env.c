/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkul <tkul@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/07 15:11:08 by tkul              #+#    #+#             */
/*   Updated: 2024/07/10 09:56:24 by tkul             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int main(int ac, char **arg)
{
	extern char	**environ;
	int i = 0;

	while(environ[i])
		printf("%s\n", environ[i++]);
		i++;

	

//	//t_node *node = ft_init();

//	//printf("%s\n", ft_get_value("MallocNanoZone", node));
//}
