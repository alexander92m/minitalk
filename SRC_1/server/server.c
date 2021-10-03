// make fclean && make && make clean && ./server && ./client

#include "../minitalk.h"

#include <stdio.h>


int bin2dec(int n)
{
  int num;
  int dec_value;
  int base;
  int temp;
  int last_digit;
    
  num = n;
  base = 1;
  dec_value = 0;
  temp = num;
  while (temp)
  {
    last_digit = temp % 10;
    temp = temp / 10;
    dec_value += last_digit * base;
    base = base * 2;
  }
  return dec_value;
}


void	ft_handler(int signum, siginfo_t *sig, void *context)
{

	ft_putstr_fd("HANDLER 1 IS ACTIVE\n", 1);
	printf("signum=%d, sig=%p, context=%p\n", signum, sig, context);
	printf("sig->pid=%d, sig->signo=%d, sig->code=%d\n", sig->si_pid, sig->si_signo, sig->si_code);
}


int main(int ac, char **av)
{
	struct sigaction	siga;

	if (ac != 1)
		ft_putstr_fd("Error arguments\n", 1);
	ft_putstr_fd("Server started!\nPID: ", 1);
	ft_putnbr_fd(getpid(), 1);
	siga.sa_flags = SA_SIGINFO;
	siga.sa_sigaction = ft_handler1;
	sigaction(SIGUSR1, &siga, NULL);
	if ((sigaction(SIGUSR1, &siga, 0)) == -1)
		ft_putstr_fd("Error sigaction\n", 1);
	if ((sigaction(SIGUSR2, &siga, 0)) == -1)
		ft_putstr_fd("Error sigaction\n", 1);
	while (1)
		pause();
	ft_putstr_fd("Exit\n", 1);
}
