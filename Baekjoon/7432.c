#include <stdio.h>
#include <malloc.h>

typedef struct _Node Node;
typedef struct _Node {
	char data[85];
	int level;
	Node* link;
	Node* child;
}Node;

Node* head;
int n;

void init(); 
int InputData();
int CompareString(char* a, char* b);
int StringCopy(char* target, char* source);
int StringProcess(char* a, int level);
Node* MakeNode(char* inputData, int level, Node* parent);


void preorder(Node* now) {
	for (int i = 0; i < now->level; i++) printf(" ");
	printf("%s\n", now->data);

	if (now->child != NULL)
		preorder(now->child);
	if (now->link != NULL)
		preorder(now->link);
	free(now);
}


Node* MakeNode(char* inputData, int level, Node* parent) {
	Node* now = parent->child;
	Node* remember = NULL;
	
	while (1) {
		if (now == NULL || CompareString(now->data, inputData) == -1) 
			break;

		else if (CompareString(now->data, inputData) == 1) {
			remember = now;
			now = now->link;
		}
		else if (CompareString(now->data, inputData) == 0) {
			return now;
		}
	}

	Node* newNode = (Node*)malloc(sizeof(Node));
	StringCopy(newNode->data, inputData);
	newNode->level = level;
	newNode->child = NULL;

	if (remember == NULL) {
		newNode->link = now;
		parent->child = newNode;
	}
	else {
		newNode->link = remember->link;
		remember->link = newNode;
	}
	return newNode;
}

int StringProcess(char* a, int lev) {
	char nowData[85];
	char* nowHere = a;
	int level = lev;
	int index = 0;
	Node* nowNode = head;
	
	while (1) {
		if (*nowHere == '\0' || *nowHere == '\\') {
			nowData[index] = '\0';
			nowNode = MakeNode(nowData, level, nowNode);
			index = 0;
			if (*nowHere == '\0')
				break;
			else {
				nowHere = nowHere + 1;
				level++;
				continue;
			}
		}
		nowData[index] = *nowHere;
		index++;
		nowHere = nowHere + 1;
	}
	return 0;
}


int InputData() {
	char inputData[85];
	int k;
	scanf("%d", &n);
	for (k = 0; k < n; k++) {
		scanf("%s", inputData);
		StringProcess(inputData, 0);
	}
}

int CompareString(char* a, char* b) {
	int k = 0;
	while (1) {
		if (*(a + k) == '\0' && *(b + k) == '\0') return 0;
		else if (*(a + k)> *(b + k)) return -1;
		else if (*(b + k) > *(a + k)) return 1;
		else {
			k++;
		}
	}
	return -100;
}

int StringCopy(char* target, char* source) {
	char* now = source;
	char* targetnow = target;
	while (1) {
		*targetnow = *now;
		if (*now == '\0')
			break;
		*targetnow++;
		*now++;
	}
	return 0;
}


void init() {
	head = (Node*)malloc(sizeof(Node));
	head->data[0] = '\0';
	head->child = NULL;
	head->level = -1;
}

int main() {
	init();
	InputData();
	preorder(head->child);

	return 0;
}