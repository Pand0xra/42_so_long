/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: narginaa <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/10 11:21:44 by narginaa          #+#    #+#             */
/*   Updated: 2026/02/10 11:21:46 by narginaa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_bonus.h"

void	ft_render_ghost(t_game *game, int y, int x)
{
	if (game->ghost_anim_frame == 0)
		ft_render_sprite(game, game->ghost_up, y, x);
	else
		ft_render_sprite(game, game->ghost_down, y, x);
}

int	ft_anim_ghost(t_game *game)
{
	if (game->ghost_anim_counter < GHOST_ANIM_DELAY)
	{
		game->ghost_anim_counter++;
		return (0);
	}
	ft_move_ghosts(game);
	game->ghost_anim_counter = 0;
	if (game->ghost_anim_frame == 0)
		game->ghost_anim_frame = 1;
	else
		game->ghost_anim_frame = 0;
	ft_render_map(game);
	return (0);
}

int	main(int argc, char **argv)
{
	t_game	*game;

	game = malloc(sizeof(t_game));
	if (!game)
		return (1);
	ft_memset(game, 0, sizeof(game));
	ft_parse_cmd_line_args(argc, argv, game);
	ft_init_map(argv[1], game);
	ft_init_vars(game);
	ft_check_map(game);
	ft_flood_fill(game);
	ft_init_ghosts(game);
	ft_init_mlx(game);
	ft_init_sprites(game);
	ft_render_map(game);
	mlx_hook(game->win_ptr, KeyPress, KeyPressMask, ft_handle_input, game);
	mlx_hook(game->win_ptr, DestroyNotify, ButtonPressMask, ft_close_game, \
game);
	mlx_hook(game->win_ptr, Expose, ExposureMask, ft_render_map, game);
	mlx_loop_hook(game->mlx_instance, ft_anim_ghost, game);
	mlx_loop(game->mlx_instance);
	ft_free_memory(game);
}
