// contains useful information for debugging
#pragma once

// aborts the program with a message and other information
#define PANIC(_error_msg) fprintf(stderr, "ERROR: %s\n{line: %i, function: %s}\n", _error_msg, __LINE__, __FUNCTION__); abort();
