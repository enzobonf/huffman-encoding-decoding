#include <iostream>
#include <string>
#include <unordered_map>
#include "estruturas.h"

using namespace std;

#ifndef ARQUIVO_H
#define ARQUIVO_H

class Arquivo {
    private:
        string nomeArq;
    public:
        Arquivo(string momeArq);
        void lerArquivo();
        static void escreverArquivoBinario(string stringBinaria, TabelaHuffmanChar tabela, string filename);
        static ArqHuffmanChar* lerArquivoCodificadoCaractere(string filename);
        string conteudoArq;
};

#endif