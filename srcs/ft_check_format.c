/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_format.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nana <nana@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/12 18:15:00 by nana              #+#    #+#             */
/*   Updated: 2026/02/12 19:32:31 by nana             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"
#include <stdio.h>

void    ft_check_format(t_game *game)
{
    int y;
    int x;
    int count_x;

    y = 0;
    count_x = game->map.columns;
    printf("%d\n", count_x);
    while (game->map.full[y])
    {
        x = 0;
        while (game->map.full[y][x])
            x++;
        printf("%d\n", x);
        if (x != count_x)
            ft_error_msg("Map must be a rectangle or a square.\n", game);
        y++;
    }
}

