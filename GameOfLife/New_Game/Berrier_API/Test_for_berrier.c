#include "ADT_Berrier.h"

#include "mu_test.h"

#include <pthread.h>		/*For pthreads*/
#include <stdlib.h>			/*For malloc*/
#include <stdio.h>

#define MAX_THREADS 5
#define MAX_Iter 30

int _thelastThread (void* _context)
{
	printf("im the last!!!!!!\n");
	
	return 0;
}


void* WaitThread(void* _berrier)
{
	BERRErr err;

	err = BarrierWait((Barrier*)_berrier);

	pthread_exit(0);
}


/************************************/
/*Test for init*/
/************************************/
UNIT(Init_berrier)

	Barrier* berrier;
	unsigned int count = MAX_THREADS;
	
	berrier = BarrierInit( count, _thelastThread, NULL);
	ASSERT_THAT(NULL != berrier);
	
END_UNIT


/************************************/
/*Test for BarrierWait*/
/************************************/
UNIT(Inset_with_2_threads)

	Barrier* berrier;
	unsigned int count = MAX_THREADS;
	pthread_t th[MAX_Iter];	
	int i;
	
	berrier = BarrierInit( count, _thelastThread, NULL);
	ASSERT_THAT(NULL != berrier);
	
	for(i = 0; i < MAX_Iter; ++i)	
	{
		if( pthread_create(&th[i], NULL, WaitThread, (void*) berrier) < 0 )
		{
			perror("pthread_create");
		}
	}
	
	for(i = 0; i < MAX_Iter; ++i)	
	{
		pthread_join(th[i], NULL);
	}
	
END_UNIT


TEST_SUITE(Test For Berrier)  /* main */
 
	TEST(Init_berrier)
	TEST(Inset_with_2_threads)

END_SUITE

