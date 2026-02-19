/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nana <nana@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/10 11:25:38 by narginaa          #+#    #+#             */
/*   Updated: 2026/02/17 17:54:24 by nana             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	main(int argc, char **argv)
{
	t_game	*game;

	game = malloc(sizeof(t_game));
	if (!game)
		return (1);
	ft_memset(game, 0, sizeof(t_game));
	ft_init_vars(game);
	ft_parse_cmd_line_args(argc, argv, game);
	ft_init_map(argv[1], game);
	ft_check_map(game);
	ft_flood_fill(game);
	ft_init_mlx(game);
	ft_init_sprites(game);
	ft_render_map(game);
	ft_shell_movement(game);
	mlx_hook(game->win_ptr, KeyPress, KeyPressMask, ft_handle_input, game);
	mlx_hook(game->win_ptr, DestroyNotify, ButtonPressMask, \
ft_close_game, game);
	mlx_hook(game->win_ptr, Expose, ExposureMask, ft_render_map, game);
	mlx_loop(game->mlx_instance);
	ft_free_memory(game);
}
