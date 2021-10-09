/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wadina <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/05 05:04:01 by wadina            #+#    #+#             */
/*   Updated: 2021/10/05 05:04:17 by wadina           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minitalk.h"
#include <stdio.h>

t_msg	g_msg;
	// ft_putstr_fd("1 SER|", 1);
	// ft_putnbr_fd(g_msg.len, 1);
	// ft_putstr_fd("|", 1);
	// ft_putnbr_fd(g_msg.bits, 1);
	// ft_putstr_fd("|", 1);
	// ft_putnbr_fd(info->si_pid, 1);
	// ft_putstr_fd("|", 1);
	// ft_putnbr_fd(info->si_signo, 1);
	// ft_putstr_fd("\n", 1);
	// if (info->si_pid == 0)
	// 	exit(1);

void	ft_len_recieve(int sig, siginfo_t *info, void *context)
{
	(void)context;
	if (info->si_pid == 0)
		exit(1);
	if (sig == SIGUSR2)
		g_msg.c += (1 << (g_msg.bits % 8));
	g_msg.bits++;
	// printf("CHECK 2, pid=%d, g_msg.bits=%zu ", info->si_pid, g_msg.bits);

	// printf("c=%d, b=%zu\n", g_msg.c, g_msg.bits);
	if (g_msg.bits % 8 == 0)
	{
		write(1, &g_msg.c, 1);
		g_msg.c = 0;
		g_msg.bits = 0;
	}
	kill(info->si_pid, SIGUSR1);
}
// printf("CHECK 2, pid=%d, g_msg.bits=%zu, g_msg.len=%zu\n", info->si_pid, g_msg.bits, g_msg.len);
	
int	main(void)
{
	struct sigaction	siga;

	ft_putnbr_fd(getpid(), 1);
	ft_putchar_fd('\n', 1);
	g_msg = (t_msg){0};
	siga.sa_flags = SA_SIGINFO;
	sigemptyset(&siga.sa_mask);
	sigaddset(&siga.sa_mask, SIGUSR1);
	sigaddset(&siga.sa_mask, SIGUSR2);
	siga.sa_sigaction = ft_len_recieve;
	sigaction(SIGUSR1, &siga, NULL);
	sigaction(SIGUSR2, &siga, NULL);
	while (1)
		pause();
	return (0);
}
