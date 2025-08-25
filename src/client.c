/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myli-pen <myli-pen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/25 14:07:45 by myli-pen          #+#    #+#             */
/*   Updated: 2025/08/25 19:48:03 by myli-pen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "client.h"
#include "utils.h"

static inline void	send_str(pid_t pid, char *str);
static inline int	send_sig(pid_t pid, char bit);

int	main(int argc, char *argv[])
{
	pid_t	pid;
	int64_t	val;
	char	end;

	if (argc != 3)
		ft_error("client", "invalid number of args.");
	val = ft_strtol(argv[1], &end);
	if (end || val < 2 || val > PID_MAX)
		ft_error("client", "invalid PID.");
	pid = (pid_t)val;
	send_str(pid, argv[2]);
	return (EXIT_SUCCESS);
}

static inline void	send_str(pid_t pid, char *str)
{
	int	bit;

	while (*str)
	{
		bit = 0;
		while (bit < 8)
		{
			if (send_sig(pid, (*str >> bit) & 1))
				ft_error("client", "signal not sent.");
			usleep(100);
			++bit;
		}
		++str;
	}
}

static inline int	send_sig(pid_t pid, char bit)
{
	int	sig;

	sig = 0;
	if (bit == 0)
		sig = SIGUSR1;
	else if (bit == 1)
		sig = SIGUSR2;
	if (!sig)
		ft_error("client", "invalid signal.");
	return (kill(pid, sig));
}
