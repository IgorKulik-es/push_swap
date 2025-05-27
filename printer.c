/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printer.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikulik <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/10 18:22:16 by ikulik            #+#    #+#             */
/*   Updated: 2025/05/27 19:40:11 by ikulik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static void	print_one_command(int type)
{
	if (type == SA)
		write(1, "sa\n", 3);
	if (type == SB)
		write(1, "sb\n", 3);
	if (type == SS)
		write(1, "ss\n", 3);
	if (type == RA)
		write(1, "ra\n", 3);
	if (type == RB)
		write(1, "rb\n", 3);
	if (type == RR)
		write(1, "rr\n", 3);
	if (type == RRA)
		write(1, "rra\n", 4);
	if (type == RRB)
		write(1, "rrb\n", 4);
	if (type == RRR)
		write(1, "rrr\n", 4);
	if (type == PA)
		write(1, "pa\n", 3);
	if (type == PB)
		write(1, "pb\n", 3);
}

static void	print_commands(int type, int reps)
{
	while (reps > 0)
	{
		print_one_command(type);
		reps--;
	}
}

int	print_result(t_list *res)
{
	t_list	*iter;
	int		counter;

	iter = res;
	counter = 0;
	if (iter == NULL)
		return (0);
	print_commands(iter->val, iter->shift);
	counter += iter->shift;
	iter = iter->next;
	while (iter != res)
	{
		print_commands(iter->val, iter->shift);
		counter += iter->shift;
		iter = iter->next;
	}
	return (counter);
}
