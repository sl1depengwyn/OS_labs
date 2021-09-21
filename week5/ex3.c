#define _XOPEN_SOURCE 500
#define _REENTRANT
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <stdio.h>
#include <values.h>
#include <errno.h>
#include <signal.h>
#include <time.h>

#define BUF_SIZE 10 

int b[BUF_SIZE];
int in = 0, out = 0;

#define N_CONSUMERS 6
int arguments[N_CONSUMERS];
pthread_t consumer_id[N_CONSUMERS];
pthread_t producer;

pthread_mutex_t M;
pthread_mutexattr_t mattr;
pthread_cond_t  C;
pthread_condattr_t cattr;

void * consumer_body (void *arg) {

  int tmp;
  int self = *((int *) arg);

  fprintf(stdout, "consumer thread starts\n"); 
  for (;;) {
     pthread_mutex_lock (&M);
     
     while (out == in)
       if (pthread_cond_wait (&C, &M)) {
          fprintf (stdout, "pthread_cond_wait: consumer\n");
         exit (-1);
       }
     tmp = b[out];
       
     if (((in + 1) % BUF_SIZE) == out) pthread_cond_signal (&C);
     out = (out + 1) % BUF_SIZE;     
     
     pthread_mutex_unlock (&M);
     
     fprintf (stdout, "thread %d:", self);
     fprintf (stdout, "%d\n", tmp); fflush (stdout);
  }
  fprintf(stdout, "consumer thread exits\n"); 
  return NULL;
}
void * producer_body (void * arg) {

   int i;
   fprintf(stdout, "producer thread starts\n"); 
   for (i = 0; i < 100; i++) {
     
     pthread_mutex_lock (&M);
     
     while (((in + 1) % BUF_SIZE) == out)
       if (pthread_cond_wait (&C, &M)) {
          fprintf (stdout, "pthread_cond_wait: producer\n");
          exit (-1);
       }
     
     b[in] = i;
     in = (in + 1) % BUF_SIZE;
     
     pthread_mutex_unlock (&M);
     
     pthread_cond_signal (&C);
  }
  return NULL;
}

int main () {
   int i, result;
   pthread_attr_t attrs;
   sigset_t set;

   pthread_mutex_init (&M, NULL);
   pthread_cond_init (&C, NULL);
   
   pthread_attr_init (&attrs);
   
   pthread_attr_setscope (&attrs, PTHREAD_SCOPE_SYSTEM);
   
   if ((result = pthread_create(&producer,&attrs,producer_body,NULL)))   {
      fprintf (stdout, "pthread_create: %d\n", result);
      exit (-1);
   } 
   fprintf(stdout, "producer thread created\n");
   
   for (i = 0; i < N_CONSUMERS; i++) {
      arguments[i] = i;
      if ((result = pthread_create (
          &consumer_id[i],
          &attrs,
          consumer_body,
          &arguments[i]))) {
        fprintf (stdout, "pthread_create: %d\n", result);
        exit (-1);
      } 
   }
   fprintf(stdout, "consumer threads created\n");
   
   sigfillset (&set);
   sigdelset (&set, SIGINT);
   sigsuspend (&set);
   return 0;
}

