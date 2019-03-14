#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <conio.h>

struct Node
{
	Node *next;
	int data;
};

void print(Node *head)
{
	Node * temp = head;

	//printf("Printing list\n");
	while(temp)
	{
		printf("%d\t", temp->data);
		temp = temp->next;
	}
	printf("\n");
}

int add_at_hd(Node **hd, int v)
{
	Node *newNode = (Node *) malloc(sizeof(Node));

	if(!newNode)
		return -1;

	newNode->data = v;

	if(!*hd)
	{
		newNode->next = NULL;
		*hd = newNode;
	}

	else {
		newNode->next = *hd;
		*hd = newNode;
	}

	return 1;
}


Node * rev_list(Node *hd)
{
	Node *c = hd;
	Node *p= NULL;
	Node *n;

	while(c) {
		n = c->next; // save next pointer to move forward
		c->next = p; // point current's next to prev
		p = c; // only used for returning head of reversed list since c is null when loop terminates
		c = n; // move current forward in list
	}

	return p;
}


void rev_even_nodes(Node *hd)
{
	Node *list_even = NULL;
	Node *cur = hd;

	while(cur && cur->next){

		Node *even = cur->next; // next even node
		cur->next = even->next; // current list's next should point to next odd value

		// insert at head
		even->next = list_even; 
		list_even = even;

		cur = cur->next;

	}

	print(list_even);
	print(hd);


}

/*
Node *merge_lists(Node *od, Node *even)
{
	Node *e = even;
	Node *o = od;

	while(even && od->next) {
	
		//Node *temp = o->next; // keep next odd
		//o->next = e;
		//e->next = temp;

		//e = e->next;
		//o = o->next;

		Node * tmp = even;
		even = even->next;

		tmp->next = od->next;
		od->next = tmp;
		od = tmp->next;
	}

	if(!od->next)
		od->next = even;

	//return od;
	return o;
}
*/


// Hand coded with logic understood. Keep extending odd list by appending even nodes alternately 
Node * merge_lists(Node *od, Node *ev)
{
	Node *hd = od;

	while(od && ev) {

		// save next pointers
		Node *od_next = od->next;
		Node *ev_next = ev->next;

		// copy ev to odd list
		ev->next = od->next;
		od->next = ev;

		// update both to next pointers
		od = od_next;
		ev = ev_next;
	}

	return hd;
}

//Node * rvr_even_nd(Node *hd)
//{
//	Node *t = hd;
//	Node *even_list = NULL;
//
//	while(t && t->next) {
//
//		Node *even = t->next;
//		t->next = even->next;
//
//		even->next = even_list;
//		even_list = even;
//		t = t->next;
//	}
//
//	printf("Even list after reversal is\n");
//	print(even_list);
//	printf("And Odd list is \n");
//	print(hd);
//
//	Node *od = merge_lists(hd, even_list);
//
//	return od;
//}

// Hand coded
Node * rvr_even_nd(Node *hd)
{
	Node *t = hd;
	Node *e_list = NULL;
	Node *even_n = NULL;


	while(t && t->next)
	{
		even_n = t->next; // every next of t will be an even node

		t->next = even_n->next; // even's next is again odd, so original list should point to next odd
		
		//insert even at head of even list
		even_n->next = e_list;
		e_list = even_n;

		t = t->next;
	}

	printf("Even list after reversal is\n");
	print(even_n);
	printf("And Odd list is \n");
	print(hd);

	return NULL;

}


/// ========  //// TEST ATTEMPT - WORKED ALHAMDULILLAH

// reverse even nodes
Node *merge(Node *odd, Node *even)
{
	Node *ev_nxt, *od_nxt;
	Node *h = odd;

	while(odd && even){
		od_nxt = odd->next;
		ev_nxt = even->next;

		even->next = odd->next;
		odd->next = even;

		odd = od_nxt;
		even = ev_nxt;
	}

	return h;
}

Node * rev_even(Node *hd)
{
	Node *t =hd;
	Node *even = NULL;

	while(t && t->next) {
		Node *e = t->next;
		t->next = e->next;
		e->next = even;
		even = e;
		t = t->next;
	}

	Node *r = merge(hd, even);

	return r;
}


//2,4,6 1,3,5   

// Merge two halves of an array into the original one assuming there is enough space
// Hint to remember, start from right, since going from left you cannot avoid overwriting.
// However, this can only be done when you actually have two different arrays i.e. it won't
// work if you are using a single array
void merge_inplace(int a[], int b[], int sa, int sb) // a is big enough to hold both
{
	int c_idx = sa + sb - 1;
	int ia = sa-1;
	int ib = sb-1;

	while(ib >= 0 && ia >= 0) {
		if(b[ib] >= a[ia])
			a[c_idx--] = b[ib--];
		else
			a[c_idx--] = a[ia--];
	}

	if(ia < 0) {
		while(ib >=0)
			a[c_idx--] = b[ib--];
	}
}


#define SIZE 20

// REALLY REALLY TAKE CARE OF OFF BY ONE.
// When merging and copying, you never start array from zero
// always start from left.
// Thanks to http://www.cquestions.com/2011/07/merge-sort-program-in-c.html

// TODO: HAVE TO DO THE IN PLACE MERGE ASSUMING array has enough space as an exercise
void merge_arrays(int a[], int left, int mid, int right)
{
	int res[SIZE];

	int i=left;
	int j=mid+1;
	int k = left;

	for(;i<=mid && j<=right;)
	{
		if(a[i] <= a[j])
			res[k++] = a[i++];
		else
			res[k++] = a[j++];
	}

	if(i>mid){
		for (;j<=right;)
			res[k++] = a[j++];
	}

	if(j>right){
		for (;i<=mid;)
			res[k++] = a[i++];
	}

	// copy back to original array
	// ON THE CURRENT LEFT TO RIGHT
	for(int c=left; c<=right; c++)
		a[c] = res[c];

}

