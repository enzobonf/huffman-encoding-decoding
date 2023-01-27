#include <iostream>
#include <fstream>
#include <string>
#include <unordered_map>
#include <queue>
#include <cstdlib>
#include <cstdio>
#include <bitset>
#include <sstream>
#include <chrono>
#include <cstring>
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

struct NoPalavra {
    string palavra;
    int freq;
    NoPalavra *esq, *dir;

    NoPalavra(string palavra, int freq){
        this->palavra = palavra;
        this->freq = freq;
        this->esq = this->dir = nullptr;
    }

    NoPalavra(string palavra, int freq, NoPalavra* esq, NoPalavra* dir){
        this->palavra = palavra;
        this->freq = freq;
        this->esq = esq;
        this->dir = dir;
    }
};

typedef struct No* ArvoreHChar;
typedef struct NoPalavra* ArvoreHPalavra;

typedef unordered_map<char, string> TabelaHuffmanChar;
typedef unordered_map<string, string> TabelaHuffmanPalavra;

template <typename T>
struct Compare {
    bool operator()(T esq, T dir){
        return esq->freq > dir->freq;
    }
};

struct CabecalhoHuffman {
    size_t nBytes;
    size_t tamTabela;
    short nFillBits;
};

struct ArqHuffmanChar {
    size_t nBytes;
    short nFillBits;
    TabelaHuffmanChar tabelaCodigos;
    vector<bitset<8>> vetorBytes;

    ArqHuffmanChar(size_t nBytes, short nFillBits, TabelaHuffmanChar tabelaCodigos, vector<bitset<8>> vetorBytes){
        this->nBytes = nBytes;
        this->nFillBits = nFillBits;
        this->tabelaCodigos = tabelaCodigos;
        this->vetorBytes = vetorBytes;
    }
};

struct ArqHuffmanPalavra {
    size_t nBytes;
    short nFillBits;
    TabelaHuffmanPalavra tabelaCodigos;
    vector<bitset<8>> vetorBytes;

    ArqHuffmanPalavra(size_t nBytes, short nFillBits, TabelaHuffmanPalavra tabelaCodigos, vector<bitset<8>> vetorBytes){
        this->nBytes = nBytes;
        this->nFillBits = nFillBits;
        this->tabelaCodigos = tabelaCodigos;
        this->vetorBytes = vetorBytes;
    }
};

ArvoreHChar construirArvoreHuffmanChar(string text);
ArvoreHPalavra construirArvoreHuffmanPalavra(string text);
TabelaHuffmanChar gerarTabelaCodigosChar(ArvoreHChar raiz);
TabelaHuffmanPalavra gerarTabelaCodigosPalavra(ArvoreHPalavra raiz);
string gerarBitStringCaractere(string conteudoArq, TabelaHuffmanChar tabelaCodigos);
string gerarBitStringPalavra(string conteudoArq, TabelaHuffmanPalavra tabelaCodigos);
void gerarBitset(string bitString, vector<bitset<8>> &bit_set, short &nFillBits);
string decodeBitString(string bitString, TabelaHuffmanChar tabelaCodigos);
string decodeBitString(string bitString, TabelaHuffmanPalavra tabelaCodigos);
string decodeArquivoCaractere(ArqHuffmanChar *arq);
string decodeArquivoPalavra(ArqHuffmanPalavra *arq);

#endif