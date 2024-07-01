/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dq.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bammar <bammar@student.42abudhabi.ae>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 22:12:06 by bammar            #+#    #+#             */
/*   Updated: 2024/07/02 03:07:20 by bammar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_DQ_H
# define FT_DQ_H

# include "../libft.h"

typedef struct s_dlist
{
	char				*content;
	struct s_dlist		*next;
	struct s_dlist		*prev;
}				t_dlist;

t_dlist	*ft_dlstnew(char *content);

typedef struct s_dq
{
	t_dlist	*head;
	t_dlist	*tail;
}					t_dq;

t_dq	*ft_dqnew(void);
void	ft_dqadd_first(t_dq *lst, t_dlist *new);
void	ft_dqadd_last(t_dq *lst, t_dlist *new);
void	ft_dqdel_first(t_dq *lst);
void	ft_dqdel_last(t_dq *lst);
void	ft_dqdel(t_dq *dq, void (*del)(void *));
size_t	ft_dqsize(t_dq *lst);
int		ft_dqcontains(t_dq *dq, char *item);

#endif
