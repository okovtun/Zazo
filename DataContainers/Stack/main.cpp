#include<iostream>
using namespace std;

#define tab "\t"
#define delimiter "\n-----------------------------------------\n"

/*
Stack (Стопка) - это модель памяти, из которой последний записанный элемент считывается первым.
Например: стопка тарелок
*/

class Stack
{
	class Element
	{
		int Data;	//Значение элемента
		Element* pNext;
	public:
		Element(int Data, Element* pNext = nullptr) :Data(Data), pNext(pNext)
		{
			cout << "EConstructor:\t" << this << endl;
		}
		~Element()
		{
			cout << "EDestructor:\t" << this << endl;
		}
		friend class Stack;
	};
	Element* Head;
public:
	Stack() :Head(nullptr)
	{
		cout << "SConstructor:\t" << this << endl;
	}
	~Stack()
	{
		cout << "SDestructor:\t" << this << endl;
	}
	int push(int Data)
	{
		//Метод push, помещает значение на вершину стека
		Head = new Element(Data, Head);
		return Head->Data;
	}
	int pop()
	{
		//Извлекает значение из вершины стека
		int Data = Head->Data;
		Element* Temp = Head;	//Сохраняем адрес удаляемого элемента
		Head = Head->pNext;	//исключаем удаляемый элемент из списка
		delete Temp;	//Удаляем элемент из памяти
		return Data;
	}
};

void main()
{
	setlocale(LC_ALL, "Russian");
	int n;
	cout << "Введите размер стопки: "; cin >> n;
	Stack stack;
	for (int i = 0; i < n; i++)
	{
		cout << stack.push(rand() % 100) << tab;
	}
	cout << delimiter << endl;
	for (int i = 0; i < n; i++)
	{
		cout << stack.pop() << endl;
	}
}