void partition(int a[], int left, int right)
{
	int mid;

	if(left < right) {
		mid = (left+right)/2;
		partition(a, left, mid);
		partition(a,mid+1, right);
		merge_arrays(a, left, mid, right);
	}
}

// WORKS FINE ON BOTH EVEN AND ODD ARRAYS
void merge_sort(int arr[], int size)
{
	partition(arr, 0, size);
}


// Find an element in a rotated array that was originally sorted e.g.
// (4 5 6 7 0 1 2).
// if found, return index else return -1
// courtesy http://leetcode.com/2010/04/searching-element-in-rotated-array.html
int find_el_rotated(int ar[], int size, int el)
{
	int left=0, right = size-1;

	while(left <= right) {
		int mid = (right - left) / 2 + left;

		if(ar[mid] == el)
			return mid;

		if(ar[mid] >= ar[left]) { // bottom half is sorted
			if (el >= ar[left]  && el < ar[mid]) // if number is in the bottom range go left
				right = mid-1;
			else // go right
				left = mid+1;
		}

		else { // upper half is sorted
			if (el >ar[mid]  && el <= ar[right]) // if number is in the upper half range, go right
				left = mid+1;
			else // go left
				right = mid-1;
		
		}
	}

	return -1;
}


// Find the index on which actual rotation happened
//(4 5 6 7 0 1 2)
int find_rotation_idx(int a[], int size)
{
	int left = 0, right = size-1, mid;

	while(a[left] > a[right]) {
		mid = (right - left)/2 + left;

		if(a[mid] > a[right]) // then number is on right, so go there
			left = mid+1;

		else right = mid;
	}

	return left;

}

// return index
int fnd_el(int a[], int size, int key)
{
	int l=0, r=size-1, m;

	while(l<=r) {
		m = (l+r)/2;

		if(key == a[m])
			return m;

		if(a[l] <= a[m]) // left side is sorted
		{
			if(a[l] <= key && key < a[m])
				r = m-1;
			else
				l = m+1;
		}

		else // right side is sorted
		{
			if(a[m] < key && key <= a[r])
				l = m+1;
			else
				r = m-1;
		}

	}

	return -1;
}

//7,9,10,1
int fnd_pivot(int a[], int size)
{
	int l=0, r=size-1, m;

	while(a[l] > a[r]){ // compared values not indexes
		m = (l+r)/2;

		if(a[m] > a[r]) { // left is not sorted
			l = m+1;
		}

		else {
			r = m;
		}
	}

	return l;
}

#define MAX 10


int coin_change(int denom[], int size, int sum)
{
	int *res = (int *)malloc( (sum+1) * sizeof(int));
	memset(res, 0,  (sum+1) * sizeof(int));

	
	if(!res)
		return -1; // error failed allocation

	res[0] = 1;

	//for(int a=0; a<  (sum+1) * sizeof(int); ++a)
	//	printf("%d\t", res[a]);

	// for each denom
	for(int i=0; i<size; ++i)
	{
 		int d = denom[i];
		// for each sum value starting from denom[i] to sum
		for(int j=d; j<sum+1; j++) {
			res[j] = res[j] + res[j-d];
			//printf("res[j]=%d\t", res[j]);
		}
	
	}

	return res[sum];
}


// largest consequtive sum in array
int subsum_conseq(int a[], int size)
{
	// find sum of array ending at each index using prior sums.
	// Keep one global and one current max

	int g_max = -1, c_max=-1;
	int st, end;

	for(int i=0; i<size; ++i)
	{
		if(c_max < 0) {
			c_max = a[i];
			st = i; // array starts here
		}
		else
			c_max += a[i];

		if(c_max > g_max) {
			g_max = c_max;
			end = i; // ends here
		}
	}

	while(st<=end)
		printf("%d\t", a[st++]);

	printf("\n");

	return g_max;
}


int main()
{
	int a[] = {-4,2,-5,1,2,3,6,-13,7,6};

	printf("SUM IS %d \n", subsum_conseq(a, sizeof(a)/sizeof(int)));

	//int d[] ={1,2,5};

	//for(int c=1; c<=10; ++c) {
	//	int ways = coin_change(d, sizeof(d)/sizeof(int), c);
	//	printf("%d can be summed in %d ways\n", c, ways);
	//}
	//int a[MAX] = {3,5,7,10};
	//int b[] = {6,8,9};

	//merge_inplace(a,b,4,3);

	//for(int i=0;i<MAX;i++)
	//	printf("%d\t", a[i]);
	//printf("\n");


	//int a[] = {4,5,6,7,9,10,1,2};

	//int idx =find_rotation_idx(a, sizeof(a) / sizeof(int));
	//printf("idx is %d\n", idx);

	//for(int f=0; f<=7; f++) {

	//	int r = find_el_rotated(a, sizeof(a)/sizeof (int), f);

	//	if(r>=0)
	//		printf("%d found at index %d\n", f,r);
	//	else
	//		printf("%d Not found\n", f);
	//};
	//int a[SIZE] = {5,4,1,8,7,2,6,3,20,19,18,17,16,15,14,13,12,11,10,9};

	//merge_sort(a, SIZE-1);

	//for(int i=0;i<SIZE; i++)
	//	printf("%d\t", a[i]);
	//printf("\n");
	//merge_sort
	//Node *root=NULL;

	//for(int i=0; i<6; i++)
	//	add_at_hd(&root,i);

	//print(root);
	//Node *res = rev_even(root);
	//printf("Printing list after reversal and merge\n");
	//print(res);

	_getche();
	return 0;
}
