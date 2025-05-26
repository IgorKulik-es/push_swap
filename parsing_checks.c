/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_checks.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikulik <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 19:26:21 by ikulik            #+#    #+#             */
/*   Updated: 2025/05/22 16:15:50 by ikulik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int	check_element(char *arg)
{
	int			index;
	int			len;
	long long	res;

	index = 1;
	if (arg == NULL)
		return (0);
	len = ft_strlen(arg);
	if (len > 11)
		return (0);
	if (arg[0] != '-' && !('0' <= arg[0] && arg[0] <= '9'))
		return (0);
	while (index < len)
	{
		if (!('0' <= arg[index] && arg[index] <= '9'))
			return (0);
		index++;
	}
	res = ft_atol(arg);
	if (res > (long long)INT_MAX || res < (long long)INT_MIN)
		return (0);
	return (1);
}

long long	ft_atol(char *nptr)
{
	long long	result;
	int			is_positive;

	result = 0;
	is_positive = 1;
	if (*nptr == '-' || *nptr == '+')
	{
		if (*nptr == '-')
			is_positive = -1;
		nptr++;
	}
	while ('0' <= *nptr && *nptr <= '9')
	{
		result = result * 10 + *nptr - '0';
		nptr++;
	}
	result *= is_positive;
	return (result);
}

void	stupid_sort(int	*arr, int size)
{
	int	i;
	int	j;
	int	temp;

	i = 0;
	while (i < size - 1)
	{
		j = i + 1;
		while (j < size)
		{
			if (arr[i] > arr[j])
			{
				temp = arr[i];
				arr[i] = arr[j];
				arr[j] = temp;
			}
			j++;
		}
		i++;
	}
}

int	check_noncoincidence(int *arr, int size)
{
	int	index;

	if (size == 0)
		return (0);

	index = 0;
	while (index < size - 1)
	{
		if (arr[index] == arr[index + 1])
			return (0);
		index++;
	}
	return (1);
}

int	*check_arguments(int words, char **argv, t_list **lst)
{
	int	*arr;
	int	index;

	index = 0;
	arr = malloc((words) * sizeof(int));
	if (arr == NULL)
		return (0);
	while (index < words)
	{
		if (check_element(argv[index]) == 0)
		{
			free(arr);
			return (lst_clean(lst));
		}
		lst_push_back(lst, ft_atol(argv[index]), 0);
		arr[index] = (*lst)->prev->val;
		index++;
	}
	stupid_sort(arr, words);
	if (check_noncoincidence(arr, words) == 0)
	{
		free(arr);
		return (lst_clean(lst));
	}
	return (arr);
}
