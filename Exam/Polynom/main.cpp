#include<iostream>
#include<forward_list>
using namespace std;

#define tab "\t"

class Polynom
{
	forward_list<int> polynom;
public:
	Polynom()
	{
		
	}
	Polynom(const initializer_list<int>& il)
	{
		for (int const* it = il.begin(); it != il.end(); it++)
			polynom.push_front(*it);
		polynom.reverse();
	}
	Polynom(const Polynom& other)
	{
		this->polynom.assign(other.polynom.begin(), other.polynom.end());
	}
	~Polynom()
	{
		//polynom.~forward_list();
		polynom.clear();
	}

	//				Operators:
	Polynom& operator=(const Polynom& other)
	{
		this->polynom.clear();
		this->polynom.assign(other.polynom.begin(), other.polynom.end());
	}

	int calculate()
	{
		int sum = 0;
		for (forward_list<int>::iterator it = polynom.begin(); it != polynom.end(); it++)
		{
			sum += *it;
		}
		return sum;
	}
	friend Polynom operator*(const Polynom& left, const Polynom& right);
	friend ostream& operator<<(ostream& os, const Polynom& obj);
};

Polynom operator*(const Polynom& left, const Polynom& right)
{
	Polynom result;
	for (forward_list<int>::const_iterator l_it = left.polynom.begin(); l_it != left.polynom.end(); l_it++)
	{
		for (forward_list<int>::const_iterator r_it = right.polynom.begin(); r_it != right.polynom.end(); r_it++)
		{
			result.polynom.push_front(*l_it * *r_it);
		}
	}
	result.polynom.reverse();
	return result;
}

ostream& operator<<(ostream& os, const Polynom& obj)
{
	//:: - Scope operator (Оператор разрешения видимости). Открывает область видимости (пространство имен),
	//и позволяет взять из этого пространства любое имя (переменной, константы, функции, и т.д.)
	for (forward_list<int>::const_iterator it = obj.polynom.begin(); it != obj.polynom.end(); it++)
	{
		if (it != obj.polynom.begin() && *it > 0)os << "+";
			//os << (*it > 0 ? " + " : " - ");
		os << *it;// << " + ";
		//else os << " - ";
	}
	/*os << "\b \b";
	os << "\b \b";*/
	return os;
}

void main()
{
	setlocale(LC_ALL, "");
	Polynom poly1 = { 3, -5, 8 };
	cout << poly1 << endl;
	//Polynom poly2 = poly1;
	Polynom poly2 = { 2, 4, -7 };
	cout << poly2 << endl;
	cout << poly1 * poly2 << endl;
	cout << (poly1 * poly2).calculate() << endl;

	int a = 2;
	int b = 3;
}