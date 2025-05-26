/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap_main.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikulik <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 18:51:06 by ikulik            #+#    #+#             */
/*   Updated: 2025/05/26 19:11:05 by ikulik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"
#include <stdio.h>

void	print_arr(int *arr, int size)
{
	int	i;

	for(i = 0; i < size; i++)
		printf("%d ", arr[i]);
	printf("\n");
}

void	print_list(t_list *lst)
{
	t_list	*temp;
	int	flag = 1;

	if (lst == NULL)
	{
		printf("Empty list\n");
		return ;
	}
	temp = lst;
	while (temp != lst || flag)
	{
		printf("%d ", temp->val);
		flag = 0;
		temp = temp->next;
	}
	printf("\n");
}

int	main(int argc, char **argv)
{
	int			index;
	int			average;
	char		**args_par;
	int			*arr;
	int			words;
	t_qs_prs	params;
	t_list		*lst_a;
	t_list		*lst_b;
	t_list		*res;

	index = 0;
	lst_a = NULL;
	lst_b = NULL;
	args_par = NULL;
	res = NULL;
	if (argc == 2)
		words = ft_split(argv[1], ' ', &args_par);
	else
	{
		words = argc - 1;
		args_par = &argv[1];
	}
	//printf("words %d\n", words);
	arr = check_arguments(words, args_par, &lst_a);
	//print_arr(arr, words);
	if (arr == NULL)
		return (write(2, "Error\n", 6));
	params.len = words;
	params.mode = A | DOWN;
	average = process_list(&lst_a, arr, words);
/* 	printf("up %d down %d comb %d \n", A|DOWN, A|UP, A|((A|UP) ^ (UP|DOWN)));
	printf("pivots check %d\n", find_pivots(lst_a, &params));
	printf("starting pivots %d %d, sizes %d %d %d len %d\n", params.pivots[0], params.pivots[1], params.pt_size[0]
		, params.pt_size[1], params.pt_size[2], params.len); */
	qsort_a(&lst_a, &lst_b, &res, params);
	index = print_result(res);
	//print_list(lst_a);
	//print_list(lst_b);
	//printf("moves %d\n", index);
	lst_clean(&lst_a);
	lst_clean(&res);
	if (argc== 2)
		clean_split(args_par, words);
	free(arr);
	return (0);
}
