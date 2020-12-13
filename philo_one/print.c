
#include "philo.h"

void	print_msg(int id, int msg)
{
	struct timeval time;
	char str[50];

	gettimeofday(&time, NULL);
	if (msg == MSG_FORK)
		strcpy(str, "has taken a fork");
	else if (msg == MSG_EAT)
		strcpy(str, "is eating");
	else if (msg == MSG_SLEEP)
		strcpy(str, "is sleeping");
	else if (msg == MSG_THINK)
		strcpy(str, "is thinking");
	else if (msg == MSG_DIED)
		strcpy(str, "died");

	printf("%d %d %s\n", get_timestamp(&time), id, str);
}
