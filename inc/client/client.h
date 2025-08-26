/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myli-pen <myli-pen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/25 14:06:42 by myli-pen          #+#    #+#             */
/*   Updated: 2025/08/26 02:53:34 by myli-pen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CLIENT_H
# define CLIENT_H

# include <stdlib.h>
# include <unistd.h>
# include <signal.h>
# include <sys/types.h>

# include "libft_io.h"
# include "libft_utils.h"
# include "libft_str.h"

# define PID_MAX 4194304

void	client_error(char *msg);
void	send_msg(pid_t pid, char *msg, int bit, char *err);

#endif
