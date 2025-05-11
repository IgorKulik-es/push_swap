/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   qsort.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikulik <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/11 09:50:06 by ikulik            #+#    #+#             */
/*   Updated: 2025/05/11 09:50:06 by ikulik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#define A 32
#define B 64
#define UP 128
#define DOWN 256

#include "push_swap.h"




int	*qsort_a(t_list **lst_a, t_list **lst_b, int size, int mode)
{
	int		len;
	int		pivots[2];

	len = 0;
	len = count_section_length(*lst_a, size, mode);
	if (find_pivots(*lst_a, pivots, len, mode))
		send_them_out();
	if (len <= 3)
		return (sort_small(lst_a, len, mode));
	
}

int	count_section_length(t_list *lst, int size, int mode)
{
	int		len;
	int		flag;
	t_list	*iter;

	len = 0;
	flag = 1;
	iter = lst;
	if (mode == UP)
		iter = iter->prev;
	if (mode == UP)
		while ((iter != lst->prev || flag) && iter->true_pos < size)
		{
			iter = iter->prev;
			flag = 0;
			len++;
		}
	if (mode == DOWN)
		while ((iter != lst || flag) && iter->true_pos < size)
		{
			iter = iter->next;
			flag = 0;
			len++;
		}
	return (len);
}

int	find_pivots(t_list *lst, int *pivots, int len, int mode)
{
	int		*arr;
	int		index;
	t_list	*start;

	index = -1;
	start = lst;
	arr = (int *)malloc(len * sizeof(int));
	if (arr == NULL)
		return ;
	if (mode == UP)
		lst = lst->prev;
	while (++index < len)
	{
		arr[index] = lst->true_pos;
		lst = lst->next;
		if (mode == UP)
			lst = lst->prev->prev;
	}
	stupid_sort(arr, len);	
	index = check_if_sorted(start, arr, len, mode);
	len = (len + (len % 3)) / 3;
	pivots[0] = arr[len - 1];
	pivots[1] = arr[2 * len - 1];
	free(arr);
	return (index);
}

int	check_if_sorted(t_list *lst, int *arr, int len, int mode)
{
	int	index;

	if (mode & UP)
	{
		index = -1;
		while (++index < len)
			lst = lst->prev;
	}
	index = 0;
	while (index < len)
	{
		if (arr[index] != lst->true_pos && (((mode & A) && (mode & DOWN)) 
			|| ((mode & B) && (mode & UP))))
			return (0);
		if (arr[len - 1 - index] != lst->true_pos && ((mode & B) && (mode & DOWN))
			|| ((mode & A) && (mode & UP)))
			return (0);
		lst = lst->next;
		index++;
	}
	return (1);
}
