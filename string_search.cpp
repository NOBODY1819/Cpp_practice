#include <iostream>
#include <string>
#include <vector>

size_t naive_find(const std::string &text, const std::string &pattern, size_t start = 0) // Nive approach for searching a substring
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

size_t kmp_find(const std::string &text, const std::string &pattern, size_t start = 0) // return the index where patter is found in text else npos
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

void auto_test()
{
  std::string text = "hello world hello again";
  std::string pat1 = "hello";
  std::string pat2 = "xyz";
  std::string pat3 = "";
  std::string pat4 = "world";

  std::cout << "Text: \"" << text << "\"\n\n";

  auto test = [&](const std::string &p, size_t start = 0)
  {
    size_t pos = naive_find(text, p, start);
    std::cout << "Pattern \"" << p << "\" starting at " << start
              << " -> " << (pos != std::string::npos ? std::to_string(pos) : "npos") << "\n";
  };

  test("hello");      // 0
  test("hello", 6);   // 12
  test("world");      // 6
  test("xyz");        // npos
  test("");           // 0
  test("hello", 100); // npos
}

int main(int argc, char *argv[])
{
  if (argc == 2 && static_cast<std::string>(argv[1]) == static_cast<std::string>("test"))
  {
    auto_test();
    return 0;
  }

  if (argc != 3)
  {
    std::cout << "invalid use\nUsage: " << argv[0] << " 'text' 'pattern'\n";
    std::cout << argc << " provided ";

    for (size_t i = 0; i < argc; i++)
      std::cout << "\"" << argv[i] << "\" ";
    std::cout << "\n\n";
    return 1;
  }

  std::string text = argv[1], pattern = argv[2];
  std::cout << "text: \"" << text << "\"\npattern: \"" << pattern << "\"\n";
  size_t pos = naive_find(text, pattern);

  if (pos != std::string::npos)
  {
    std::cout << "found match at position: " << pos << "\n";
  }
  else
  {
    std::cout << "not found\n";
  }

  return 0;
}
