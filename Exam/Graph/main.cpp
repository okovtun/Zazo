#include<iostream>
using namespace std;

#define tab "\t"
#define delimiter "\n-------------------------------------\n"

class Graph
{
	unsigned int size;	//Количество узлов графа
	int** matrix;		//Матрица смежности графа
public:
	Graph(int size)
	{
		this->size = size;
		this->matrix = new int*[size] {};//Создаем массив указателей
		for (int i = 0; i < size; i++)
		{
			this->matrix[i] = new int[size] {};	//Выделяем память под строки матрицы
		}
		cout << "Constructor:\t" << this << endl;
	}
	Graph(const initializer_list<initializer_list<int>>& il) :Graph(il.size())
	{
		if (il.size() != il.begin()->size())
			cout << "Заданная матрица НЕ квадратная, и рассчеты могут быть неверными" << endl;
		//if(il.size()>il.begin()->size())
		cout << typeid(il.begin()).name() << endl;
		int i = 0;
		int j = 0;
		for (initializer_list<int> const* r_it = il.begin(); r_it != il.end(); r_it++)
		{
			for (int const* c_it = r_it->begin(); c_it != r_it->end(); c_it++)
			{
				this->matrix[i][j] = *c_it;
				j++;
			}
			j = 0;
			i++;
		}
	}
	Graph(const Graph& other) :Graph(other.size)
	{
		for (int i = 0; i < size; i++)
		{
			for (int j = 0; j < size; j++)
			{
				this->matrix[i][j] = other.matrix[i][j];
			}
		}
		cout << "CopyConstructor:" << this << endl;
	}
	~Graph()
	{
		for (int i = 0; i < size; i++)
		{
			delete[] this->matrix[i];	//Удаляем строки матрицы
		}
		delete[] this->matrix;	//Удаляем массив указателей
	}

	//				Operators:
	Graph& operator=(const Graph& other)
	{
		for (int i = 0; i < size; i++)delete[]matrix[i];
		delete[] matrix;
		this->size = other.size;
		this->matrix = new int*[size] {};
		for (int i = 0; i < size; i++)matrix[i] = new int[size] {};
		for (int i = 0; i < size; i++)
		{
			for (int j = 0; j < size; j++)
			{
				this->matrix[i][j] = other.matrix[i][j];
			}
		}
		cout << "CopyAssignment:\t" << this << endl;
		return *this;
	}

	//				Methods
	unsigned int links(unsigned int vertex)
	{
		if (vertex - 1 >= size)
		{
			cout << "Нет такой вершины" << endl;
			return 0;
		}
		unsigned int number_of_links = 0;
		for (int i = 0; i < size; i++)
		{
			if (matrix[vertex - 1][i])number_of_links++;
		}
		return number_of_links;
	}
	unsigned int links(unsigned int vertex1, unsigned int vertex2)
	{
		if (vertex1 - 1 >= size)
		{
			cout << "Bad vertex 1" << endl;
			return 0;
		}
		if (vertex2 - 1 >= size)
		{
			cout << "Bad vertex 2" << endl;
			return 0;
		}
		unsigned int number_of_links = 0;
		for (int i = 0; i < size; i++)
		{
			if (matrix[vertex1 - 1][i] && matrix[i][vertex2 - 1] == 0/*&& i != vertex2*/)
			{
				number_of_links++;
			}
		}
		return number_of_links;
	}

	void print()
	{
		cout << delimiter << endl;
		for (int i = 0; i < size; i++)
		{
			for (int j = 0; j < size; j++)
			{
				cout << matrix[i][j] << tab;
			}
			cout << endl;
		}
		cout << delimiter << endl;
	}
};

void main()
{
	setlocale(LC_ALL, "");
	Graph graph =
	{
		{0,2,3,0,2,0},
		{2,0,0,3,0,6},
		{3,0,0,0,0,0},
		{0,3,0,0,1,0},
		{2,0,0,1,0,0},
		{0,2,0,0,0,0}
	};
	graph.print();
	/*Graph graph2(3);
	graph2 = graph;
	graph2.print();*/
	cout << graph.links(1, 4) << endl;
}