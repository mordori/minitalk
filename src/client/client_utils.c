/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myli-pen <myli-pen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/25 22:33:04 by myli-pen          #+#    #+#             */
/*   Updated: 2025/08/26 03:24:55 by myli-pen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "client.h"

static inline int	send_sig(pid_t pid, char bit);

void	client_error(char *msg)
{
	ft_putstr_fd("Client error: ", STDERR_FILENO);
	ft_putendl_fd(msg, STDERR_FILENO);
	exit(EXIT_FAILURE);
}

void	send_msg(pid_t pid, char *msg, int bit, char *err)
{
	if (send_sig(pid, (*msg >> bit) & 1))
		client_error(err);
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
		client_error("invalid signal.");
	return (kill(pid, sig));
}
