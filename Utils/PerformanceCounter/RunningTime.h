#pragma once

#include <chrono>

class PC_RunningTime
{
private:
	std::chrono::system_clock::time_point _start;
	std::chrono::system_clock::time_point _end;

public:
	PC_RunningTime()
	{
		Start();
	}

	void Start()
	{
		_start = std::chrono::system_clock::now();
	}

	void End()
	{
		_end = std::chrono::system_clock::now();
	}

	template <typename Unit>
	Unit GetElapsed()
	{
		std::chrono::system_clock::time_point end = std::chrono::system_clock::now();
		return std::chrono::duration_cast<Unit>(end - _start);
	}

	template <typename Unit>
	Unit GetDuration()
	{
		return std::chrono::duration_cast<Unit>(_end - _start);
	}
};
