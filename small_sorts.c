/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   small_sorts.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikulik <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 15:47:10 by ikulik            #+#    #+#             */
/*   Updated: 2025/05/26 17:17:54 by ikulik           ###   ########.fr       */
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

void	rubicks_cube_trick(t_list **lst, t_list **res, t_qs_prs *pars)
{
	if (pars->mode & A)
	{
		rotate(lst, res, RA, 1);
		swap_top(lst, res, SA);
		rotate(lst, res, RRA, -1);
	}
}


int	ssort(t_list **lst_a, t_list **lst_b, t_list **res, t_qs_prs *params)
{
	int	order;

	if (params->len == 2)
	{
		sort_pair(lst_a, lst_b, res, *params);
		return (params->len);
	}
	order = determine_order(*lst_a, params->mode);
	if (order == ORD213 || order == ORD312 || order == ORD321)
		swap_top(lst_a, res, SA);
	if (order == ORD132 || order == ORD231)
		rubicks_cube_trick(lst_a, res, params);
	if (determine_order(*lst_a, params->mode) != ORD123)
		ssort(lst_a, lst_b, res, params);
	return (params->len);
}

void	sort_pair(t_list **lst_a, t_list **lst_b, t_list **res, t_qs_prs pars)
{
	if (pars.mode == A + DOWN)
	{
		if ((*lst_a)->true_pos > (*lst_a)->next->true_pos || ((*lst_a)->true_pos == 2))
			swap_top(lst_a, res, SA);
		rotate(lst_a, res, RA, 2);
	}
	if (pars.mode == A + UP)
	{
		rotate(lst_a, res, RRA, -2);
		pars.mode = A + DOWN;
		sort_pair(lst_a, lst_b, res, pars);
	}
	if (pars.mode == B + DOWN)
	{
		move_push(lst_b, lst_a, res, PA);
		move_push(lst_b, lst_a, res, PA);
		pars.mode = A + DOWN;
		sort_pair(lst_a, lst_b, res, pars);
	}
	if (pars.mode == B + UP)
	{
		rotate(lst_b, res, RRB, -2);
		pars.mode = B + DOWN;
		sort_pair(lst_a, lst_b, res, pars);
	}
}
/*
void	sort_one(t_list **lst_a, t_list **lst_b, t_list **res, t_qs_prs *pars)
{
	if (pars->mode == A + DOWN)
		rotate(lst_a, res, RA, 1);
	if (pars->mode == B + DOWN)
		move_push(lst_b, lst_a, res, PA);
	if (pars->mode == B + UP)
	{
		rotate(lst_b, res, RRB, -1);
		move_push(lst_b, lst_a, res, PA);
	}
} */
