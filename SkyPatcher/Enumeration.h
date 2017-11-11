#pragma once

template<typename T>
class Enum
{
public:
	Enum() = default;
	Enum(size_t value)
		:
		value(value)
	{}
	void operator++()
	{
		++value;
	}
	T operator*()
	{
		return (T)value;
	}
	typename Enum<T> begin()
	{
		return Enum<T>((size_t)T::First);
	}
	typename Enum<T> end()
	{
		return Enum<T>(((size_t)T::Last) + 1);
	}
	bool operator!=(const Enum<T> & rhs)
	{
		return value != rhs.value;
	}
private:
	size_t value;
};
