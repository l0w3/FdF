/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   learn_mlx.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alrodri2 <alrodri2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/10 12:31:18 by alrodri2          #+#    #+#             */
/*   Updated: 2023/03/14 12:51:21 by alrodri2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./minilibx_macos/mlx.h"
#include <stdio.h>

typedef struct s_mystruct{
    void    *mlx;
    void    *win;
}   t_mystruct;

int test(t_mystruct *my)
{
    int x = 0;
    int y = 0;
    while (x != 1000 && y != 1000)
    {
        
            
        mlx_pixel_put(my->mlx, my->win,x, y,  0xFFFFFF);
        long int j = 0;
        while (j < 1000000)
            ++j;

        ++x;
        ++y;
    }
    
    
    return (0);
}

typedef struct	s_data {
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}				t_data;

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

void draw_square(int heigth, int width, t_data img)
{
    int i;
    int j;

    i = 0;
    j = 0;
    while (i < heigth)
        my_mlx_pixel_put(&img, i++, j, 0x0000FF00);
    while (j < width)
        my_mlx_pixel_put(&img, i, j++, 0x0000FF00);
    while (i > 0)
        my_mlx_pixel_put(&img, i--, j, 0x0000FF00);
    while (j > 0)
        my_mlx_pixel_put(&img, i, j--, 0x0000FF00);
}

void draw_grid(int width, int heigth, int rows, int columns, t_data img)
{
    int dimensions_x;
    int dimensions_y;
    int x;
    int y;

    dimensions_x = width / columns;
    dimensions_y = heigth / rows;
    x = 0;
    y = 0;
    while (x < columns)
        draw_square(dimensions_x*(x++), dimensions_y, img);
    while (y < rows)
        draw_square(dimensions_x, dimensions_y*(y++), img);
    while (x > 0)
        draw_square(dimensions_x*(x--), dimensions_y*rows, img);
    while (y > 0)
        draw_square(dimensions_x*columns, dimensions_y*(y--), img);

    
}

void draw_point(int x, int y, t_data img)
{
    
	my_mlx_pixel_put(&img, x, y, 0x00FF0000);
    my_mlx_pixel_put(&img, --x, --y, 0x00FF0000);
	my_mlx_pixel_put(&img, ++x, y, 0x00FF0000);
	my_mlx_pixel_put(&img, ++x, y++, 0x00FF0000);
	my_mlx_pixel_put(&img, x-2, y, 0x00FF0000);
	my_mlx_pixel_put(&img, x, y++, 0x00FF0000);
	my_mlx_pixel_put(&img, x-2, y, 0x00FF0000);
	my_mlx_pixel_put(&img, x-1, y, 0x00FF0000);
	my_mlx_pixel_put(&img, x, y, 0x00FF0000);
}

int	main(void)
{
	void	*mlx;
	void	*mlx_win;
	t_data	img;

	mlx = mlx_init();
	mlx_win = mlx_new_window(mlx, 1080, 720, "Hello world!");
	img.img = mlx_new_image(mlx, 1080, 720);
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length, &img.endian);
    //draw_grid(100, 100, 10, 10, img);
    draw_point(10, 10, img);
    draw_point(10, 70, img);
    draw_point(70, 10, img);
    draw_point(70, 70, img);
	mlx_put_image_to_window(mlx, mlx_win, img.img, 1080/2, 720/2);
	mlx_loop(mlx);
}
