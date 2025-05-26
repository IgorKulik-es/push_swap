/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   insertion_sort.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikulik <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 14:05:28 by ikulik            #+#    #+#             */
/*   Updated: 2025/05/22 18:44:38 by ikulik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int	find_closest_mismatch(t_list *lst, int size)
{
	int		down;
	int		up;
	t_list	*temp;

	up = 0;
	down = 0;
	temp = lst;
	if (lst->shift != 0)
		return (0);
	while (down <= size / 2 && lst->shift == 0)
	{
		down++;
		lst = lst->next;
	}
	while (up <= size / 2 && temp->shift == 0)
	{
		up++;
		temp = temp->prev;
	}
	if ((up > size / 2) && (down > size / 2))
		return (size);
	if (up < down)
		return (-up);
	return (down);
}

int	find_highest_mismatch(t_list *lst, int size)
{
	int		max[2];
	int		index;
	t_list	*start;

	if (lst->next == lst)
		return (0);
	start = lst;
	max[0] = lst->shift;
	max[1] = 0;
	index = -1;
	lst = lst->next;
	while (++index < size)
	{
		if (lst->shift > max[0])
		{
			max[0] = lst->shift;
			max[1] = index;
		}
		if (lst->shift < -max[0])
		{
			max[0] = -max[0];
			max[1] = index;
		}
		lst = lst->next;
	}
	if (max[0] == 0)
		return (size);
	return (transform_r(max[1], size, 1));
}

void	update_shifts_takeout(t_list *lst, int size)
{
	int	up;
	int	down;
	t_list	*temp_up;
	t_list	*temp_down;

	up = 1;
	down = 0;
	temp_up = lst;
	temp_down = lst;
	while (up <= size / 2)
	{
		temp_up = temp_up->prev;
		if (temp_up->shift < -up)
			temp_up->shift = transform_r(temp_up->shift + 1, size, 1);
		up++;
	}
	while (down <= size / 2)
	{
		if (temp_down->shift > down)
			temp_down->shift = transform_r(temp_down->shift - 1, size, 1);
		temp_down = temp_down->next;
		down++;
	}
}

void	update_shifts_put_in(t_list *lst, int size)
{
	int		up;
	int		down;
	t_list	*temp_up;
	t_list	*temp_down;

	up = 1;
	down = 0;
	temp_up = lst;
	temp_down = lst;
	while (up <= size / 2)
	{
		temp_up = temp_up->prev;
		if (temp_up->shift > up)
			temp_up->shift = transform_r(temp_up->shift - 1, size, 1);
		up++;
	}
	while (down <= size / 2)
	{
		if (temp_down->shift < -down)
			temp_down->shift = transform_r(temp_down->shift + 1, size, 1);
		temp_down = temp_down->next;
		down++;
	}
}

void	check_swap(t_list **lst, t_list **res)
{
	int	swap;

	if ((*lst)->next == *lst)
		return ;
	swap = 0;
	if ((*lst)->shift < 0 && (*lst)->next->shift >= 0)
		swap = 1;
	if ((*lst)->shift <= 0 && (*lst)->next->shift > 0)
		swap = 1;
	if (swap == 1)
	{
		if ((*lst)->shift < 0)
			((*lst)->shift)++;
		if ((*lst)->next->shift > 0)
			((*lst)->next->shift)--;
		swap_top(lst, res, SA);
	}
}

int	insert_sort(t_list **lst_a, t_list **res, int size)
{
	int	next_element;
	t_list	*lst_b;
	int	average_shift ;

	lst_b = NULL;
	average_shift = orderered_check(lst_a, size);
	while (average_shift == size)
	{
		check_swap(lst_a, res);
		average_shift = orderered_check(lst_a, size);
		if (average_shift != size)
			break ;
		next_element = find_closest_mismatch(*lst_a, size);
		//next_element = find_highest_mismatch(*lst_a, size);
		rotate(lst_a, res, RA, next_element);
		move_push(lst_a, &lst_b, res, PA);
		update_shifts_takeout(*lst_a, size);
		rotate(lst_a, res, RA, -lst_b->shift);
		lst_b->shift = 0;
		update_shifts_put_in(*lst_a, size);
		move_push(&lst_b, lst_a, res, PB);
		average_shift = orderered_check(lst_a, size);
	}
	average_shift = transform_r(orderered_check(lst_a, size), size, 1);
	rotate(lst_a, res, RA, -average_shift);
	return (average_shift);
}

void	printf_one_command(int type)
{
	if (type == SA)
		printf("sa\n");
	if (type == SB)
		printf("sb\n");
	if (type == SS)
		printf("ss\n");
	if (type == RA)
		printf("ra\n");
	if (type == RB)
		printf("rb\n");
	if (type == RR)
		printf("rr\n");
	if (type == RRA)
		printf("rra\n");
	if (type == RRB)
		printf("rrb\n");
	if (type == RRR)
		printf("rrr\n");
	if (type == PA)
		printf("pa\n");
	if (type == PB)
		printf("pb\n");
}
