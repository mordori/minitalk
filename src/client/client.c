/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myli-pen <myli-pen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/25 14:07:45 by myli-pen          #+#    #+#             */
/*   Updated: 2025/08/26 03:11:14 by myli-pen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "client.h"

static inline void	code_len(pid_t pid, char *str);
static inline void	code_str(pid_t pid, char *str);

int	main(int argc, char *argv[])
{
	pid_t	pid;
	int64_t	val;
	char	end;

	if (argc != 3)
		client_error("invalid number of args.");
	val = ft_strtol(argv[1], &end);
	if (end || val < 2 || val > PID_MAX)
		client_error("invalid PID.");
	pid = (pid_t)val;
	if (!argv[2])
		client_error("empty string.");
	code_len(pid, argv[2]);
	code_str(pid, argv[2]);
	return (EXIT_SUCCESS);
}

static inline void	code_len(pid_t pid, char *str)
{
	size_t	len;
	char	*str_len;

	len = ft_strlen(str);
	if (len > INT_MAX)
		client_error("str_len is too long.");
	str_len = ft_itoa((int)len, BASE_10);
	if (!str_len)
		client_error("str_len malloc.");
	code_str(pid, str_len);
	free(str_len);
}

static inline void	code_str(pid_t pid, char *str)
{
	int	bit;

	while (*str)
	{
		bit = 0;
		while (bit < 8)
		{
			send_msg(pid, str, bit, "signal not transmitted.");
			usleep(100);
			++bit;
		}
		++str;
	}
	send_msg(pid, str, bit, "signal not transmitted.");
}
