/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tugcekul <tugcekul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/07 12:13:50 by tkul              #+#    #+#             */
/*   Updated: 2024/08/07 20:37:09 by tugcekul         ###   ########.fr       */
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


// < (Input Redirection): Bir dosyadan giriş almak için kullanılır.
// > (Output Redirection): Çıktıyı bir dosyaya yönlendirmek için kullanılır (dosyayı oluşturur veya üzerine yazar).
// >> (Append Redirection): Çıktıyı bir dosyaya ekler (dosyayı oluşturur veya sonuna ekler).
// << (Here Document): Çok satırlı giriş sağlamak için kullanılır.

# define INT_RED 1
# define OUT_RED 2
# define APP_RED 3
# define HER_DOC 4

#define  BHWHT "\e[1;97m"
#define COLOR_RESET "\e[0m"


// typedef struct s_env
// {
// 	char *value;
// 	struct s_en *next;
// } t_env;

typedef struct s_token
{
	char	*value;
	int		type;
	struct s_token *next;
	struct s_token *prev;
	
} t_token;


typedef struct s_lexer
{
	int pipe_count;
	int token_count;
	int i;
	int j;
	int quote;
	char *key;
	char *value;
	
} t_lexer;

typedef struct s_split
{
	char **cmds;
    int quote;
    int len;
	int i;
	int j;
	int k;
} t_split;


typedef struct s_data
{
	char *cmd;
	char **env;
	int status;
	t_token **tokens;
	char *cwd;
	int *exit_status;
	int pipe_count;
	t_lexer *lexer;
} t_data;

size_t	ft_strlen(const char *str);
char	*ft_strdup(const char *s1);
char **ft_getenv(char **env);
char *ft_getenv_by_key(char *key, char **env);
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
char	**ft_split_by_quote(char const *s, char c);
// int count_word(char *str, char c);
int count_word(const char *str, char c);
int handle_dollar(t_data *data, char **str);
char	*ft_joinstr_index(char *s1, char *s2, int start_index);
char *remove_by_index(char *str, int start, int end);
void ft_set_quote_type(int *quote, char c);
int ft_init_redirections(char *str);
int ft_remove_quotes(char **s);
int ft_control_quotes(char *s);
int	ft_strcmp(char *s1, char *s2);

#endif