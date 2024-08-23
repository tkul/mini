/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayirmili <ayirmili@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/07 12:13:50 by tkul              #+#    #+#             */
/*   Updated: 2024/08/24 01:22:07 by ayirmili         ###   ########.fr       */
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
# include <sys/stat.h>
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
# define ERROR 1
# define EXIT_ERROR 255
# define SYNTAX_ERROR 258
# define ERR_NOT_VALID_IDFR 1

# define BHWHT "\e[1;97m"
# define COLOR_RESET "\e[0m"

typedef struct s_token
{
	char			*value;
	int				type;
	int				index;
	struct s_token	*next;
	struct s_token	*prev;
}					t_token;

typedef struct s_lexer
{
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

typedef struct s_exec
{
	t_token	**t_ptr1;
	t_token	*t_ptr2;
	char	*cmd_path;
	char	**cmd_args;
	char	**heredocs;
	int		err_no;
	char	*err_value;
	int		is_without_cmd;
	int		count_heredocs;
	int		here_doc_idx;
	int		out_type;
	char	*out_file;
	char	*in_file;
	int		in_type;
	int		should_run;
	char	*is_here_doc;
	int		in_fd;
	int		out_fd;
	int		type;
}					t_exec;
typedef struct s_data
{
	char			*cmd;
	char			**env;
	char			**export;
	int				status;
	t_token			**tokens;
	char			*cwd;
	int				pipe_count;
	t_lexer			*lexer;
	char			**cmds;
	char			**new;
	char			*path;
	int				ret;
	char			*old_pwd;
	int				i;
	int				j;
	t_token			*token_buffer;
	int				cmd_amount;
	int				check;
	// asim oluşturulanlar
	int				*pid;
	char			*cleaned_cmd;
	t_exec			*exec;
	int				*pipe_fd;
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
int					ft_count_pipes(t_data *data, char *str);
void				ft_free_tokens(t_token **tokens);
int					ft_parser(t_data *data);
char				**ft_split_by_quote(char const *s, char c);
int					count_word(const char *str, char c);
char				*ft_joinstr_index(char *s1, char *s2, int start_index);
char				*remove_by_index(char *str, int start, int end);
void				ft_set_quote_type(int *quote, char c);
int					ft_init_redirections(t_data *data);
int					ft_control_quotes(char *s);
int					ft_strcmp(char *s1, char *s2);
int					is_redirection(char *str);
int					ft_create_token(t_data *data, char *str, int i, int j);
void				ft_print_tokens(t_token **token);
t_token				*get_last_token(t_token *token);
t_token				*new_token(char *value, int type, int index);
void				token_add_back(t_token **token, t_token *new);
void				ft_error(t_data *data, int error);
int					is_valid(char *str);
int					ft_control_token(t_data *data, t_token **token);
char				*remove_space(char *str);
int					ft_is_builtins(char *cmd);
void				ft_pwd(t_data *data);
void				ft_echo(t_data *data, int *index);
void				ft_env(t_data *data);
void				ft_execute(t_data *data);
void				ft_free_array(char **array);
void				ft_exit(t_data *data, int *index);
void				ft_redirect_arrange(t_token **tokens);
void				ft_cd(t_data *data, int *index);
void				ft_export(t_data *data, int *index);
void				ft_setenv(t_data *data, char *key, char *value);
void				ft_set_export(t_data *data, char *key, char *value);
char				**ft_realloc(char **env, int size);
int					ft_unset(t_data *data, int *index);
int					my_isalpha(int c);
int					process_dollar_variable(t_data *data, char **str, int *i,
						int quote);
void				ft_print_token_buffer(t_token *token);

void				ft_update_export_entry(t_data *data, char *key,
						char *value);
void				ft_update_or_add_export_entry(t_data *data, char *key,
						char *value);
char				*ft_create_export_entry(const char *key, const char *value);
void				t_run_single_cmd(t_data *data, int i);
int					ft_remove_quotes(t_data *data, char **s);
void    			ft_run_multiple_command(t_data *data);
char				*clear_quotes(char *cmd);
int					ft_pipe(t_data *data, t_token **tokens);
int					ft_create_pipe(t_data *data);
void				pipe_fork(t_data *data, int i, t_token **tokens);
void				handle_pipe_dup(t_data *data, int i);
int					check_direct(t_data *mini, t_token **tokens);
int					close_fd(t_data *data);

#endif