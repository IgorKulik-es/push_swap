/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikulik <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 12:19:56 by ikulik            #+#    #+#             */
/*   Updated: 2025/05/28 16:14:57 by ikulik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"
#include "get_next_line_bonus.h"
#include <stdio.h>

static int	run_operations(t_list **lst_a, t_list **lst_b);
static int	check_sorted(t_list *lst, t_qs_prs params);
static void	manipulate(t_list **lst_a, t_list **lst_b, t_list **res, char *op);
static int	check_operation_syntax(char *op);

/* void	print_list(t_list *lst)
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

int	main(int argc, char **argv)
{
	t_qs_prs	params;
	t_list		*lst_a;
	t_list		*lst_b;
	int			is_sorted;

	lst_a = NULL;
	lst_b = NULL;
	is_sorted = 0;
	if (argc == 1)
		return (0);
	lst_a = parse_arguments(argc, argv, &params);
	if (lst_a == NULL)
		return (write(2, "Error\n", 6));
	is_sorted += run_operations(&lst_a, &lst_b);
	is_sorted += check_sorted(lst_a, params);
	if (is_sorted == 0)
		write(1, "OK\n", 3);
	else if (is_sorted == 1)
		write(1, "KO\n", 3);
	else
		write(2, "Error\n", 6);
	lst_clean(&lst_a);
	lst_clean(&lst_b);
	return (0);
}

static int	run_operations(t_list **lst_a, t_list **lst_b)
{
	char	*operation;
	t_list	*temp_res;

	temp_res = NULL;
	operation = get_next_line(0);
	while (operation != NULL)
	{
		if (check_operation_syntax(operation) == 0)
		{
			free(operation);
			lst_clean(&temp_res);
			return (2);
		}
		manipulate(lst_a, lst_b, &temp_res, operation);
		free(operation);
		operation = get_next_line(0);
	}
	lst_clean(&temp_res);
	return (0);
}

static void	manipulate(t_list **lst_a, t_list **lst_b, t_list **res, char *op)
{
	int	len;

	len = ft_strlen(op);
	if ((ft_strncmp(op, "sa\n", len) == 0)
		|| (ft_strncmp(op, "ss\n", len) == 0))
		swap_top(lst_a, res, SA);
	if ((ft_strncmp(op, "sb\n", len) == 0)
		|| (ft_strncmp(op, "ss\n", len) == 0))
		swap_top(lst_b, res, SB);
	if (ft_strncmp(op, "pa\n", len) == 0)
		move_push(lst_b, lst_a, res, PA);
	if (ft_strncmp(op, "pb\n", len) == 0)
		move_push(lst_a, lst_b, res, PB);
	if ((ft_strncmp(op, "ra\n", len) == 0)
		|| (ft_strncmp(op, "rr\n", len) == 0))
		rotate(lst_a, res, RA, 1);
	if ((ft_strncmp(op, "rb\n", len) == 0)
		|| (ft_strncmp(op, "rr\n", len) == 0))
		rotate(lst_b, res, RB, 1);
	if ((ft_strncmp(op, "rra\n", len) == 0)
		|| (ft_strncmp(op, "rrr\n", len) == 0))
		rotate(lst_a, res, RRA, -1);
	if ((ft_strncmp(op, "rrb\n", len) == 0)
		|| (ft_strncmp(op, "rrr\n", len) == 0))
		rotate(lst_b, res, RRB, -1);
}

static int	check_sorted(t_list *lst, t_qs_prs params)
{
	int	counter;

	counter = 0;
	if (lst == NULL)
		return (0);
	while (counter < params.len - 1)
	{
		if (lst->val >= lst->next->val)
			return (1);
		lst = lst->next;
		counter++;
	}
	return (0);
}

static int	check_operation_syntax(char *op)
{
	int	len;

	len = ft_strlen(op);
	if ((ft_strncmp(op, "sa\n", len) == 0)
		|| (ft_strncmp(op, "ss\n", len) == 0))
		return (1);
	if ((ft_strncmp(op, "sb\n", len) == 0)
		|| (ft_strncmp(op, "ss\n", len) == 0))
		return (1);
	if ((ft_strncmp(op, "pa\n", len) == 0)
		|| (ft_strncmp(op, "pb\n", len) == 0))
		return (1);
	if ((ft_strncmp(op, "ra\n", len) == 0)
		|| (ft_strncmp(op, "rr\n", len) == 0))
		return (1);
	if ((ft_strncmp(op, "rb\n", len) == 0)
		|| (ft_strncmp(op, "rr\n", len) == 0))
		return (1);
	if ((ft_strncmp(op, "rra\n", len) == 0)
		|| (ft_strncmp(op, "rrr\n", len) == 0))
		return (1);
	if ((ft_strncmp(op, "rrb\n", len) == 0)
		|| (ft_strncmp(op, "rrr\n", len) == 0))
		return (1);
	return (0);
}
