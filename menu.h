#include <vector>
#include <iostream>
#include <string>
#include <chrono>
using namespace std;

#ifndef MENU_H
#define MENU_H

class Menu {
    private:
      vector<string> opcoes;
      void mostrarOpcoes();
    public:
      Menu();
    void novaOpcao(string opcao);
      void mostrar();
};

void codificarArquivoCaractere();
void decodificarArquivoCaractere();

#endif