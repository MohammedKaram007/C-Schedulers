#include <stdlib.h>
#include <stdio.h>
#define MAXBUFFER 10
typedef struct buffer{
   int front;
   int rear;
   int size;
   int entry[MAXBUFFER];
}Buffer;

int served;

void CreateBuffer(Buffer *pq){
	pq->front= 0;
	pq->rear = -1;
	pq->size = 0;
}
//Initializing front =5 and rear =4 will work if MAXBUFFER >=6. But, since MAXBUFFER can be 1 we intialize as above.

void Append(int e, Buffer* pq){
  if (pq -> rear == MAXBUFFER-1)
	pq -> rear = 0;
  else
	pq -> rear++;
  pq->entry[pq->rear] = e;
  pq->size++;
}

void Serve(int *pe, Buffer* pq){
  *pe = pq->entry[pq->front];
  pq->front = (pq->front + 1) % MAXBUFFER;
  pq->size--;
}

int BufferEmpty(Buffer* pq){
	return !pq->size;
}

int BufferFull(Buffer* pq){
	return (pq->size == MAXBUFFER);
}

int BufferSize(Buffer* pq){
	return pq->size;
}

void ClearBuffer(Buffer* pq){
	pq->front = 0;
	pq->rear  = -1;
	pq->size  = 0; 
}//same as CreateBuffer. No nodes to free.

void TraverseBuffer(Buffer* pq, void (*pf)(int)){
	int pos, s;
	for(pos=pq->front, s=0; s<pq->size; s++){
		(*pf)(pq->entry[pos]);
		pos=(pos+1)%MAXBUFFER;
	}
}


void main (){
	Buffer B;
	CreateBuffer (&B);
	Append (1, &B);
	Append (7, &B);
	Append (8, &B);
	Append (9, &B);
	Append (0, &B);
	Append (123, &B);
	Append (32, &B);
	Append (43, &B);
	Append (54, &B);
	Append (65, &B);
	Append (76, &B);//first served because of the circular overwrite
	Append (87, &B);
	Append (98, &B);
	Append (6, &B);
	Serve (&served, &B);
	printf("The served element is %d\n", served);
}

