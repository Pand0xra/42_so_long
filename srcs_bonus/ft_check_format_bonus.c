/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_format_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: narginaa <narginaa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/12 18:15:00 by nana              #+#    #+#             */
/*   Updated: 2026/02/13 09:22:19 by narginaa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_bonus.h"

void	ft_check_format(t_game *game)
{
	int	y;
	int	x;
	int	count_x;

	y = 0;
	count_x = game->map.columns;
	while (game->map.full[y])
	{
		x = 0;
		while (game->map.full[y][x])
			x++;
		if (x != count_x)
			ft_error_msg("Map must be a rectangle or a square.\n", game);
		y++;
	}
}
