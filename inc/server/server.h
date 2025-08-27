/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myli-pen <myli-pen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/25 14:06:53 by myli-pen          #+#    #+#             */
/*   Updated: 2025/08/27 17:45:30 by myli-pen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SERVER_H
# define SERVER_H

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
# include "libft_io.h"

// Minitalk
// -----------------------------------------------------------------------------
# include "utils.h"

typedef struct s_message
{
	int		len;
	int		idx;
	char	*str;
}				t_message;

#endif
