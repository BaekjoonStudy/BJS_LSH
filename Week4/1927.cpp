#include <iostream>
using namespace std;

int min_heap[100000] = { 0 }; // 0으로 초기화
int heap_size = 0;

void push(int x) {
	int parent = (heap_size - 1) / 2;
	int self = heap_size++;
	min_heap[self] = x;
	while (self >= 1) {
		if (min_heap[self] < min_heap[parent]) {
			min_heap[self] = min_heap[parent];
			min_heap[parent] = x;
			self = parent;
			parent = (self - 1) / 2;
		}
		else
			break;
	}
}

void pop() {
	int self = 0, left = 1, right = 2, tmp;
	cout << min_heap[self] << "\n";
	if (heap_size > 0) {
		min_heap[self] = min_heap[--heap_size];
		min_heap[heap_size] = 0;
	
		while (true) {
			if (left >= heap_size) // 자식 노드가 없을 때
				break;
			else if (right >= heap_size) { // 왼쪽 자식 노드만 있을 때
				if (min_heap[self] > min_heap[left]) {
					tmp = min_heap[self];
					min_heap[self] = min_heap[left];
					min_heap[left] = tmp;
				}
				break;
			}
			else { // 양쪽 자식 노드 모두 있을 때
				if (min_heap[left] < min_heap[right]) { // 자식 노드끼리 비교해서 left가 더 작을 때
					if (min_heap[self] > min_heap[left]) { // 부모와 비교해서 자식이 더 작다면 바꿔줌
						tmp = min_heap[self];
						min_heap[self] = min_heap[left];
						min_heap[left] = tmp;
						self = left;
					}
					else
						break;
				}
				else { // right가 더 작을 때
					if (min_heap[self] > min_heap[right]) { // 부모와 비교해서 자식이 더 작다면 바꿔줌
						tmp = min_heap[self];
						min_heap[self] = min_heap[right];
						min_heap[right] = tmp;
						self = right;
					}
					else
						break;
				}
				left = 2 * self + 1;
				right = left + 1;
			}
		}
	}
}


int main()
{
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);

	int N, x;
	cin >> N;
	
	while (N--) {
		cin >> x;
		if (x == 0)
			pop();
		else
			push(x);
	}

	return 0;
}