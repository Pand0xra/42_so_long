/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ghost_logic_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: narginaa <narginaa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/10 11:21:44 by narginaa          #+#    #+#             */
/*   Updated: 2026/03/04 08:32:25 by narginaa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_bonus.h"

static void	ft_init_ghosts_helper(int y, int x, t_game *game)
{
	t_ghost	*ghost;
	t_list	*new_node;

	if (game->map.full[y][x] == GHOST)
	{
		ghost = malloc(sizeof(t_ghost));
		if (!ghost)
			ft_error_msg("Malloc failed for ghost", game);
		ghost->x = x;
		ghost->y = y;
		new_node = ft_lstnew(ghost);
		if (!new_node)
		{
			free(ghost);
			ft_error_msg("Malloc failed for ghost node.\n", game);
		}
		ft_lstadd_back(&game->ghosts, new_node);
	}
}

void	ft_init_ghosts(t_game *game)
{
	int		x;
	int		y;

	srand(time(NULL));
	y = 0;
	while (y < game->map.rows)
	{
		x = 0;
		while (x < game->map.columns)
		{
			ft_init_ghosts_helper(y, x, game);
			x++;
		}
		y++;
	}
}

static void	ft_update_ghost_pos(t_game *game, t_ghost *ghost, int ny, int nx)
{
	if (game->map.full[ny][nx] == PLAYER)
		ft_loss(game);
	game->map.full[ghost->y][ghost->x] = FLOOR;
	game->map.full[ny][nx] = GHOST;
	ghost->x = nx;
	ghost->y = ny;
}

static int	ft_is_valid_move(t_game *game, int y, int x)
{
	char	pos;

	if (y < 0 || x < 0 || y >= game->map.rows || x >= game->map.columns)
		return (0);
	pos = game->map.full[y][x];
	if (pos == WALL || pos == EXIT || pos == COINS || pos == GHOST)
		return (0);
	return (1);
}

void	ft_move_ghosts(t_game *game)
{
	t_list	*head;
	t_ghost	*ghost;
	int		dir;
	int		nx;
	int		ny;

	head = game->ghosts;
	while (head)
	{
		ghost = (t_ghost *)head->content;
		dir = rand() % 4;
		nx = ghost->x;
		ny = ghost->y;
		if (dir == 0)
			ny--;
		else if (dir == 1)
			ny++;
		else if (dir == 2)
			nx--;
		else
			nx++;
		if (ft_is_valid_move(game, ny, nx))
			ft_update_ghost_pos(game, ghost, ny, nx);
		head = head->next;
	}
}
