#include <stdlib.h>
#include <stdio.h>
int show;
int content;
int traversePointer;
int x=0;
typedef struct queuenode{
	int entry;
	struct queuenode *next;
}QueueNode;

typedef struct queue{
	QueueNode *front;
	QueueNode *rear;
	int	size;	//old trick
}Queue;

void CreateQueue(Queue *pq){
   pq->front=NULL;
   pq->rear=NULL;
   pq->size=0;
}

void Serve(int *pe, Queue* pq){
	QueueNode *pn=pq->front;
	*pe=pn->entry;
	pq->front=pn->next;
	free(pn);
	if (!pq->front)
		pq->rear=NULL;
	pq->size--;
}

int QueueEmpty(Queue* pq){
	return !pq->front;
}

int QueueFull(Queue* pq){
	return 0;
}

int QueueSize(Queue* pq){
	return pq->size;
}


void ClearQueue(Queue* pq){
	while(pq->front){
		pq->rear=pq->front->next;
		free(pq->front);
		pq->front=pq->rear;
	}
	pq->size  = 0; 
}/*Moving with two pointers,
   Exactly as in LinkedStacks*/


void TraverseQueue(Queue* pq, void(*pf)(int)){
	for(QueueNode *pn=pq->front; pn; pn=pn->next)
		(*pf)(pn->entry);
}

void showContent(int content){
	printf("The Contained Entry is %d\n", content);
}

void addContent (int content){
	x = x+content;
}



int Append(int e, Queue* pq){
  QueueNode*pn=(QueueNode*)malloc(sizeof(QueueNode));
  if (!pn)
    return 0;
    /*This is much better than the Error message of  	the book because this is more flexible. Also, 	the same function for contiguous implementation 	has to return 1 always to have consistent 	interface*/
  else{
	pn->next=NULL;
	  pn->entry=e; 			
	  if (!pq->rear)
	    pq->front=pn; 
	  else
	    pq->rear->next=pn;//run time error for empty queue
	  pq->rear=pn;
	  pq->size++;
	}
    return 1;
  }

void main(){
/*
	show = QueueSize(&q);
	printf("Size of the queue %d\n"  , show) ; 
	Append (5,&q);
	show = QueueSize(&q);
	printf("Size of the queue %d\n"  , show) ; 
	Serve (&content, &q);
	printf("The served Entry is %d\n", content);
	show = QueueSize (&q);
	printf("Size after serving is %d\n", show);
	Append (7, &q);
	Append (8, &q);
	Append (9, &q);
	TraverseQueue(&q, showContent);
	TraverseQueue(&q, addContent);
	printf("The sum of the contents is %d\n",x);*/
	char str[10];
	int value;
 
	initial: do{
		printf("\nWelcome to client/server system.(I)nitialize or (Q)uit :");
		scanf("%s", str);

	}while(!(str[0]!='q'||str[0]!='Q'||str[0]!='i'||str[0]!='I'));
 
	if(str[0]=='q'||str[0]=='Q')
		goto quit;
	else {
		if (str[0] == 'I' || str[0] == 'i'){
			Queue q;
			CreateQueue (&q);
			printf("\n(R)equest for service as a client, or (Q)uit :");
			scanf("%s", str);
		more:	printf("\n(C)hoose a value to add or (F)inish: ");
			scanf("%s", str);
			if (str[0] == 'C' || str[0] == 'c'){
				printf("Enter a value\n");
				scanf("%d", &value);
				Append (value,&q);
				goto more;
			}
			else{
				if (str[0] == 'F' || str[0] == 'f')
					{
		more2:			printf("\n Click (S) to serve, or (C) to add a new value: ");
					scanf("%s", str);
					if (str[0] == 'C' || str[0] == 'c')
						goto more;
					else{
						if (str[0]=='S'||str[0]=='s')
							if (QueueEmpty(&q))
							printf("All clients have been served \n");
							else{
						Serve (&content, &q);
						printf("served value is %d\n", content);
						
						goto more2;
						}
						else
							goto more;
						}
					}
				else goto more;
			}
		}
		else{	
			goto initial;
		}
	}
 
 
	quit: printf("Thank you, shutting down now.\n");

}
