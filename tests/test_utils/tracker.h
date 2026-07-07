#pragma once

struct Tracker
{
	static inline int constructions = 0;
	static inline int destructions = 0;

	int value;

	Tracker(int v = 0)
		: value(v)
	{
		++constructions;
	}

	Tracker(const Tracker& other)
		: value(other.value)
	{
		++constructions;
	}

	~Tracker()
	{
		++destructions;
	}
};