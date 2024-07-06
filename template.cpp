
template<typename T>
T atoi_impl(const char* str)
{
    while (std::isspace(static_cast<unsigned char>(*str)))
        ++str;
 
    bool negative = false;
 
    if (*str == '+')
        ++str;
    else if (*str == '-')
    {
        ++str;
        negative = true;
    }
 
    T result = 0;
    for (; std::isdigit(static_cast<unsigned char>(*str)); ++str)
    {
        int digit = *str - '0';
        result *= 10;
        result -= digit; // calculate in negatives to support INT_MIN, LONG_MIN,..
    }
 
    return negative ? result : -result;
}
 
int atoi(const char* str)
{
    return atoi_impl<int>(str);
}
 
long atol(const char* str)
{
    return atoi_impl<long>(str);
}
 
long long atoll(const char* str)
{
    return atoi_impl<long long>(str);
}