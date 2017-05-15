#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

/* number of matrix columns and rows */
#define X 3
#define Y 4
#define Z 5

int A[X][Y];
int B[Y][Z];
int C[X][Z];

/*** functions for non threaded multiplications ****/
int dotProduct(int r, int c)
// r and c are the row and coloumn of matrices A and B, respectively
{     int i,j;
	C[r][c]=0;
// Calculate the dot product of the row r from A with the column c from B
      for(i=0;i<Y;i++){
      C[r][c]+=A[r][i]*B[i][c];

}

}
void print_array(char c){
int i,j;
if(c=='A'){
printf("//////////////////A///////////////////////\n");
for(i=0;i<X;i++){
for(j=0;j<Y;j++){
printf("%d  ",A[i][j]);

}
printf("\n");

}
}
if(c=='B'){
printf("//////////////////B///////////////////////\n");
for(i=0;i<Y;i++){
for(j=0;j<Z;j++){
printf("%d  ",B[i][j]);

}
printf("\n");
}
}

}

void zprint(FILE *zPtr){
int i,j;
for(i=0;i<X;i++){
for(j=0;j<Z;j++){
fprintf( zPtr, "%d ",C[i][j]);
}
fprintf( zPtr, "%c ",'\n');
}



}
void nonThreadedMatMult()
{int i,j;
	// Loop over every point in the matrix C and calculate it by calling
	for(i=0;i<X;i++){
        for(j=0;j<Z;j++){
        // the dot product fuction
	dotProduct(i, j);
	// Print the elements of C
}
}

}

/*** functions for threaded element multiplications ****/

struct thread_data
{
int i;//row
int j;//column
	// You may need this fill this struct to pass and receive data from
	// threads
};
struct thread_data thread_data_array[X*Z];

void *dotProductThreadElem(void *threadArgs)
// Element by element threaded calculation
{   struct thread_data *data = threadArgs;

	// Exctract the passed arguments from the threadArgs structure
	// Calculate the dotProduct
       dotProduct(data->i,data->j);
	// Exit the thread
           pthread_exit(0);
}

void threadedMatMultPerElement()
{	pthread_t threads[X*Z];
	// Create X*Z threads and pass the appropriate threadArgs to it
     int i,j, count = 0;
   for(i = 0; i < X; i++) {
      for(j = 0; j < Z; j++) {
         //Assign a row and column for each thread
         struct thread_data *data = (struct thread_data *) malloc(sizeof(struct thread_data));
         data->i = i;
         data->j = j;
    pthread_create(&threads[count],NULL,dotProductThreadElem,data);
	// Join the X*Z threads
pthread_join(threads[count], NULL);
      count++;
      }
   }
	// Print the elements of C

}

/*** functions for threaded row multiplications ****/
// Similar to the element multiplication but only X threads are created

void *MultiRow(void *threadArgs){
  int *data=threadArgs;
  int j;
   for(j=0;j<Z;j++){
     dotProduct(*data,j);
	// Exit the thread

}
pthread_exit(0);
}
void threadedMatMultPerRow()
{	pthread_t threads[X];
	// Create X*Z threads and pass the appropriate threadArgs to it
     int i,j, count = 0;
   for(i = 0; i < X; i++) {
         //Assign a row and column for each thread
         int *data = malloc(sizeof(int));
         *data = i;
    pthread_create(&threads[count],NULL,MultiRow,data);
// Join the X*Z threads
pthread_join(threads[count], NULL);
      count++;
      }

	// Print the elements of C
}
int main(int argc, char *argv[])
{  FILE *xPtr,*yPtr,*zPtr;
int i, j;
if ( ( xPtr = fopen( "X.dat", "r" ) ) == NULL ) {
 printf( "File could not be opened\n" );
 }
rewind( xPtr );
for (i= 0;i<X;++i)
		for (j= 0;j<Y;++j)
			fscanf( xPtr, "%d", &A[i][j]);
print_array('A');

if ( ( yPtr = fopen( "Y.dat", "r" ) ) == NULL ) {
 printf( "File could not be opened\n" );
 }
rewind( yPtr );
for (i= 0;i<Y;++i)
		for (j= 0;j<Z;++j)
			fscanf( yPtr, "%d", &B[i][j]);

print_array('B');
if ( ( zPtr = fopen( "Z.dat", "w" ) ) == NULL ) {
 printf( "File could not be opened\n" );
 }
rewind(zPtr );
        nonThreadedMatMult();
fprintf( zPtr, "%s\n ","//////////////////C///////////////////////");
zprint(zPtr);

	threadedMatMultPerElement();
fprintf( zPtr, "%s\n ","//////////////////C///////////////////////");
zprint(zPtr);
	threadedMatMultPerRow();
fprintf( zPtr, "%s\n ","//////////////////C///////////////////////");
zprint(zPtr);
	return 0;
}

