/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkul <tkul@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/07 12:13:50 by tkul              #+#    #+#             */
/*   Updated: 2024/07/07 15:10:27 by tkul             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
#define MINISHELL_H


#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
# include <readline/readline.h>
# include <readline/history.h>

//#define HBLK "\e[0;90m"
//#define  BWHT "\e[1;37m"
#define  BHWHT "\e[1;97m"
#define COLOR_RESET "\e[0m"



typedef struct s_node {
	char		*key;
	char		*value;
	struct node *next;
} t_node;


char *ft_remove_quote(char *s);






#endif