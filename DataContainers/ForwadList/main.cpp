#include<iostream>
using namespace std;
using std::cin;
using std::cout;
using std::endl;

#define tab "\t"
#define delimiter "\n-----------------------------------------------------------\n"
//#define - определеить
//Директива #define создает макроопределение (макрос)
//Директива #define показыват что заменить, чес заменить

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
	friend class Iterator;
};

int Element::count = 0;	//Инициализация статической переменной
//:: - Оператор разрешения видимости

class Iterator
{
	Element* Temp;
public:
	Iterator(Element* Temp = nullptr) :Temp(Temp)
	{
		//this->Temp = Temp;
		cout << "ITConstructor:\t" << this << endl;
	}
	~Iterator()
	{
		cout << "ITDestructor:\t" << this << endl;
	}

	Iterator& operator++()
	{
		Temp = Temp->pNext;
		return *this;//this - это указатель на объект, для которого вызывается метод.
		//Оператор - это функция, имя которой состоит из ключевого слова operator и знака оператора
		//operator++ является методом, поскольку он перегружен внутри класса.
		//Метод - это функция внутри класса.
	}

	bool operator==(const Iterator& other)const
	{
		return this->Temp == other.Temp;
	}
	bool operator!=(const Iterator& other)const
	{
		return this->Temp != other.Temp;
	}

	int& operator*()
	{
		return Temp->Data;
	}
};

class ForwardList
{
	Element* Head;
	unsigned int size;
public:
	Element* getHead()const
	{
		return Head;
	}

	Iterator begin()
	{
		return Head;
	}
	Iterator end()
	{
		return nullptr;
	}

	ForwardList()	//DefaultConstructor - Конструктор по умолчанию
	{
		this->Head = nullptr;//Если Голова указывает на 0, значит список пуст
		this->size = 0;
		cout << "LConstructor:\t" << this << endl;
	}
	ForwardList(const initializer_list<int>& il) :ForwardList()
	{
		//begin() - возвращает итератор на начало контейнера
		//end()   - возвращает итератор на конец контейнера
		cout << typeid(il.begin()).name() << endl;
		for (int const* it = il.begin(); it != il.end(); it++)
		{
			//it - это итератор.
			push_back(*it);	//*it - разыменовывает указатель
							//* - оператор разыменования возвращает значение по адресу
		}
	}
	ForwardList(const ForwardList& other) :ForwardList()	//Делегирование конструкторов
	{
		/*this->Head = nullptr;
		this->size = 0;*/
		Element* Temp = other.Head;
		while (Temp)
		{
			push_back(Temp->Data);
			Temp = Temp->pNext;
		}
		cout << "CopyConstructor:" << this << endl;
	}
	~ForwardList()
	{
		while (Head != nullptr)pop_front();
		cout << "LDestuctor:\t" << this << endl;
	}

	//				Operators:
	ForwardList& operator=(const ForwardList& other)
	{
		if (this == &other)return *this;	//Ключевое слово return прерывает работу функции
											//и возвращает значение и управление на место вызова
		while (Head)pop_front();
		Element* Temp = other.Head;
		while (Temp)
		{
			push_back(Temp->Data);
			Temp = Temp->pNext;
		}
		cout << "CopyAssignment:" << this << endl;
		return *this;
	}

	//				Adding elements:
	void push_front(int Data)	//Добавляет значение в начало списка
	{
		/*Element* New = new Element(Data, Head);
		New->pNext = Head;
		Head = New;*/
		Head = new Element(Data, Head);
		size++;
	}
	void push_back(int Data)
	{
		if (Head == nullptr)
		{
			push_front(Data);
			return;
		}
		//Element* New = new Element(Data);
		Element* Temp = Head;
		while (Temp->pNext)
		{
			Temp = Temp->pNext;
		}//После этого цикла мы оказались в последнем элементе
		Temp->pNext = new Element(Data);
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
		/*Element* New = new Element(data);
		New->pNext = Temp->pNext;
		Temp->pNext = New;*/
		Temp->pNext = new Element(data, Temp->pNext);
		size++;
	}

	void erase(int index)
	{
		Element* Temp = Head;
		for (int i = 0; i < index - 1; i++)
			Temp = Temp->pNext;
		Element* to_del = Temp->pNext;	//1) Запоминаем адрес удаляемого элемента
		Temp->pNext = Temp->pNext->pNext;	//2) Исключаем удаляемый элемент из списка
		delete to_del;	//3) Удаляем элемент из памяти
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
		//Element* Temp = Head;	//Temp - это итератор.
		//						//Итератор - это указатель, при помощи которого можно получить доступ
		//						//к элементам структуры данных.
		//while (Temp)
		//{
		//	cout << Temp << tab << Temp->Data << tab << Temp->pNext << endl;
		//	Temp = Temp->pNext;	//Переход на следующий элемент
		//}
		for (Element* Temp = Head; Temp; Temp = Temp->pNext)
			cout << Temp << tab << Temp->Data << tab << Temp->pNext << endl;
		cout << "Количество элементов списка: " << size << endl;
		cout << "Общее колчество элементов:   " << Element::count << endl;
	}
};

#define BASE_CHECK
//define - определить
//#define COPY_METHODS_CHECK
//#define ITERATORS_CHECK

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
	list = list;
	list.print();

#if defined BASE_CHECK
	/*cout << delimiter << endl;
	list.push_back(123);
	list.print();
	cout << delimiter << endl;
	list.pop_front();
	list.print();
	cout << delimiter << endl;
	list.pop_back();
	list.print();
	cout << delimiter << endl;*/
	int index;
	int value;
	cout << "Введите индекс добавляемого элемента: "; cin >> index;
	cout << "Введите значение добавляемого элемента: "; cin >> value;
	list.insert(index, value);
	list.print();
	cout << "Введите индекс удаляемого элемента: "; cin >> index;
	list.erase(index);
	list.print();
#endif // BASE_CHECK

	/*ForwardList list2;
	list2.push_back(123);
	list2.push_back(234);
	list2.push_back(345);
	list2.print();*/

#ifdef COPY_METHODS_CHECK
	ForwardList list2 = list;	//CopyConstructor
	list2.print();

	ForwardList list3;	//DefaultConstructor - Конструктор по умолчанию
	list3 = list2;	//CopyAssignment - Оператор приваивания
	list3.print();

	int a = 2;
	int b = 3;
	a = b;	//Assignment operator - Оператор присваивания  
#endif // COPY_METHODS_CHECK

#ifdef ITERATORS_CHECK
			/*int arr[] = { 3,5,8,13,21 };
for (int i = 0; i < sizeof(arr)/sizeof(int); i++)
{
	cout << arr[i] << tab;
}
cout << endl;
for (int i : arr)
{
	cout << i << tab;
}
cout << endl;*/

	ForwardList list = { 3,5,8,13,21 };	//В классе ForwardList нужен конструктор с одним параметром типа initializer_list.
	list.print();
	//private:
	//public:
	//protected:

	//get/set - методы
	/*for (Iterator it = list.getHead(); it != nullptr; ++it)
	{
		cout << *it << tab;
	}
	cout << endl;*/
	for (int i : list)	//range-base for
	{
		cout << i << tab;
	}
	cout << endl;
#endif // ITERATORS_CHECK

}