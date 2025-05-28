/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   step_recorder.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikulik <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 18:01:35 by ikulik            #+#    #+#             */
/*   Updated: 2025/05/28 18:08:02 by ikulik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	optimize_push_or_swap(t_list **lst, int *type, int *reps, int *swapped);
void	optimize_rev_rotations(t_list **lst, int type, int *reps, int *swapped);

void	record_step(t_list **lst, int type, int reps)
{
	int	swapped;

	swapped = 0;
	if (*lst == NULL)
	{
		lst_push_back(lst, type, reps);
		return ;
	}
	if ((((*lst)->prev->val * 2) == type) || (type * 2) == (*lst)->prev->val)
		optimize_push_or_swap(lst, &type, &reps, &swapped);
	else if (type == -(*lst)->prev->val)
		optimize_rev_rotations(lst, type, &reps, &swapped);
	if (swapped == 0)
		lst_push_back(lst, type, reps);
}

void	optimize_push_or_swap(t_list **lst, int *type, int *reps, int *swapped)
{
	if (*type == PA || *type == PB)
	{
		*lst = (*lst)->prev;
		lst_pop(lst);
		*swapped = 1;
		return ;
	}
	if (*reps > (*lst)->prev->shift)
	{
		*reps -= (*lst)->prev->shift;
		(*lst)->prev->val += *type;
	}
	else if (*reps == (*lst)->prev->shift)
	{
		(*lst)->prev->val += *type;
		*swapped = 1;
	}
	else
	{
		*reps = (*lst)->prev->shift - *reps;
		(*lst)->prev->shift -= *reps;
		(*lst)->prev->val += *type;
		*type = (*lst)->prev->val - *type;
	}
}

void	optimize_rev_rotations(t_list **lst, int type, int *reps, int *swapped)
{
	if (*reps == (*lst)->prev->shift)
	{
		*lst = (*lst)->prev;
		lst_pop(lst);
	}
	else if (*reps > (*lst)->prev->shift)
	{
		(*lst)->prev->val = type;
		(*lst)->prev->shift = *reps - (*lst)->prev->shift;
	}
	else
		(*lst)->prev->shift -= *reps;
	*swapped = 1;
}
