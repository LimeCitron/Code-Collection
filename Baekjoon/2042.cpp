#include <cstdio>
using namespace std;
const int ARRMAX = (1024 * 1024 * 2) + 1;

typedef struct seg_tree {
	int start;
	int end;
	long long value;
}seg_tree;

seg_tree tree[ARRMAX] = { (0, 0, 0), (0, 0, 0), };
int N, M, K;

long long tree_get_sum(int left, int right, int now) {
	long long result = 0;
	if (tree[now].end < left || tree[now].start > right)
		return 0;
	if (tree[now].start >= left && tree[now].end <= right)
		return tree[now].value;
	result = tree_get_sum(left, right, now * 2) + tree_get_sum(left, right, now * 2 + 1);
	return result;
}

void tree_update(int target, long long value, int now) {
	if (tree[now].start > target || tree[now].end < target)
		return;
	if (tree[now].start == target && tree[now].end == target) {
		tree[now].value = value;
		return;
	}
	tree_update(target, value, now * 2);
	tree_update(target, value, now * 2 + 1);
	tree[now].value = tree[now * 2].value + tree[now * 2 + 1].value;
	return;
}

void tree_init(int start, int end, int now) {
	tree[now].start = start;
	tree[now].end = end;
	if (tree[now].start != tree[now].end) {
		tree_init(start, (start + end) / 2, now * 2);
		tree_init((start + end) / 2 + 1, end, now * 2 + 1);
		tree[now].value = tree[now * 2].value + tree[now * 2 + 1].value;
	}
}

int getStartOfTree() {
	int level = 1;
	int temp = N - 1;
	int result = 1;
	while(temp > 1) {
		level++;
		temp = temp / 2;
	} 
	for (int i = 1; i <= level; i++)
		result = result * 2;
	return result;
}

void inputdata() {
	long long value;
	scanf("%d %d %d", &N, &M, &K);
	int start_num = getStartOfTree();

	for (int i = 0; i < N; i++) {
		scanf("%lld", &value);
		tree[start_num + i] = { i + 1, i + 1, value };
	}
	tree_init(1, start_num, 1);
}

void inputCommand() {
	int P = M + K;
	int command;

	for (int i = 0; i < P; i++) {
		int result = 0;
		scanf("%d", &command);
		if (command == 1) {
			int target;
			long long value;
			scanf("%d %lld", &target, &value);
			tree_update(target, value, 1);
		}
		else if (command == 2)
		{
			int input1, input2;
			scanf("%d %d", &input1, &input2);
			printf("%lld\n", tree_get_sum(input1, input2, 1));
		}
	}
}

int main(){
	inputdata();
	inputCommand();
	return 0;
}