/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkul <tkul@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 01:10:53 by tkul              #+#    #+#             */
/*   Updated: 2024/09/05 01:11:05 by tkul             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	swap(char **a, char **b)
{
	char	*temp;

	temp = *a;
	*a = *b;
	*b = temp;
}

static void	bubble_sort_recursive(char **arr, int n, int i)
{
	if (i >= n - 1)
		return ;
	if (ft_strcmp(arr[i], arr[i + 1]) > 0)
		swap(&arr[i], &arr[i + 1]);
	bubble_sort_recursive(arr, n, i + 1);
}

static void	bubble_sort(char **arr, int n)
{
	if (n <= 1)
		return ;
	bubble_sort_recursive(arr, n, 0);
	bubble_sort(arr, n - 1);
}

void	sort_env_by_first_letter(char **env, int size)
{
	bubble_sort(env, size);
}
