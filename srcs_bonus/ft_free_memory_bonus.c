/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_memory_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: narginaa <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/10 11:18:29 by narginaa          #+#    #+#             */
/*   Updated: 2026/02/10 11:18:31 by narginaa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_bonus.h"

void	ft_destroy_image(t_game *game)
{
	mlx_destroy_image(game->mlx_instance, game->wall.xpm_ptr);
	mlx_destroy_image(game->mlx_instance, game->floor.xpm_ptr);
	mlx_destroy_image(game->mlx_instance, game->coins.xpm_ptr);
	mlx_destroy_image(game->mlx_instance, game->player_front.xpm_ptr);
	mlx_destroy_image(game->mlx_instance, game->player_left.xpm_ptr);
	mlx_destroy_image(game->mlx_instance, game->player_right.xpm_ptr);
	mlx_destroy_image(game->mlx_instance, game->player_back.xpm_ptr);
	mlx_destroy_image(game->mlx_instance, game->exit_open.xpm_ptr);
	mlx_destroy_image(game->mlx_instance, game->exit_closed.xpm_ptr);
	mlx_destroy_image(game->mlx_instance, game->ghost_up.xpm_ptr);
	mlx_destroy_image(game->mlx_instance, game->ghost_down.xpm_ptr);
}

void	ft_free_map(t_game *game)
{
	int	i;

	if (!game->map.full)
		return ;
	i = 0;
	while (game->map.full[i])
		free(game->map.full[i++]);
	free(game->map.full);
	game->map.full = NULL;
}

void	ft_free_memory(t_game *game)
{
	ft_lstclear(&game->ghosts, free);
	ft_destroy_image(game);
	ft_free_map(game);
	mlx_destroy_window(game->mlx_instance, game->win_ptr);
	mlx_destroy_display(game->mlx_instance);
	free(game->mlx_instance);
	free(game);
}
