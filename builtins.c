/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkul <tkul@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/12 23:25:11 by tkul              #+#    #+#             */
/*   Updated: 2024/08/16 21:55:45 by tkul             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_pwd(t_data *data)
{
	printf("%s\n", data->cwd);
}

int	n_control(char *str)
{
	int	i;

	i = 2;
	if (str[0] != '-' || str[1] != 'n')
		return (ERROR);
	while (str[i])
	{
		if (str[i] != 'n')
			return (ERROR);
		i++;
	}
	return (SUCCESS);
}

void	ft_echo(t_token *t)
{
	t_token	*token;
	int		n_flag;
	int		control;

	n_flag = 1;
	token = t;
	control = 0;
	if (!token->next)
	{
		printf("\n");
		return ;
	}
	token = token->next;
	while (token)
	{
		if (n_flag == 1 && n_control(token->value) == SUCCESS)
		{
			token = token->next;
			control = 1;
			continue ;
		}
		else
			n_flag = 0;
		if (token->type == ARG)
		{
			printf("%s", token->value);
			if (token->next)
				printf(" ");
		}
		token = token->next;
	}
	if (!control)
		printf("\n");
}

void	ft_env(t_data *data)
{
	int	i;

	i = 0;
	while (data->env[i])
	{
		printf("%s\n", data->env[i]);
		i++;
	}
}

// void	ft_exit(t_data *data)
// {
// 	t_token *token;
// 	int exit_code;
// 	int i;

// 	i = 0;
// 	exit_code = 0;
// 	token = *data->tokens;
// 	printf("exit\n");
// 	if (token && token->next && token->next->next)
// 	{
// 		write(2, "exit: too many arguments\n", 26);
// 		exit_code = 1;
// 	}
// 	else if (token && token->next)
// 	{
// 		while (token->next->value[i])
// 		{
// 			if (i == 0 && token->next->value[i] == '-')
// 			{
// 				i++;
// 				continue ;
// 			}
// 			if (!ft_isdigit(token->next->value[i]))
// 			{
// 				ft_error(data, EXIT_ERROR);
// 				exit_code = 255;
// 				break ;
// 			}
// 			i++;
// 		}
// 		if (exit_code == 0)
// 			exit_code = ft_atoi(token->next->value);
// 	}
// 	data->status = exit_code;
// 	exit(exit_code);
// }

int	validate_exit_value(const char *value)
{
	int	i;

	i = 0;
	if (value[i] == '-')
		i++;
	while (value[i])
	{
		if (!ft_isdigit(value[i]))
			return (EXIT_ERROR);
		i++;
	}
	return (0);
}

void	process_exit_code(const char *value, int *exit_code)
{
	*exit_code = ft_atoi(value);
	if (*exit_code < 0)
		*exit_code = 256 + (*exit_code % 256);
}

void	ft_exit(t_data *data)
{
	t_token	*token;
	int		exit_code;
	int		validation_code;

	exit_code = 0;
	token = *data->tokens;
	printf("exit\n");
	if (token && token->next && token->next->next)
	{
		write(2, "exit: too many arguments\n", 26);
		exit_code = 1;
	}
	else if (token && token->next)
	{
		validation_code = validate_exit_value(token->next->value);
		if (validation_code != 0)
		{
			ft_error(data, EXIT_ERROR);
			exit_code = validation_code;
		}
		else
			process_exit_code(token->next->value, &exit_code);
	}
	data->status = exit_code;
	exit(exit_code);
}
char	**ft_realloc(char **env, int size)
{
	char	**new;
	int		i;

	i = 0;
	new = malloc(sizeof(char *) * (size + 1));
	if (!new)
		return (NULL);
	while (env[i])
	{
		new[i] = ft_strdup(env[i]);
		i++;
	}
	new[i] = NULL;
	free(env);
	return (new);
}

void	ft_setenv(t_data *data, char *key, char *value)
{
	int		i;
	char	*new;
	char	*tmp;

	i = 0;
	while (data->env[i])
	{
		if (ft_strncmp(data->env[i], key, ft_strlen(key)) == 0)
		{
			free(data->env[i]);
			tmp = ft_strjoin(key, "=");
			new = ft_strjoin(tmp, value);
			free(tmp);
			data->env[i] = new;
			return ;
		}
		i++;
	}
	data->env = ft_realloc(data->env, i + 1);
	printf("key: %s\n", key);
	printf("value: %s\n", value);
	if (!value)
	{
		tmp = ft_strjoin(key, "=");
		new = ft_strjoin(tmp, value);
	}
	else
	{
		tmp = ft_strjoin(key, "");
		new = ft_strjoin(tmp, value);
	}
	free(tmp);
	data->env[i - 1] = new;
}

void	ft_cd(t_data *data)
{
	struct stat	buf;
	t_token		*token;

	data->old_pwd = getcwd(NULL, 0);
	token = *data->tokens;
	if (!token->next)
	{
		data->path = ft_getenv_by_key("HOME", data->env);
		if (!data->path)
		{
			write(2, "cd: HOME not set\n", 17);
			data->status = ERROR;
			return ;
		}
	}
	else
		data->path = token->next->value;
	data->ret = stat(data->path, &buf);
	if (data->ret == -1)
	{
		write(2, "cd: no such file or directory: ", 31);
		write(2, data->path, ft_strlen(data->path));
		write(2, "\n", 1);
		data->status = ERROR;
		return ;
	}
	if (!S_ISDIR(buf.st_mode))
	{
		write(2, "cd: not a directory: ", 21);
		write(2, data->path, ft_strlen(data->path));
		write(2, "\n", 1);
		data->status = ERROR;
		return ;
	}
	if (chdir(data->path) == -1)
	{
		write(2, "cd: error\n", 10);
		data->status = ERROR;
		return ;
	}
	ft_setenv(data, "OLDPWD", data->old_pwd);
	data->cwd = getcwd(NULL, 0);
	data->status = SUCCESS;
}

void	ft_export(t_data *data)
{
	t_token	*token;
	char	*key;
	char	*value;
	int		i;

	token = *data->tokens;
	i = 0;
	if (!token->next)
	{
		while (data->env[i])
			printf("declare -x %s\n", data->env[i++]);
		return ;
	}
	token = token->next;
	while (token)
	{
		if (ft_strchr(token->value, '='))
		{
			key = ft_substr(token->value, 0, ft_strchr(token->value, '=')
					- token->value);
			value = ft_strchr(token->value, '=') + 1;
			ft_setenv(data, key, value);
			free(key);
		}
		else
			ft_setenv(data, token->value, "");
		token = token->next;
	}
}
