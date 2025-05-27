/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   qsort_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikulik <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 16:55:45 by ikulik            #+#    #+#             */
/*   Updated: 2025/05/27 20:02:33 by ikulik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static void	count_splits(t_qs_prs *params, int *arr);
static int	check_if_sorted(t_list *lst, int *arr, t_qs_prs *params);

int	find_pivots(t_list *lst, t_qs_prs *params)
{
	int		*arr;
	int		index;
	t_list	*start;

	index = 0;
	start = lst;
	arr = (int *)malloc(params->len * sizeof(int));
	if (arr == NULL)
		return (0);
	if (params->mode & UP)
		lst = lst->prev;
	while (index < params->len)
	{
		arr[index] = lst->true_pos;
		lst = lst->next;
		if (params->mode & UP)
			lst = lst->prev->prev;
		index++;
	}
	insertion_sort(arr, params->len);
	index = check_if_sorted(start, arr, params);
	count_splits(params, arr);
	free(arr);
	return (index);
}

static void	count_splits(t_qs_prs *params, int *arr)
{
	if (params->len == 4)
	{
		params->pivots[0] = arr[2];
		params->pivots[1] = arr[2];
		params->pt_size[0] = 2;
		params->pt_size[1] = 0;
		params->pt_size[2] = 2;
	}
	else
	{
		params->pivots[0] = arr[(params->len + (params->len % 3)) / 3];
		params->pivots[1] = arr[2 * (((params->len + (params->len % 3))) / 3)];
		params->pt_size[0] = (params->len + (params->len % 3)) / 3;
		params->pt_size[1] = (2 * (((params->len + (params->len % 3))) / 3))
			- ((params->len + (params->len % 3)) / 3);
		params->pt_size[2] = params->len
			- 2 * (((params->len + (params->len % 3))) / 3);
	}
}

static int	check_if_sorted(t_list *lst, int *arr, t_qs_prs *params)
{
	int	index;
	int	mode;

	mode = params->mode;
	if (mode & UP)
	{
		index = -1;
		while (++index < params->len)
			lst = lst->prev;
	}
	index = 0;
	while (index < params->len)
	{
		if (arr[index] != lst->true_pos && ((mode & A) || (mode == (B + UP))))
			return (0);
		if (arr[params->len - 1 - index] != lst->true_pos
			&& (mode == (B + DOWN)))
			return (0);
		lst = lst->next;
		index++;
	}
	return (1);
}
