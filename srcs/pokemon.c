/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pokemon.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhaliti <dhaliti@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/11 19:24:55 by dhaliti           #+#    #+#             */
/*   Updated: 2022/03/15 19:11:55 by dhaliti          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pokemon.h"

static void	init_window(t_param *param)
{
	int	height;
	int	width;

	height = (param->height + 1) * 40;
	width = param->width * 40;
	param->mlx = mlx_init();
	param->mlx_win = mlx_new_window(param->mlx, width, height, "POKEMON");
	param->mlx_img = mlx_new_image(param->mlx, width, height);
	if (param->mlx == 0 || param->mlx_win == 0 || param->mlx_img == 0)
	{
		free_all(param);
		exit_error("ERROR: IMAGE INITIALISATION FAILED", 0);
	}
}

static void	init_images(t_param *param)
{
	put_image(param, &param->player, "./images/player_front.xpm");
	put_image(param, &param->pikachu, "./images/pikachu.xpm");
	put_image(param, &param->pokeball, "./images/pokeball.xpm");
	put_image(param, &param->grass, "./images/grass.xpm");
	put_image(param, &param->ground, "./images/ground.xpm");
}

static void	init_item(t_param *param, void *item, int i, int j)
{
	if (item == param->player)
	{
		param->player_x = i;
		param->player_y = j;
		mlx_put_image_to_window(param->mlx, param->mlx_win, \
			item, i * 40, j * 40);
	}
	else
		mlx_put_image_to_window(param->mlx, param->mlx_win, \
			item, i * 40, j * 40);
}

int	init_map(t_param *param)
{
	int	i;
	int	j;

	j = -1;
	while (param->map[++j])
	{
		i = -1;
		while (param->map[j][++i])
		{
			if (param->map[j][i] == 'E')
				init_item(param, param->pikachu, i, j);
			if (param->map[j][i] == '1')
				init_item(param, param->grass, i, j);
			if (param->map[j][i] == 'C')
				init_item(param, param->pokeball, i, j);
			if (param->map[j][i] == 'P')
				init_item(param, param->player, i, j);
			if (param->map[j][i] == '0')
				init_item(param, param->ground, i, j);
		}
	}
	return (0);
}

void	pokemon(t_param *param)
{
	init_window(param);
	init_images(param);
	init_map(param);
	mlx_hook(param->mlx_win, 2, 1L << 0, keypress, param);
	mlx_hook(param->mlx_win, 17, 1L << 17, free_all_exit, param);
	mlx_hook(param->mlx_win, 9, 1L << 21, init_map, param);
	mlx_loop(param->mlx);
}
