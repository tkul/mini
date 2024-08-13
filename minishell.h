/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkul <tkul@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/07 12:13:50 by tkul              #+#    #+#             */
/*   Updated: 2024/08/13 12:22:51 by tkul             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "./lib/libft.h"
# include <fcntl.h>
# include <limits.h>
# include <pthread.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/ioctl.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <termios.h>
# include <unistd.h>

extern int			g_qsignal;

# define IN_RED 1
# define OUT_RED 2
# define APP_RED 3
# define HER_DOC 4
# define CMD 5
# define ARG 6
# define FILE 7
# define DELIMETER 8

# define CMD_NOT_FOUND 127
# define INVALID_ARG 128
# define SUCCESS 0
# define ERROR -1
# define EXIT_ERROR 255
# define SYNTAX_ERROR 258

# define BHWHT "\e[1;97m"
# define COLOR_RESET "\e[0m"

typedef struct s_token
{
	char			*value;
	int				type;
	struct s_token	*next;
	struct s_token	*prev;

}					t_token;

typedef struct s_lexer
{
	int				pipe_count;
	int				token_count;
	int				i;
	int				j;
	int				quote;
	char			*key;
	char			*value;

}					t_lexer;

typedef struct s_split
{
	char			**cmds;
	int				quote;
	int				len;
	int				i;
	int				j;
	int				k;
}					t_split;

typedef struct s_data
{
	char			*cmd;
	char			**env;
	int				status;
	t_token			**tokens;
	char			*cwd;
	int				*exit_status;
	int				pipe_count;
	t_lexer			*lexer;
	char			**cmds;
	char			**new;
}					t_data;

size_t				ft_strlen(const char *str);
char				*ft_strdup(const char *s1);
char				**ft_getenv(char **env);
char				*ft_getenv_by_key(char *key, char **env);
int					ft_start_shell(t_data *data);
int					ft_init_data(t_data *data, char **env);
void				ft_signals(void);
void				tcsa(void);
void				ctrl_c(int sig);
void				coix(int sig);
int					ft_run(t_data *data);
int					ft_init_tokens(t_data *data);
int					ft_count_pipes(char *str);
void				ft_free_tokens(t_token **tokens);
int					ft_lexer(t_data *data);
char				**ft_split_by_quote(char const *s, char c);
int					count_word(const char *str, char c);
int					handle_dollar(t_data *data, char **str);
char				*ft_joinstr_index(char *s1, char *s2, int start_index);
char				*remove_by_index(char *str, int start, int end);
void				ft_set_quote_type(int *quote, char c);
int					ft_init_redirections(t_data *data);
int					ft_remove_quotes(char **s);
int					ft_control_quotes(char *s);
int					ft_strcmp(char *s1, char *s2);
int					is_redirection(char *str);
int					ft_create_token(t_data *data, char *str, int i, int j);
void				ft_print_tokens(t_token **token);
t_token				*get_last_token(t_token *token);
t_token				*new_token(char *value, int type);
void				token_add_back(t_token **token, t_token *new);
void				ft_error(int error);
int					is_valid(char *str);
int					ft_control_token(t_token **token);
char				*remove_space(char *str);
int					ft_is_builtins(char *cmd);
int					ft_pwd(t_data *data);
int					ft_echo(t_data *data);
int					ft_env(t_data *data);
void				ft_execute(t_data *data);

#endif