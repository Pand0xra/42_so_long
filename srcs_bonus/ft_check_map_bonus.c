/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_map_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: narginaa <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/10 11:20:00 by narginaa          #+#    #+#             */
/*   Updated: 2026/02/10 11:20:11 by narginaa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_bonus.h"

void	ft_check_rows(t_game *game)
{
	int	i;

	i = 0;
	while (i < game->map.rows)
	{
		if (game->map.full[i][0] != WALL)
		{
			ft_free_map(game);
			ft_error_msg("Invalid map. \
		Missing wall from the right side of the map or invalid line.\n", game);
		}
		else if (game->map.full[i][game->map.columns - 1] != WALL)
		{
			ft_free_map(game);
			ft_error_msg("Invalid map. \
		Missing wall from the left side of the map or invalid line\n", game);
		}
		i++;
	}
}

void	ft_check_columns(t_game *game)
{
	int	i;

	i = 0;
	while (i < game->map.columns)
	{
		if (game->map.full[0][i] != WALL)
			ft_error_msg("Invalid map.There's a wall missing on the first \
row.\n", game);
		else if (game->map.full[game->map.rows - 1][i] != WALL)
			ft_error_msg("Invalid map. There's a wall missing on the last \
row.\n", game);
		i++;
	}
}

void	ft_count_map_param(t_game *game)
{
	int	x;
	int	y;

	y = 0;
	while (y < game->map.rows)
	{
		x = 0;
		while (x < game->map.columns)
		{
			if (!ft_strchr("CEP01G", game->map.full[y][x]))
				ft_error_msg("Invalid map. Not expected map paramater.", game);
			else if (game->map.full[y][x] == PLAYER)
			{
				game->map.player.y = y;
				game->map.player.x = x;
				game->map.player.count++;
			}
			else if (game->map.full[y][x] == COINS)
				game->map.coins++;
			else if (game->map.full[y][x] == EXIT)
				game->map.exit++;
			x++;
		}
		y++;
	}
}

void	ft_check_map_param(t_game *game)
{
	if (game->map.coins == 0)
		ft_error_msg("Invalid map. Coins are missing.\n", game);
	else if (game->map.player.count != 1)
		ft_error_msg("Invalid map. It's a single player game...\n", game);
	else if (game->map.exit == 0)
		ft_error_msg("Invalid map. There's no exit.\n", game);
}

void	ft_check_map(t_game *game)
{
	ft_check_rows(game);
	ft_check_columns(game);
	ft_count_map_param(game);
	ft_check_map_param(game);
}
