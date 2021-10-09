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

#include "../minitalk.h"


void	confirm_reception(int sig, siginfo_t *info, void *context)
{
	(void)context;
	(void)info;
	if (sig != SIGUSR1)
	{
		ft_putstr_fd(FAIL_MESSAGE, 2);
		exit(1);
	}
	else
		ft_putstr_fd(SUCC_MESSAGE, 1);
}

void	send_len(pid_t pid, size_t len)
{
	size_t	i;


	i = 0;
	while (i < sizeof(len) * 8)
	{
		if (((len >> i++) & 1) == 0)
			kill(pid, SIGUSR1);
		else
			kill(pid, SIGUSR2);
		
		pause();
	}
}

void	send_message(pid_t pid, char msg)
{
	size_t	i;

	i = 0;
	while (i < 8)
	{
		if (((msg >> i++) & 1) == 0)
			kill(pid, SIGUSR1);
		else
			kill(pid, SIGUSR2);
		pause();
	}
}


int	main(int argc, char **argv)
{	
	pid_t				pid;
	size_t				len;
	struct sigaction	siga;

	if (argc != 3)
	{
		ft_putstr_fd(C_ER1_MESSAGE, 2);
		exit(1);
	}
	siga.sa_flags = SA_SIGINFO;
	sigemptyset(&siga.sa_mask);
	sigaddset(&siga.sa_mask, SIGUSR1);
	sigaddset(&siga.sa_mask, SIGUSR2);
	siga.sa_sigaction = confirm_reception;
	sigaction(SIGUSR1, &siga, NULL);
	sigaction(SIGUSR2, &siga, NULL);
	len = ft_strlen(argv[2]);
	pid = atoi(argv[1]);
	if (kill(pid, 0) != 0)
	{
		ft_putstr_fd(C_ER2_MESSAGE, 2);
		exit(1);
	}
	while (argv[2][0])
	{
		send_message(pid, *(argv[2]++));
	}
		
}
