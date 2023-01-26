#include "menu.h"
#include "arquivo.h"
#include "estruturas.h"
#include <chrono>

#define N_BITS 16

using namespace std;

int main() {

  setlocale(LC_ALL, "utf-8");

  Menu *menu = new Menu;
  menu->mostrar();

}