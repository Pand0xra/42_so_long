/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init_map_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: narginaa <narginaa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/10 11:20:58 by narginaa          #+#    #+#             */
/*   Updated: 2026/03/04 08:35:15 by narginaa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_bonus.h"

void	ft_parse_cmd_line_args(int argc, char **argv, t_game *game)
{
	int		map_len;
	char	*filename;

	if (argc > 2)
		ft_error_msg("Too many arguments.\n", game);
	else if (argc < 2)
		ft_error_msg("The Map file is missing.\n", game);
	filename = ft_strrchr(argv[1], '/');
	if (filename)
		filename++;
	else
		filename = argv[1];
	map_len = ft_strlen(filename);
	if (map_len < 5 || (ft_strncmp(filename + map_len - 4, ".ber", 4) != 0))
		ft_error_msg("Wrong file extension: `.ber` is expected.\n", game);
}

void	ft_count_rows(char *map_path, t_game *game)
{
	int		fd;
	char	*line;

	fd = open(map_path, O_RDONLY);
	if (fd == -1)
		ft_error_msg("Can't open the file map. Does the map exist?\n", game);
	game->map.rows = 0;
	line = get_next_line(fd);
	while (line)
	{
		game->map.rows++;
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
}

static void	ft_empty_line_error(int fd, t_game *game, char *line)
{
	free(line);
	line = get_next_line(fd);
	while (line)
	{
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
	ft_free_map(game);
	ft_error_msg("Invalid map: empty line\n", game);
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
			ft_empty_line_error(map_fd, game, line);
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

	ft_count_rows(map_path, game);
	if (game->map.rows == 0)
		ft_error_msg("The map is empty.\n", game);
	game->map.full = ft_calloc(game->map.rows + 1, sizeof(char *));
	if (!game->map.full)
		ft_error_msg("Map allocation failed.\n", game);
	map_fd = open(map_path, O_RDONLY);
	if (map_fd == -1)
		ft_error_msg("Can't open the file map. Does the map exist?\n", game);
	game->map.rows = 0;
	ft_init_map_helper(map_fd, game);
	game->map.columns = ft_strlen(game->map.full[0]);
	game->map.full[game->map.rows] = NULL;
	close(map_fd);
}
