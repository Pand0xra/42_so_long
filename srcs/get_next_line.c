/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: narginaa <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/21 02:56:18 by narginaa          #+#    #+#             */
/*   Updated: 2026/01/21 02:56:22 by narginaa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

char	*ft_get_line(t_gnl_list *list)
{
	char	*str;

	str = malloc(sizeof(char) * (ft_len_stash(list) + 1));
	if (!str || !list)
		return (NULL);
	ft_linecpy(list, str);
	return (str);
}

t_gnl_list	*ft_append(t_gnl_list **list, t_gnl_list *last, char *buffer)
{
	t_gnl_list	*new_node;

	new_node = malloc(sizeof(t_gnl_list));
	if (!new_node)
		return (free(buffer), NULL);
	new_node->stash = buffer;
	new_node->next = NULL;
	if (!last)
		*list = new_node;
	else
		last->next = new_node;
	return (new_node);
}

int	ft_found_newline(t_gnl_list *list)
{
	int		i;

	if (!list)
		return (0);
	while (list)
	{
		i = 0;
		while (list->stash[i])
		{
			if (list->stash[i] == '\n')
				return (1);
			i++;
		}
		list = list->next;
	}
	return (0);
}

int	ft_create_list(t_gnl_list **list, int fd)
{
	int			n;
	char		*buffer;
	t_gnl_list	*last;

	last = ft_gnl_lstlast(*list);
	while (!ft_found_newline(last))
	{
		buffer = malloc(BUFFER_SIZE + 1);
		if (!buffer)
			return (0);
		n = read(fd, buffer, BUFFER_SIZE);
		if (n == -1)
			return (free(buffer), 0);
		if (n == 0)
			return (free(buffer), 1);
		buffer[n] = '\0';
		last = ft_append(list, last, buffer);
		if (!last)
			return (0);
	}
	return (1);
}

char	*get_next_line(int fd)
{
	static t_gnl_list	*list;
	char				*next_line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	if (!ft_create_list(&list, fd) || !list)
	{
		ft_free_list(&list, NULL, NULL);
		return (NULL);
	}
	next_line = ft_get_line(list);
	if (!next_line)
	{
		ft_free_list(&list, NULL, NULL);
		return (NULL);
	}
	ft_clean(&list);
	return (next_line);
}
