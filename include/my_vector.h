#pragma once

#include <algorithm>
#include <cstddef>
#include <iterator>
#include <new>
#include <stdexcept>
#include <utility>


// Simple implementation, without custom allocators
template <typename T>
class my_vector
{
public:
	using value_type				= T;
	using size_type					= std::size_t;
	using difference_type			= std::ptrdiff_t;

	using reference					= value_type&;
	using const_reference			= const value_type&;

	using pointer					= value_type*;
	using const_pointer				= const value_type*;

	using iterator					= value_type*;
	using const_iterator			= const value_type*;

	using reverse_iterator			= std::reverse_iterator<iterator>;
	using const_reverse_iterator	= std::reverse_iterator<const_iterator>;

private:
	pointer data_;
	size_type size_;
	size_type capacity_;

	void reallocate()
	{
		reserve(capacity_ ? capacity_ * 2 : 1);
	}

public:
	my_vector()
		: data_(nullptr), capacity_(10), size_(0)
	{
		data_ = static_cast<pointer>(::operator new(sizeof(value_type) * capacity_));
	}

	my_vector(size_type count, const_reference value = value_type())
		: data_(nullptr), capacity_(count), size_(count)
	{
		data_ = static_cast<pointer>(::operator new(sizeof(value_type) * capacity_));

		size_type i{};
		try
		{
			for (; i < size_; ++i)
				::new (data_ + i) value_type(value);
		}
		catch (...)
		{
			for (size_t j{}; j < i; ++j)
				data_[j].~value_type();
			::operator delete(data_);
			throw;
		}
	}

	my_vector(const my_vector& other)
		: data_(nullptr), capacity_(other.capacity_), size_(other.size_)
	{
		data_ = static_cast<pointer>(::operator new(sizeof(value_type) * capacity_));
		size_type i{};
		try
		{
			for (; i < size_; ++i)
				::new (data_ + i) value_type(other.data_[i]);
		}
		catch (...)
		{
			for (size_t j{}; j < i; ++j)
				data_[j].~value_type();
			::operator delete(data_);
			throw;
		}
	}

	my_vector(my_vector&& other) noexcept
		: data_(other.data_), capacity_(other.capacity_), size_(other.size_)
	{
		other.data_ = nullptr;
		other.capacity_ = 0;
		other.size_ = 0;
	}

	~my_vector()
	{
		for (size_type i{}; i < size_; ++i)
			data_[i].~value_type();
		::operator delete(data_);
	}

	my_vector& operator=(const my_vector& other)
	{
		if (this == &other)
			return *this;

		my_vector tmp(other);
		std::swap(data_, tmp.data_);
		std::swap(size_, tmp.size_);
		std::swap(capacity_, tmp.capacity_);

		return *this;
	}

	my_vector& operator=(my_vector&& other) noexcept
	{
		if (this == &other)
			return *this;

		for (size_type i{}; i < size_; ++i)
			data_[i].~value_type();
		::operator delete(data_);

		data_ = other.data_;
		capacity_ = other.capacity_;
		size_ = other.size_;

		other.data_ = nullptr;
		other.capacity_ = 0;
		other.size_ = 0;

		return *this;
	}

	reference operator[](size_type index)
	{
		return data_[index];
	}

	const_reference operator[](size_type index) const
	{
		return data_[index];
	}

	reference at(size_type index)
	{
		if (index >= size_)
			throw std::out_of_range("index out of range");

		return data_[index];
	}

	const_reference at(size_type index) const
	{
		if (index >= size_)
			throw std::out_of_range("index out of range");

		return data_[index];
	}

	size_type size() const noexcept
	{
		return size_;
	}

	size_type capacity() const noexcept
	{
		return capacity_;
	}

	bool empty() const noexcept
	{
		return size_ == 0;
	}

	void push_back(const_reference value)
	{
		if (size_ >= capacity_)
			reallocate();

		::new(data_ + size_) value_type(value);
		++size_;
	}

	void push_back(value_type&& value)
	{
		if (size_ >= capacity_)
			reallocate();

		::new(data_ + size_) value_type(std::move(value));
		++size_;
	}

	template <typename... Args>
	reference emplace_back(Args&&... args)
	{
		if (size_ >= capacity_)
			reallocate();

		::new (data_ + size_) value_type(std::forward<Args>(args)...);
		++size_;
		return data_[size_ - 1];
	}

	void reserve(size_type new_capacity)
	{
		if (new_capacity <= capacity_)
			return;

		pointer new_data = static_cast<pointer>(::operator new(sizeof(value_type) * new_capacity));

		size_type i{};
		try
		{
			for (; i < size_; ++i)
				::new (new_data + i) value_type(std::move_if_noexcept(data_[i]));
		}
		catch (...)
		{
			for (size_type j{}; j < i; ++j)
				new_data[j].~value_type();
			::operator delete(new_data);
			throw;
		}

		for (size_type i{}; i < size_; ++i)
			data_[i].~value_type();
		::operator delete(data_);

		data_ = new_data;
		capacity_ = new_capacity;
	}

	void resize(size_type new_size)
	{
		if (new_size == size_)
			return;

		if (new_size < size_)
		{
			for (size_type i = new_size; i < size_; ++i)
				data_[i].~value_type();

			size_ = new_size;
			return;
		}

		if (new_size > capacity_)
			reserve(std::max(new_size, capacity_ * 2));

		for (size_type i = size_; i < new_size; ++i)
			::new (data_ + i) value_type();

		size_ = new_size;
	}

	void resize(size_type new_size, const_reference value)
	{
		if (new_size == size_)
			return;

		if (new_size < size_)
		{
			for (size_type i = new_size; i < size_; ++i)
				data_[i].~value_type();

			size_ = new_size;
			return;
		}

		if (new_size > capacity_)
			reserve(std::max(new_size, capacity_ * 2));

		for (size_type i = size_; i < new_size; ++i)
			::new (data_ + i) value_type(value);

		size_ = new_size;
	}

	void clear()
	{
		for (size_type i{}; i < size_; ++i)
			data_[i].~value_type();
		size_ = 0;
	}

	void shrink_to_fit()
	{
		if (size_ == capacity_)
			return;

		pointer new_data = static_cast<pointer>(::operator new(sizeof(value_type) * size_));

		size_type i{};
		try
		{
			for (; i < size_; ++i)
				::new (new_data + i) value_type(std::move_if_noexcept(data_[i]));
		}
		catch (...)
		{
			for (size_type j{}; j < i; ++j)
				new_data[j].~value_type();
			::operator delete(new_data);
			throw;
		}

		for (size_type i{}; i < size_; ++i)
			data_[i].~value_type();
		::operator delete(data_);

		data_ = new_data;
		capacity_ = size_;
	}
};