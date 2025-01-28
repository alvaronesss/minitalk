/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aporras- <aporras-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/06 01:48:55 by aporras-          #+#    #+#             */
/*   Updated: 2024/12/16 16:15:21 by aporras-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

int	ft_atoi(const char *str)
{
	int	res;
	int	sign;

	res = 0;
	sign = 1;
	while (*str == 32 || (*str >= 9 && *str <= 13))
		str++;
	if (*str == '-')
		sign = sign * -1;
	if (*str == '-' || *str == '+')
		str++;
	while (*str >= '0' && *str <= '9')
	{
		res = res * 10 + *str - '0';
		str++;
	}
	return (res * sign);
}

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
		pid = ft_atoi(argv[1]);
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
