#include <pthread.h>
#include "reaction.h"

// Forward declaration. This function is implemented in reaction-runner.c,
// but you needn't care what it does. Just be sure it's called when
// appropriate within reaction_o()/reaction_h().
void make_water();


void reaction_init(struct reaction *reaction)
{
	pthread_mutex_init(&(reaction->mutex), NULL);
	pthread_cond_init(&(reaction->H_cond), NULL);
    pthread_cond_init(&(reaction->O_cond), NULL);
reaction->H_counter=0;
 reaction->O_counter=0;

}


void reaction_h(struct reaction *reaction)
{
    pthread_mutex_lock(&(reaction->mutex));
    reaction->H_counter++;
	if(reaction->H_counter>=2&&reaction->O_counter>=1){
      while(reaction->H_counter>=2&&reaction->O_counter>=1){
       reaction->H_counter-=2;
       reaction->O_counter--;
     make_water();
      pthread_cond_signal(&(reaction->H_cond));
     pthread_cond_signal(&(reaction->O_cond));
}
      }
      else {
      pthread_cond_wait(&(reaction->H_cond),&(reaction->mutex));
      }
      pthread_mutex_unlock(&(reaction->mutex));
        return ;
}


void reaction_o(struct reaction *reaction)
{
	pthread_mutex_lock(&(reaction->mutex));
	reaction->O_counter++;
	if(reaction->H_counter>=2&&reaction->O_counter>=1){
      while(reaction->H_counter>=2&&reaction->O_counter>=1){
        reaction->H_counter-=2;
       reaction->O_counter--;
     make_water();
      pthread_cond_signal(&(reaction->H_cond));
     pthread_cond_signal(&(reaction->H_cond));

      }}
      else {
      pthread_cond_wait(&(reaction->O_cond),&(reaction->mutex));
      }
      pthread_mutex_unlock(&(reaction->mutex));
     return ;
}


