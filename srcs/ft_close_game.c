/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_close_game.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: narginaa <narginaa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/10 10:58:48 by narginaa          #+#    #+#             */
/*   Updated: 2026/02/13 10:08:27 by narginaa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	ft_close_game(t_game *game)
{
	ft_free_memory(game);
	ft_putstr_fd("CLOSED\n", 1);
	exit(EXIT_SUCCESS);
}

void	ft_error_msg(char *message, t_game *game)
{
	ft_putstr_fd("Error\n", 1);
	ft_putstr_fd(message, 1);
	if (game->map.full)
		ft_free_map(game);
	free(game);
	exit(EXIT_FAILURE);
}

void	ft_victory(t_game *game)
{
	game->movements++;
	ft_shell_movement(game);
	ft_free_memory(game);
	ft_putstr_fd("You win!\n", 1);
	exit(EXIT_SUCCESS);
}
