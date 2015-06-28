#ifndef _LIBC_LOCK_H
#define _LIBC_LOCK_H 1

#include <pthread.h>

#define __libc_lock_define_initialized(CLASS,NAME) \
  CLASS pthread_mutex_t NAME = PTHREAD_MUTEX_INITIALIZER;

#define __libc_once_define(CLASS, NAME) \
  CLASS pthread_once_t NAME = PTHREAD_ONCE_INIT;

#define __libc_lock_lock(NAME) \
  pthread_mutex_lock (&(NAME))

#define __libc_lock_unlock(NAME) \
  pthread_mutex_unlock (&(NAME))

/* Call handler iff the first call.  */
#define __libc_once(ONCE_CONTROL, INIT_FUNCTION) \
  do {                                           \
    if ((ONCE_CONTROL) == 0) {                   \
      INIT_FUNCTION ();                          \
      (ONCE_CONTROL) = 1;                        \
    }                                            \
  } while (0)


#endif	/* libc-lock.h */
