/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   small_sorts.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikulik <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 15:47:10 by ikulik            #+#    #+#             */
/*   Updated: 2025/05/27 19:40:48 by ikulik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	sort_pair(t_list **lst_a, t_list **lst_b, t_list **res, t_qs_prs pars);

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
