#include <stdatomic.h>

void spinlock(atomic_flag * lock){
	while (atomic_flag_test_and_set(lock)){
		// busy wait
	}
}

void spinunlock(atomic_flag * lock){
	atomic_flag_clear(lock);
}