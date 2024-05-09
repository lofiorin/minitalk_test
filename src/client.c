/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lofiorin <lofiorin@student.42firenze.it    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 17:39:13 by lofiorin          #+#    #+#             */
/*   Updated: 2024/05/09 14:58:48 by lofiorin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

size_t	g_i;

static void	client(int pid, unsigned char c)
{
	int	i;

	i = -1;
	while (++i < 8)
	{
		if ((c >> i) & 1)
			kill (pid, SIGUSR1);
		else
			kill (pid, SIGUSR2);
		usleep(100);
	}
}

static int	pid_get(char *pid)
{
	int	i;

	i = -1;
	while (pid[++i])
		if (pid[i] < '0' || pid[i] > '9')
			return (0);
	return (ft_atoi(pid));
}

static void	recived(int sig)
{
	if (sig == SIGUSR1)
	{
		ft_printf("Byte recieved\n");
		g_i++;
		return ;
	}
	else
	{
		ft_printf("All done!");
		exit(0);
	}
}

int	main(int ac, char **av)
{
	int					pid;
	size_t				i;

	if (ac != 3 || !av[2])
		return (1);
	i = 0;
	pid = pid_get(av[1]);
	if (!pid)
		return (1);
	signal(SIGUSR1, recived);
	signal(SIGUSR2, recived);
	while (av[2][i])
	{
		client(pid, av[2][i++]);
	}
	client (pid, '\0');
	pause();
	return (0);
}
