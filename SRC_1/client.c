/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wadina <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/05 05:05:59 by wadina            #+#    #+#             */
/*   Updated: 2021/10/05 05:06:08 by wadina           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

static void	confirm_reception(int sig, siginfo_t *info, void *context)
{
	(void)sig;
	(void)info;
	(void)context;
	ft_putstr_fd(SUCC_MESSAGE, 1);
	usleep(50);
}

static void	send_message(pid_t pid, char msg)
{
	size_t	i;

	i = 0;
	while (i < 8)
	{
		if (((msg >> i++) & 1) == 0)
			kill(pid, SIGUSR1);
		else
			kill(pid, SIGUSR2);
		usleep(1000);
	}
}

static void	check_err1(int argc)
{
	if (argc != 3)
	{
		ft_putstr_fd(C_ER1_MESSAGE, 2);
		exit(1);
	}
}

static void	check_err2(int pid)
{
	if (kill(pid, 0))
	{
		ft_putstr_fd(C_ER2_MESSAGE, 2);
		exit(1);
	}
}

int	main(int argc, char **argv)
{	
	pid_t				pid;
	struct sigaction	sa;

	check_err1(argc);
	pid = atoi(argv[1]);
	check_err2(pid);
	sa.sa_flags = SA_SIGINFO;
	sa.sa_sigaction = confirm_reception;
	if (sigaction(SIGUSR1, &sa, NULL) == -1
		|| sigaction(SIGUSR2, &sa, NULL) == -1)
		return (-1);
	while (*(argv[2]))
		send_message(pid, *(argv[2]++));
	send_message(pid, '\n');
}
