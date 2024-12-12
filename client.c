/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aporras- <aporras-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/06 01:48:55 by aporras-          #+#    #+#             */
/*   Updated: 2024/12/12 18:02:17 by aporras-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

int	send_bit(int pid, char bit)
{
	if (bit == '1')
		kill(pid, SIGUSR1);
	else if (bit == '0')
		kill(pid, SIGUSR2);
	usleep(100);
	return (1);
}

void	ft_binary(int pid, int c)
{
	int	i;
	int	substract;

	i = 0;
	substract = 128;
	while (i < 8)
	{
		if (c >= substract)
		{
			send_bit(pid, '1');
			c = c - substract;
		}
		else
			send_bit(pid, '0');
		substract = substract / 2;
		i++;
	}
}

int	main(int argc, char **argv)
{
	char	*str;
	int		pid;
	int		i;
	int		z;

	i = 2;
	if (argc == 3)
	{
		pid = atoi(argv[1]);
		while (argv[i] != NULL)
		{
			z = 0;
			str = argv[i];
			while (str[z])
			{
				ft_binary(pid, str[z]);
				z++;
			}
			if (str[z] == '\0')
				ft_binary(pid, 0);
			i++;
		}
	}
	return (0);
}
