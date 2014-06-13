/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mle-roy <mle-roy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/12/10 18:04:43 by mle-roy           #+#    #+#             */
/*   Updated: 2014/03/25 20:33:02 by dcohen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

static void		free_lst(void *content, size_t t)
{
	(void)t;
	if (content != NULL)
		free(content);
}

t_list			*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem))
{
	t_list		*tmp;
	t_list		*new;
	t_list		*start;
	t_list		*tmp2;

	start = NULL;
	while (lst)
	{
		tmp = f(lst);
		if ((new = ft_lstnew(tmp->content, tmp->content_size)) == NULL)
		{
			ft_lstdel(&start, free_lst);
			return (NULL);
		}
		if (start == NULL)
			start = new;
		else
			tmp2->next = new;
		tmp2 = new;
		lst = lst->next;
	}
	return (start);
}
