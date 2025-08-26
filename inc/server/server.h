/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myli-pen <myli-pen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/25 14:06:53 by myli-pen          #+#    #+#             */
/*   Updated: 2025/08/26 02:24:19 by myli-pen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SERVER_H
# define SERVER_H

# define _POSIX_C_SOURCE 200112L

# include <stdlib.h>
# include <unistd.h>
# include <signal.h>
# include <sys/types.h>

# include "libft_io.h"
# include "libft_vector.h"

# define PID_MAX 4194304

void	server_error(char *msg);

#endif
