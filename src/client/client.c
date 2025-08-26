/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myli-pen <myli-pen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/25 14:07:45 by myli-pen          #+#    #+#             */
/*   Updated: 2025/08/26 19:38:09 by myli-pen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "client.h"
#include "utils.h"

static inline void	send_str_len(const pid_t pid, char *str);
static inline void	send_str(const pid_t pid, char *str);
static inline void	send_sig(const pid_t pid, const char bit);
static inline void	ack_handler(int sig);

static volatile sig_atomic_t	ack = 0;

int	main(int argc, char *argv[])
{
	pid_t	pid;
	int64_t	val;
	char	end;

	if (argc != 3)
		ft_error("invalid number of args");
	val = ft_strtol(argv[1], &end);
	if (end || val < 1 || val > PID_MAX)
		ft_error("invalid PID");
	pid = (pid_t)val;
	if (!argv[2])
		ft_error("empty string");
	if (signal(SIGUSR1, ack_handler) == SIG_ERR)
		ft_error("register signal");
	send_str_len(pid, argv[2]);
	send_str(pid, argv[2]);
	return (EXIT_SUCCESS);
}

static inline void	ack_handler(int sig)
{
	(void)sig;
	ack = 1;
}

static inline void	send_str_len(const pid_t pid, char *str)
{
	size_t	len;
	int		bit;

	len = ft_strlen(str);
	if (!len || len > UINT16_MAX)
		ft_error("invalid str length");
	bit = 0;
	while (bit < 16)
	{
		send_sig(pid, (len >> bit) & 1);
		++bit;
	}
}

static inline void	send_str(const pid_t pid, char *str)
{
	int	bit;

	while (*str)
	{
		bit = 0;
		while (bit < 8)
		{
			send_sig(pid, (*str >> bit) & 1);
			++bit;
		}
		++str;
	}
}

static inline void	send_sig(const pid_t pid, const char bit)
{
	int	sig;
	int	time;

	sig = 0;
	if (bit == 0)
		sig = SIGUSR1;
	if (bit == 1)
		sig = SIGUSR2;
	if (!sig)
		ft_error("invalid signal");
	if (kill(pid, sig))
		ft_error("signal not transmitted");
	time = 0;
	while (!ack)
	{
		if (time > TIMEOUT)
			ft_error("timed out");
		usleep(SLEEP_TIME);
		time += SLEEP_TIME;
	}
	ack = 0;
}
