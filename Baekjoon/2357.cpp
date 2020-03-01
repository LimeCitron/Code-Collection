#include <cstdio>
using namespace std;
const int ARRMAX = (512 * 512) + 1;
const int CONSTMAX = 1000000001;
const int CONSTMIN = 0;

typedef struct seg_tree {
	int start;
	int end;
	int min;
	int max;
}seg_tree;

seg_tree tree[ARRMAX] = { (0, 0, 0), (0, 0, 0), };
int N, M;

int getMin(int a, int b) { return (a < b ? a : b); }
int getMax(int a, int b) { return (a > b ? a : b); }

int treeMinimum(int left, int right, int now) {
	int result = CONSTMAX;
	if (tree[now].end < left || tree[now].start > right)
		return CONSTMAX;
	if (left <= tree[now].start && tree[now].end <= right)
		return tree[now].min;
	result = getMin(treeMinimum(left, right, now * 2), treeMinimum(left, right, now * 2 + 1));
	return result;
}

int treeMaximum(int left, int right, int now) {
	int result = CONSTMIN;
	if (tree[now].end < left || tree[now].start > right)
		return CONSTMIN;
	if (left <= tree[now].start && tree[now].end <= right)
		return tree[now].max;
	result = getMax(treeMaximum(left, right, now * 2), treeMaximum(left, right, now * 2 + 1));
	return result;
}

void tree_init(int start, int end, int now) {
	tree[now].start = start;
	tree[now].end = end;
	if (tree[now].start != tree[now].end) {
		tree_init(start, (start + end) / 2, now * 2);
		tree_init((start + end) / 2 + 1, end, now * 2 + 1);
		tree[now].min = getMin(tree[now * 2].min, tree[now * 2 + 1].min);
		tree[now].max = getMax(tree[now * 2].max, tree[now * 2 + 1].max);
	}
}

int getStartOfTree() {
	int level = 1;
	int temp = N - 1;
	int result = 1;
	while (temp > 1) {
		level++;
		temp = temp / 2;
	}
	for (int i = 1; i <= level; i++)
		result = result * 2;
	return result;
}

void inputdata() {
	int value;
	scanf("%d %d", &N, &M);
	int start_num = getStartOfTree();

	for (int i = 0; i < N; i++) {
		scanf("%d", &value);
		tree[start_num + i] = { i + 1, i + 1, value, value };
	}
	tree_init(1, start_num, 1);
}

void inputCommand() {
	int start, end;
	for (int i = 0; i < M; i++) {
		scanf("%d %d", &start, &end);
		printf("%d %d\n", treeMinimum(start, end, 1), treeMaximum(start, end, 1));
	}
}

int main() {
	inputdata();
	inputCommand();
	return 0;
}