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

void	ft_msg_recieve(int sig, siginfo_t *info, void *context)
{
	struct sigaction	sa;

	context = NULL;
	if (sig == SIGUSR2)
		g_msg.txt[g_msg.bits / 8] += 1 << (g_msg.bits % 8);
	g_msg.bits++;
	if (g_msg.bits / 8 == g_msg.len)
	{
		write(1, g_msg.txt, g_msg.len);
		ft_putchar_fd('\n', 1);
		free(g_msg.txt);
		g_msg = (t_msg){0, 0, 0};
		sa.sa_flags = SA_SIGINFO;
		sa.sa_sigaction = ft_len_recieve;
		sigaction(SIGUSR1, &sa, 0);
		sigaction(SIGUSR2, &sa, 0);
	}
	kill(info->si_pid, SIGUSR1);
}

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
	struct sigaction	sa;

	context = NULL;
	if (sig == SIGUSR2)
		g_msg.len += 1 << g_msg.bits;
	g_msg.bits++;
	if (g_msg.bits == sizeof(g_msg.len) << 3)
	{
		g_msg.txt = malloc(g_msg.len + 1);
		ft_check_err(info);
		i = 0;
		while (i <= g_msg.len)
			g_msg.txt[i++] = 0;
		g_msg.bits = 0;
		sa.sa_flags = SA_SIGINFO;
		sa.sa_sigaction = ft_msg_recieve;
		sigaction(SIGUSR1, &sa, 0);
		sigaction(SIGUSR2, &sa, 0);
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
