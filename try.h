#include <stdarg.h>

#define _DEBUG

#define _STR(s) #s
#define STR(s) _STR(s)

#ifdef _DEBUG
#define DEBUG(s, ...) printf("[DEBUG] : "#s, ##__VA_ARGS__)
#else
#define DEBUG(s, ...)
#endif // _DEBUG

#define var(left, right) decltype(right) left = (right)


template<typename T> void swap(T& a, T& b) {
	T tempT;
	tempT = a;
	a = b;
	b = tempT;
}
