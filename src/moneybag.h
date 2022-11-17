#ifndef MONEYBAG_H
#define MONEYBAG_H
#include <cstdint>
#include <compare>
#include <string>

/* Phantom class, for compilation & testing only*/
class Moneybag {
    public:
    constexpr uint64_t livre_number() const {return 0;};
    constexpr uint64_t denier_number() const {return 0;};
    constexpr uint64_t solidus_number() const {return 0;};
};

class Value {
    public:
        constexpr Value(const Moneybag &moneybag);
        constexpr Value(uint64_t n);
        constexpr Value(const Value &val);
        constexpr std::strong_ordering operator<=>(const Value &other) const {
            return v <=> other.v;
        }
        constexpr std::strong_ordering operator<=>(const uint64_t &other) const {
            return v <=> other;
        }
        constexpr bool operator==(const Value &other) const {
            return v == other.v;
        }
        constexpr bool operator==(const uint64_t &other) const {
            return v == other;
        }
        operator std::string() const {
            const int mod = 10;
            char digit;
            std::string res;
            __uint128_t tmp = v;
            do {
                digit = '0' + tmp % mod;
                res += digit;
                tmp /= 10;
            } while (tmp);
            std::reverse(res.begin(), res.end());
            return res;
        }
    private:
        __uint128_t v;
    

};

constexpr Value::Value(const Moneybag &moneybag)
    : v(moneybag.livre_number() * 240 +
        moneybag.solidus_number() * 12 + moneybag.denier_number()) {}

constexpr Value::Value(uint64_t n)
    : v(n) {}

constexpr Value::Value(const Value &val)
    : v(val.v) {}

#endif // moneybag.h