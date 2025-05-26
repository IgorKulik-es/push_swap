/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   small_sorts.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikulik <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 15:47:10 by ikulik            #+#    #+#             */
/*   Updated: 2025/05/26 21:07:51 by ikulik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"


void	rubicks_cube_trick(t_list **lst, t_list **res, t_qs_prs *pars)
{
	if (pars->mode & A)
	{
		rotate(lst, res, RA, 1);
		swap_top(lst, res, SA);
		rotate(lst, res, RRA, -1);
	}
	if (pars->mode & B)
	{
		rotate(lst, res, RB, 1);
		swap_top(lst, res, SB);
		rotate(lst, res, RRB, -1);
	}
}


int	ssort(t_list **lst_a, t_list **lst_b, t_list **res, t_qs_prs *params)
{
	if (params->len == 2)
	{
		sort_pair(lst_a, lst_b, res, *params);
		return (params->len);
	}
	if (params->len == 3 && params->mode == (A | DOWN))
		sort_3_a_d(lst_a, lst_b, res, *params);
	if (params->len == 3 && params->mode == (A | UP))
		sort_3_a_u(lst_a, lst_b, res, *params);
	if (params->len == 3 && params->mode == (B | DOWN))
		sort_3_b_d(lst_a, lst_b, res, *params);
	if (params->len == 3 && params->mode == (B | UP))
		sort_3_b_u(lst_a, lst_b, res, *params);
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

