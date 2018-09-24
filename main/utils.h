#ifndef UTILS_H
#define UTILS_H

#include<algorithm>
#include<cctype>
#include<string>


namespace utils {

static inline std::string &
ltrim(std::string &s)
{
    s.erase(s.begin(), std::find_if(s.begin(), s.end(),
        [](int ch) { return !std::isspace(ch); }));
    return s;
}


static inline std::string &
rtrim(std::string &s)
{
    s.erase(std::find_if(s.rbegin(), s.rend(),
        [](int ch) { return !std::isspace(ch); }).base(), s.end());
    return s;
}


static inline std::string &
trim(std::string &s)
{
    return ltrim(rtrim(s));
}


static inline std::string
ltrim(const std::string &s)
{
    std::string locS(s);
    return ltrim(locS);
}


static inline std::string
rtrim(const std::string &s)
{
    std::string locS(s);
    return rtrim(locS);
}


static inline std::string
trim(const std::string &s)
{
    std::string locS(s);
    return trim(locS);
}


template< typename T >
class QuoteObj {
public:
    QuoteObj(const T &v, const char c) : v_(v), c_(c) { }
    ~QuoteObj() {};
    const T &   v_;
    const char  c_;
};
template< typename T >
inline const QuoteObj<T>    Quote(const T &v, const char c = '"') {
                                return QuoteObj<T>(v, c); }

template< typename T >
inline std::ostream & operator<<(std::ostream& os, const QuoteObj<T> &q)
{
    os << q.c_ << q.v_ << q.c_;
    return os;
}

}

#endif  // UTILS_H
