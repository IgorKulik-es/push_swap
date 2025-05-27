/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   qsort.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikulik <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 18:11:55 by ikulik            #+#    #+#             */
/*   Updated: 2025/05/27 20:23:01 by ikulik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int	compare_pivots(int pos, t_qs_prs *params);
int	send_sortd(t_list **lst_a, t_list **lst_b, t_list **res, t_qs_prs *pars);
int	send_parts(t_list **lst_1, t_list **lst_2, t_list **res, t_qs_prs pars);
int	qsort_b(t_list **lst_a, t_list **lst_b, t_list **res, t_qs_prs params);

int	qsort_a(t_list **lst_a, t_list **lst_b, t_list **res, t_qs_prs params)
{
	int		len;

	len = params.len;
	if (params.len > 3 && find_pivots(*lst_a, &params))
		return (send_sortd(lst_a, lst_b, res, &params));
	else
	{
		if (params.len <= 3)
			return (ssort(lst_a, lst_b, res, &params));
		send_parts(lst_a, lst_b, res, params);
	}
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

	mode_old = params.mode;
	len = params.len;
	if (params.len > 3 && find_pivots(*lst_b, &params))
		return (send_sortd(lst_a, lst_b, res, &params));
	else
	{
		if (params.len <= 3)
			return (ssort(lst_a, lst_b, res, &params));
		send_parts(lst_b, lst_a, res, params);
	}
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

int	send_parts(t_list **lst_1, t_list **lst_2, t_list **res, t_qs_prs pars)
{
	int	index;
	int	pos;

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
	return (pars.len);
}

int	compare_pivots(int pos, t_qs_prs *params)
{
	if (pos < params->pivots[0])
		return (SMALL);
	if (params->pivots[0] <= pos && pos < params->pivots[1])
		return (MED);
	return (BIG);
}
