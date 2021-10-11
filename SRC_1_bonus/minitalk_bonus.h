/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minitalk_bonus.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wadina <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/10 02:26:38 by wadina            #+#    #+#             */
/*   Updated: 2021/10/10 02:26:44 by wadina           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINITALK_BONUS_H
# define MINITALK_BONUS_H
# define SUCC_MESSAGE "client: SIGNAL OK\n"
# define C_ER1_MESSAGE "client: Wrong number of arguments!\n"
# define C_ER2_MESSAGE "client: Wrong server's PID\n"
# define S_ER_MESSAGE "server: Error!"

# include "../SRC_0/libft/libft.h"
# include <unistd.h>
# include <signal.h>

typedef struct s_msg
{
	unsigned char	c;
	size_t			bits;
}				t_msg;

#endif
