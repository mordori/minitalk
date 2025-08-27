/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myli-pen <myli-pen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/25 14:08:11 by myli-pen          #+#    #+#             */
/*   Updated: 2025/08/27 16:59:58 by myli-pen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"

static inline void	sig_handler(int sig, siginfo_t *info, void *ucontext);
static inline void	init_msg(t_message *msg, const int val);
static inline void	print_msg(t_message *msg, const int val);

/**
 * @brief Server main.
 *
 * Registers signal handlers, prints its PID, and waits indefinitely for
 * messages.
 *
 * @return EXIT_SUCCESS when program closes successfully.
 */
int	main(void)
{
	struct sigaction	sa;

	sa.sa_flags = (SA_SIGINFO | SA_RESTART);
	sa.sa_sigaction = sig_handler;
	if (sigemptyset(&sa.sa_mask) == ERROR || \
sigaction(SIGUSR1, &sa, NULL) == ERROR || \
sigaction(SIGUSR2, &sa, NULL) == ERROR)
		ft_error("registering sigaction");
	if (!ft_printf("%d\n", getpid()))
		ft_error("print PID");
	while (true)
		pause();
	return (EXIT_SUCCESS);
}

/**
 * @brief Signal handler that reconstructs messages bit by bit.
 *
 * Handles both SIGUSR1 and SIGUSR2signals from the client.
 * Sends acknowledgment to the sender after processing each bit.
 *
 * - SIGUSR1 = 0 bit
 *
 * - SIGUSR2 = 1 bit
 *
 * @param sig Signal number received (SIGUSR1 or SIGUSR2).
 * @param info Pointer to siginfo_t containing sender information.
 * @param ucontext Unused context pointer.
 */
static inline void	sig_handler(int sig, siginfo_t *info, void *ucontext)
{
	static int			bit;
	static int			val;
	static t_message	msg;

	(void)ucontext;
	if (sig == SIGUSR2)
		val |= (1 << bit);
	++bit;
	if (!msg.len && bit == 16)
	{
		init_msg(&msg, val);
		val = 0;
		bit = 0;
	}
	else if (msg.len && bit == 8)
	{
		print_msg(&msg, val);
		val = 0;
		bit = 0;
	}
	if (kill(info->si_pid, SIGUSR1))
		ft_error("failed to send ack");
}

/**
 * @brief Initializes a message structure.
 *
 * Allocates memory for the message string after receiving its length.
 *
 * @param msg Pointer to the message structure.
 * @param val Length of the message in bytes.
 */
static inline void	init_msg(t_message *msg, const int val)
{
	msg->len = val;
	msg->str = malloc(sizeof(char) * (msg->len + 1));
	if (!msg->str)
		ft_error("msg malloc");
	msg->str[msg->len] = '\0';
}

/**
 * @brief Adds a character to the message and prints it when complete.
 *
 * If the message is complete, it prints the string, frees memory,
 * and resets the structure.
 *
 * @param msg Pointer to the message structure.
 * @param val Character value received.
 */
static inline void	print_msg(t_message *msg, const int val)
{
	msg->str[msg->idx++] = val;
	if (msg->idx == msg->len)
	{
		if (!ft_printf("%s\n", msg->str))
		{
			free(msg->str);
			ft_error("print msg");
		}
		msg->len = 0;
		msg->idx = 0;
		free(msg->str);
		msg->str = NULL;
	}
}
