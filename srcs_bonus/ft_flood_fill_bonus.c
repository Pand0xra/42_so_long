/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_flood_fill_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: narginaa <narginaa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/13 17:26:18 by nana              #+#    #+#             */
/*   Updated: 2026/02/27 09:14:34 by narginaa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_bonus.h"

void	ft_free_map_copy(t_game *game)
{
	int	i;

	i = 0;
	while (i < game->map.rows)
	{
		free(game->map.copy[i]);
		i++;
	}
	free(game->map.copy);
}

static void	ft_validate_map(t_game *game)
{
	int	y;
	int	x;

	y = 0;
	while (game->map.copy[y])
	{
		x = 0;
		while (game->map.copy[y][x])
		{
			if (game->map.copy[y][x] == EXIT || game->map.copy[y][x] == COINS)
			{
				ft_free_map_copy(game);
				ft_error_msg("Invalid map. \
					The exit and/or coins aren't reachable.\n", game);
			}
			x++;
		}
		y++;
	}
}

void	ft_fill(char **map, t_game *game, int y, int x)
{
	if (y < 0 || x < 0 || y >= game->map.rows || x >= game->map.columns)
		return ;
	if (map[y][x] == WALL || map[y][x] == 'F')
		return ;
	if (map[y][x] == EXIT)
	{
		map[y][x] = 'F';
		return ;
	}
	map[y][x] = 'F';
	ft_fill(map, game, y - 1, x);
	ft_fill(map, game, y + 1, x);
	ft_fill(map, game, y, x - 1);
	ft_fill(map, game, y, x + 1);
}

void	ft_flood_fill(t_game *game)
{
	int		i;

	game->map.copy = ft_calloc(game->map.rows + 1, sizeof(char *));
	if (!game->map.copy)
		ft_error_msg("Memory allocation failed for map copy.\n", game);
	i = 0;
	while (i < game->map.rows)
	{
		game->map.copy[i] = ft_strdup(game->map.full[i]);
		if (!game->map.copy[i])
		{
			ft_free_map_copy(game);
			ft_error_msg("Memory allocation failed for map row copy.\n", game);
		}
		i++;
	}
	game->map.copy[i] = NULL;
	ft_fill(game->map.copy, game, game->map.player.y, game->map.player.x);
	ft_validate_map(game);
	ft_free_map_copy(game);
}
