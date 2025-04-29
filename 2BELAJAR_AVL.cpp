#include <bits/stdc++.h>
using namespace std;

struct Node {
	Node *left;
	Node *right;
	int key;
	int height;
	Node (){
     key = 0 ;
	 height = 1;
	 right = left = NULL;
	}Node (int _key){
		 key = _key;
		 height = 1;
		 left = right = NULL;
	}
};
struct AVL{
	public:
	Node *root;
	int getHeight(Node *cur){
		if(cur == NULL)return 0;
		return cur->height;
	}
	Node *updateHeight(Node *cur){
		if(cur == NULL)return cur;
		cur->height = 1 + max(getHeight(cur->left),getHeight(cur->right));
	}
	int getBalance(Node *cur){
		if(cur == NULL)return 0;
		return getHeight(cur->left)-getHeight (cur->right);
		
	}
	Node *leftrotate(Node *y){
		Node *x = y->right;
		Node *T2 = x->left;
		y->right = T2; updateHeight(y);
		x->left = y;  updateHeight (x);
		return x;
	}Node *rightrotate(Node *x){
		Node *y = x->left;
		Node *T2 = y->right;
		x->left = T2; updateHeight(x);
		y->right = x; updateHeight (y);
		return y;
	}Node *rebalancing(Node *cur){
		if(getBalance(cur) < -1){
			if(getBalance(cur->right)> 0 ){
				cur->right = rightrotate(cur->right);
			}
			cur = leftrotate(cur);
		}else if(getBalance(cur) > 1){
			if(getBalance(cur) < 0){
				cur->left = leftrotate(cur->left);
			}
			cur = rightrotate(cur);
		}
	}
	
	Node *insert(Node *cur, int key){
		if(cur == NULL){
			return new Node (key);
		}if(key == cur->key){
			return cur;
		}if(key < cur->key){
			cur->left = insert(cur->left,key);
		}if(key > cur->key){
			cur->right = insert (cur->right,key);
		}
		updateHeight(cur);
		return rebalancing(cur);
	}Node *erase(Node *cur , int key){
		if(cur == NULL){
			return cur;
		}if(key < cur->key){
			cur->left = erase (cur->left,key);
		}if(key > cur->key){
			cur->right = erase (cur->right,key);
		}else{
			if(cur->left == NULL && cur->right == NULL){
				delete cur;
				return NULL;
			}else if(cur->left != NULL && cur->right != NULL){
				int succ = findMin(cur->right);
				cur->key = succ;
				cur->right = erase(cur->right,succ);
			}else if(cur->left != NULL){
				Node *temp = cur;
				cur = cur->left;
				delete temp;
			}else{
				Node *temp = cur;
				cur = cur->right;
				delete temp;
			}
		}
			updateHeight(cur);
		return rebalancing(cur);
	}
	
	int findMin(Node *cur){
		if(cur->left == NULL) return cur->key;
		return findMin(cur->left);
	}
	void debug(Node *cur){
		debug(cur->left);
		cout<<cur->key<<","<<cur->height<<" ";
		debug(cur->right);
	}
	public:
		AVL(){
			root = NULL;
		}
		void insert(int key){
			insert(root,key);
		}void erase(int key){
			erase(root,key);
		}void debug(){
			debug(root);
		}
	
};
int main() {
	AVL A;
	for (int i = 0; i < 100000; i++) A.insert(i);
	for (int i = 0; i < 100000; i++) A.erase(i);
	return 0;
}
