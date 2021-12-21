#include "multithreading.h"

#define DELIMITER(a, b) (((a) < (b)) ? (a) : (b))

/**
 * blur_portion - blurs an image
 * @portion: image section
 */

void blur_portion(blur_portion_t const *portion)
{
	size_t x_axis, y_axis;

	x_axis = portion->x;
	y_axis = portion->y;

	while (y_axis < portion->y + portion->h)
	{
		blurrer(portion, x_axis, y_axis);
		++x_axis;
		if (x_axis == portion->x + portion->w)
		{
			x_axis = portion->x;
			++y_axis;
		}
	}
}

/**
 * blurrer - blurs a specific pixel
 * @portion: portion struct
 * @x: pixel at x-axis
 * @y: pixel at y-axis
 */

void blurrer(blur_portion_t const *portion, size_t x, size_t y)
{
	size_t s_x = x, s_y = y, e_x, e_y;
	size_t a, c, k_x, k_y, kernel_x, kernel_y;
	float r, g, b, k;

	k_x = k_y = r = g = b = k = 0;

	b_checker(portion, &s_x, &s_y, &e_x,
		      &e_y, &kernel_x, &kernel_y);
	a = s_x, c = s_y;
	k_x = kernel_x, k_y = kernel_y;

	while (c < e_y)
	{
		r += portion->kernel->matrix[k_x][k_y]
			* portion->img->pixels[portion->img->w * c + a].r;
		g += portion->kernel->matrix[k_x][k_y]
			* portion->img->pixels[portion->img->w * c + a].g;
		b += portion->kernel->matrix[k_x][k_y]
			* portion->img->pixels[portion->img->w * c + a].b;
		k += portion->kernel->matrix[k_x][k_y];
		++k_x, ++x;

		if (a == e_x)
		{
			a = s_x, ++c;
			k_x = kernel_x, ++k_y;
		}
	}
	portion->img_blur->pixels[portion->img->w * y + x].r = r / k;
	portion->img_blur->pixels[portion->img->w * y + x].g = g / k;
	portion->img_blur->pixels[portion->img->w * y + x].b = b / k;
}

/**
 * b_checker - checks for out of bound errors and set start/end positions
 * @portion: portion struct
 * @s_x: start x-axis
 * @s_y: start y-axis
 * @e_x: end x-axis
 * @e_y: end y-axis
 * @kernel_x: kernel at x-axis
 * @kernel_y: kernel at y-axis
 */

void b_checker(blur_portion_t const *portion, size_t *s_x,
		   size_t *s_y, size_t *e_x, size_t *e_y,
		   size_t *kernel_x, size_t *kernel_y)
{
	size_t ker_delim = portion->kernel->size / 2;

	if (*s_x < ker_delim)
	{
		*kernel_x = ker_delim - *s_x;
		*e_x = ker_delim + *s_x + 1;
		*s_x = 0;
	}
	else
	{
		*kernel_x = 0;
		*s_x = *s_x - ker_delim;
		*e_x = DELIMITER(*s_x + portion->kernel->size, portion->img->w);
	}

	if (*s_y < ker_delim)
	{
		*kernel_y = ker_delim - *s_y;
		*e_y = ker_delim + *s_y + 1;
		*s_y = 0;

	}
	else
	{
		*kernel_y = 0;
		*s_y = *s_y - ker_delim;
		*e_y = DELIMITER(*s_y + portion->kernel->size, portion->img->h);
	}
}
