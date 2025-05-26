/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data_cleanup.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikulik <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 13:09:55 by ikulik            #+#    #+#             */
/*   Updated: 2025/05/21 16:10:11 by ikulik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"
#include <stdio.h>

int	*create_array(t_list **lst, int size)
{
	int		*res;
	int		index;
	t_list	*iter;

	if (lst == NULL)
		return (NULL);
	iter = *lst;
	index = 0;
	res = malloc(size * sizeof(int));
	if (res == NULL)
		return (NULL);
	while (index < size)
	{
		res[index] = iter->val;
		iter = iter->next;
		index++;
	}
	return (res);
}

int	transform_r(int n, int size, int mode)
{
	if (mode == 1)
	{
		if (n < -(size / 2))
			n += size;
		if (n > size / 2)
			n -= size;
	}
	if (mode == 2)
	{
		if (n < 0)
			n = size + n;
	}
	return (n);
}

static void	shift_list_to_optimal(t_list **lst, int size, int avg)
{
	t_list	*iter;
	int		index;

	if (lst == NULL)
		return ;
	if (*lst == NULL)
		return ;
	iter = *lst;
	index = 0;
	while (index < size)
	{
		iter->shift = transform_r(iter->shift - avg, size, 1);
		iter = iter->next;
		index++;
	}
}

int	process_list(t_list **lst, int *arr, int size)
{
	int		i;
	int		j;
	int		average_shift;
	t_list	*iter;

	i = 0;
	average_shift = 0;
	while (i < size)
	{
		j = 0;
		iter = *lst;
		while (iter->val != arr[i] && j < size)
		{
			iter = iter->next;
			j++;
		}
		average_shift += transform_r(j - i, size, 1);
		iter->shift = transform_r(j - i, size, 1);
		//printf("shift %d pos %d\n", iter->shift, i);
		iter->true_pos = i + 1;
		i++;
	}
	average_shift = transform_r(average_shift / size, size, 1);
	shift_list_to_optimal (lst, size, average_shift);
	return (average_shift);
}

int	orderered_check(t_list **lst, int size)
{
	int		i;
	int		average_shift;
	t_list	*iter;

	if (lst == NULL)
		return (0);
	if (*lst == NULL)
		return (0);
	i = 0;
	iter = *lst;
	average_shift = iter->shift;
	while (i < size)
	{
		if (iter->shift != average_shift)
			return (size);
		iter = iter->next;
		i++;
	}
	return (average_shift);
}




