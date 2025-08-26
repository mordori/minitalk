/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myli-pen <myli-pen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/25 14:08:11 by myli-pen          #+#    #+#             */
/*   Updated: 2025/08/26 19:32:56 by myli-pen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"
#include "utils.h"

static inline void	sig_handler(int sig, siginfo_t *info, void *ctx);
static inline void	init_msg(t_message *msg, const int val);
static inline void	print_msg(t_message *msg, const int val);

int	main(void)
{
	struct sigaction	sa;

	sa.sa_flags = SA_SIGINFO;
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

static inline void	sig_handler(int sig, siginfo_t *info, void *ctx)
{
	static int			bit;
	static int			val;
	static t_message	msg;

	(void)ctx;
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

static inline void	init_msg(t_message *msg, const int val)
{
	msg->len = val;
	msg->str = malloc(sizeof(char) * (msg->len + 1));
	if (!msg->str)
		ft_error("msg malloc");
	msg->str[msg->len] = '\0';
}

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
