#pragma once
#include <random>

template <typename T>
class const_wrapper {
public:
	const_wrapper(const T& val) : val_{ val } {}
	const_wrapper(T&& val) : val_{ std::move(val) } {}
	T& operator=(const T&) = delete;
	auto get() const -> const T& { return val_; }
	operator const T&() const { return val_; }
private:
	T val_;
};

template <typename T>
void CopySelf(T& v, size_t n)
{
	T tmp;
	for (size_t i = 0; i < n; ++i)
	{
		std::copy_n(v.begin(), v.size(), std::back_inserter(tmp));
	}
	std::copy(tmp.begin(), tmp.end(), std::back_inserter(v));
}

template <typename T>
void CopySelfShuffle(T& v, size_t n)
{
	T tmp;
	for (size_t i = 0; i < n; ++i)
	{
		std::random_device rd;
		std::mt19937 g(rd());
		std::shuffle(v.begin(), v.end(), g);

		std::copy_n(v.begin(), v.size(), std::back_inserter(tmp));
	}
	std::copy(tmp.begin(), tmp.end(), std::back_inserter(v));
}
