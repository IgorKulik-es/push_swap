/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_basics.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikulik <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 18:54:53 by ikulik            #+#    #+#             */
/*   Updated: 2025/05/21 14:26:11 by ikulik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

t_list	*lst_push_back(t_list **lst, int val, int shift)
{
	t_list	*new;

	new = malloc(sizeof(t_list));
	if (new == NULL)
		return (NULL);
	new->val = val;
	new->shift = shift;
	if (*lst != NULL)
	{
		new->next = *lst;
		new->prev = (*lst)->prev;
		(*lst)->prev->next = new;
		(*lst)->prev = new;
	}
	else
	{
		new->next = new;
		new->prev = new;
		*lst = new;
	}
	return (*lst);
}

t_list	*lst_push_front(t_list **lst, int n)
{
	t_list	*new;

	new = malloc(sizeof(t_list));
	if (new == NULL)
		return (NULL);
	new->val = n;
	if (*lst != NULL)
	{
		new->next = *lst;
		new->prev = (*lst)->prev;
		(*lst)->prev->next = new;
		(*lst)->prev = new;
		*lst = new;
	}
	else
	{
		new->next = new;
		new->prev = new;
		*lst = new;
	}
	return (*lst);
}

int	lst_pop(t_list **lst)
{
	t_list	*temp;
	int		res;

	temp = *lst;
	if (temp == NULL)
		return (0);
	else
	{
		temp->prev->next = temp->next;
		temp->next->prev = temp->prev;
		res = (*lst)->val;
		if (temp->next == temp)
			*lst = NULL;
		else
			*lst = temp->next;
		free(temp);
	}
	return (res);
}

int	*lst_clean(t_list **lst)
{
	if (lst == NULL)
		return (NULL);
	while (*lst)
	{
		lst_pop(lst);
	}
	return (NULL);
}
