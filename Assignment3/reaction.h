#include <stdio.h>
#include <pthread.h>

struct reaction {
pthread_mutex_t mutex;
pthread_cond_t H_cond;
pthread_cond_t O_cond;
int H_counter;
int O_counter;


};

void reaction_init(struct reaction *reaction);

void reaction_h(struct reaction *reaction);

void reaction_o(struct reaction *reaction);
