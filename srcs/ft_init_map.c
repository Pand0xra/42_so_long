/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init_map.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: narginaa <narginaa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/10 11:00:23 by narginaa          #+#    #+#             */
/*   Updated: 2026/02/13 09:15:38 by narginaa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"
#include <stdio.h>

void	ft_parse_cmd_line_args(int argc, char **argv, t_game *game)
{
	int	map_name_len;

	if (argc > 2)
		ft_error_msg("Too many arguments.\n", game);
	else if (argc < 2)
		ft_error_msg("The Map file is missing.\n", game);
	map_name_len = ft_strlen(argv[1]);
	if (!ft_strnstr(argv[1] + (map_name_len - 4), ".ber", 4))
		ft_error_msg("Wrong file extension: `.ber`is expected.\n", game);
	else if (argv[1][0] == '.')
		ft_error_msg("A filename cannot consist only of `.ber`!\n", game);
}

void	ft_count_rows(char *map_path, t_game *game)
{
	int		fd;
	char	*line;

	fd = open(map_path, O_RDONLY);
	if (fd == -1)
		ft_error_msg("Can't open the file map. Does the map exist?\n", game);
	game->map.rows = 0;
	while (1)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		free(line);
		game->map.rows++;
	}
	close(fd);
}

static void	ft_init_map_helper(int map_fd, t_game *game)
{
	char	*line;
	size_t	len;

	while (1)
	{
		line = get_next_line(map_fd);
		if (!line)
			break ;
		len = ft_strlen(line);
		if (len > 0 && line[0] == '\n')
		{
			free(line);
			close(map_fd);
			ft_free_map(game);
			ft_error_msg("Invalid map. Empty line in the middle of the map.\n", \
game);
		}
		while (len > 0 && (line[len - 1] == '\n' || line[len - 1] == '\r'))
		{
			line[len - 1] = '\0';
			len--;
		}
		game->map.full[game->map.rows++] = line;
	}
}

void	ft_init_map(char *map_path, t_game *game)
{
	int		map_fd;

	map_fd = open(map_path, O_RDONLY);
	if (map_fd == -1)
		ft_error_msg("Can't open the file map. Does the map exist?\n", game);
	ft_count_rows(map_path, game);
	if (game->map.rows == 0)
		ft_error_msg("The map is empty.\n", game);
	game->map.full = ft_calloc(game->map.rows + 1, sizeof(char *));
	printf("rows: %d\n", game->map.rows);
	printf("full: %p\n", game->map.full);
	if (!game->map.full)
		ft_error_msg("Map allocation failed.\n", game);
	game->map.rows = 0;
	ft_init_map_helper(map_fd, game);
	game->map.columns = ft_strlen(game->map.full[0]);
	game->map.full[game->map.rows] = NULL;
	close(map_fd);
}
