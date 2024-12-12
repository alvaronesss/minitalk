/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aporras- <aporras-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/06 20:56:50 by aporras-          #+#    #+#             */
/*   Updated: 2024/12/12 18:55:03 by aporras-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

void	ft_putnbr_fd(int n, int fd)
{
	char	c;

	if (n == -2147483648)
		write(fd, "-2147483648", 11);
	else
	{
		if (n < 0)
		{
			write(fd, "-", 1);
			n = n * -1;
		}
		if (n > 9)
			ft_putnbr_fd(n / 10, fd);
		c = (n % 10) + '0';
		write(fd, &c, 1);
	}
}

void	handler_signal(int signal)
{
	static char	char_final = 0;
	static int	finalbits[8];
	static int	i = -1;
	int			mult;

	mult = 128;
	if (signal == SIGUSR1)
		finalbits[++i] = 1;
	else if (signal == SIGUSR2)
		finalbits[++i] = 0;
	if (i == 7)
	{
		i = -1;
		while (++i < 8)
		{
			char_final += finalbits[i] * mult;
			mult = mult / 2;
		}
		if (char_final == 0)
			write(1, "\n", 1);
		else
			write(1, &char_final, 1);
		char_final = 0;
		i = -1;
	}
}

int	main(void)
{
	signal(SIGUSR1, handler_signal);
	signal(SIGUSR2, handler_signal);
	write(1, "Server PID: ", 13);
	ft_putnbr_fd(getpid(), 1);
	write(1, "\n", 1);
	while (1)
		pause();
	return (0);
}
