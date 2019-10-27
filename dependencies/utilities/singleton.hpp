#pragma once

template <typename T>
class singleton {
public:
	static T* get()
	{
		static T* _inst = nullptr;

		if (!_inst)
			_inst = new T();

		return _inst;
	}
};