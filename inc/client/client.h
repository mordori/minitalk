/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myli-pen <myli-pen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/25 14:06:42 by myli-pen          #+#    #+#             */
/*   Updated: 2025/08/27 17:45:41 by myli-pen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CLIENT_H
# define CLIENT_H

// System
// -----------------------------------------------------------------------------
# define _POSIX_C_SOURCE 200112L
# define _GNU_SOURCE

# include <stdlib.h>
# include <unistd.h>
# include <signal.h>
# include <sys/types.h>

// Libft
// -----------------------------------------------------------------------------
# include "libft_utils.h"
# include "libft_str.h"

// Minitalk
// -----------------------------------------------------------------------------
# include "utils.h"

# ifndef PID_MAX
#  define PID_MAX 4194304
# endif

#endif
