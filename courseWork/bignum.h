#pragma once

/*			Big number structure:
*	- reverse std::vector of uint32_t digit;
*	- size cant be less that 1;
*/
#include <iostream>
#include <vector>
#include <string>

typedef uint32_t big_digit;

using namespace std;

class BigNum
{

	vector<big_digit> data;
	static const unsigned int _base = 1000000000; // 1e9
	static const unsigned int _base_length = 9;
	

public:
	BigNum();
	BigNum(string num);
	BigNum(int num);
	~BigNum();

	string toString() const;

	friend const BigNum operator+(const BigNum &first, const BigNum &second);
	friend const BigNum operator-(const BigNum &first, const BigNum &second);

	friend bool operator<(const BigNum &first, const BigNum &second);
	friend bool operator==(const BigNum& first, const BigNum& second);
	friend bool operator!=(const BigNum& first, const BigNum& second);
	
	friend std::ostream& operator<< (std::ostream& out, const BigNum& num);

	BigNum& operator++();
	BigNum& operator--();

	bool operator!() const;
	explicit operator bool() const;

	const BigNum& operator=(const BigNum &other);

private:
	void _clear_front_zeros();
};

