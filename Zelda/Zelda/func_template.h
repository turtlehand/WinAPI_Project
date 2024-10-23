#pragma once

// 동적할당된 자료형들을 지우기 위한 Delete 함수
template<typename T>
void Delete_Vector(vector<T*>& _vec)
{
	for (size_t i = 0; i < _vec.size(); ++i)
	{
		DELETEGAMEOBJECT(_vec[i]);
	}

	_vec.clear();
}

// 동적할당된 자료형들을 지우기 위한 Delete 함수
// 배열의 자료형이 T이고 크기가 ArraySize인 배열을 참조로 받는다. 
template<typename T, int ArraySize>
void Delete_Array(T* (&_arr)[ArraySize])
{
	for (size_t i = 0; i < ArraySize; ++i)
	{
		DELETEGAMEOBJECT(_arr[i])
	}
}

template<typename T1, typename T2>
void Delete_Map(map<T1, T2>& _map)
{
	typename map<T1, T2>::iterator iter = _map.begin();

	for (; iter != _map.end();++iter)
	{
		DELETEGAMEOBJECT(iter->second);
	}
	_map.clear();
}