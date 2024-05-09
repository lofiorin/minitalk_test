/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lofiorin <lofiorin@student.42firenze.it    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 17:39:27 by lofiorin          #+#    #+#             */
/*   Updated: 2024/05/09 14:56:35 by lofiorin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

void	handler(int sig, siginfo_t *info, void *ucontext)
{
	static t_server	serv = (t_server){0};

	serv.c = serv.c + ((sig == SIGUSR1) << serv.i);
	(void)ucontext;
	if (++serv.i == 8)
	{
		if (serv.c == 0)
		{
			write(1, "\n", 1);
			kill(info->si_pid, SIGUSR2);
		}
		else
		{
			write(1, &(serv.c), 1);
			kill(info->si_pid, SIGUSR1);
		}
		serv.c = 0;
		serv.i = 0;
	}
}

int	main(void)
{
	struct sigaction	sa;

	ft_printf("pid :\t %d\n", getpid());
	sa = (struct sigaction){0};
	sa.sa_flags = SA_SIGINFO;
	sa.sa_sigaction = &handler;
	sigaction(SIGUSR1, &sa, NULL);
	sigaction(SIGUSR2, &sa, NULL);
	while (1)
		pause();
}
