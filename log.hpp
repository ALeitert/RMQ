// Implements logarithm functions.

#ifndef __Log_H__
#define __Log_H__

#ifdef __GNUC__

// Returns the floor of the logarithm base 2 of the given number.
inline unsigned logF(unsigned n)
{
    return (sizeof(unsigned) * __CHAR_BIT__ - 1) xor __builtin_clz(n | 1);
}

// Returns the floor of the logarithm base 2 of the given number.
inline unsigned logF(unsigned long n)
{
    return (sizeof(unsigned long) * __CHAR_BIT__ - 1) xor __builtin_clzl(n | 1);
}

// Returns the floor of the logarithm base 2 of the given number.
inline unsigned logF(unsigned long long n)
{
    return (sizeof(unsigned long long) * __CHAR_BIT__ - 1) xor __builtin_clzll(n | 1);
}

#else

#endif


// Returns the ceil of the logarithm base 2 of the given number.
template<class T>
inline unsigned logC(T n)
{
    return logF(n - 1) + 1;
}

#endif
