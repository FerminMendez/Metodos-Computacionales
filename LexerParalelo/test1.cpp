#include <iostream>
#include <fstream>
#include <cctype>

using namespace std;

int main(int argc, char* argv[]) {
  ifstream file;
  char c;
  
  //Comentario
  
  int var = -120;
  
  //Sigue un float
  
  float decimal = 2.3;
  
  float vex_max = -5.4E-12;

  float ent_exp = 2e8;

  file.open("input.txt");
  if (!file) {
    cout << "file not found\n";
    return -1;
  }

  int finished = false;
  while (file.peek()!=eof) {
    file >> c;
    if (isspace(c)) {
      cout << ". . ";
      continue;
    }
    cout << ((int) c) << " ";
  }

  file.close();

  return 0;
}