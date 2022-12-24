#ifndef __PROJ5_PRIORITY_QUEUE_HPP
#define __PROJ5_PRIORITY_QUEUE_HPP

#include "runtimeexcept.h"
#include <vector>
using namespace std;

class PriorityQueueEmptyException : public RuntimeException
{
public:
	PriorityQueueEmptyException(const std::string& err) : RuntimeException(err) {}
};

template<typename Object>
struct Node
{
	Node<Object>* left;
	Node<Object>* right;
	Object val;

	Node(Object v) {
		left = NULL;
		right = NULL;
		val = v;
	}

	Node() {
		left = NULL;
		right = NULL;
	}
};

template<typename Object>
class MyPriorityQueue
{
private:
	Node<Object>* root;
	vector<Node<Object>*> heapList;
public:

	MyPriorityQueue();

	~MyPriorityQueue();

	size_t size() const noexcept;

	bool isEmpty() const noexcept;

	void insert(const Object& elem);

	// Note:  no non-const version of this one.  This is on purpose because
	// the interior contents should not be able to be modified due to the
	// heap property.  This isn't true of all priority queues but 
	// for this project, we will do this.
	// min and extractMin should throw PriorityQueueEmptyException if the queue is empty.
	const Object& min() const;

	void swap(Node<Object>* a, Node<Object>* b);
	void extractMin();
	vector<Object> returnVector() {
		vector<Object> v;
		for (unsigned i = 0; i < heapList.size(); i++) {
			v.push_back(heapList[i]->val);
		}
		return v;
	}

};

template<typename Object>
MyPriorityQueue<Object>::MyPriorityQueue()
{
	root = nullptr;
}

template<typename Object>
MyPriorityQueue<Object>::~MyPriorityQueue()
{
	for (unsigned i = heapList.size() - 1; i < -1; i--) {
		delete heapList[i];
		heapList.pop_back();
	}
}

template<typename Object>
void MyPriorityQueue<Object>::swap(Node<Object>* a, Node<Object>* b)
{
	Object temp = a->val;
	a->val = b->val;
	b->val = temp;
}

template<typename Object>
size_t MyPriorityQueue<Object>::size() const noexcept
{
	return heapList.size();
}

template<typename Object>
bool MyPriorityQueue<Object>::isEmpty() const noexcept
{
	if (heapList.size() < 1) {
		return true;
	}
	return false;
}

template<typename Object>
void MyPriorityQueue<Object>::insert(const Object& elem)
{
	//time complexity should be O(log n)

	// insert the element at the end of the vector, then percolate up
	// until min-heap is satisfied

	Node<Object>* element = new Node<Object>(elem);

	if (isEmpty()) {
		root = element;
		heapList.push_back(element);
	}

	else {
		heapList.push_back(element);

		unsigned insertedIndex = heapList.size() - 1;
		unsigned parentIndex = (insertedIndex - 1) / 2;
		unsigned rightIndex = 2 * parentIndex + 2;

		if (insertedIndex < rightIndex) {
			heapList[parentIndex]->left = heapList[insertedIndex];
		}
		else {
			heapList[parentIndex]->right = heapList[insertedIndex];
		}

		unsigned currIndex = insertedIndex;
		unsigned currParentIndex = parentIndex;

		while (0 < currIndex) {
			currParentIndex = (currIndex - 1) / 2;
			if (heapList[currParentIndex]->val < heapList[currIndex]->val) {
				break;
			}
			else if (heapList[currIndex]->val < heapList[currParentIndex]->val) {
				swap(heapList[currParentIndex], heapList[currIndex]);
				currIndex = currParentIndex;
			}
			else {
				break;
			}
		}
	}
}

template<typename Object>
const Object& MyPriorityQueue<Object>::min() const
{
	if (isEmpty()) {
		throw PriorityQueueEmptyException("Error: priority queue is empty");
	}
	return root->val;
}



template<typename Object>
void MyPriorityQueue<Object>::extractMin()
{
	if (isEmpty()) {
		throw PriorityQueueEmptyException("Error: priority queue is empty");
	}

	//	delete min value
	swap(heapList[0], heapList[heapList.size() - 1]);
	delete heapList[heapList.size() - 1];
	heapList.pop_back();

	//	rearrange minheap
	//	time complexity should be O(log n)
	unsigned currIndex = 0;
	while (currIndex < heapList.size()) {
		unsigned currLeftIndex = 2 * currIndex + 1;
		unsigned currRightIndex = 2 * currIndex + 2;
		if (heapList.size() - 1 < currLeftIndex) {
			break;
		}
		else if (currLeftIndex < heapList.size() && heapList[currIndex]->val < heapList[currLeftIndex]->val) {
			break;
		}
		else if (currLeftIndex < heapList.size() && heapList[currLeftIndex]->val < heapList[currIndex]->val && heapList[currLeftIndex]->val < heapList[currRightIndex]->val) {
			swap(heapList[currLeftIndex], heapList[currIndex]);
			currIndex = currLeftIndex;
		}
		else if (currRightIndex < heapList.size() && heapList[currRightIndex]->val < heapList[currIndex]->val) {
			swap(heapList[currRightIndex], heapList[currIndex]);
			currIndex = currRightIndex;
		}
		else {
			swap(heapList[currLeftIndex], heapList[currIndex]);
			currIndex = currLeftIndex;
			break;
		}
	}
}

#endif