struct queue
{
	int max_size;
	int start; // start index initially zero but is increased after pop out and eventually needs to be moved back
	int curr_size; // indicates highest index in the queue in use currently. Would indicate current queue size as long as start is at zero
	int *values;
};

int queue_size(queue *q)
{
	return q->curr_size - q->start;
}

int create_queue(queue *q, int max)
{
	if(q) {
		q->values = (int *)malloc(sizeof(int) * max);

		if(q->values)
		{
			q->max_size = max;
			q->start = 0;
			q->curr_size = 0;
			return 1; // success
		}		
	}

	return -1; //failure
}

int enqueue(queue *q, int val)
{
	// curr_size should always be on the next empty index i.e. 0 when empty, 1 with 1 element, 2 with 2 elements and so on
	if(q){
		if(q->curr_size < q->max_size) {
			q->values[q->curr_size] = val;
			q->curr_size++;
			return 1;
		}

		// TODO: We need to shift elements when queue reaches max size if there have been dequeues done already
		// Doing it only on max is because it is an expensive operation to move entire queue and should only be done when needed
		else { // curr_size is touching max

			// check if start is greater than 0.
			// if so, shift back entire queue by as many elements. (We can actually make it circular too by inserting in the beginning, but that would make code more complex
			// and the values start, max and current would have more cases to cover

			if(q->start > 0)
			{
				int idx;
				for(idx=0; q->start < q->curr_size; idx++) {
					q->values[idx] = q->values[q->start];
					q->start++;
				}

				q->start = 0;
				q->curr_size = idx;

				// Now do the enqueue after making space
				q->values[q->curr_size] = val;
				q->curr_size++;
				return 1;

			}
		}

	}

	return -1;
}

int dequeue(queue *q)
{
	// curr_size should always be on the next empty index i.e. 0 when empty, 1 with 1 element, 2 with 2 elements and so on
	if(q){
		if(q->start < q->curr_size){
			int r_val = q->values[q->start];
			q->start++;
			return r_val;
		}
	}

	return -1; // assuming it is an invalid value
}

// STACK USING QUEUES
struct stack
{
	queue *q1;
	queue *q2;
};

int push(stack *st, int val)
{
	// just enqueue in first queue
	return enqueue(st->q1, val);
}

int pop(stack *st)
{
	// if size of q1 is greater than 1, keep dequeueing from q1 and enqueue in q2
	int size = queue_size(st->q1);
	while(size > 1) {
		int tmp = dequeue(st->q1);
		enqueue(st->q2,tmp);
		size = queue_size(st->q1);
	}

	// dequeue and return the last element from q1
	int ret = dequeue(st->q1);

	// swap both queues before returning
	queue *tmp = st->q1;
	st->q1 = st->q2;
	st->q2 = tmp;
	return ret;
}

//push:
//enqueue in queue2
//enqueue all items of queue1 in queue2, then switch the names of queue1 and queue2
//pop:
//deqeue from queue1

// constant time pop, and linear time push implementation
int push_linear(stack *s, int val)
{
	int status = enqueue(s->q2, val);

	//printf("After enqueue in q2\n");

	//for(int c=0; c<5; c++)
	//	printf( "queue1index  %d has value %d\n", c, s->q1[c]);

	if(status == -1)
		return status;

	while(queue_size(s->q1) > 0) {
		int curr = dequeue(s->q1);
		status = enqueue(s->q2, curr);
	}

	queue *tmp = s->q1;
	s->q1 = s->q2;
	s->q2 = tmp;

	return status;
}

int pop_const(stack *s)
{
	return dequeue(s->q1);
}
