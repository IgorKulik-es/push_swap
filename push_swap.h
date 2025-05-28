/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikulik <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 18:51:45 by ikulik            #+#    #+#             */
/*   Updated: 2025/05/28 16:57:41 by ikulik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PUSH_SWAP_H
# define PUSH_SWAP_H
# include <stdlib.h>
# include <unistd.h>
# include <limits.h>
# define SA 1
# define SB 2
# define SS 3
# define PA 8
# define PB 16
# define RA 64
# define RB 128
# define RR 192
# define RRA -64
# define RRB -128
# define RRR -192
# define A 64
# define B 128
# define UP 256
# define DOWN 512
# define ORD123 0
# define ORD132 1
# define ORD213 2
# define ORD231 3
# define ORD312 4
# define ORD321 5
# define SMALL 0
# define MED 1
# define BIG 2

typedef struct s_list
{
	int				val;
	int				shift;
	int				true_pos;
	struct s_list	*next;
	struct s_list	*prev;
}	t_list;

typedef struct s_qsort_params
{
	int	pivots[2];
	int	len;
	int	mode;
	int	pt_size[3];
}				t_qs_prs;

size_t	ft_strlen(const char *s);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
size_t	ft_strlcpy(char *dst, const char *src, size_t size);
int		ft_split(char const *s, char c, char ***result);
t_list	*clean_split(char **arr, int words);
t_list	*lst_push_back(t_list **lst, int val, int shift);
t_list	*lst_push_front(t_list **lst, int n);
int		lst_pop(t_list **lst);
int		*lst_clean(t_list **lst);
int		*check_arguments(int argc, char **argv, t_list **lst);
int		process_list(t_list **lst, int *arr, int size);
void	swap_top(t_list **lst, t_list **res, int type);
void	move_push(t_list **lst_1, t_list **lst_2, t_list **res, int type);
void	rotate(t_list **lst, t_list **res, int type, int reps);
void	record_step(t_list **lst, int type, int reps);
int		print_result(t_list *res);
void	insertion_sort(int	*arr, int size);
int		qsort_a(t_list **lst_a, t_list **lst_b, t_list **res, t_qs_prs params);
int		find_pivots(t_list *lst, t_qs_prs *params);
int		ssort(t_list **lst_a, t_list **lst_b, t_list **res, t_qs_prs *params);
void	sort_small(t_list **lst_a, t_list **lst_b, t_list **res, t_qs_prs pars);
int		determine_order(t_list *lst, int mode);
void	sort_3_a_d(t_list **lst_a, t_list **lst_b, t_list **res, t_qs_prs pars);
void	sort_3_a_u(t_list **lst_a, t_list **lst_b, t_list **res, t_qs_prs pars);
void	sort_3_b_d(t_list **lst_a, t_list **lst_b, t_list **res, t_qs_prs pars);
void	sort_3_b_u(t_list **lst_a, t_list **lst_b, t_list **res, t_qs_prs pars);
int		find_pivots(t_list *lst, t_qs_prs *params);
t_list	*parse_arguments(int argc, char **argv, t_qs_prs *params);

#endif
