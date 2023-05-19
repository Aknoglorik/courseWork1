#include <iostream>
#include <Windows.h>
#include "bignum.h"
#include "biglist.hpp"



// tests
void BigNumTest()
{
	cout << "Math operators test" << endl;
	BigNum a("923456789123456789");
	BigNum b("111111111111111111");

	BigNum c; 


	c = a - b;

	cout << a << " - " << b << " = " << (a - b) << endl;
	cout << a << " + " << b << " = " << (a + b) << endl;
	
	cout << "1000000000 - 1 = " << (BigNum(1000000000) - BigNum(1)) << endl << endl;

	cout << "++" << a << " = ";
	cout << ++a << endl;

	cout << "--" << a << " = "; 
	cout << --a << endl << endl;

	c = 0;

	cout << "Boolean test" << endl;
	cout << "A = bool(" << a << ")  = " << bool(a) << endl;
	cout << "B = bool(" << c << ")  = " << bool(c) << endl << endl;

	cout << "A == B = " << (a == c) << endl;
	cout << "A != B = " << (a != c)<< endl;
	cout << "A < B = " << (a < c)<< endl;
	cout << "!A = " << (!a)<< endl;
	cout << "!B = " << (!c) << endl << endl;;


	
}

void calcBigNum()
{
	cout << "Addition time: ";
	time_t st = time(0);
	BigNum result("923456789123456789");
	BigNum b("111111111111111111");
	for (BigNum i = 0; i < 100000; ++i)
	{
		result = result + b;
	}
	time_t end = time(0);

	cout << (end - st) << " sec" << endl << endl;
}

void inserting()
{
	BigList<int> a;

	a.insert(1, 1); // 1
	a.insert(2, 0); // 1 2
	a.insert(3, 1); // 1 2 3
	a.insert(4, 1); // 1 2 4 3

	cout << "Inserting (1 2 4 3): ";
	cout << a << endl;
	cout << endl;

}

void erasing()
{
	BigList<int> a;

	for (int i = 0; i < 6; i++)
		a.push_back(i);

	a.erase(0); // 1 2 3 4 5
	a.erase(4); // 1 2 3 4
	a.erase(1); // 1 3 4

	cout << "Erasing (1 3 4): ";
	cout << a << endl;
	cout << endl;
}

void pushing()
{
	BigList<int> a;

	for (int i = 0; i < 6; i++)
		a.push_back(i);

	cout << "Pushing (0 1 2 3 4 5): ";
	cout << a << endl;
	cout << endl;
}

void clear()
{
	BigList<int> a;

	for (int i = 0; i < 6; i++)
		a.push_back(i);

	cout << "Clear before: " << a << endl;
	a.clear();
	cout << "Clear after: "  << a << endl;
	cout << endl;
}

void indexing()
{
	BigList<BigNum> mylist;

	for (BigNum i = 0; i < BigNum(10); ++i)
	{
		mylist.push_back(i);
	}
	cout << mylist << endl << "Item with index 2: " << mylist[2] << endl << endl;
}

// Need to check debug info
void mem_lost()
{
	BigList<BigNum> mylist;

#define NUM 10000

	cout << "Pushing " << NUM << " and after pop" << endl;
	for (BigNum i = 0; i < BigNum(NUM); ++i)
	{
		mylist.push_back(i);
	}

	for (BigNum i = 0; i < BigNum(NUM); ++i)
	{
		mylist.pop_back();
	}

	cout << mylist << endl;
	
	cout << "Pushing " << NUM << " and clear" << endl;
	for (BigNum i = 0; i < BigNum(NUM); ++i)
	{
		mylist.push_back(i);
	}
	mylist.clear();
}

void tests()
{
	calcBigNum();
	BigNumTest();
	pushing();
	inserting();
	erasing();
	clear();
	indexing();
	mem_lost();
}


int main(int argc, char* argv[])
{
	tests();

	return 0;
}