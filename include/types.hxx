#ifndef HEADER_TYPES
#define HEADER_TYPES

#include <cstdint>
#include <iostream>
#include <unordered_set>
#include <vector>

using std::cerr;
using std::cout;
using std::endl;
using std::unordered_set;
using std::vector;

typedef vector<uint16_t> uint16_vector;
typedef vector<uint16_vector> uint16_matrix;
typedef unordered_set<uint16_t> uint16_uset;

#endif