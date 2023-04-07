#include <stdio.h>
#include <sys/time.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include "../include/philo.h"

// int main()
// {
//     struct timeval time1;
//     struct timeval time2;
//     float diff_time;
//     gettimeofday(&time1, NULL);
//    printf("sec: %d, usec: %d\n", (int)time1.tv_sec, (int)time1.tv_usec);
//     /** Describe Function for Measurement of time **/
//     gettimeofday(&time2, NULL);
//    printf("sec: %d, usec: %d\n", (int)time2.tv_sec, (int)time2.tv_usec);
//     diff_time = time2.tv_sec - time1.tv_sec +  (float)(time2.tv_usec - time1.tv_usec) / 1000000;
//     printf("diff: %f[s]\n", diff_time);
//     return 0;
// }

// int main(int argc, char **argv)
// {
//     struct timeval tp;
//     gettimeofday(&tp, NULL);
//     printf("tp.tv_sec:%zu\n", tp.tv_sec);//seconds
//     printf("tp.tv_usec:%d\n", tp.tv_usec);//micorseconds

//     // size_t ret = get_time();
//     // printf("get_time():%zu\n", ret);
//     printf("_______________\n");
//     size_t start_sec = tp.tv_sec;
//     size_t start_mic = tp.tv_usec;
// 	while (1)
// 	{
// 		usleep(25);
// 		gettimeofday(&tp, NULL);
// 		size_t now_sec = tp.tv_sec;
// 		size_t now_mic = tp.tv_usec;
// 		size_t now_time = (now_sec * 1000 - start_sec * 1000) + (now_mic / 1000 - start_mic / 1000);
// 		if (now_time % 100 == 0)
// 			printf("second information:%zu\n", now_time);
// 	}
// 	return 0;
// }

// int main(int argc, char **argv)
// {
//     struct timeval tp;
//     gettimeofday(&tp, NULL);
//     printf("tp.tv_sec:%zu\n", tp.tv_sec);//seconds
//     printf("tp.tv_usec:%d\n", tp.tv_usec);//micorseconds

//     // size_t ret = get_time();
//     // printf("get_time():%zu\n", ret);
//     printf("_______________\n");
//     size_t second = tp.tv_sec * 1000;
//     printf("second information:%zu\n", second);
//     size_t microsecond = tp.tv_usec / 1000;
//     printf("microsecond information:%zu\n", microsecond);
//     size_t millisecond = second + microsecond;
//     printf("millisecond information:%zu\n", millisecond);
// }

typedef struct s_data
{
	int				sum;
	pthread_mutex_t	*mutex;
}	t_data;

void	*thread_func(void *arg)
{
	int				i;
	t_data			*data;

	data = (t_data *)arg;
	i = 0;
	while (i < 100000)
	{
		pthread_mutex_lock(data->mutex);
		data->sum++;
		i++;
		pthread_mutex_unlock(data->mutex);
	}
	return (NULL);
}

int	main(void)
{
	pthread_t		th[2];
	t_data			data;
	pthread_mutex_t	mutex;

	data.sum = 0;
	pthread_mutex_init(&mutex, NULL);
	data.mutex = &mutex;
	pthread_create(&th[0], NULL, thread_func, &data);
	pthread_create(&th[1], NULL, thread_func, &data);
	pthread_join(th[0], NULL);
	pthread_join(th[1], NULL);

	printf("sum = %d\n", data.sum);
}
