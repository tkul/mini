/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkul <tkul@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/07 12:13:50 by tkul              #+#    #+#             */
/*   Updated: 2024/09/05 16:09:24 by tkul             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "./lib/libft.h"
# include <dirent.h>
# include <errno.h>
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

# define CMD_PATH 19
# define CMD_BUILTIN 20
# define CMD_WITHOUT_CMD 21

# define CMD_NOT_FOUND 127
# define INVALID_ARG 128
# define SUCCESS 0
# define ERROR 1
# define EXIT_ERROR 255
# define SYNTAX_ERROR 258
# define ERR_PIPE_INIT 124
# define ERR_PERMISSION_DENIED 1261
# define ERR_PERMISSION_DENIED2 1262
# define ERR_NO_SUCH_FILE 1271
# define ERR_NO_FILE_OR_DIR 1
# define ERR_IS_DIR 126

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
	char			**tmp;
}					t_split;

typedef struct s_exec
{
	int				err_no;
	char			*err_value;
	int				is_without_cmd;
	int				out_type;
	char			*out_file;
	char			*in_file;
	int				in_type;
	int				should_run;
	char			*is_here_doc;
	int				in_fd;
	int				out_fd;
	int				count_heredocs;
	int				type;
}					t_exec;

typedef struct s_data
{
	char			**original;
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
	int				is_red;
	int				*forks;
	int				*pipes;
	char			**args;
	int				control;
	int				index;
	int				flag;
	int				rm1;
	int				rm2;
	int				red;
	int				red_extra;
	int				is_created_token_is_null;
	t_token			*last;
	t_token			*new_token;
	int				offset;
	t_exec			**exec;
	int				is_really_env;
	char			*t_path;
	int				t_status;
	int				h_flag;
	int				red_i;
	int				cmd_flag;
}					t_data;

size_t				ft_strlen(const char *str);
char				*ft_strdup(const char *s1);
char				**ft_getenv(char **env);
char				*ft_getenv_by_key(char *key, char **env);
int					ft_start_shell(t_data *data);
void				ft_signals(void);
void				tcsa(void);
void				ctrl_c(int sig);
void				coix(int sig);
int					ft_run(t_data *data);
int					ft_init_tokens(t_data *data);
int					ft_count_pipes(t_data *data, char *str, int can_thow_err);
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
int					ft_is_builtins(char *cmd);
void				ft_pwd(t_data *data);
void				ft_echo(t_data *data, int *index);
void				ft_env(t_data *data);
void				ft_start_execute(t_data *data);
void				ft_free_array(char **array);
void				ft_exit(t_data *data, int *index);
void				ft_redirect_arrange(t_data *data,t_token **tokens);
void				ft_cd(t_data *data, int *index);
void				ft_export(t_data *data, int *index);
void				ft_setenv(t_data *data, char *key, char *value);
char				**ft_realloc(char **env, int size);
void				ft_unset(t_data *data, int *index);
int					my_isalpha(char *str);
int					process_dollar_variable(t_data *data, char **str, int *i,
						int quote);
void				ft_print_token_buffer(t_token *token);

void				ft_update_export_entry(t_data *data, char *key,
						char *value);
char				*ft_create_export_entry(const char *key, const char *value);
int					ft_remove_quotes(t_data *data, char **s);
void				ft_execve(t_data *data, t_exec **exec, int i);
char				*find_in_path(char *path, char *cmd);
int					ft_count_cmds(t_data *data, t_token **tokens);
void				ft_run_builtin(t_data *data, int i, t_token *token,
						t_exec *exec);
void				ft_init_exec(t_data *data, t_exec *exec, t_token *token);
int					ft_is_redirection(t_token *token);
void				ft_init_here_docs(t_data *data, t_exec **exec, int i,
						t_token *token);
int					ft_count_heredocs(t_token *token);
char				*ft_is_here_doc2(t_exec *exec, t_token *token);
char				*ft_is_here_doc(t_token *token);
int					isredwocmd(t_token *tokens);
int					ft_is_redirection_single(t_token *token);
void				ft_set_args(t_data *data, t_token *token);
void				ft_init_pipes(t_data *data);
void				ft_set_path(t_data *data, t_token *token, t_exec *exec);
void				ft_init_dupes(t_data *data, t_exec *exec, int i);
void				close_redir_fd(t_data *data, t_exec *exec, int fd1,
						int fd2);
int					close_redir_pipe_fd(t_data *data, t_exec *exec, int i);
void				mother_close_pipes_all(t_data *data);
void				close_pipes_all(int *pipes, int cmd_amount, int i);
void				ft_is_without_cmd(t_exec *exec, t_data *data);
int					ft_find_exec_type(t_exec **exec, t_token *token, int i);
int					ft_isalphaaa(int c);
int					ft_exec_init_redirection(t_data *data, t_exec *exec,
						t_token *token);
int					ft_dup_redictions(t_exec *exec, t_data *data);
void				ft_print_exec(t_exec **exec);
int					ft_open_check_files(t_exec *exec, int status, t_data *data);
void				ft_run_redirects(t_data *data, t_token *token, t_exec *exec,
						int i);
void				ft_run_commands(t_data *data, t_token *token, int i,
						t_exec *exec);
void				ft_run_single_cmd(t_data *data, t_exec **exec, int i,
						t_token *token);
void				ft_run_pipes(t_data *data, t_exec *exec, int i,
						t_token *token);
void				ft_set_exec_err(t_data *data, t_exec *exec, int err,
						char *value);
void				ft_exec_error(t_data *data, t_exec *exec, int err,
						char *value);
void				free_exec_data(t_data *data, t_exec **exec, int cmd_amount);
void				free_exec_data(t_data *data, t_exec **exec, int cmd_amount);
void				ft_heredoc_loop(t_data *data, t_token *token, t_exec *exec,
						int pipe_fd[2]);
void				ft_heredoc_writer(t_data *data, int pipe_fd[2],
						char **buff);
void				ft_wait_part(t_data *data);
void				ft_exec_part(t_data *data, t_exec *exec, t_token *token);
int					ft_parser_free(t_data *data);
void				ft_tokenclear(t_token **token, void (*del)(void *));
void				ft_print_exec_error(t_data *data, t_exec *exec);
int					ft_toknssize(t_token *token);
int					ft_dollar_handle(t_data *data, char **s, int *i, int quote);
void				remove_index(char **s, int index);
void				sort_env_by_first_letter(char **env, int size);
void				ft_heredoc_writer(t_data *data, int pipe_fd[2],
						char **buff);
void				rl_replace_line(const char *text, int clear_undo);

#endif