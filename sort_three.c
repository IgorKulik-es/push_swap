/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_three.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikulik <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 19:50:32 by ikulik            #+#    #+#             */
/*   Updated: 2025/05/26 21:15:35 by ikulik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int	determine_order(t_list *lst, int mode)
{
	int	nums[3];

	if (mode & UP)
		lst = lst->prev->prev->prev;
	nums[0] = lst->true_pos;
	nums[1] = lst->next->true_pos;
	nums[2] = lst->next->next->true_pos;
	if (nums[0] < nums[1] && nums[1] < nums[2])
		return (ORD123);
	if (nums[0] < nums[1] && nums[1] > nums[2] && nums[0] < nums[2])
		return (ORD132);
	if (nums[0] > nums[1] && nums[1] < nums[2] && nums[2] > nums[0])
		return (ORD213);
	if (nums[0] < nums[1] && nums[1] > nums[2] && nums[0] > nums[2])
		return (ORD231);
	if (nums[0] > nums[1] && nums[1] < nums[2] && nums[0] > nums[2])
		return (ORD312);
	if (nums[0] > nums[1] && nums[1] > nums[2])
		return (ORD321);
	return (0);
}


void	sort_3_a_d(t_list **lst_a, t_list **lst_b, t_list **res, t_qs_prs pars)
{
 	int order;

	order = determine_order(*lst_a, pars.mode);
	if (pars.mode == (A | DOWN))
	{
		if (order == ORD132 || order == ORD231)
			rubicks_cube_trick(lst_a, res, &pars);
		if (order == ORD213 || order == ORD312 || order == ORD321)
			swap_top(lst_a, res, SA);
		if (determine_order(*lst_a, pars.mode) != ORD123)
			sort_3_a_d(lst_a, lst_b, res, pars);
	}
}

void	sort_3_a_u(t_list **lst_a, t_list **lst_b, t_list **res, t_qs_prs pars)
{
	int	order;

	order = determine_order(*lst_a, pars.mode);
	if (order == ORD123)
		rotate(lst_a, res, RRA, -3);
	if (order == ORD132)
	{
		rotate(lst_a, res, RRA, -2);
		swap_top(lst_a, res, SA);
		rotate(lst_a, res, RRA, -1);
	}
	if (order == ORD213)
	{
		rotate(lst_a, res, RRA, -3);
		swap_top(lst_a, res, SA);
	}
	if (order == ORD231)
	{
		rotate(lst_a, res, RRA, -1);
		move_push(lst_a, lst_b, res, PB);
		rotate(lst_a, res, RRA, -2);
		move_push(lst_b, lst_a, res, PA);
	}
	if (order == ORD312)
	{
		rotate(lst_a, res, RRA, -2);
		move_push(lst_a, lst_b, res, PB);
		rotate(lst_a, res, RRA, -1);
		swap_top(lst_a, res, SA);
		move_push(lst_b, lst_a, res, PA);
	}
	if (order == ORD321)
	{
		rotate(lst_a, res, RRA, -1);
		move_push(lst_a, lst_b, res, PB);
		rotate(lst_a, res, RRA, -2);
		swap_top(lst_a, res, SA);
		move_push(lst_b, lst_a, res, PA);
	}
}

void	sort_3_b_d(t_list **lst_a, t_list **lst_b, t_list **res, t_qs_prs pars)
{
	int	order;

	order = determine_order(*lst_a, pars.mode);
	if (order == ORD321)
	{
		move_push(lst_b, lst_a, res, PA);
		move_push(lst_b, lst_a, res, PA);
		move_push(lst_b, lst_a, res, PA);
	}
	if (order == ORD312)
	{
		move_push(lst_b, lst_a, res, PA);
		swap_top(lst_b, res, SB);
		move_push(lst_b, lst_a, res, PA);
		move_push(lst_b, lst_a, res, PA);
	}
	if (order == ORD231)
	{
		swap_top(lst_b, res, SB);
		move_push(lst_b, lst_a, res, PA);
		move_push(lst_b, lst_a, res, PA);
		move_push(lst_b, lst_a, res, PA);
	}
	if (order == ORD213)
	{
		rotate(lst_b, res, RB, 1);
		swap_top(lst_b, res, SB);
		move_push(lst_b, lst_a, res, PA);
		rotate(lst_b, res, RRB, -1);
		move_push(lst_b, lst_a, res, PA);
		move_push(lst_b, lst_a, res, PA);
	}
	if (order == ORD132)
	{
		rotate(lst_b, res, RB, 1);
		move_push(lst_b, lst_a, res, PA);
		move_push(lst_b, lst_a, res, PA);
		rotate(lst_b, res, RRB, -1);
		move_push(lst_b, lst_a, res, PA);
	}
	if (order == ORD123)
	{
		rotate(lst_b, res, RB, 1);
		swap_top(lst_b, res, SB);
		move_push(lst_b, lst_a, res, PA);
		move_push(lst_b, lst_a, res, PA);
		rotate(lst_b, res, RRB, -1);
		move_push(lst_b, lst_a, res, PA);
	}
}

void	sort_3_b_u(t_list **lst_a, t_list **lst_b, t_list **res, t_qs_prs pars)
{
	int	order;

	order = determine_order(*lst_a, pars.mode);
	if (order == ORD321)
	{
		rotate(lst_b, res, RRA, -3);
		move_push(lst_b, lst_a, res, PA);
		move_push(lst_b, lst_a, res, PA);
		move_push(lst_b, lst_a, res, PA);
	}
	if (order == ORD312)
	{
		rotate(lst_b, res, RRA, -1);
		move_push(lst_b, lst_a, res, PA);
		rotate(lst_b, res, RRA, -2);
		swap_top(lst_b, res, SB);
		move_push(lst_b, lst_a, res, PA);
		move_push(lst_b, lst_a, res, PA);
	}
	if (order == ORD231)
	{
		rotate(lst_b, res, RRA, -2);
		swap_top(lst_b, res, SB);
		move_push(lst_b, lst_a, res, PA);
		rotate(lst_b, res, RRA, -1);
		move_push(lst_b, lst_a, res, PA);
		move_push(lst_b, lst_a, res, PA);
	}
	if (order == ORD213)
	{
		rotate(lst_b, res, RRB, -1);
		move_push(lst_b, lst_a, res, PA);
		rotate(lst_b, res, RRB, -2);
		swap_top(lst_b, res, SB);
		move_push(lst_b, lst_a, res, PA);
		move_push(lst_b, lst_a, res, PA);
	}
	if (order == ORD132)
	{
		rotate(lst_b, res, RRB, -2);
		swap_top(lst_b, res, SB);
		move_push(lst_b, lst_a, res, PA);
		move_push(lst_b, lst_a, res, PA);
		rotate(lst_b, res, RRB, -1);
		move_push(lst_b, lst_a, res, PA);
	}
	if (order == ORD123)
	{
		rotate(lst_b, res, RRB, -1);
		move_push(lst_b, lst_a, res, PA);
		rotate(lst_b, res, RRB, -1);
		move_push(lst_b, lst_a, res, PA);
		rotate(lst_b, res, RRB, -1);
		move_push(lst_b, lst_a, res, PA);
	}
}
