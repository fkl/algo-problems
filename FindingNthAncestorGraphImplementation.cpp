#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <conio.h>

//////////////////////////////////////////////////////////

//////////// GRAPH CREATION AND UTILITY API /////////////////

#define NAME_LEN 25

struct vertex;

struct edge
{
	edge *next; // next edge to/from current vertex
	vertex *dst;  // pointer to destination vertex of current edge
};

struct vertex
{
	char name[NAME_LEN]; // current vertex's value
	edge *edges; // list of edges it points to
};

struct graph
{
	vertex *v_array;
	int num_vertices;
};

// Creates graph with only vertices - null edges
struct graph* create_graph(int vcount, char **ar)
{
	graph *gp = (graph *)malloc(sizeof (graph));
	
	if(gp) {
		gp->num_vertices = vcount;
		gp->v_array =  (vertex *)malloc(sizeof (vertex) * vcount);

		if(gp->v_array) { //
			for(int c=0; c<vcount; c++) {
				gp->v_array[c].edges = NULL;
				strcpy(gp->v_array[c].name, ar[c]);
			}
		}
	}

	return gp;
}

// add edges between frm and to - which are string values
void insert_edge(graph *gp, char *frm, char * to)
{
	int fr_idx, to_idx; // indexes of vertices 

	for(int ctr=0; ctr < gp->num_vertices; ctr++)
	{
		if(strcmp(gp->v_array[ctr].name, frm) == 0)  // have to be null terminated strings,
			fr_idx = ctr;
		else if(strcmp(gp->v_array[ctr].name, to) == 0)
			to_idx = ctr;
	}

	// TODO: No need to create parent->child edge - Hence commented out for now. BACK UP latter
	//edge *new_edge = (edge *)malloc(sizeof edge);

	//if(new_edge) { // Create new edge and assign its destination
	//	new_edge->dst = &(gp->v_array[to_idx]);
	//	new_edge->next = gp->v_array[fr_idx].edges;
	//}

	//gp->v_array[fr_idx].edges = new_edge;	

	// TODO - See if we need to add the reverse edge
	// We need the reverse edge for searching from child to parent
	edge *rev_edge = (edge *)malloc(sizeof edge);

	if(rev_edge) { // Create new edge and assign its destination
		rev_edge->dst = &(gp->v_array[fr_idx]);
		rev_edge->next = gp->v_array[to_idx].edges;
	}

	gp->v_array[to_idx].edges = rev_edge;	

}

////////////////////////////////////////

struct req
{
	char child[NAME_LEN]; // names simple arrays
	char parent[NAME_LEN];
};

// UPDATE - Todo - Can this function check if there is an edge from child to parent????
// Verify if there is an edge between parent and child, then we have found the correct child node.
// This helps to cater multiple children with same names, without adding any extra memory assuming at least the parent name would be different.
// Though we could use additional factors such as age, dob etc stored in vertex for further verification
// Returns NULL if not connected and the dst vertex (parent) if connected.
 vertex * IsConnected(graph *g, int prnt_idx, int chld_idx)
{
	// for each edge in parent's edge list (UPDATE - EACH IN CHILD if there is a parent)
	for(edge *tmp= g->v_array[chld_idx].edges; tmp!=NULL;)
	{
		if(tmp->dst == &(g->v_array[prnt_idx])) // if edge points to Parent (this could also have been checked by string comparing names)
			return &(g->v_array[chld_idx]); // return pointer to child 
		tmp = tmp->next;
	}

	return NULL;
}

// Locates the vertex that we are treating as child from the graph
vertex * find_node(graph *g, req* requester)
{ 
	int child_idx=-1, prnt_idx=-1;
	bool chld_fnd = false, prnt_fnd = false; 

	// With the graph representation i chose, iterating the vertices was simpler, so i did that instead of a DFS or BFS like fashion 
	for(int idx=0; idx < g->num_vertices; idx++) {
		
		// Look for both child and parent name match and remember their indexes
		if(!chld_fnd) {
			if (strcmp(g->v_array[idx].name, requester->child) == 0){
				child_idx = idx;
				chld_fnd = true;
			}
		}
		
		else if(!prnt_fnd)
		{
			if (strcmp(g->v_array[idx].name, requester->parent) == 0) {
				prnt_idx = idx;
				prnt_fnd = true;
			}
		}

		if(chld_fnd && prnt_fnd) { // if both found, check if they are parent child

			// TODO: THIS WOULD BE A PROBLEM NOW because of two edges. Whether parent or child, we would find an edge both ways
			vertex *child = IsConnected(g, prnt_idx, child_idx);

			if(child) // if so then return the child else continue looking
				return child;
			else { // reset the flags
				chld_fnd = false;
				prnt_fnd = false;
			}
		}
			
    }
    
	// failed finding the edge
	return NULL;
}


void recurse_nthParent(vertex *gv, int count, int n)
{
	if(count == n) {
		printf(" %dth Parent name %s\n", n, gv->name);
		return;
	}

	// for all edges of the current Node
	// recurse nthparent(count+1, n); 
	//for(int idx=0; idx < gv->edgesnum_vertices; i++)
	for(edge *tmp=gv->edges; tmp!=NULL;)
	{
		vertex *node = tmp->dst; // we have to send next vertex
		recurse_nthParent(node,count+1, n);
		tmp = tmp->next;
	} 

}

void findNthParent(vertex *child, int n)
{
	int count=0; 
	recurse_nthParent(child, count, n);
}

// Driver and test program
int main()
{
	char * names [] = {"first", "sec", "third", "frth", "fifth"};
	graph *g = create_graph(5, names);

	// TODO: For now we are only inserting one way edges (parent to child - directed graphs) but can be changed if needed
	insert_edge(g, "sec", "first");
	insert_edge(g, "third", "sec");
	insert_edge(g, "frth", "third");

	// TODO: The reverse case (sec and first still found second - check and fix that)
	req r = {"first", "sec"};  
	vertex * child = find_node(g,&r);

	if(child)
		// gn is not necessarily the node we start from
		printf("The person whose parent we are finding is %s \n", child->name);

	else {
		printf("Child does not exist in graph \n");
		return 0;
	}

	for(int n=1; n<=4; n++)
		findNthParent(child, n); 
	_getche();
}
