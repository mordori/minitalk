/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myli-pen <myli-pen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/25 14:07:45 by myli-pen          #+#    #+#             */
/*   Updated: 2025/08/27 20:09:54 by myli-pen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "client.h"

static inline void	send_str_len(const pid_t pid, char *str);
static inline void	send_str(const pid_t pid, char *str);
static inline void	send_sig(const pid_t pid, const char bit);
static inline void	ack_handler(int sig);

static volatile sig_atomic_t	g_ack = 0;

/**
 * @brief Client main.
 *
 * Validates arguments, sets up the signal handler,
 * and sends a string to another process via signals.
 *
 * - argv[1] = server PID
 *
 * - argv[2] = string to send
 *
 * @param argc Argument count.
 * @param argv Argument values.
 * @return EXIT_SUCCESS when program closes successfully.
 */
int	main(int argc, char *argv[])
{
	pid_t				pid;
	int64_t				val;
	char				end;
	struct sigaction	sa;

	if (argc != 3)
		ft_error("invalid number of args");
	val = ft_strtol(argv[1], &end);
	if (end || val < 1 || val > PID_MAX)
		ft_error("invalid PID");
	pid = (pid_t)val;
	sa.sa_flags = SA_RESTART;
	sa.sa_handler = ack_handler;
	if (sigemptyset(&sa.sa_mask) == ERROR || \
sigaction(SIGUSR1, &sa, NULL) == ERROR)
		ft_error("registering sigaction");
	send_str_len(pid, argv[2]);
	send_str(pid, argv[2]);
	return (EXIT_SUCCESS);
}

/**
 * @brief Signal handler for acknowledgment signals.
 *
 * Sets the global `ack` flag when a SIGUSR1 is received.
 *
 * @param sig Signal number received (unused).
 */
static inline void	ack_handler(int sig)
{
	(void)sig;
	g_ack = 1;
}

/**
 * @brief Sends the length of a string to a process as 16 bits.
 *
 * @param pid PID of the target process.
 * @param str The string whose length is being sent.
 */
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

/**
 * @brief Sends a string to a process, bit by bit.
 *
 * @param pid PID of the target process.
 * @param str The string to send.
 */
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

/**
 * @brief Sends a single bit to a process using signals and waits for
 * acknowledgment.
 *
 * @param pid PID of the target process.
 * @param bit Bit to send (0 or 1).
 */
static inline void	send_sig(const pid_t pid, const char bit)
{
	int	sig;

	sig = 0;
	if (bit == 0)
		sig = SIGUSR1;
	if (bit == 1)
		sig = SIGUSR2;
	if (!sig)
		ft_error("invalid signal");
	if (kill(pid, sig))
		ft_error("signal not transmitted");
	while (!g_ack)
		pause();
	g_ack = 0;
}
