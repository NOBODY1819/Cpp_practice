#include "naive_find.h"

size_t naive_find(const std::string &text, const std::string &pattern, size_t start) // Nive approach for searching a substring
{
  if (pattern.empty())
    return start;

  size_t t_size = text.size(), p_size = pattern.size();

  if (p_size > t_size - start)
    return std::string::npos;

  for (size_t i = start; i <= t_size - p_size; i++)
  {
    bool match = true;
    for (size_t j = 0; j < p_size; j++)
    {
      if (text[i + j] != pattern[j])
      {
        match = false;
        break;
      }
    }
    if (match)
    {
      return i;
    }
  }

  return std::string::npos;
}