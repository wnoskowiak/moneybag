#ifndef MONEYBAG_H
#define MONEYBAG_H
#include <cstdint>
#include <compare>
#include <string>

class Moneybag
{
private:
    uint64_t livre_num;
    uint64_t denier_num;
    uint64_t solidus_num;

public:
    using coin_number_t = uint64_t;
    Moneybag(coin_number_t livre, coin_number_t solidus, coin_number_t dinar)
    {
        livre_num = livre;
        denier_num = dinar;
        solidus_num = solidus;
    }
    Moneybag &operator=(Moneybag other)
    {
        livre_num = other.livre_number();
        solidus_num = other.solidus_number();
        denier_num = other.denier_number();
        return *this;
    }
    Moneybag(const Moneybag& other)
    {
        livre_num = other.livre_number();
        denier_num = other.solidus_number();
        solidus_num = other.denier_number();
    }
    Moneybag operator+(Moneybag other) const
    {
        return Moneybag(livre_num + other.livre_number(),
                        solidus_num + other.solidus_number(),
                        denier_num + other.denier_number());
    }
    Moneybag operator-(Moneybag other) const
    {
        return Moneybag(livre_num - other.livre_number(),
                        solidus_num - other.solidus_number(),
                        denier_num - other.denier_number());
    }
    Moneybag operator*(coin_number_t other) const
    {
        return Moneybag(livre_num * other,
                        solidus_num * other,
                        denier_num * other);
    }
    Moneybag &operator+=(Moneybag other)
    {
        livre_num + other.livre_number();
        solidus_num + other.solidus_number();
        denier_num + other.denier_number();
        return *this;
    }
    Moneybag &operator-=(Moneybag other)
    {
        livre_num - other.livre_number();
        solidus_num - other.solidus_number();
        denier_num - other.denier_number();
        return *this;
    }
    Moneybag &operator*=(coin_number_t other)
    {
        livre_num *other;
        solidus_num *other;
        denier_num *other;
        return *this;
    }
    auto operator<=>(Moneybag other)
    {
        __uint128_t uno = 240 * livre_num + 20 * solidus_num + denier_num;
        __uint128_t dos = 240 * other.livre_number() + 20 * other.solidus_number() + other.denier_number();
        return uno <=> dos;
    }
    bool operator==(Moneybag other)
    {
        return (livre_num == other.livre_number()) &&
               (denier_num == other.denier_number()) &&
               (solidus_num == other.solidus_number());
    }
    explicit operator bool()
    {
        return (livre_num > 0) &&
               (denier_num > 0) &&
               (solidus_num > 0);
    }
    constexpr coin_number_t livre_number() const { return livre_num; };
    constexpr coin_number_t denier_number() const { return denier_num; };
    constexpr coin_number_t solidus_number() const { return solidus_num; };
};

Moneybag operator*(Moneybag::coin_number_t other, Moneybag bag)
{
    return Moneybag(bag.livre_number() * other,
                    bag.solidus_number() * other,
                    bag.denier_number() * other);
}

std::ostream &operator<<(std::ostream &os, Moneybag bag)
{
    std::string livre_s = "livres";
    Moneybag::coin_number_t livre_n = bag.livre_number();
    if (livre_n == 1)
    {
        livre_s = "livr";
    }
    livre_s = std::to_string(livre_n) + " " + livre_s;
    std::string solidus_s = "soliduses";
    Moneybag::coin_number_t solidus_n = bag.solidus_number();
    if (solidus_n == 1)
    {
        solidus_s = "solidus";
    }
    solidus_s = std::to_string(solidus_n) + " " + solidus_s;
    std::string denier_s = "deniers";
    Moneybag::coin_number_t denier_n = bag.denier_number();
    if (denier_n == 1)
    {
        denier_s = "denier";
    }
    denier_s = std::to_string(denier_n) + " " + denier_s;
    os << "(" + livre_s + " ," + solidus_s + " ," + denier_s + ")";
    return os;
}

const Moneybag Livre(1, 0, 0);
const Moneybag Solidus(0, 1, 0);
const Moneybag Denier(0, 0, 1);

class Value
{
public:
    constexpr Value();
    constexpr Value(const Moneybag &moneybag);
    constexpr Value(uint64_t n);
    constexpr Value(const Value &val);
    constexpr std::strong_ordering operator<=>(const Value &other) const
    {
        return v <=> other.v;
    }
    constexpr std::strong_ordering operator<=>(const uint64_t &other) const
    {
        return v <=> other;
    }
    constexpr bool operator==(const Value &other) const
    {
        return v == other.v;
    }
    constexpr bool operator==(const uint64_t &other) const
    {
        return v == other;
    }
    operator std::string() const
    {
        const int mod = 10;
        char digit;
        std::string res;
        __uint128_t tmp = v;
        do
        {
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