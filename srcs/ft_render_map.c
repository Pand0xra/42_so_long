/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_render_map.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: narginaa <narginaa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/10 10:59:45 by narginaa          #+#    #+#             */
/*   Updated: 2026/02/13 10:09:43 by narginaa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	ft_render_sprite(t_game *game, t_image sprite, int y, int x)
{
	mlx_put_image_to_window(game->mlx_instance, game->win_ptr, \
sprite.xpm_ptr, x * sprite.width, y * sprite.height);
}

void	ft_render_player(t_game *game, int y, int x)
{
	if (game->player_sprite == FRONT)
		ft_render_sprite(game, game->player_front, y, x);
	else if (game->player_sprite == LEFT)
		ft_render_sprite(game, game->player_left, y, x);
	else if (game->player_sprite == RIGHT)
		ft_render_sprite(game, game->player_right, y, x);
	else if (game->player_sprite == BACK)
		ft_render_sprite(game, game->player_back, y, x);
}

void	ft_identify_sprite(t_game *game, int y, int x)
{
	char	parameter;

	parameter = game->map.full[y][x];
	if (parameter == WALL)
		ft_render_sprite(game, game->wall, y, x);
	else if (parameter == FLOOR)
		ft_render_sprite(game, game->floor, y, x);
	else if (parameter == COINS)
		ft_render_sprite(game, game->coins, y, x);
	else if (parameter == EXIT)
	{
		if (game->map.coins == 0)
			ft_render_sprite(game, game->exit_open, y, x);
		else
			ft_render_sprite(game, game->exit_closed, y, x);
	}
	else if (parameter == PLAYER)
		ft_render_player(game, y, x);
}

void	ft_shell_movement(t_game *game)
{
	char	*str;

	ft_putstr_fd("\n			Movements: ", 1);
	str = ft_itoa(game->movements);
	if (!str)
		ft_error_msg("Allocation failed.\n", game);
	ft_putstr_fd(str, 1);
	free(str);
	ft_putstr_fd("\n", 1);
}
int	ft_render_map(t_game *game)
{
	int	x;
	int	y;

	y = 0;
	while (y < game->map.rows)
	{
		x = 0;
		while (x < game->map.columns)
		{
			ft_identify_sprite(game, y, x);
			x++;
		}
		y++;
	}
	return (0);
}