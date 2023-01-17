#include <iostream>
#include <string>
#include <unordered_map>
#include <queue>
#include <cstdlib>
#include <bitset>
using namespace std;

#ifndef ESTRUTURAS_H
#define ESTRUTURAS_H

struct No {
    char ch;
    int freq;
    No *esq, *dir;

    No(char ch, int freq){
        this->ch = ch;
        this->freq = freq;
        this->esq = this->dir = nullptr;
    }

    No(char ch, int freq, No* esq, No* dir){
        this->ch = ch;
        this->freq = freq;
        this->esq = esq;
        this->dir = dir;
    }
};

typedef struct No* ArvoreH;
typedef unordered_map<char, string> TabelaHuffman;
struct Compare {
    bool operator()(No *esq, No *dir){
        return esq->freq > dir->freq;
    }
};

struct CabecalhoHuffman {
    size_t nBytes;
    size_t tamTabela;
};

struct ArquivoHuffman {
    size_t nBytes;
    TabelaHuffman tabelaCodigos;
    vector<bitset<8>> vetorBits;
};

ArvoreH construirArvoreHuffman(string text);
TabelaHuffman gerarTabelaCodigos(ArvoreH raiz);
string gerarBitString(string conteudoArq, TabelaHuffman tabelaCodigos);
string decodeArquivo(string bitString, TabelaHuffman tabelaCodigos);

#endif