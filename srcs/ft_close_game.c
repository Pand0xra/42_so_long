/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_close_game.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nana <nana@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/10 10:58:48 by narginaa          #+#    #+#             */
/*   Updated: 2026/02/12 19:01:08 by nana             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	ft_close_game(t_game *game)
{
	char	*str;

	ft_putstr_fd("\n			Movements: ", 1);
	str = ft_itoa(++game->movements);
	if (!str)
		ft_error_msg("Allocation failed.\n", game);
	ft_putstr_fd(str, 1);
	free(str);
	ft_putstr_fd("\n", 1);
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
	char	*str;

	ft_putstr_fd("\n			Movements: ", 1);
	str = ft_itoa(++game->movements);
	if (!str)
		ft_error_msg("Allocation failed.\n", game);
	ft_putstr_fd(str, 1);
	free(str);
	ft_putstr_fd("\n", 1);
	ft_free_memory(game);
	ft_putstr_fd("You win!\n", 1);
	exit(EXIT_SUCCESS);
}

void	ft_loss(t_game *game)
{
	char	*str;

	ft_putstr_fd("\n			Movements: ", 1);
	str = ft_itoa(++game->movements);
	if (!str)
		ft_error_msg("Allocation failed.\n", game);
	ft_putstr_fd(str, 1);
	free(str);
	ft_putstr_fd("\n", 1);
	ft_free_memory(game);
	ft_putstr_fd("You lose!\n", 1);
	exit(EXIT_SUCCESS);
}
