#include <unordered_map>
#include <iostream>
#include <cstdlib>
#include <cstdint>
#include <string>
#include <memory>
#include <bitset>
#include <cmath>

uint64_t gcd(uint64_t a, uint64_t b)
{
  return (b == 0) ? a : gcd(b, a % b);
}

uint64_t extended_euclidean(uint64_t a, uint64_t b, uint64_t& x, uint64_t& y)
{
  if (a == 0)
  {
    x = 0;
    y = 1;

    return b;
  }

  uint64_t x1, y1;
  uint64_t extended = extended_euclidean(b % a, a, x1, y1);
  x = y1 - (b / a) * x1;
  y = x1;

  return extended;
}

bool is_coprime(uint64_t a, uint64_t b)
{
  return (gcd(a, b) == 1);
}

uint64_t reduced_totient(uint64_t n, uint64_t j)
{
  for (int i{0}; i < n; i++)
  {
    if (!is_coprime(i, n))
      continue;
    
    if ((uint64_t)(pow(i, j)) % n != 1)
      return reduced_totient(n, j + 1);
  }
  
  return j;
}

uint64_t generate_encryption_exponent(uint64_t upper)
{
  uint64_t random = rand() % upper + 1;
  
  return (is_coprime(random, upper)) ? random : generate_encryption_exponent(upper);
}

uint64_t generate_decryption_exponent(uint64_t e, uint64_t lambda_n)
{
  uint64_t x, y;
  extended_euclidean(e, lambda_n, x, y);

  return (x % lambda_n + lambda_n) % lambda_n;
}

std::unordered_map<char, uint64_t> generate_keys(uint64_t p, uint64_t q)
{
  std::unordered_map<char, uint64_t> keys;
  uint64_t n = p*q;
  uint64_t lambda_n = reduced_totient(n, 1);
  uint64_t e = generate_encryption_exponent(lambda_n);
  uint64_t d = generate_decryption_exponent(e, lambda_n);
  keys['d'] = d;
  keys['n'] = n;
  keys['e'] = e;

  return keys;
}

template<size_t len>
struct ConstexprString
{
  char data[len];

  constexpr ConstexprString(const char(&str)[len])
  {
    std::copy(str, str + len, data);
  }
};

template<ConstexprString str>
uint64_t numeric_representation()
{
  uint64_t size = sizeof(str.data) / sizeof(str.data[0]);
  std::string binary_array[size];
  unsigned int i = 0;
  
  for (char c : str.data)
  {
    if (c == '\0')
      break;
    
    std::bitset<8> binary(c);
    binary_array[i++] = binary.to_string();
  }

  std::string binaries = "";

  for (int i{0}; i < size; i++)
    binaries += binary_array[i];

  return std::stoull(binaries, nullptr, 2);
}

template<ConstexprString str>
std::string encrypt(uint64_t n, uint64_t e)
{
  uint64_t M = numeric_representation<str>();
  
  return std::to_string((uint64_t)(pow(M, e)) % n);
}

int main()
{
  
  return 0;
}
