#pragma once
#include <iostream>


struct Element
{
	int data = 0;
	Element* next = nullptr;
	Element* prev = nullptr;
};

class RingList
{
private:
	Element* head = nullptr;

public:
	RingList() = default;
	~RingList();

	void MoveRight();
	void MoveLeft();
	void AddElement(const int& pos, const int& data);
	void DeleteElement(const int& pos);
	int SearchElement(const int& num) const;
	void PrintRing() const;
};
