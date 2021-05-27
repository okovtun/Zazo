#include<iostream>
using namespace std;

#define tab "\t"
#define delimiter "\n-----------------------------------------------------------\n"

class Element
{
	int Data;	//Значение элемента
	Element* pNext;	//Адрес следующего элемента
	static int count;	//Количество элементов
public:
	Element(int Data, Element* pNext = nullptr)
	{
		count++;
		this->Data = Data;
		this->pNext = pNext;
		cout << "EConstructor:\t" << this << endl;
	}
	~Element()
	{
		count--;
		cout << "EDestructor:\t" << this << endl;
	}
	friend class ForwardList;
};

int Element::count = 0;	//Инициализация статической переменной
//:: - Оператор разрешения видимости

class ForwardList
{
	Element* Head;
	unsigned int size;
public:
	ForwardList()
	{
		this->Head = nullptr;//Если Голова указывает на 0, значит список пуст
		this->size = 0;	
		cout << "LConstructor:\t" << this << endl;
	}
	~ForwardList()
	{
		cout << "LDestuctor:\t" << this << endl;
	}

	//				Adding elements:
	void push_front(int Data)	//Добавляет значение в начало списка
	{
		Element* New = new Element(Data);
		New->pNext = Head;
		Head = New;
		size++;
	}
	void push_back(int Data)
	{
		if (Head == nullptr)
		{
			push_front(Data);
			return;
		}
		Element* New = new Element(Data);
		Element* Temp = Head;
		while (Temp->pNext)
		{
			Temp = Temp->pNext;
		}//После этого цикла мы оказались в последнем элементе
		Temp->pNext = New;
		size++;
	}
	void insert(int index, int data)
	{
		//0) Проверяем индекс:
		if (index > Element::count)return;
		//Ключевое слово return ПРЕРЫВАЕТ РАБОТУ ФУНКЦИИ и возвращает управление на место вызова.

		if (index == 0)
		{
			push_front(data);
			return;
		}

		//1) Доходим до нужного элемента:
		Element* Temp = Head;
		for (int i = 0; i < index - 1; i++)
			Temp = Temp->pNext;
		//2) Содаем новый элемент, и добавляем его в список:
		Element* New = new Element(data);
		New->pNext = Temp->pNext;
		Temp->pNext = New;
		size++;
	}

	//				Removing elements:
	void pop_front()
	{
		//0)Запоминаем адрес удаляемого элемента:
		Element* to_del = Head;
		//1) Исключить элемент из списка:
		Head = Head->pNext;
		//2) Удалить элемент и памяти:
		delete to_del;
		size--;
	}
	void pop_back()
	{
		Element* Temp = Head;
		while (Temp->pNext->pNext)	//Доходим до предпоследнего элемента списка
			Temp = Temp->pNext;
		delete Temp->pNext;
		Temp->pNext = nullptr;
		size--;
	}
	

	//				Methods:
	void print()
	{
		Element* Temp = Head;	//Temp - это итератор.
								//Итератор - это указатель, при помощи которого можно получить доступ
								//к элементам структуры данных.
		while (Temp)
		{
			cout << Temp << tab << Temp->Data << tab << Temp->pNext << endl;
			Temp = Temp->pNext;	//Переход на следующий элемент
		}
		cout << "Количество элементов списка: " << size << endl;
		cout << "Общее колчество элементов:   " << Element::count << endl;
	}
};

//#define BASE_CHECK
//define - определить

void main()
{
	setlocale(LC_ALL, "Russian");
	int n;
	cout << "Введите размер списка: "; cin >> n;
	ForwardList list;
	for (int i = 0; i < n; i++)
	{
		list.push_front(rand() % 100);
	}
	list.print();

#if defined BASE_CHECK
	cout << delimiter << endl;
	list.push_back(123);
	list.print();
	cout << delimiter << endl;
	list.pop_front();
	list.print();
	cout << delimiter << endl;
	list.pop_back();
	list.print();
	cout << delimiter << endl;
	int index;
	int value;
	cout << "Введите индекс добавляемого элемента: "; cin >> index;
	cout << "Введите значение добавляемого элемента: "; cin >> value;
	list.insert(index, value);
	list.print();
#endif // BASE_CHECK

	ForwardList list2;
	list2.push_back(123);
	list2.push_back(234);
	list2.push_back(345);
	list2.print();
}