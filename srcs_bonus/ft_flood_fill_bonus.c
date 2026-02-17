/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_flood_fill_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nana <nana@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/13 17:26:18 by nana              #+#    #+#             */
/*   Updated: 2026/02/17 18:19:58 by nana             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_bonus.h"

void	ft_free_map_copy(char **map, int rows)
{
	int	i;

	i = 0;
	while (i < rows)
	{
		free(map[i]);
		i++;
	}
	free(map);
}

static void	ft_validate_map(char **map, t_game *game)
{
	int	y;
	int	x;

	y = 0;
	while (map[y])
	{
		x = 0;
		while (map[y][x])
		{
			if (map[y][x] == EXIT || map[y][x] == COINS)
			{
				ft_free_map_copy(map, game->map.rows);
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
	if (map[y][x] == WALL || map[y][x] == EXIT || map[y][x] == 'F')
		return ;
	map[y][x] = 'F';
	ft_fill(map, game, y - 1, x);
	ft_fill(map, game, y + 1, x);
	ft_fill(map, game, y, x - 1);
	ft_fill(map, game, y, x + 1);
}

void	ft_flood_fill(t_game *game)
{
	char	**map_copy;
	int		i;

	map_copy = malloc(sizeof(char *) * (game->map.rows + 1));
	if (!map_copy)
		ft_error_msg("Memory allocation failed for map copy.\n", game);
	i = 0;
	while (i < game->map.rows)
	{
		map_copy[i] = ft_strdup(game->map.full[i]);
		if (!map_copy[i])
		{
			ft_free_map_copy(map_copy, i);
			ft_error_msg("Memory allocation failed for map row copy.\n", game);
		}
		i++;
	}
	map_copy[i] = NULL;
	ft_fill(map_copy, game, game->map.player.y, game->map.player.x);
	ft_validate_map(map_copy, game);
	ft_free_map_copy(map_copy, game->map.rows);
}
