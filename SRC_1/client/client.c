
#include "../minitalk.h"

#include <stdio.h>

int dec2bin(int server_pid, int num)
{
  int bin = 0;
  int k = 1;
  int i = 0;

  while (num)
  {
    bin += (num % 2) * k;
    k *= 10;
    num /= 2;
    i++;
  }
  return bin;
}

int gnl(char **line)
{
	int rd = 0;
	int i = 0;
	char ch;
	char *buffer = malloc(100000);
	*line = buffer;
	while ((rd = read(0, &ch, 1)) > 0 && ch != '\n')
		buffer[i++] = ch;
	buffer[i] = '\0';
	return (rd);
}

int	main(int ac, char **av)
{
	if (ac == 2)
	{
		printf("Zdorova, server! Im client, my PID=%d\n", getpid());
		kill(ft_atoi(av[1]), SIGUSR1);
		kill(ft_atoi(av[1]), SIGUSR1);
		
	}
}
