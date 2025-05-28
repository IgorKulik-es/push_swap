/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap_main.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikulik <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 18:51:06 by ikulik            #+#    #+#             */
/*   Updated: 2025/05/28 18:15:38 by ikulik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int	main(int argc, char **argv)
{
	t_qs_prs	params;
	t_list		*lst_a;
	t_list		*lst_b;
	t_list		*res;

	lst_a = NULL;
	lst_b = NULL;
	res = NULL;
	lst_a = parse_arguments(argc, argv, &params);
	if (lst_a == NULL)
	{
		lst_clean(&lst_a);
		return (write(2, "Error\n", 6));
	}
	if (params.len <= 5)
		sort_small(&lst_a, &lst_b, &res, params);
	else
		qsort_a(&lst_a, &lst_b, &res, params);
	print_result(res);
	lst_clean(&lst_a);
	lst_clean(&res);
	return (0);
}
