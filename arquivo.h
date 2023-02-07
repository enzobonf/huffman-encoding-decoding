#include <iostream>
#include <fstream>
#include <cmath>
#include <string>
#include <sstream>
#include <unordered_map>
#include <vector>
#include <bitset>
#include <cstdio>
#include <string.h>
#include <locale>
#include "estruturas.h"

using namespace std;

#ifndef ARQUIVO_H
#define ARQUIVO_H

#define MAX_WORD_LENGTH 40

class Arquivo {
    private:
        string nomeArq;
    public:
        string conteudoArq;
        // Construtor da classe arquivo, inicializa o nome do arquivo
        // Pré-condição: deve ser passado um nome de arquivo válido
        // Pós-condição: o nome do arquivo é colocado no objeto Arquivo.
        Arquivo(string momeArq);

        // Lê todo o conteúdo do arquivo
        // Pré-condição: o arquivo deve estar inicializado
        // Pós-condição: o conteúdo é colocado na variável conteudoArq no objeto
        void lerArquivo();

        // Escreve uma string binária e o cabeçalho de codificação por caractere num arquivo binário
        // Pré-condição: a string binária, a tabela de códigos e o nome do arquivo devem ser válidos
        // Pós-condição: o arquivo binário é escrito
        static void escreverArquivoBinarioCaractere(string stringBinaria, TabelaHuffmanChar tabela, string filename);
        
        // Escreve uma string binária e o cabeçalho de codificação por palavra num arquivo binário
        // Pré-condição: a string binária, a tabela de códigos e o nome do arquivo devem ser válidos
        // Pós-condição: o arquivo binário é escrito
        static void escreverArquivoBinarioPalavra(string stringBinaria, TabelaHuffmanPalavra tabela, string filename);

        // Escreve uma string comum (arquivo decodificado) no arquivo
        // Pré-condição: string e nome de arquivo válido
        // Pós-condição: o conteúdo decodificado é escrito no arquivo
        static void escreverArquivoDecodificado(string str, string filename);

        // Lê um arquivo binário feito via codificação por caractere
        // Pré-condição: o arquivo é um arquivo codificado por caractere válido
        // Pós-condição: o objeto do arquivo é retornado com as informações para a decodificação
        static ArqHuffmanChar* lerArquivoCodificadoCaractere(string filename);

        // Lê um arquivo binário feito via codificação por palavra
        // Pré-condição: o arquivo é um arquivo codificado por palavra válido
        // Pós-condição: o objeto do arquivo é retornado com as informações para a decodificação
        static ArqHuffmanPalavra* lerArquivoCodificadoPalavra(string filename);
};

#endif