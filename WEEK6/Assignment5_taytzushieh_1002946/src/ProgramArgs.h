#ifndef PROGRAM_ARGS_H
#define PROGRAM_ARGS_H

#include <iostream>

using namespace std;

class ProgramArgs {
 public:
  static ProgramArgs parse(const int, const char* const[]);

  // attributes
  string getInputFilename();
  string getOutputFilename();
  int getImgWidth();
  int getImgHeight();

 private:
  string input_filename = "";
  string output_filename = "";
  int img_width = -1;
  int img_height = -1;
};

#endif  // PROGRAM_ARGS_H