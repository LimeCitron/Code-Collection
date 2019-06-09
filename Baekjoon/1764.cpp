#include <iostream>
using namespace std;

const int STRINGMAX = 21;
const int HASHMAX = 100003;

typedef struct _node Node;
typedef struct _node {
	char text[STRINGMAX];
	Node* link;
}Node;

typedef struct _tree Tree;
typedef struct _tree {
	Node* stringNode;
	Tree* left;
	Tree* right;
}Tree;


Tree* stack[500000];
Node* hashTable[HASHMAX];
Tree* root = NULL;
int totalcount = 0;





void StringCopy(char* dest, char* src) {
	int i = 0;
	while (src[i] != '\0') {
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
}

int StringCompare(char* txt1, char* txt2) {
	int i = 0;
	while (1) {
		if (txt1[i] > txt2[i])
			return -1;
		else if (txt1[i] < txt2[i])
			return 1;
		else if (txt1[i] == '\0' && txt2[i] == '\0')
			return 0;
		else
			i++;
	}
}

Node* NodeInsert(Node* next, char* txt) {
	Node* newNode = new Node;
	StringCopy(newNode->text, txt);
	newNode->link = next;

	return newNode;
}

void TreeInsert(Node* strNode) {
	Tree* prevTree = root;
	int comres;

	Tree* newTree = new Tree;
	newTree->stringNode = strNode;
	newTree->left = NULL;
	newTree->right = NULL;

	if (root == NULL) {
		root = newTree;
	}
	
	while (prevTree != NULL) {
		comres = StringCompare(prevTree->stringNode->text, strNode->text);
		if (comres == 1) {
			if(prevTree-> right != NULL)
				prevTree = prevTree->right;
			else {
				prevTree->right = newTree;
				break;
			}
				
		}
		else if (comres == -1) {
			if (prevTree->left != NULL)
				prevTree = prevTree->left;
			else {
				prevTree->left = newTree;
				break;
			}
		}
	}	
}

void TreeTraversal(Tree* treenode) {
	int top = -1;
	Tree* now = treenode;

	if (now == NULL)
		return;

	while (1) {
		while (now != NULL) {
			top++; 
			stack[top] = now;
			now = now->left;
		}
		now = stack[top];
		top--;
		if (now == NULL)
			break;
		cout << now->stringNode->text << endl;
		now = now->right;
	}
}


int hashFun(char* txt) {
	int ret = 0;
	int i = 1;
	while (txt[i] != '\0') {
		ret = (ret + ((((txt[i] - '0') * i * i ) + i) % HASHMAX) % HASHMAX);
		i++;
	}
	return ret % HASHMAX;
}

int main() {

	int N, M, key;
	char input[STRINGMAX];
	Node* prevNode;
	cin >> N >> M;
	for (int i = 0; i < N; i++) {
		cin >> input;
		key = hashFun(input);
		prevNode = hashTable[key];
		hashTable[key] = NodeInsert(prevNode, input);
	}

	for (int i = 0; i < M; i++) {
		cin >> input;
		key = hashFun(input);
		prevNode = hashTable[key];

		while (prevNode != NULL) {
			if (StringCompare(prevNode->text, input) == 0) {
				totalcount++;
				TreeInsert(prevNode);
				break;
			}
			prevNode = prevNode->link;
		}
		
	}

	cout << totalcount << endl;
	TreeTraversal(root);
	
	return 0;
}