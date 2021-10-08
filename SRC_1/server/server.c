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
t_msg	g_msg;
	// ft_putstr_fd("1 SER|", 1);
	// ft_putnbr_fd(g_msg.len, 1);
	// ft_putstr_fd("|", 1);
	// ft_putstr_fd((char*)g_msg.txt, 1);
	// ft_putstr_fd("|", 1);
	// ft_putnbr_fd(g_msg.bits, 1);
	// ft_putstr_fd("|", 1);
	// ft_putnbr_fd(info->si_pid, 1);
	// ft_putstr_fd("|", 1);
	// ft_putnbr_fd(info->si_signo, 1);
	// ft_putstr_fd("\n", 1);

static void	ft_check_err(siginfo_t *info)
{
	if (!g_msg.txt)
	{
		ft_putstr_fd(S_ER_MESSAGE, 2);
		kill(info->si_pid, SIGUSR2);
		exit(1);
	}
}

void	ft_len_recieve(int sig, siginfo_t *info, void *context)
{
	size_t				i;

	context = NULL;
	ft_putstr_fd("1 SER|", 1);
	ft_putnbr_fd(g_msg.len, 1);
	ft_putstr_fd("|", 1);
	ft_putnbr_fd(g_msg.bits, 1);
	ft_putstr_fd("|", 1);
	ft_putnbr_fd(info->si_pid, 1);
	ft_putstr_fd("|", 1);
	ft_putnbr_fd(info->si_signo, 1);
	ft_putstr_fd("\n", 1);
	if (info->si_pid == 0)
		exit(1);
	if (g_msg.bits < 64)
	{
		if (sig == SIGUSR2)
			g_msg.len = g_msg.len + (1 << g_msg.bits);
		g_msg.bits++;
		if (g_msg.bits == sizeof(g_msg.len) << 3)
		{
			g_msg.txt = malloc(g_msg.len + 1);
			ft_check_err(info);
			i = 0;
			while (i <= g_msg.len + 1)
				g_msg.txt[i++] = 0;	
		}


	}
	else
	{
		if (sig == SIGUSR2)
			g_msg.txt[(g_msg.bits - 64) / 8] = g_msg.txt[(g_msg.bits - 64) / 8] + (1 << ((g_msg.bits - 64) % 8));
		g_msg.bits++;
		if ((g_msg.bits - 64) / 8 == g_msg.len)
		{
			g_msg.txt[g_msg.len] = 0;
			write(1, g_msg.txt, g_msg.len);
			ft_putchar_fd('\n', 1);
			free(g_msg.txt);
			g_msg = (t_msg){0, 0, 0};
		}


	}
	
	kill(info->si_pid, SIGUSR1);
}

int	main(void)
{
	struct sigaction	siga;

	ft_putnbr_fd(getpid(), 1);
	ft_putchar_fd('\n', 1);
	g_msg = (t_msg){0, 0, 0};
	siga.sa_flags = SA_SIGINFO;
	siga.sa_sigaction = ft_len_recieve;
	sigaction(SIGUSR1, &siga, NULL);
	sigaction(SIGUSR2, &siga, NULL);
	while (1)
		pause();
	
	return (0);
}
