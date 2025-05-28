/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikulik <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/27 17:36:43 by ikulik            #+#    #+#             */
/*   Updated: 2025/05/28 13:48:56 by ikulik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_BONUS_H
# define GET_NEXT_LINE_BONUS_H
# include <unistd.h>
# include <stdlib.h>
# include <limits.h>
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 30
# else
#  if BUFFER_SIZE < 1
#   error BUFFER SIZE INVALID
#  endif
# endif

typedef struct s_list_g
{
	char			*str;
	int				len;
	struct s_list_g	*next;
	struct s_list_g	*prev;
}				t_list_g;

typedef struct s_gnl_ctrl
{
	int			type_guide;
	int			read_bytes;
	int			nwl;
	char		*result;
}				t_gnl_ctrl;

void		*ft_lstclear(t_list_g **lst);
void		*ft_lstadd_front(t_list_g **lst);
char		*get_next_line(int fd);
t_list_g	*find_position(char *buffer, t_gnl_ctrl *ctrl, int type);
void		clean_buffer(char *buffer, int start);
#endif
