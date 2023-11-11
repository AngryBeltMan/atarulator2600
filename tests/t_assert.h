#pragma once
#define ASSERT(cmp) if (!(cmp)) { printf("Assertion failed running test: %s\n (line: %i, comparison: %s)\n", __FUNCTION__, __LINE__, #cmp); }
/* #define ASSERT_EQ(_lhs, _rhs) if () { printf("Assertion failed running test: %s\nline: %i\n", __FUNCTION__, __LINE__); } */
