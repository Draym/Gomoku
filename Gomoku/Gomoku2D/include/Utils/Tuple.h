#pragma once


template<typename T1, typename T2, typename T3>
class Tuple
{
public:
	Tuple(T1 v1, T2 v2, T3 v3) : first(v1), second(v2), third(v3) {}
public:
	T1	first;
	T2	second;
	T3	third;
};