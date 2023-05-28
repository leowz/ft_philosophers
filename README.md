# Philosophers

42 project of Philosophers. A classical problem for multithreading and lock. The idea of this project is to avoid dead lock.

Dining philosophers problem’s definition is [here](https://en.wikipedia.org/wiki/Dining_philosophers_problem)

This problem was designed to illustrate the challenges of avoiding deadlock. That is when all philosophers picked up left fork and wait for the right fork to be available.

## Arbitrator solution

To guarantee that a philosopher can only pick up both forks or none by introducing an arbitrator, aka waiter. Philosophers let the arbitrator to give them forks and the arbitrator processes one request at a time.

---

## Multithreaded Programming

[tutorial](https://randu.org/tutorials/threads/)

Use different thread as different philosophers and start the simulation.

### Thread functions:

- pthread_create

```c
// create threads
int pthread_create(pthread_t *thread, pthread_attr_t *attr, 
                   void *(*start_routine)(void *), void *arg)
```

1. `pthread_t *thread`: the actual thread object that contains pthread id
2. `pthread_attr_t *attr`: attributes to apply to this thread
3. `void *(*start_routine)(void *)`: the function this thread executes
4. `void *arg`: arguments to pass to thread function above
- pthread_join

```c
// wait created threads to terminate
int pthread_join(pthread_t thread, void **retval);
```

1. `pthread_t thread` : The thread id that need to wait.
2. `void **retval`: The return values of all waited thread in an void * array
- pthread_detach

```c
// detach thread. Meanning this thread will automatically be recycled when finish
// it is detached from the main thread. No need to wait.
int pthread_detach(pthread_t thread);
```

1. `pthread_t thread` : The thread id that need to detach.
- pthread_mutex_init
- pthread_mutex_destroy

```c
// init the mutex defined equals to pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
int pthread_mutex_init(pthread_mutex_t *restrict mutex,
           const pthread_mutexattr_t *restrict attr);
// recycle the resource, destroy the mutex
int pthread_mutex_destroy(pthread_mutex_t *mutex);
```

- pthread_mutex_lock
- pthread_mutex_unlock

```c
// lock and unlock the mutex
int pthread_mutex_lock(pthread_mutex_t *mutex);
int pthread_mutex_trylock(pthread_mutex_t *mutex);
int pthread_mutex_unlock(pthread_mutex_t *mutex);
```

### Exponential Back Off Algorithm

In our algorithm, multiple thread philosophers will compete for resources here is forks. So they will send request to arbitrator for forks and when the request is too much, then the program will throttle.

In order to avoid the throttle for the requests for forks, I implemented a backoff algorithm. 

```c
void	cal_thinking_backoff_time(t_philo *philo, long ts)
{
	if (philo->status != THINKING)
	{
		philo->status = THINKING;
		philo->backoff = 37;
		log_philo_msg_ts(philo, "is thinking", ts);
	}
	else
	{
		philo->backoff *= 2;
		if (philo->backoff > 501)
			philo->backoff = 501;
	}
}
```

So the request interval is set initially at 36um. Meaning after first reject from the arbitrator, it will wait 37um for the next request, then the interval is multiplied by 2, until it reaches 501um. In the case, we can minimize throttle.

## Multi-process Programming

functions to use: fork, kill, exit, waitpid, sem_open, sem_close, sem_post, sem_wait, sem_unlink.

In this case, Philosophers are represented by processes created by fork(). And the since the forks are in the middle of the table for the philosophers, the total number is controlled by a semaphore.

- fork, waitpid, kill, exit

```c
// fork process, return 0 is children process, 
//otherwise return the pid of created chilren process
pid_t fork(void);
// wait for fork created process to end, block execution.
pid_t waitpid(pid_t pid, int *stat_loc, int options);
// send signal
int kill(pid_t pid, int sig);
// exit from process
void exit(int status);
```

### Semaphore

In computer science, a semaphore is a variable or abstract data type used to control access to a common resource by multiple threads and avoid critical section problems in a concurrent system such as a multitasking operating system. Semaphores are a type of synchronization primitive. A trivial semaphore is a plain variable that is changed (for example, incremented or decremented, or toggled) depending on programmer-defined conditions.

A useful way to think of a semaphore as used in a real-world system is as a record of how many units of a particular resource are available, coupled with operations to adjust that record safely (i.e., to avoid race conditions) as units are acquired or become free, and, if necessary, wait until a unit of the resource becomes available.

Semaphores are a useful tool in the prevention of race conditions; however, their use is not a guarantee that a program is free from these problems. Semaphores which allow an arbitrary resource count are called counting semaphores, while semaphores which are restricted to the values 0 and 1 (or locked/unlocked, unavailable/available) are called binary semaphores and are used to implement locks.

- sem_open, sem_init

```c
// open an semaphore by name, if not exist, then create one
sem_t *sem_open(const char *name, int oflag,
                       mode_t mode, unsigned int value);
// init an semaphore.
int sem_init(sem_t *sem, int pshared, unsigned int value);
```

- sem_post, sem_wait

```c
// reduce the value of the semaphore if value is alread 0, 
//then block until one is released
int sem_wait(sem_t *sem);
int sem_trywait(sem_t *sem);
// release an semaphore value, increment value of the semaphore.
int sem_post(sem_t *sem);
```

- sem_close, sem_unlink

```c
// close the semphore. release the resource,
int sem_close(sem_t *sem);
// if the semaphore is created by sem_open, 
//then releae the link between the semaphore and the file on disk created by semaphore open
int sem_unlink(const char *name);
```

### ps: free heap memory when forking

When you allocate memory using **`malloc`** and then fork multiple processes, each process will have its own copy of the memory space, including the allocated memory. In this case, it's important to note that freeing memory in one process does not automatically free the memory in the other processes.

To ensure proper memory management, you need to call **`free`** in each process that allocated memory using **`malloc`**. This means that each process should have its own call to **`free`** to deallocate the memory it allocated. You can determine which process is currently running by checking the return value of **`fork`**.