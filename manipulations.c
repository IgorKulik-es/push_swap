/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manipulations.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikulik <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 18:54:35 by ikulik            #+#    #+#             */
/*   Updated: 2025/05/27 18:02:54 by ikulik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	swap_top(t_list **lst, t_list **res, int type)
{
	t_list	*top;
	t_list	*bot;

	if (*lst == NULL)
		return ;
	if ((*lst)->next == *lst)
		return ;
	top = *lst;
	bot = (*lst)->next;
	if (bot->next == top)
	{
		*lst = bot;
		record_step(res, type, 1);
		return ;
	}
	top->prev->next = bot;
	bot->next->prev = top;
	bot->prev = top->prev;
	top->next = bot->next;
	bot->next = top;
	top->prev = bot;
	*lst = bot;
	record_step(res, type, 1);
}

void	move_push(t_list **lst_1, t_list **lst_2, t_list **res, int type)
{
	int	temp_val;
	int	temp_shift;
	int	temp_true_pos;

	if (type != 0)
	{
		if (*lst_1 == NULL)
			return ;
		temp_val = (*lst_1)->val;
		temp_shift = (*lst_1)->shift;
		temp_true_pos = (*lst_1)->true_pos;
		lst_pop(lst_1);
		lst_push_front(lst_2, temp_val);
		(*lst_2)->shift = temp_shift;
		(*lst_2)->true_pos = temp_true_pos;
	}
	record_step(res, type, 1);
}

void	rotate(t_list **lst, t_list **res, int type, int reps)
{
	int	counter;

	counter = reps;
	while (counter > 0)
	{
		*lst = (*lst)->next;
		counter--;
	}
	while (counter < 0)
	{
		*lst = (*lst)->prev;
		counter++;
	}
	if (((type == RA) || (type == RB)) && (reps < 0))
		type = -type;
	if (reps < 0)
		reps = -reps;
	record_step(res, type, reps);
}
