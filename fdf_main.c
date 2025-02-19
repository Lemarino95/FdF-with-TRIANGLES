/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_main.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lemarino <lemarino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 12:17:42 by lemarino          #+#    #+#             */
/*   Updated: 2025/02/19 11:40:48 by lemarino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

//Close window
static int	handle_destroy(void *param)
{
	t_myimg	*mlx;

	mlx = (t_myimg *)param;//Per non ricevere messaggio "variabile inutilizzata su 'param'"
	mlx_destroy_window(mlx->mlx_ptr, mlx->mlx_win);
	exit(0);
	return (0);
}
 
int	main(int ac, char **av)
{
	t_myimg	img;

	if (ac != 2)
		perror("ERR: invalid number of arguments.");
	img.mlx_ptr = mlx_init();//leak
	if (img.mlx_ptr == NULL)
		return (0);
	img.mlx_win = mlx_new_window(img.mlx_ptr, 1600, 900, "FdF");//leak
	if (img.mlx_win == NULL)
		return (0);
	img.nimg = mlx_new_image(img.mlx_ptr, 1600, 900);//leak
	img.addr = mlx_get_data_addr(img.nimg, &img.bits_per_pixel,\
					&img.line_length, &img.endian);
	img.map = cartography(av[1]);
	img.zoom = 20;
	img.height = get_height(av[1]);//errore con linee vuote
	img.width = get_width(av[1]);//errore con spazi alla fine della prima riga
	printf("Map size(h*w) = %dx%d\n", img.height, img.width);//######
	draw(&img);
	mlx_put_image_to_window(img.mlx_ptr, img.mlx_win, img.nimg, 0, 0);
	mlx_hook(img.mlx_win, 17, 0, handle_destroy, &img);
	mlx_loop(img.mlx_ptr);
}
