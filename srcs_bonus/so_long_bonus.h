/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long_bonus.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nana <nana@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/10 11:21:37 by narginaa          #+#    #+#             */
/*   Updated: 2026/02/12 18:17:17 by nana             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_BONUS_H
# define SO_LONG_BONUS_H

# include "../libft/libft.h"
# include "../minilibx-linux/mlx.h"
# include <X11/X.h>
# include <X11/keysym.h>
# include <fcntl.h>
# include <stdbool.h>
# include <unistd.h>
# include <stdlib.h>
# include <time.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

# define IMG_HEIGHT 		96
# define IMG_WIDTH 			96

# define WALL 				'1'
# define FLOOR 				'0'
# define COINS 				'C'
# define PLAYER 			'P'
# define EXIT 				'E'
# define GHOST 				'G'

# define GHOST_ANIM_DELAY	20000
# define FRONT				1
# define LEFT				2
# define RIGHT				3
# define BACK				4

# define WALL_XPM			"assets/sprites/wall.xpm"
# define FLOOR_XPM	  		"assets/sprites/floor.xpm"
# define COINS_XPM	  		"assets/sprites/coin.xpm"
# define PLAYER_FRONT_XPM 	"assets/sprites/player/front.xpm"
# define PLAYER_LEFT_XPM 	"assets/sprites/player/left.xpm"
# define PLAYER_RIGHT_XPM 	"assets/sprites/player/right.xpm"
# define PLAYER_BACK_XPM 	"assets/sprites/player/back.xpm"
# define EXIT_OPEN_XPM 		"assets/sprites/exit_opened.xpm"
# define EXIT_CLOSED_XPM 	"assets/sprites/exit_closed.xpm"
# define GHOST_UP 			"assets/sprites/ghost_up.xpm"
# define GHOST_DOWN 		"assets/sprites/ghost_down.xpm"

# define KEY_UP				65362
# define KEY_LEFT			65361
# define KEY_RIGHT			65363
# define KEY_DOWN			65364

# define KEY_ESC			65307
# define KEY_Q				113

# define KEY_W				119
# define KEY_A				97
# define KEY_D				100
# define KEY_S				115

typedef struct s_player
{
	int	x;
	int	y;
	int	count;
}				t_player;

typedef struct s_map
{
	char		**full;
	int			rows;
	int			columns;
	int			coins;
	int			exit;
	t_player	player;
}				t_map;

typedef struct s_image
{
	int		width;
	int		height;
	void	*xpm_ptr;
}				t_image;

typedef struct s_ghost
{
	int	x;
	int	y;
	int	prev_x;
	int	prev_y;
}				t_ghost;

typedef struct s_game
{
	t_map	map;
	int		movements;
	void	*mlx_instance;
	void	*win_ptr;
	int		player_sprite;
	t_image	wall;
	t_image	floor;
	t_image	coins;
	t_image	exit_open;
	t_image	exit_closed;
	t_image	player_front;
	t_image	player_left;
	t_image	player_right;
	t_image	player_back;
	t_image	ghost_up;
	t_image	ghost_down;
	int		ghost_anim_frame;
	int		ghost_anim_counter;
	t_list	*ghosts;
}				t_game;

typedef struct s_gnl_list
{
	char				*stash;
	struct s_gnl_list	*next;
}				t_gnl_list;

void		ft_error_msg(char *message, t_game *game);
void		ft_parse_cmd_line_args(int argc, char **argv, t_game *game);
void		ft_init_map(char *map, t_game *game);
void		ft_init_vars(t_game *game);
void		ft_check_map(t_game *game);
void		ft_check_format(t_game *game);
void		ft_flood_fill(t_game *game);
void		ft_init_mlx(t_game *game);
void		ft_init_sprites(t_game *game);
int			ft_render_map(t_game *game);
int			ft_handle_input(int keysym, t_game *game);
int			ft_close_game(t_game *game);
void		ft_free_memory(t_game *game);
void		ft_free_map(t_game *game);
void		ft_victory(t_game *game);
void		ft_loss(t_game *game);
void		ft_render_ghost(t_game *game, int y, int x);
void		ft_render_sprite(t_game *game, t_image sprite, int y, int x);
void		ft_init_ghosts(t_game *game);
int			ft_anim_ghost(t_game *game);
void		ft_move_ghosts(t_game *game);

char		*get_next_line(int fd);
int			ft_create_list(t_gnl_list **list, int fd);
char		*ft_get_line(t_gnl_list *list);
void		ft_clean(t_gnl_list **list);
int			ft_found_newline(t_gnl_list *list);
t_gnl_list	*ft_gnl_lstlast(t_gnl_list *list);
t_gnl_list	*ft_append(t_gnl_list **list, t_gnl_list *last, char *buffer);
void		ft_free_list(t_gnl_list **list, t_gnl_list *clean_n, char *clean_s);
void		ft_linecpy(t_gnl_list *list, char *str);
int			ft_len_stash(t_gnl_list *list);

#endif
