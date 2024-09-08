/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_color.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: waalexan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/21 12:25:44 by waalexan          #+#    #+#             */
/*   Updated: 2024/06/21 12:26:04 by waalexan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_strcolor(char *text, char *color_code)
{
	const char	*reset_color_code;

	reset_color_code = "\033[0m";
	write(STDOUT_FILENO, color_code, 7);
	write(STDOUT_FILENO, text, ft_strlen(text));
	write(STDOUT_FILENO, reset_color_code, 4);
}

void	ft_clear(void)
{
	const char	*clear_screen;

	clear_screen = "\033[H\033[2J";
	write(STDOUT_FILENO, clear_screen, ft_strlen(clear_screen));
}
