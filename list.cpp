#include<iostream>
#include "list.h"

using namespace std;


/**** List의 마지막에 새로운 data에 대한 Node 추가 ****/
void LinkedList::Append(int data) {
	Node* newNode = new Node; // 노드 생성

	// 처음 삽입되는 노드라면 (더미노드 없기때문에 조건 달리 지정)
	if (head == NULL) {
		head = newNode;

		newNode->data = data;
		newNode->next = NULL;
	}
	else { // 처음 삽입되는 경우가 아니라면 
		Node* cur = head;
		newNode->data = data;
		newNode->next = NULL;

		while (cur->next != NULL)
			cur = cur->next;
		cur->next = newNode;
		cur = newNode;
	}
	return;
}
/**** List의 처음에 새로운 data에 대한 Node 추가 ****/
void LinkedList::Prepend(int data) {
	Node* newNode = new Node; // 노드 생성
	// 처음 삽입되는 노드라면 (더미노드 없기때문에 조건 달리 지정)
	if (head == NULL) {
		head = newNode;

		newNode->data = data;
		newNode->next = NULL;
	}
	else { // 처음 삽입되는 경우가 아니라면
		newNode->data = data;
		newNode->next = head; // newNode의 next와 head 연결
		head = newNode; // head와 newNode를 연결
	}
}

/**** List에 있는 Node의 수를 return ****/
int LinkedList::Length() {
	Node* List;
	int count = 0;
	for (List = head; List != NULL; List = List->next)
		count++;
	return count;
}
/**** List에 있는 모든 Node를 head부터 순서대로 출력
ex) 4,3,5 => "4 3 5"  ****/
void LinkedList::Print() {
	if (head == NULL) {
		cout << "노드가 존재하지 않습니다." << endl;
		return;
	}
	Node* cur = head;

	while (cur != NULL) {
		cout << cur->data << " ";
		cur = cur->next;
	}
	cout << endl;
}