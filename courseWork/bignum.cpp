#include "BigNum.h"

void BigNum::_clear_front_zeros()
{
	size_t size_without_front_zeros = data.size();

	for (auto it = data.crbegin(); it != data.crend(); it++)
	{
		if (*it || (size_without_front_zeros == 1))
			break;

		size_without_front_zeros--;
	}

	data.resize(size_without_front_zeros);
}

BigNum::BigNum()
{
	data.resize(1);
}

BigNum::BigNum(string num)
{
	size_t num_size = num.size();

	size_t resize_amount = num_size / _base_length;

	if (num.size() % _base_length != 0)
		resize_amount++;

	data.resize(resize_amount);

	// fill data
	for (size_t str_pos = 0, vec_pos = 0; str_pos < num_size; str_pos += BigNum::_base_length, vec_pos++)
	{
		// remain
		if (num_size + 1 <= str_pos + _base_length)
			data[vec_pos] = stoi(num.substr(0, num_size - str_pos));
		else
			data[vec_pos] = stoi(num.substr(num_size - str_pos - _base_length, _base_length));
	}
}

BigNum::BigNum(int num) : BigNum(to_string(num)) {}

BigNum::~BigNum()
{
}

string BigNum::toString() const
{
	string result = "";
	string s_num;

	for (int i = 0; i < data.size(); i++)
	{
		s_num = to_string(data[i]);
		if (((i + 1) != data.size()) && s_num.size() < 9)
			for (int j = 0; j < 9 - s_num.size(); j++) // adding front zeros for numbers inside
				s_num = '0' + s_num;
		result = s_num + result;
	}

	return result;
}

BigNum& BigNum::operator++()
{
	size_t max_size = data.size();
	data.resize(max_size + 1); // TODO! need to calc new size

	big_digit new_digit, carry = 1;
	big_digit old_digit;

	for (size_t i = 0; i < max_size; i++)
	{
		old_digit = data[i];

		new_digit = old_digit + carry;

		carry = new_digit / BigNum::_base;
		new_digit %= BigNum::_base;

		data[i] = new_digit;
	}

	_clear_front_zeros();
	return *this;
}

BigNum& BigNum::operator--()
{
	big_digit digit, borrow = 0;
	big_digit fst_digit, snd_digit;

	for (size_t i = 0; i < data.size(); i++)
	{
		fst_digit = data[i];
		
		if (!i) snd_digit = 1;
		else snd_digit = 0;

		if (borrow) snd_digit++; // analog fst_digit--; since we have big_digit (uint32_t) for work we must avoid byte overflow

		if (snd_digit > fst_digit)
			borrow = BigNum::_base;
		else
			borrow = 0;

		fst_digit += borrow;

		digit = fst_digit - snd_digit;

		data[i] = digit;
	}

	_clear_front_zeros();
	return *this;
}

bool BigNum::operator!() const
{
	if (data.size() > 1 || data[0])
		return false;

	return true;
}

BigNum::operator bool() const
{
	if (data.size() > 1 || data[0])
		return true;

	return false;
}

const BigNum& BigNum::operator=(const BigNum& other)
{
	data.resize(other.data.size());

	

	for (int i = 0; i < other.data.size(); i++)
		data[i] = other.data[i];

	return *this;
}

const BigNum operator+(const BigNum& first, const BigNum& second) // FIXME! mb here must be  ->  16 | BigNum&& operator+...
{
	size_t first_size = first.data.size();
	size_t second_size = second.data.size();

	size_t max_size = max(first_size, second_size);

	BigNum result;
	result.data.pop_back();
	result.data.resize(max_size + 1); // TODO! need to calc new size

	big_digit digit, carry = 0;
	big_digit fst_digit, snd_digit;

	for (size_t i = 0; i < max_size+1; i++) // TODO! check above
	{
		if (i < first_size) fst_digit = first.data[i];
		else fst_digit = 0;

		if (i < second_size) snd_digit = second.data[i];
		else snd_digit = 0;

		digit = fst_digit + snd_digit + carry;

		carry = digit / BigNum::_base;
		digit %= BigNum::_base;

		result.data[i] = digit;
	}

	result._clear_front_zeros();
	return result;
}

const BigNum operator-(const BigNum& first, const BigNum& second)
{
	size_t first_size = first.data.size();
	size_t second_size = second.data.size();

	size_t max_size = max(first_size, second_size);

	BigNum result;
	result.data.pop_back();
	result.data.resize(max_size); // TODO! need to calc new size

	big_digit digit, borrow = 0;
	big_digit fst_digit, snd_digit;

	for (size_t i = 0; i < max_size; i++)
	{
		if (i < first_size) fst_digit = first.data[i];
		else fst_digit = 0;

		if (i < second_size) snd_digit = second.data[i];
		else snd_digit = 0;

		if (borrow) snd_digit++; // analog fst_digit--; since we have big_digit for work we must avoid byte overflow

		if (snd_digit > fst_digit)
			borrow = BigNum::_base;
		else
			borrow = 0;

		fst_digit += borrow;

		digit = fst_digit - snd_digit;

		result.data[i] = digit;
	}

	result._clear_front_zeros();
	return result;
}

bool operator<(const BigNum& first, const BigNum& second)
{
	if (first.data.size() != second.data.size())
		return (first.data.size() < second.data.size());

	for (size_t i = 0; i < first.data.size(); i++)
		if (first.data[i] != second.data[i])
			return first.data[i] < second.data[i];

	// They are equal
	return false;
}

bool operator==(const BigNum& first, const BigNum& second)
{
	if (first.data.size() != second.data.size())
		return false;

	for (int i = 0; i < first.data.size(); i++)
		if (first.data[i] != second.data[i])
			return false;
	return true;
}

bool operator!=(const BigNum& first, const BigNum& second)
{
	if (first.data.size() != second.data.size())
		return true;

	for (int i = 0; i < first.data.size(); i++)
		if (first.data[i] != second.data[i])
			return true;
	return false;
}

std::ostream& operator<<(std::ostream& out, const BigNum& num)
{
	out << "BigNum(" << num.toString() << ')';

	return out;
}
