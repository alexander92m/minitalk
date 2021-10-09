/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minitalk.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wadina <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/05 05:04:33 by wadina            #+#    #+#             */
/*   Updated: 2021/10/05 05:05:49 by wadina           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINITALK_H
# define MINITALK_H
# define SUCC_MESSAGE "SIGNAL OK\n"
# define FAIL_MESSAGE "SIGNAL KO\n"
# define C_ER1_MESSAGE "client: Wrong number of arguments!\n"
# define C_ER2_MESSAGE "client: Wrong server's PID\n"
# define S_ER_MESSAGE "server: Error!"

# include "../SRC_0/libft/libft.h"
# include <unistd.h>
# include <signal.h>

typedef struct s_msg
{
	size_t			len;
	unsigned char	c;
	size_t			bits;
	int				mes;
}				t_msg;

void	ft_len_recieve(int sig, siginfo_t *info, void *context);
void	ft_msg_recieve(int sig, siginfo_t *info, void *context);

#endif
