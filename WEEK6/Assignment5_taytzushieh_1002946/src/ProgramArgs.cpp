#include <iostream>
#include <cassert>
#include <algorithm>
#include "ProgramArgs.h"

using namespace std;

ProgramArgs ProgramArgs::parse(const int argc, const char* const argv[]) {
  ProgramArgs args = ProgramArgs();

  for (int argNum = 1; argNum < argc; ++argNum) {
    string currentArg = string(argv[argNum]);

    if (currentArg == "-input" && argNum + 1 < argc) {
      // set the input file
      args.input_filename = string(argv[++argNum]);

    } else if (currentArg == "-size" && argNum + 2 < argc) {
      // set the image size
      // validate height value
      string height = string(argv[++argNum]);
      if (all_of(height.begin(), height.end(), ::isdigit)) {
        args.img_height = stoi(height);
      } else {
        cerr << "Invalid height value (expect integer): " << height << endl;
        exit(EXIT_FAILURE);
      }

      // verify height value
      if (args.img_height <= 0) {
        cerr << "Image height must > 0 " << endl;
        exit(EXIT_FAILURE);
      }

      // validate width value
      string width = string(argv[++argNum]);
      if (all_of(width.begin(), width.end(), ::isdigit)) {
        args.img_width = stoi(width);
      } else {
        cerr << "Invalid width value (expect integer): " << width << endl;
        exit(EXIT_FAILURE);
      }

      // verify width value
      if (args.img_width <= 0) {
        cerr << "Image width must > 0 " << endl;
        exit(EXIT_FAILURE);
      }
    } else if (currentArg == "-output" && argNum + 1 < argc) {
      // set the output file
      args.output_filename = string(argv[++argNum]);
    } else {
      cerr << "Invalid argument: " << currentArg << endl;
      exit(EXIT_FAILURE);
    }
  }

  return args;
}

// Attributes getter
string ProgramArgs::getInputFilename() {
  return input_filename;
}

string ProgramArgs::getOutputFilename() {
  return output_filename;
}

int ProgramArgs::getImgWidth() {
  return img_width;
}

int ProgramArgs::getImgHeight() {
  return img_height;
}