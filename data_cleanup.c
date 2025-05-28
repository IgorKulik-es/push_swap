/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data_cleanup.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikulik <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 13:09:55 by ikulik            #+#    #+#             */
/*   Updated: 2025/05/28 16:12:36 by ikulik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int	*create_array(t_list **lst, int size)
{
	int		*res;
	int		index;
	t_list	*iter;

	if (lst == NULL)
		return (NULL);
	iter = *lst;
	index = 0;
	res = malloc(size * sizeof(int));
	if (res == NULL)
		return (NULL);
	while (index < size)
	{
		res[index] = iter->val;
		iter = iter->next;
		index++;
	}
	return (res);
}

int	process_list(t_list **lst, int *arr, int size)
{
	int		i;
	int		j;
	int		average_shift;
	t_list	*iter;

	i = 0;
	average_shift = 0;
	if (arr == NULL)
		return (0);
	while (i < size)
	{
		j = 0;
		iter = *lst;
		while (iter->val != arr[i] && j < size)
		{
			iter = iter->next;
			j++;
		}
		iter->shift = 0;
		iter->true_pos = i + 1;
		i++;
	}
	return (average_shift);
}

t_list	*parse_arguments(int argc, char **argv, t_qs_prs *params)
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
	params->len = words;
	params->mode = A | DOWN;
	process_list(&lst_a, arr, words);
	if (argc == 2)
		clean_split(args_par, words);
	if (arr == NULL)
		return (NULL);
	free(arr);
	return (lst_a);
}
