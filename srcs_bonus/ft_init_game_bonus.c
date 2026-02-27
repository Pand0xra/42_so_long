/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init_game_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: narginaa <narginaa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/10 11:20:38 by narginaa          #+#    #+#             */
/*   Updated: 2026/02/27 09:35:50 by narginaa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_bonus.h"

void	ft_init_vars(t_game *game)
{
	game->player_sprite = RIGHT;
	game->ghosts = NULL;
	game->map.coins = 0;
	game->map.exit = 0;
	game->map.player.count = 0;
	game->map.player.x = 0;
	game->map.player.y = 0;
	game->map.full = NULL;
	game->map.copy = NULL;
	game->mlx_instance = NULL;
	game->win_ptr = NULL;
}

void	ft_init_mlx(t_game *game)
{
	game->mlx_instance = mlx_init();
	if (game->mlx_instance == NULL)
		ft_error_msg("Couldn't find mlx pointer. Try it using a VNC.\n", game);
	mlx_get_screen_size(game->mlx_instance, &screen_width, &screen_height);
	game->win_ptr = mlx_new_window(game->mlx_instance, \
game->map.columns * IMG_WIDTH, game->map.rows * IMG_HEIGHT, "so_long");
	if (game->win_ptr == NULL)
		ft_close_game(game);
}

t_image	ft_new_sprite(void *mlx, char *path, t_game *game)
{
	t_image	sprite;

	sprite.xpm_ptr = mlx_xpm_file_to_image(mlx, path, &sprite.width, \
&sprite.height);
	if (sprite.xpm_ptr == NULL)
		ft_error_msg("Couldn't find a sprite. Does it exist?\n", game);
	return (sprite);
}

void	ft_init_sprites(t_game *game)
{
	void	*mlx;

	mlx = game->mlx_instance;
	game->wall = ft_new_sprite(mlx, WALL_XPM, game);
	game->floor = ft_new_sprite(mlx, FLOOR_XPM, game);
	game->coins = ft_new_sprite(mlx, COINS_XPM, game);
	game->player_front = ft_new_sprite(mlx, PLAYER_FRONT_XPM, game);
	game->player_left = ft_new_sprite(mlx, PLAYER_LEFT_XPM, game);
	game->player_right = ft_new_sprite(mlx, PLAYER_RIGHT_XPM, game);
	game->player_back = ft_new_sprite(mlx, PLAYER_BACK_XPM, game);
	game->exit_open = ft_new_sprite(mlx, EXIT_OPEN_XPM, game);
	game->exit_closed = ft_new_sprite(mlx, EXIT_CLOSED_XPM, game);
	game->ghost_up = ft_new_sprite(mlx, GHOST_UP, game);
	game->ghost_down = ft_new_sprite(mlx, GHOST_DOWN, game);
}
