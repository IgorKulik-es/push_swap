/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manipulations.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikulik <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 18:54:35 by ikulik            #+#    #+#             */
/*   Updated: 2025/05/26 17:10:14 by ikulik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

/* void	checker_transform(t_list **lst_a, t_list **lst_b, char *cmd)
{
	if (ft_strncmp(cmd, "sa", 2) == 0)
		swap_top(lst_a, NULL);
	if (ft_strncmp(cmd, "sb", 2) == 0)
		swap_top(NULL, lst_b);
	if (ft_strncmp(cmd, "ss", 2) == 0)
		swap_top(lst_a, lst_b);
	if (ft_strncmp(cmd, "pa", 2) == 0)
		move(lst_a, lst_b);
	if (ft_strncmp(cmd, "pb", 2) == 0)
		move(lst_b, lst_a);
	if (ft_strncmp(cmd, "ra", 2) == 0)
		rotate(lst_a, NULL, 1);
	if (ft_strncmp(cmd, "rb", 2) == 0)
		rotate(lst_b, NULL, 1);
	if (ft_strncmp(cmd, "rr", 2) == 0)
		rotate(lst_a, lst_b, 1);
	if (ft_strncmp(cmd, "rra", 3) == 0)
		rotate(lst_a, NULL, 0);
	if (ft_strncmp(cmd, "rrb", 3) == 0)
		rotate(lst_b, NULL, 0);
	if (ft_strncmp(cmd, "rrr", 3) == 0)
		rotate(lst_a, lst_b, 0);
} */

/* void	call_operation(t_list **lst_a, t_list **lst_b, int cmd, int reps)
{
	if (cmd & SA)
		swap_top(lst_a);
	if (cmd & SB)
		swap_top(lst_b);
	if (cmd & PA)
		move_to_other(lst_a, lst_b, reps);
	if (cmd & PB)
		move_to_other(lst_b, lst_a, reps);
	if (cmd & RA)
		rotate(lst_a, reps);
	if (cmd & RB)
		rotate(lst_b, reps);
	if (cmd & RRA)
		rotate(lst_a, -reps);
	if (cmd & RRB)
		rotate(lst_b, -reps);
} */

void	swap_top(t_list **lst, t_list **res, int type)
{
	t_list	*top;
	t_list	*bot;

	//printf("swapping %d ", type);
	//printf_one_command(type);
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

	//printf("pushing %d", type);
	//printf_one_command(type);
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

	//printf("rotating %d ", type);
	//printf_one_command(type);
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

void	record_step(t_list **lst, int type, int reps)
{
	int	swapped;

	//printf("recording reps %d ", reps);
	//printf_one_command(type);
	swapped = 0;
	if (*lst != NULL)
	{
		if ((((*lst)->prev->val * 2) == type)
			|| (type * 2) == (*lst)->prev->val)
		{
			if (type == PA || type == PB)
			{
				*lst = (*lst)->prev;
				lst_pop(lst);
				swapped = 1;
			}
			else
			{
				if (reps > (*lst)->prev->shift)
				{
					reps -= (*lst)->prev->shift;
					(*lst)->prev->val += type;
				}
				else if (reps == (*lst)->prev->shift)
				{
					(*lst)->prev->val += type;
					swapped = 1;
				}
				else
				{
					reps = (*lst)->prev->shift - reps;
					(*lst)->prev->shift -= reps;
					(*lst)->prev->val += type;
					type = (*lst)->prev->val - type;
				}
			}
		}
		else if (type == -(*lst)->prev->val)
		{
			if (reps == (*lst)->prev->shift)
			{
				*lst = (*lst)->prev;
				lst_pop(lst);
			}
			else if (reps > (*lst)->prev->shift)
			{
				(*lst)->prev->val = type;
				(*lst)->prev->shift = reps - (*lst)->prev->shift;
			}
			else
				(*lst)->prev->shift -= reps;
			swapped = 1;
		}
	}
	if (swapped == 0)
		lst_push_back(lst, type, reps);
	//printf("after conversion %d ", (*lst)->prev->shift);
	//printf_one_command((*lst)->prev->val);
}
