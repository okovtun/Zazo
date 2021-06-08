#include <iostream>
#include <forward_list>
using namespace std;

#define tab "\t"

/// <summary>
/// //////////////////////////////////////////////////
/// </summary>

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
		polynom.~forward_list();
	}

	friend ostream& operator<<(ostream& os, const Polynom& obj);
	friend Polynom operator*(const Polynom& left, const Polynom& right);
};

Polynom operator*(const Polynom& left, const Polynom& right)
{
	Polynom result;
	for (forward_list<int>::const_iterator l_it = left.polynom.cbegin(); l_it != left.polynom.cend(); l_it++)
	{
		for (forward_list<int>::const_iterator r_it = right.polynom.cbegin(); r_it != right.polynom.cend(); r_it++)
		{
			result.polynom.push_front((*l_it) * (*r_it));
		}
	}
	return result;
}

ostream& operator<<(ostream& os, const Polynom& obj)
{
	//:: - Scope operator(Оператор разрешения видимости). Открывает область видимости (пространство имен),
	// и позволяет взять из этого пространства любое имя (переменно, константы, функции, и т.д.)
	for (forward_list<int>::const_iterator it = obj.polynom.begin(); it != obj.polynom.end(); it++)
	{
		if (it != obj.polynom.begin() && *it > 0)os << "+";
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
	Polynom poly1 = { 3,-5,8 };
	cout << poly1 << endl;
	Polynom poly2 = poly1;
	cout << poly2 << endl;
	//cout << poly1 * poly2 << endl;
	Polynom poly3 = poly1 * poly2;
	cout << poly3 << endl;
}