#include <iostream>

using namespace std;

void lexerAritmetico(string archivo) {
  // to do
}

int main(int argc, char* argv[]) {
  if (argc != 2) {
    cout << "usage: " << argv[0] << " pathname\n";
    return -1;
  }

  lexerAritmetico(argv[1]);

  return 0;
}
