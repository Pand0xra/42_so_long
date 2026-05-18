/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_close_game.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: narginaa <narginaa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/10 10:58:48 by narginaa          #+#    #+#             */
/*   Updated: 2026/03/04 08:16:36 by narginaa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	ft_close_game(t_game *game)
{
	ft_free_memory(game);
	ft_putstr_fd("CLOSED\n", 2);
	exit(EXIT_SUCCESS);
}

void	ft_error_msg(char *message, t_game *game)
{
	ft_putstr_fd("Error\n", 2);
	ft_putstr_fd(message, 2);
	ft_free_memory(game);
	exit(EXIT_FAILURE);
}

void	ft_victory(t_game *game)
{
	game->movements++;
	ft_shell_movement(game);
	ft_free_memory(game);
	ft_putstr_fd("You win!\n", 2);
	exit(EXIT_SUCCESS);
}
