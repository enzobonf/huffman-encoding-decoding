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

      // Mostra as opções do menu.
      // Pré-condição: O menu deve estar inicializado
      // Pós-condição: As opções do menu são exibidas na tela, 
      // e a opção do usuário é pedida
      void mostrarOpcoes();
      void startCronometro();
      void stopCronometro();
      std::chrono::time_point<std::chrono::high_resolution_clock> start;
      std::chrono::time_point<std::chrono::high_resolution_clock> end;
    public:
      // Construtor padrão do menu
      // Pré-condição: Nenhuma
      // Pós-condição: Um objeto do tipo Menu com as opções padrão é criado e inicializado.
      Menu();

      // Adiciona uma nova opção ao menu.
      // Pré-condição: opcao é uma string válida.
      // Pós-condição: A string opcao é adicionada ao vetor de opções do menu
      void novaOpcao(string opcao);

      // Mostra as opções do menu.
      // Pré-condição: O menu deve estar inicializado
      // Pós-condição: As opções do menu são exibidas na tela, 
      // e a opção do usuário é pedida
      void mostrar();

      // Encaminha a codificação por caractere
      // Pré-condição: O menu deve estar inicializado
      // Pós-condição: arquivo codificado é salvo
      void codificarArquivoCaractere();

      // Encaminha a decodificação por caractere
      // Pré-condição: O menu deve estar inicializado
      // Pós-condição: arquivo decodificado é salvo
      void decodificarArquivoCaractere();

      // Encaminha a codificação por palavra
      // Pré-condição: O menu deve estar inicializado
      // Pós-condição: arquivo ccodificado é salvo
      void codificarArquivoPalavra();

      // Encaminha a decodificação por palavra
      // Pré-condição: O menu deve estar inicializado
      // Pós-condição: arquivo decodificado é salvo
      void decodificarArquivoPalavra();
};

#endif