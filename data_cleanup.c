/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data_cleanup.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikulik <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 13:09:55 by ikulik            #+#    #+#             */
/*   Updated: 2025/05/27 18:09:20 by ikulik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

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
		iter->shift = 0;
		iter->true_pos = i + 1;
		i++;
	}
	return (average_shift);
}
