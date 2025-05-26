/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   qsort.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikulik <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 18:11:55 by ikulik            #+#    #+#             */
/*   Updated: 2025/05/26 21:11:23 by ikulik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */



#include "push_swap.h"

int	compare_pivots(int pos, t_qs_prs *params);
int	send_sortd(t_list **lst_a, t_list **lst_b, t_list **res, t_qs_prs *pars);
int	qsort_b(t_list **lst_a, t_list **lst_b, t_list **res, t_qs_prs params);
void	count_splits(t_qs_prs *params, int *arr);

int	qsort_a(t_list **lst_a, t_list **lst_b, t_list **res, t_qs_prs params)
{
	int		len;

	//printf("Enter qsort_a at %d, len %d\n", params.mode, params.len);
	len = params.len;
	//printf("before split\n");
	//print_list(*lst_a);
	//print_list(*lst_b);
	if (find_pivots(*lst_a, &params))
		return (send_sortd(lst_a, lst_b, res, &params));
	else
	{
		if (params.len <= 3)
			return (ssort(lst_a, lst_b, res, &params));
		send_parts(lst_a, lst_b, res, params);
	}
	//printf("after split\n");
	//print_list(*lst_a);
	//print_list(*lst_b);
	params.len = params.pt_size[2];
	params.mode = (params.mode ^ (UP | DOWN));
	qsort_a(lst_a, lst_b, res, params);
	params.len = params.pt_size[1];
	params.mode = (B | DOWN);
	qsort_b(lst_a, lst_b, res, params);
	params.len = params.pt_size[0];
	params.mode = (B | UP);
	qsort_b(lst_a, lst_b, res, params);
	return (len);
}

int	qsort_b(t_list **lst_a, t_list **lst_b, t_list **res, t_qs_prs params)
{
	int		len;
	int		mode_old;

	//printf("Enter qsort_b at %d, len %d\n", params.mode, params.len);
	mode_old = params.mode;
	len = params.len;
	//printf("before split\n");
	//print_list(*lst_a);
	//print_list(*lst_b);
	if (find_pivots(*lst_b, &params))
		return (send_sortd(lst_a, lst_b, res, &params));
	else
	{
		if (params.len <= 3 /*||  ((params.len == 3) && (params.mode == A + DOWN)) */)
			return (ssort(lst_a, lst_b, res, &params));
		send_parts(lst_b, lst_a, res, params);
	}
	//printf("after split\n");
	//print_list(*lst_a);
	//print_list(*lst_b);
	params.len = params.pt_size[2];
	params.mode = (A | DOWN);
	qsort_a(lst_a, lst_b, res, params);
	params.len = params.pt_size[1];
	params.mode = (A | UP);
	qsort_a(lst_a, lst_b, res, params);
	params.len = params.pt_size[0];
	params.mode = (mode_old ^ (UP | DOWN));
	qsort_b(lst_a, lst_b, res, params);
	return (len);
}

int	send_sortd(t_list **lst_a, t_list **lst_b, t_list **res, t_qs_prs *pars)
{
	int	index;

	//printf("sending sorted %d, at %d\n", pars->len, pars->mode);
	index = 0;
	while (index < pars->len)
	{
		if (pars->mode == (B | DOWN))
		{
			move_push(lst_b, lst_a, res, PA);
		}
		if (pars->mode == (B | UP))
		{
			rotate(lst_b, res, RRB, -1);
			move_push(lst_b, lst_a, res, PA);
		}
		index++;
	}
	if (pars->mode == (A | UP))
		rotate(lst_a, res, RRA, -pars->len);
	return (pars->len);
}

void	send_parts(t_list **lst_1, t_list **lst_2, t_list **res, t_qs_prs pars)
{
	int	index;
	int	pos;

	//printf("sending parts len %d, at %d\n", pars.len, pars.mode);
	index = 0;
	while (index < pars.len)
	{
		if (pars.mode & UP)
		{
			rotate(lst_1, res, pars.mode & (A | B), -1);
		}
		pos = compare_pivots((*lst_1)->true_pos, &pars);
		if ((pars.mode & A) && pos <= MED)
			move_push(lst_1, lst_2, res, PB);
		if ((pars.mode & A) && pos == SMALL)
			rotate(lst_2, res, RB, 1);
		if ((pars.mode & B) && pos > SMALL)
			move_push(lst_1, lst_2, res, PA);
		if ((pars.mode & B) && pos == MED)
			rotate(lst_2, res, RA, 1);
		if (((pars.mode == (A + DOWN)) && pos == BIG)
			|| ((pars.mode == (B + DOWN)) && pos == SMALL))
			rotate(lst_1, res, pars.mode & (A | B), 1);
		index++;
	}
}

int	compare_pivots(int pos, t_qs_prs *params)
{
	if (pos < params->pivots[0])
		return (SMALL);
	if (params->pivots[0] <= pos && pos < params->pivots[1])
		return (MED);
	return (BIG);
}

int	find_pivots(t_list *lst, t_qs_prs *params)
{
	int		*arr;
	int		index;
	t_list	*start;

	index = -1;
	start = lst;
	arr = (int *)malloc(params->len * sizeof(int));
	if (arr == NULL)
		return (0);
	if (params->mode & UP)
		lst = lst->prev;
	while (++index < params->len)
	{
		arr[index] = lst->true_pos;
		lst = lst->next;
		if (params->mode & UP)
			lst = lst->prev->prev;
	}
	stupid_sort(arr, params->len);
	index = check_if_sorted(start, arr, params);
	count_splits(params, arr);
	free(arr);
	return (index);
}

void	count_splits(t_qs_prs *params, int *arr)
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

int	check_if_sorted(t_list *lst, int *arr, t_qs_prs *params)
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

