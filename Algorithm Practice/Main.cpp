#include <fstream>

#include "AlgorithmCollection.h"
#include "AlgorithmChooser.h"

#define ENABLETIMER


static char* helpMessage = "\
Example Useage:\n\
\t./Practice <algorithm-id> <input-path> <output-path>\n\
\n\
<algorithm-id> should be a 4 digit code that matches the id of the algorithm that you want to run\n\
<input-path> is required, and should match the format of the sample inputs provided in the SampleInputs directory\n\
<Output-path> is optional, by defailt std out will be used\n\
";

string infile;
string outfile;
int algoID = 0;  // vtable will continue to grow the more algorithms I add

bool handleInput(int argc, char const* argv[]) {
  // TODO: Validate file paths
  switch (argc) {
    case 4:
      outfile = string{argv[3]};
    case 3:
      infile = string{argv[2]};
      algoID = atoi(argv[1]);
      return true;
    default:
      return false;  // -1 returned because something is wrong with the input
  }
}

int main(int argc, char const *argv[]) {
  int callok = handleInput(argc, argv);
  if (!callok) {
    std::cout << helpMessage << std::endl;
    return -1;
  }

  std::ifstream in;
  std::ofstream out;
  
  in.open(infile, std::ios_base::in);
  if (outfile.size() != 0) out.open(outfile, std::ios_base::out);

  AlgorithmWrapper algo = choose(algoID);
  if (outfile.size() != 0) {
    out.open(outfile, std::ios_base::out);
    algo.algorithm->run(in,out);
    out.close();
  } else {
    algo.algorithm->run(in,std::cout);
  }
  in.close();

  Logger& l = Logger::getLogger();
  std::cout << l << std::endl;
  return 0;
}
