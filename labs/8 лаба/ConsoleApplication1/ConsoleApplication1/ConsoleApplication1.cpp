#include <iostream>
using namespace std;

/*
7. Разработать алгоритм и программу слияния двух непересекающихся приоритетных 
очередей, представленных в виде левосторонних деревьев, в одну (в частности, 
если одна из данных очередей содержит всего один элемент, то алгоритм будет 
вставлять его в другую очередь).
*/

class PriorityQueue
{
private:

	struct Node
	{
		int key;     // Ключ узла
		int dist;    // Глубина узла
		Node* left;  // Левый потомок
		Node* right; // Правый потомок

		Node(int k) : key(k), dist(0), left(nullptr), right(nullptr) {}
	};

	Node* root;		 // Корень дерева

	// Объединяет два узла
	Node* merge_nodes(Node* node1, Node* node2)
	{
		if (node1 == nullptr)
		{
			return node2;
		}
		if (node2 == nullptr)
		{
			return node1;
		}

		if (node1->key < node2->key)
		{
			swap(node1, node2);
		}

		node1->right = merge_nodes(node1->right, node2);
		if (node1->left == nullptr || node1->left->dist < node1->right->dist)
		{
			swap(node1->left, node1->right);
		}
		if (node1->right == nullptr)
		{
			node1->dist = 0;
		}
		else
		{
			node1->dist = node1->right->dist + 1;
		}

		return node1;
	}
public:
	// Конструктор
	PriorityQueue()
		: root(nullptr) {}

	// Проверка, пуста ли очередь
	bool isEmpty()
	{
		return root == nullptr;
	}

	// Вставка элемента в очередь
	void insert(int key)
	{
		Node* new_node = new Node(key);
		if (isEmpty())
		{
			root = new_node;
		}
		else
		{
			root = merge_nodes(root, new_node);
		}
	}

	// Удаление и возврат элемента с максимальным значением ключа
	int removeMax()
	{
		if (isEmpty())
		{
			return -1;
		}

		int max_key = root->key;
		Node* left_child = root->left;
		Node* right_child = root->right;
		delete root;
		root = merge_nodes(left_child, right_child);
		return max_key;
	}

	// Слияние текущей очереди с другой очередью
	void merge(PriorityQueue& other_queue)
	{
		if (isEmpty())
		{
			root = other_queue.root;
		}
		else if (!other_queue.isEmpty())
		{
			root = merge_nodes(root, other_queue.root);
		}
		other_queue.root = nullptr; // clear the other queue
	}

	// Печать значений узлов дерева
	void print(Node* head)
	{
		if (head == nullptr)
			return;

		cout << "Значение: " << head->key << ", Глубина: " << head->dist << endl;
		print(head->left);
		print(head->right);
	}

	// Печать значений узлов дерева
	void print()
	{
		print(root);
	}
};

int main() 
{
	system("chcp 1251&cls");

	PriorityQueue pq1;
	pq1.insert(5);
	pq1.insert(10);
	pq1.insert(3);

	/*
			10
			/\
		   5  3
	*/
	pq1.print();
	cout << endl;

	PriorityQueue pq2;
	pq2.insert(7);
	pq2.insert(1);

	/*
			7
		   /
		  1
	*/
	pq2.print();
	cout << endl;

	pq1.merge(pq2);

	/*
		   10
		   /\
		  7  5
		 /\
		1  3
	*/
	pq1.print();
	cout << endl;

	return 0;
}