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
		for (int i : il)polynom.push_front(i);
		polynom.reverse();
	}
	Polynom(const Polynom& other)
	{
		/*forward_list<int>::const_iterator other_first = other.polynom.begin();
		forward_list<int>::const_iterator other_last = other.polynom.begin();
		for (; other_last != other.polynom.end(); other_last++);
		this->polynom.assign(other_first, other_last);*/
		this->polynom.assign(other.polynom.begin(), other.polynom.end());
	}
	~Polynom()
	{
		polynom.~forward_list();
	}
	friend Polynom operator*(const Polynom& left, const Polynom& right);
	friend ostream& operator<<(ostream& os, const Polynom& obj)
	{
		for (int i : obj.polynom)os << i << " + ";
		os << "\b \b";
		os << "\b \b";
		return os;
	}
};

Polynom operator*(const Polynom& left, const Polynom& right)
{
	Polynom result;
	for (forward_list<int>::const_iterator lit = left.polynom.begin(); lit != left.polynom.end(); lit++)
	{
		for (forward_list<int>::const_iterator rit = right.polynom.begin(); rit != right.polynom.end(); rit++)
		{
			result.polynom.push_front(*lit * *rit);
		}
	}
	result.polynom.reverse();
	return result;
}

void main()
{
	setlocale(LC_ALL, "");
	Polynom poly1{ 3, 5, 8 };
	cout << poly1 << endl;
	Polynom poly2 = poly1;
	cout << poly2 << endl;
	cout << poly1 * poly2 << endl;
}