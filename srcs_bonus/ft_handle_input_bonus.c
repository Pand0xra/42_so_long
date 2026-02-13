/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_handle_input_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: narginaa <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/10 11:19:38 by narginaa          #+#    #+#             */
/*   Updated: 2026/02/10 11:19:40 by narginaa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_bonus.h"

void	ft_player_move(t_game *game, int new_x, int new_y, int player_sprite)
{
	int	last_x;
	int	last_y;

	game->player_sprite = player_sprite;
	last_x = game->map.player.x;
	last_y = game->map.player.y;
	if (game->map.full[new_y][new_x] == GHOST)
		ft_loss(game);
	if (game->map.full[new_y][new_x] == EXIT && game->map.coins == 0)
		ft_victory(game);
	else if (game->map.full[new_y][new_x] == FLOOR
	|| game->map.full[new_y][new_x] == COINS)
	{
		game->map.full[last_y][last_x] = FLOOR;
		if (game->map.full[new_y][new_x] == COINS)
			game->map.coins--;
		game->map.player.x = new_x;
		game->map.player.y = new_y;
		game->map.full[new_y][new_x] = PLAYER;
		game->movements++;
		ft_render_map(game);
	}
}

int	ft_handle_input(int keysym, t_game *game)
{
	if (keysym == KEY_UP || keysym == KEY_W)
		ft_player_move(game, game->map.player.x, game->map.player.y - 1, BACK);
	else if (keysym == KEY_LEFT || keysym == KEY_A)
		ft_player_move(game, game->map.player.x - 1, game->map.player.y, LEFT);
	else if (keysym == KEY_RIGHT || keysym == KEY_D)
		ft_player_move(game, game->map.player.x + 1, game->map.player.y, RIGHT);
	else if (keysym == KEY_DOWN || keysym == KEY_S)
		ft_player_move(game, game->map.player.x, game->map.player.y + 1, FRONT);
	else if (keysym == KEY_ESC || keysym == KEY_Q)
		ft_close_game(game);
	return (0);
}
