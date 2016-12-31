#include <stdio.h>
#include <stdbool.h>
/* Function to remove the front junction 
   from the queue and return it */
int deque(int queue[], int *queue_front, 
	  int *queue_back);
/* Function to add a new junction to the back of the queue */
void enque(int junction, int queue[], 
	   int *queue_front, int *queue_back);
/* Function to check if the queue is empty */
bool queueEmpty(int queue[], int *queue_front);
/* Function to find a route from source to destination */
bool findRoute(int neighbourhood[], int source, 
	       int dest, bool visited[], int queue[], 
	       int parent[]);
int readMap(int neighbourhood[], int *numjunctionsp);

int const MAX_JUNCTIONS = 10000;

int main(void)
{
  int neighbourhood[4*MAX_JUNCTIONS];
  int parent[MAX_JUNCTIONS];
  int queue[MAX_JUNCTIONS];
  bool visited[MAX_JUNCTIONS];
  int numjunctions;
  int i;
  int source, destination;
  int err;

  err = readMap(neighbourhood, &numjunctions);
  switch(err)
    {
    case -1:
      printf("Map is too large.\n");
      return -1;
      break;
    case -2:
      printf("Incorrect junction.\n");
      return -1;
    }
  printf("Enter source : ");
  scanf("%d", &source);
  printf("Enter destination : ");
  scanf("%d", &destination);

  printf("Route from %d to %d\n", source, destination);

  for (i=0;i<numjunctions;i++)
    {
      queue[i]=-1;
      parent[i]=-1;
      visited[i] = false;
    }

  if ( findRoute(neighbourhood, source, destination, visited, queue, parent) )
    {
      /* Print the route backwards from destination to source */
      i = destination;
      do
	{
	  printf("%d ", i);
	  i = parent[i];
	} while (i != -1);
    } 
  else
    {
      printf("No route exists from source %d to destination %d\n", source, destination);
    }
  return 0;
}


bool findRoute(int neighbourhood[], int source, 
	       int dest, bool visited[], int queue[], 
	       int parent[])
{
  int neighbour, j, curr_junction;
  bool dest_found = false;
  int queue_front=-1, queue_back=-1;
  /* Add the source junction to the queue */
  enque(source, queue, &queue_front, &queue_back);
  /* Record the source as visited */
  visited[source]=true;
  /* Keep searching until dest is found or
     the queue is empty */
  while (!dest_found && 
	 !queueEmpty(queue, &queue_front)) {
      /* Get current junction from queue */
      curr_junction = 
	deque(queue, &queue_front, &queue_back);
      /* Check if it is the destination */
      dest_found = (curr_junction == dest);
      if (!dest_found)
  /* Check four neighbours of current junction */
	for (j=0;j<4;j++) {
	    neighbour = 
	      neighbourhood[curr_junction*4+j];
	    if (neighbour != -1 
		&& !visited[neighbour])
	      {
		/* Set parent of neighbour */
		parent[neighbour] = curr_junction;
		/* Enqueue the neighbour */
		enque(neighbour, queue, 
		      &queue_front, &queue_back);
		/* Record the neighbour as visited */
		visited[neighbour]=true;
	      }
	  }
    }
  return dest_found;
}

void enque(int junction, int queue[], 
	   int *queue_front, int *queue_back)
{
  /* Get the values of front and back
     from the arguments */
  int front = *queue_front;
  int back = *queue_back;
  /* Add junction to the front of the queue, 
     making sure to update back if the queue 
     was originally empty */
  
  if (front != -1)
	queue[junction]=front;
  else
  {
	queue[junction]=-1;
	back = junction;
  }
  front = junction;
  
  /* Return values of front and back 
     in the arguments */
  *queue_front = front;
  *queue_back = back;
}

int deque(int queue[], int *queue_front, 
	  int *queue_back)
{  
  /* Get the values of front and back
     from the arguments */
  int front = *queue_front;
  int back = *queue_back;
  int junction = front;
  /* Remove junction from the queue */
  if (back == junction)
    back = -1;
  front = queue[front];
  queue[junction] = -1;
  /* Return the modified values of queue_front 
     and queue_back in the arguments */
  *queue_front = front;
  *queue_back = back;
  /* Return the junction that was at front of queue */
  return junction;
}
bool queueEmpty(int queue[], int *queue_front)
{
  return *queue_front == -1;
}


int readMap(int neighbourhood[], int *numjunctionsp)
{
  int numjunctions,i,d;
  /* First get the number of junctions  and check
     that it is not greater than the maximum size */
  scanf("%d", &numjunctions);
  if (numjunctions > MAX_JUNCTIONS)
      return -1;
  /* Next read the map into the neighbourhood array */
  for (i=0;i<numjunctions*4;i++)
    {
      d = scanf("%d", &neighbourhood[i]);
      if (d !=1 || neighbourhood[i]>=numjunctions 
	  || neighbourhood[i]<-1)
	{
	  printf("%d %d %d %d\n", d, neighbourhood[i], numjunctions, neighbourhood[i]<0);
	  return -2;
	}
    }
  /* Return the number of junctions in the argument */
  *numjunctionsp = numjunctions;
  /* Return value 0 to indicate successful reading */
  return 0;
}
