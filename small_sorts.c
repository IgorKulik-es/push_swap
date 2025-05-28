/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   small_sorts.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikulik <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 15:47:10 by ikulik            #+#    #+#             */
/*   Updated: 2025/05/28 18:15:48 by ikulik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static void	sort_basic_three(t_list **lst, t_list **res);

void	sort_pair(t_list **lst_a, t_list **lst_b, t_list **res, t_qs_prs pars)
{
	if (pars.mode == A + DOWN)
	{
		if ((*lst_a)->true_pos > (*lst_a)->next->true_pos)
			swap_top(lst_a, res, SA);
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

int	ssort(t_list **lst_a, t_list **lst_b, t_list **res, t_qs_prs *params)
{
	if (params->len == 2)
	{
		sort_pair(lst_a, lst_b, res, *params);
		return (params->len);
	}
	if (params->len == 3)
	{
		if (params->mode == (A | DOWN))
			sort_3_a_d(lst_a, lst_b, res, *params);
		if (params->mode == (A | UP))
			sort_3_a_u(lst_a, lst_b, res, *params);
		if (params->mode == (B | DOWN))
			sort_3_b_d(lst_a, lst_b, res, *params);
		if (params->mode == (B | UP))
			sort_3_b_u(lst_a, lst_b, res, *params);
	}
	return (params->len);
}

static void	sort_basic_three(t_list **lst, t_list **res)
{
	int	order;

	order = determine_order(*lst, A | DOWN);
	if (order == ORD132 || order == ORD213 || order == ORD321)
		swap_top (lst, res, SA);
	if (order == ORD132 || order == ORD312)
		rotate(lst, res, RA, 1);
	if (order == ORD231 || order == ORD321)
		rotate(lst, res, RRA, -1);
}

void	throw_45(t_list **lst_a, t_list **lst_b, t_list **res, t_qs_prs pars)
{
	while ((*lst_a)->true_pos != 4 && (*lst_a)->true_pos != 5)
		rotate(lst_a, res, RA, 1);
	move_push(lst_a, lst_b, res, PB);
	if (pars.len == 5)
	{
		while ((*lst_a)->true_pos != 4 && (*lst_a)->true_pos != 5)
			rotate(lst_a, res, RA, 1);
		move_push(lst_a, lst_b, res, PB);
	}
	if ((*lst_b)->true_pos < (*lst_b)->next->true_pos)
		swap_top(lst_b, res, SB);
}

void	sort_small(t_list **lst_a, t_list **lst_b, t_list **res, t_qs_prs pars)
{
	int	index;

	index = 3;
	if (pars.len > 3)
		throw_45(lst_a, lst_b, res, pars);
	sort_basic_three(lst_a, res);
	if (pars.len == 3)
		return ;
	while (index < pars.len)
	{
		move_push(lst_b, lst_a, res, PA);
		index++;
	}
	if ((*lst_a)->true_pos > 3)
		rotate(lst_a, res, RA, 6 - (*lst_a)->true_pos);
	else
		rotate(lst_a, res, RRA, 1 + -(*lst_a)->true_pos);
}
