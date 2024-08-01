/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tugcekul <tugcekul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/07 12:13:50 by tkul              #+#    #+#             */
/*   Updated: 2024/08/01 22:29:02 by tugcekul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
#define MINISHELL_H


#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
# include <readline/readline.h>
# include <readline/history.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>
# include <limits.h>
# include <pthread.h>
# include <fcntl.h>
# include <sys/ioctl.h>
# include <termios.h>
# include "./lib/libft.h"

//#define HBLK "\e[0;90m"
//#define  BWHT "\e[1;37m"
#define  BHWHT "\e[1;97m"
#define COLOR_RESET "\e[0m"

typedef struct s_count
{
	int rm1;
	int rm2;
	int quote;
} t_count;

typedef struct s_env
{
	char *value;
	struct s_en *next;
} t_env;

typedef struct s_token
{
	char	*value;
	int		type;
	struct s_token *next;
	struct s_token *prev;
	
} t_token;

typedef struct s_node
{
	char		*key;
	char		*value;
	struct node *next;
} t_node;

typedef struct s_lexer
{
	int pipe_count;
	int token_count;
	int i;
	int j;
	int quote;
	
} t_lexer;


typedef struct s_data
{
	char *cmd;
	char **env;
	int status;
	int is_pipe;
	t_token **tokens;
	char *cwd;
	int *exit_status;
	int cmd_count;
	int pipe_count;
	
	
	
} t_data;

size_t	ft_strlen(const char *str);
char	*ft_strdup(const char *s1);
void remove_index(char **str, int index);
void check_parser_error(char *str);
char *ft_remove_quote(char *str);
char **ft_getenv(char **env);
int ft_start_shell(t_data *data);
int ft_init_data(t_data *data, char **env);
void	ft_signals(void);
void	tcsa(void);
void	ctrl_c(int sig);
void	coix(int sig);
int ft_run(t_data *data);
int  ft_init_tokens(t_data *data);
int ft_count_pipes(char *str);
void ft_free_tokens(t_token **tokens);
int ft_lexer(t_data *data);
int count_word(char *str, char c);
char **ft_split_by_quote(char *str, char c);



#endif