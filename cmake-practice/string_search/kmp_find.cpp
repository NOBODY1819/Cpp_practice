#include "kmp_find.h"

std::vector<size_t> compute_lps(const std::string &pattern) // return the longes prefix sufix table
{
  size_t m = pattern.size(), j = 0, i = 1;
  std::vector<size_t> lps(m, 0);

  while (i < m)
  {
    if (pattern[i] == pattern[j])
    {
      j++;
      lps[i] = j;
      i++;
    }
    else
    {
      if (j != 0)
      {
        j = lps[j - 1];
      }
      else
      {
        lps[i] = 0;
        i++;
      }
    }
  }
  return lps;
}

size_t kmp_find(const std::string &text, const std::string &pattern, size_t start) // return the index where patter is found in text else npos
{
  size_t n = text.size(), m = pattern.size();

  if (m == 0)
    return start;
  if (start >= n || m > n - start)
    return std::string::npos;

  std::vector<size_t> lps = compute_lps(pattern);
  size_t i = start, j = 0;

  while (i < n)
  {
    if (pattern[j] == text[i])
    {
      i++;
      j++;
    }

    if (j == m)
    {
      return i - j;
    }
    else if (i < n && pattern[j] != text[i])
    {
      if (j != 0)
      {
        j = lps[j - 1];
      }
      else
      {
        i++;
      }
    }
  }

  return std::string::npos;
}