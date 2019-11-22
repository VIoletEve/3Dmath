#pragma once
#ifndef __COMMONSTUFF_H_INCLUDED__
#define __COMMONSTUFF_H_INCLUDED__

template<typename T>
inline const T& min(const T& a, const T& b) {
	return(a < b) ? a : b;
}

template<typename T>
inline const T& max(const T& a, const T& b) {
	return(a > b) ? a : b;
}

template<typename T>
inline void swap(T& a, T& b) {
	T temp = a;
	a = b;
	b = temp;
}



#endif // !__COMMONSTUFF_H_INCLUDED__