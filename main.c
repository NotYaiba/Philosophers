#include <pthread.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

pthread_mutex_t lock;
void ft_putchar(char *str, int fd)
{
    int i;

	i = 0;
	while (str[i])
	{
		write(fd, &str[i], 1);
		i++;
	}
}

void    *routine(void *as)
{
	
	ft_putchar("hello\n", 1);
    return (NULL);
}
int main(int ac, char **av)
{
    pthread_t *th;
    int i;
    int d = 1000;
    th = malloc(sizeof(pthread_t) * 0);
    i = 0;
    while (i < d)
    {
        pthread_create(&th[i], NULL, &routine, NULL);
        i++;
    }
    i = 0;
     while (i < d)
    {
        pthread_join(th[i], NULL);
        i++;
    }
    return (0);
}

