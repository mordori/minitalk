/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myli-pen <myli-pen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/25 14:08:11 by myli-pen          #+#    #+#             */
/*   Updated: 2025/08/25 20:18:06 by myli-pen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"
#include "utils.h"

static inline void signal_handler_1(int sig);
static inline void signal_handler_2(int sig);

int	main(void)
{
	pid_t	pid;

	pid = getpid();
	if (ft_printf(STDOUT_FILENO, "%d\n", pid) == ERROR)
		ft_error("server", "print PID");
	signal(SIGUSR1, signal_handler_1);
	signal(SIGUSR2, signal_handler_2);
	while (true)
	{
		pause();
	}
	return (EXIT_SUCCESS);
}

static inline void signal_handler_1(int sig)
{
	(void)sig;
	if (ft_printf(STDOUT_FILENO, "Signal 1 received!\n") == ERROR)
		exit(EXIT_FAILURE);
}

static inline void signal_handler_2(int sig)
{
	(void)sig;
	if (ft_printf(STDOUT_FILENO, "Signal 2 received!\n") == ERROR)
		exit(EXIT_FAILURE);
}
