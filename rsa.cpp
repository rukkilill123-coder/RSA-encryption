#include <unordered_map>
#include <iostream>
#include <cstdlib>
#include <string>
#include <memory>
#include <cmath>

typedef unsigned long long int big;

big gcd(big a, big b)
{
  return (b == 0) ? a : gcd(b, a % b);
}

big extended_euclidean(big a, big b, big& x, big& y)
{
  if (a == 0)
  {
    x = 0;
    y = 1;

    return b;
  }

  big x1, y1;

  big extended = extended_euclidean(b % a, a, x1, y1);

  x = y1 - (b / a) * x1;
  y = x1;

  return extended;
}

bool is_coprime(big a, big b)
{
  return (gcd(a, b) == 1);
}

big reduced_totient(big n, big j)
{
  for (int i = 0; i < n; i++)
  {
    if (!is_coprime(i, n))
      continue;
    
    if ((big)(pow(i, j)) % n != 1)
      return reduced_totient(n, j + 1);
  }
  
  return j;
}

big generate_encryption_exponent(big upper)
{
  big random = rand() % upper + 1;
  
  return (is_coprime(random, upper)) ? random : generate_encryption_exponent(upper);
}

big generate_decryption_exponent(big e, big lambda_n)
{
  big x, y;

  extended_euclidean(e, lambda_n, x, y);

  return (x % lambda_n + lambda_n) % lambda_n;
}

std::unordered_map<char, big> generate_keys(big p, big q)
{
  std::unordered_map<char, big> keys;
  
  big n = p*q;
  big lambda_n = reduced_totient(n, 1);
  big e = generate_encryption_exponent(lambda_n);
  big d = generate_decryption_exponent(e, lambda_n);

  keys['d'] = d;
  keys['n'] = n;
  keys['e'] = e;

  return keys;
}
  
int main()
{
  return 0;
}
