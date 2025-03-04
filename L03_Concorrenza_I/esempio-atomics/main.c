#include <stdio.h>
#include <threads.h>
#include <stdatomic.h>

atomic_int atomic_value = 0;
int value = 0;

int thread_func(void *arg)
{
	for (int i = 0; i < 1000000; i++)
	{
		atomic_value++;
		value++;
	}

	return 0;
}

int main()
{
	const int N = 5;
	thrd_t threads[N];
	int thread_ids[] =	{0, 1, 2, 3, 4};

	for (int i = 0; i < N; i++)
	{
		thrd_create(
			&threads[i],
			thread_func,
			&thread_ids[i]
		);
	}

	for (int i = 0; i < N; i++)
	{
		int ret = thrd_join(threads[i], NULL);
		if (ret == thrd_success)
		{
			printf("Thread %d terminato correttamente.\n", i);
		}
		else
		{
			printf("Errore nel join del thread %d\n", i);
		}
	}

	printf("Valore finale variabile non atomica: %d\n", value);
	printf("Valore finale variabile atomica: %d\n", atomic_value);

	printf("Termine.\n");
	return 0;
}