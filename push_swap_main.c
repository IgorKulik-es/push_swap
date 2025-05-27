/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap_main.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikulik <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 18:51:06 by ikulik            #+#    #+#             */
/*   Updated: 2025/05/27 20:20:58 by ikulik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"
#include <stdio.h>

static t_list	*parse_arguments(int argc, char **argv, t_qs_prs *params);

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
		return (write(2, "Error\n", 6));
	qsort_a(&lst_a, &lst_b, &res, params);
	print_result(res);
	lst_clean(&lst_a);
	lst_clean(&res);
	return (0);
}

static t_list	*parse_arguments(int argc, char **argv, t_qs_prs *params)
{
	char		**args_par;
	int			*arr;
	int			words;
	t_list		*lst_a;

	args_par = NULL;
	lst_a = NULL;
	if (argc == 2)
		words = ft_split(argv[1], ' ', &args_par);
	else
	{
		words = argc - 1;
		args_par = &argv[1];
	}
	arr = check_arguments(words, args_par, &lst_a);
	if (arr == NULL)
		return (NULL);
	params->len = words;
	params->mode = A | DOWN;
	process_list(&lst_a, arr, words);
	free(arr);
	if (argc == 2)
		clean_split(args_par, words);
	return (lst_a);
}

/* void	print_arr(int *arr, int size)
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
} */
