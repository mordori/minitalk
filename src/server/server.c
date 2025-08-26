/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myli-pen <myli-pen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/25 14:08:11 by myli-pen          #+#    #+#             */
/*   Updated: 2025/08/26 03:29:38 by myli-pen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"

static inline void sig_handler(int sig, siginfo_t *info, void *ctx);

int	main(void)
{
	struct sigaction	sa;

	sa.sa_flags = SA_SIGINFO;
	sa.sa_sigaction = sig_handler;
	sigemptyset(&sa.sa_mask);
	if (sigaction(SIGUSR1, &sa, NULL) == ERROR || \
sigaction(SIGUSR2, &sa, NULL) == ERROR)
		server_error("registering sigactions.");
	if (!ft_printf("%d\n", getpid()))
		server_error("print PID");
	while (true)
		pause();
	return (EXIT_SUCCESS);
}

static inline void sig_handler(int sig, siginfo_t *info, void *ctx)
{
	static int	bit = 0;
	static char	c = 0;
	//static char	str_len[11];
	//static int	i;

	(void)ctx;
	(void)info;
	if (sig == SIGUSR2)
		c |= 1 << bit;
	++bit;
	if (bit == 8)
	{
		//str_len[i++] = c;
		bit = 0;
		c = 0;
	}
}
