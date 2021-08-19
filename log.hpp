// Implements logarithm functions.

#ifndef __Log_H__
#define __Log_H__

// Returns the ceil of the logarithm base 2 of the given number.
inline unsigned logC(unsigned n)
{
    return (sizeof(unsigned) << 3) - __builtin_clz(n - 1);
}

// Returns the ceil of the logarithm base 2 of the given number.
inline unsigned logC(unsigned long n)
{
    return (sizeof(unsigned long) << 3) - __builtin_clzl(n - 1);
}

// Returns the ceil of the logarithm base 2 of the given number.
inline unsigned logC(unsigned long long n)
{
    return (sizeof(unsigned long long) << 3) - __builtin_clzll(n - 1);
}


// Returns the floor of the logarithm base 2 of the given number.
inline unsigned logF(unsigned n)
{
    return (sizeof(unsigned) << 3) - __builtin_clz(n) - 1;
}

// Returns the floor of the logarithm base 2 of the given number.
inline unsigned logF(unsigned long n)
{
    return (sizeof(unsigned long) << 3) - __builtin_clzl(n) - 1;
}

// Returns the floor of the logarithm base 2 of the given number.
inline unsigned logF(unsigned long long n)
{
    return (sizeof(unsigned long long) << 3) - __builtin_clzll(n) - 1;
}

#endif
