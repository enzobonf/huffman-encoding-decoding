#include <iostream>
#include <cmath>
#include <string>
#include <sstream>
#include <unordered_map>
#include <vector>
#include <bitset>
#include <cstdio>
#include <string.h>
#include "estruturas.h"

using namespace std;

#ifndef ARQUIVO_H
#define ARQUIVO_H

#define MAX_WORD_LENGTH 50

class Arquivo {
    private:
        string nomeArq;
    public:
        Arquivo(string momeArq);
        void lerArquivo();
        static void escreverArquivoBinarioCaractere(string stringBinaria, TabelaHuffmanChar tabela, string filename);
        static void escreverArquivoBinarioPalavra(string stringBinaria, TabelaHuffmanPalavra tabela, string filename);
        static void escreverArquivoDecodificado(string str, string filename);
        static ArqHuffmanChar* lerArquivoCodificadoCaractere(string filename);
        static ArqHuffmanPalavra* lerArquivoCodificadoPalavra(string filename);
        string conteudoArq;
};

#endif