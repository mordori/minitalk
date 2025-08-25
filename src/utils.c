/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myli-pen <myli-pen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/25 18:12:27 by myli-pen          #+#    #+#             */
/*   Updated: 2025/08/25 18:29:15 by myli-pen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

void	ft_error(char *app, char *msg)
{
	ft_printf(STDERR_FILENO, "%s error: %s\n", app, msg);
	exit(EXIT_FAILURE);
}
