#pragma once

#include "../include/string.h"
#include <stdio.h>

namespace atl {

class ofstream {

public:
  /* Constructor */
  ofstream(const atl::string &filename) {
    filePtr = fopen(filename.c_str(), "w");
  }

  ofstream(const ofstream &rhs) = delete;
  ofstream(ofstream &&rhs) {
    filePtr = rhs.filePtr;
    rhs.filePtr = nullptr;
  }

  ~ofstream() { fclose(filePtr); }

  bool good() {
    if (filePtr)
      return true;
    else
      return false;
  }

  void write(const atl::string &contents) { fputs(contents.c_str(), filePtr); }

private:
  FILE *filePtr;
};

} // namespace atl
