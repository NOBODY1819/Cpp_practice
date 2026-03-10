// kmp_find.h
#ifndef KMP_FIND_H
#define KMP_FIND_H

#include<string>
#include<vector>

size_t kmp_find(const std::string &text, const std::string &pattern, size_t start = 0);

#endif