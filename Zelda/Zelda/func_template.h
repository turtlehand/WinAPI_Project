#pragma once

// �����Ҵ�� �ڷ������� ����� ���� Delete �Լ�
template<typename T>
void Delete_Vector(vector<T*>& _vec)
{
	for (size_t i = 0; i < _vec.size(); ++i)
	{
		DELETEGAMEOBJECT(_vec[i]);
	}

	_vec.clear();
}

// �����Ҵ�� �ڷ������� ����� ���� Delete �Լ�
// �迭�� �ڷ����� T�̰� ũ�Ⱑ ArraySize�� �迭�� ������ �޴´�. 
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