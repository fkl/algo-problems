
#include <iostream>

# include <sys/types.h>
# include <unistd.h>
# include <errno.h>

using namespace std;

struct tnode {
	tnode *left;
	tnode *right;
	int data;
};


void dfs(tnode * root) {
	if(!root)
		return;
	
	dfs(root->left);
	cout << root->data;
	dfs(root->right);
}

// Error checking is caller's job
tnode * createNode(int val) {
	
	tnode * newNode = new tnode;
	
	if(newNode) {
		newNode->data = val;
		newNode->left = NULL;
		newNode->right = NULL;
	}
	
	return newNode;
}

int insert_recurse(tnode *root, int v) {
	return 0;
}

bool insert(tnode * root, int v)
{
	tnode * it = root;
	tnode * newNode = createNode(v);
	
	while(it) {
		
		if(v < it->data){
			if (!it->left) {
				it->left = newNode;
				break;
			}
			else
				it = it->left;
		}
		else if (v > it->data) {
			if( !it->right) {
				it->right = newNode;
				break;
			}
			else
				it = it->right;
		}
	}
	
	return true;
}

// tnode * create_bst(int num_nodes) {}

void traverse(tnode *r)
{
	if(r == NULL)
		return;
	
	traverse(r->left);
	cout << r->data << " ";
	traverse(r->right);
}

int main(int argc, const char * argv[]) {
	
	tnode * tree = NULL;
	tree = createNode(10);
	insert(tree, 12); //  create_bst(3);
	insert(tree, 6); //  create_bst(3);
	insert(tree, 7);
	insert(tree, 11);
	
	// insert code here...
	std::cout << "Hello, root tree->val " << tree->data  << endl;
	std::cout << "Hello, root tree->left->val " << tree->left->data  << endl;
	std::cout << "Hello, root tree->right->val " << tree->right->data  << endl;
	
	traverse(tree);
  return 0;
}
