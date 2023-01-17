#include <iostream>
#include <string>
#include <unordered_map>
#include <queue>
#include <cstdlib>
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
    unsigned int nBytes;
    TabelaHuffman tabela;

    CabecalhoHuffman(unsigned int nBytes, TabelaHuffman tabela){
        this->nBytes = nBytes;
        this->tabela = tabela;
    }
};

ArvoreH construirArvoreHuffman(string text);
TabelaHuffman gerarTabelaCodigos(ArvoreH raiz);
string encodeArquivo(string conteudoArq, TabelaHuffman tabelaCodigos);

#endif