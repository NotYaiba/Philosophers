#include "philosophers.h"


int	get_time(void)
{
	struct timeval	time;
	unsigned int	i;

	gettimeofday(&time, NULL);
	i = (unsigned int)time.tv_sec;
	return ((time.tv_sec * 1000));
}
