/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: narginaa <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/21 02:56:04 by narginaa          #+#    #+#             */
/*   Updated: 2026/01/21 02:56:09 by narginaa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	ft_free_list(t_gnl_list **list, t_gnl_list *clean_node, char *clean_s)
{
	t_gnl_list	*tmp;

	if (!*list)
		return ;
	while (*list)
	{
		tmp = (*list)->next;
		free((*list)->stash);
		free(*list);
		*list = tmp;
	}
	if (clean_node && clean_node->stash[0])
		*list = clean_node;
	else
	{
		free(clean_s);
		free(clean_node);
	}
}

void	ft_clean(t_gnl_list **list)
{
	t_gnl_list	*new;
	t_gnl_list	*last;
	int			i;
	int			j;

	last = ft_gnl_lstlast(*list);
	if (!last)
		return ;
	new = malloc(sizeof(t_gnl_list));
	if (new)
		new->stash = malloc(sizeof(char) * BUFFER_SIZE);
	if (!new || (new && !new->stash))
		return (free(new), ft_free_list(list, NULL, NULL));
	i = 0;
	while (last->stash[i] && last->stash[i] != '\n')
		i++;
	i += (last->stash[i] == '\n');
	j = -1;
	while (last->stash[i])
		new->stash[++j] = last->stash[i++];
	new->stash[++j] = '\0';
	new->next = NULL;
	ft_free_list(list, new, new->stash);
}

t_gnl_list	*ft_gnl_lstlast(t_gnl_list *list)
{
	if (!list)
		return (NULL);
	while (list->next)
		list = list->next;
	return (list);
}

void	ft_linecpy(t_gnl_list *list, char *str)
{
	int	i;
	int	j;

	if (!list)
		return ;
	j = 0;
	while (list)
	{
		i = 0;
		while (list->stash[i])
		{
			if (list->stash[i] == '\n')
			{
				str[j++] = '\n';
				str[j] = '\0';
				return ;
			}
			str[j++] = list->stash[i++];
		}
		list = list->next;
	}
	str[j] = '\0';
}

int	ft_len_stash(t_gnl_list *list)
{
	int	i;
	int	count;

	if (!list)
		return (0);
	count = 0;
	while (list)
	{
		i = 0;
		while (list->stash[i])
		{
			if (list->stash[i] == '\n')
			{
				count++;
				return (count);
			}
			count++;
			i++;
		}
		list = list->next;
	}
	return (count);
}
