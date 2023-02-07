#include "menu.h"
#include <fstream>
using namespace std;

int main() {

  setlocale(LC_ALL, "Portuguese");
  
  Menu *menu = new Menu();
  menu->mostrar();

  /* ifstream fin("6mb.txt");

  char ch; string arqCompleto;
  while(fin.get(ch)){
      arqCompleto += ch;
  }

  fin.close();

  ofstream fout("60mb.txt");
  for(auto i = 0; i < 10; i++){
    fout.write(arqCompleto.c_str(), arqCompleto.size());
  } */




}