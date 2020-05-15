#ifndef PTHREAD_SPINLOCK_H
#define PTHREAD_SPINLOCK_H

//function declaration

typedef int pthread_spinlock_t;

int pthread_spin_init(pthread_spinlock_t* lock, int pshared);

int pthread_spin_destroy(pthread_spinlock_t* lock);

int pthread_spin_lock(pthread_spinlock_t* lock);

int pthread_spin_trylock(pthread_spinlock_t* lock);

int pthread_spin_unlock(pthread_spinlock_t* lock);

#endif