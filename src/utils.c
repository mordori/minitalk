/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myli-pen <myli-pen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/26 19:24:16 by myli-pen          #+#    #+#             */
/*   Updated: 2025/08/26 19:26:36 by myli-pen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

void	ft_error(char *msg)
{
	ft_putstr_fd("Error: ", STDERR_FILENO);
	ft_putendl_fd(msg, STDERR_FILENO);
	exit(EXIT_FAILURE);
}
