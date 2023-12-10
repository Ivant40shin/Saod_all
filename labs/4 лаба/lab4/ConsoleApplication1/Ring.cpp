#include "Ring.h"
using namespace std;

RingList::~RingList()
{
	// Удаление всех элементов списка
	if (head != nullptr)
	{
		Element* current = head;
		Element* next = nullptr;
		do
		{
			next = current->next;
			delete current;
			current = next;
		} while (current != head);
	}
}

void RingList::MoveRight()
{
	if (head != nullptr)
		head = head->next;
}

void RingList::MoveLeft()
{
	if (head != nullptr)
		head = head->prev;
}

void RingList::AddElement(const int& pos, const int& data)
{
	Element* newElement = new Element;
	newElement->data = data;

	if (head == nullptr)
	{
		// Если список пуст, новый элемент становится головой
		head = newElement;
		head->next = head;
		head->prev = head;
		return;
	}
	if (pos == 0)
	{
		Element* lastElement = head->prev;
		newElement->next = head;
		newElement->prev = lastElement;
		lastElement->next = newElement;
		head->prev = newElement;
		head = newElement;
	}
	else
	{
		Element* current = head;

		for (int i = 0; i < pos; i++)
			current = current->next;

		// Вставка нового элемента перед текущим
		newElement->next = current;
		newElement->prev = current->prev;
		current->prev->next = newElement;
		current->prev = newElement;
	}
}

void RingList::DeleteElement(const int& pos)
{
	if (head != nullptr)
	{
		Element* current = head;

		for (int i = 0; i < pos; i++)
			current = current->next;

		// Удаление текущего элемента
		current->prev->next = current->next;
		current->next->prev = current->prev;

		if (current == head)
			head = current->next;

		delete current;
	}
}

int RingList::SearchElement(const int& num) const
{
	if (head != nullptr)
	{
		Element* current = head;
		int pos = 0;
		do
		{
			if (current->data == num)
				return pos;
			
			current = current->next;
			pos++;
		} while (current != head);
	}
	return -1; // Возвращаем -1, если элемент не найден
}

void RingList::PrintRing() const
{
	if (head != nullptr)
	{
		Element* current = head;
		do
		{
			cout << current->data << " ";
			current = current->next;
		} while (current != head);
		cout << endl;
	}
}