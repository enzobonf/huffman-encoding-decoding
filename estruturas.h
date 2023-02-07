#include <iostream>
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
    // Compara os nós da esquerda e direita para criação da fila
    // Pré-condição: O tipo ser No ou NoPalavra
    // Pós-condição: retorna true/false sobre se o nó da esquerda
    // tem frequência maior que o da esquerda
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

    // Construtor do objeto do arquivo codificado por caractere
    // Pré-condição: parâmetros válidos
    // Pós-condição: o objeto é criado
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

    // Construtor do objeto do arquivo codificado por palavras
    // Pré-condição: parâmetros válidos
    // Pós-condição: o objeto é criado
    ArqHuffmanPalavra(size_t nBytes, short nFillBits, TabelaHuffmanPalavra tabelaCodigos, vector<bitset<8>> vetorBytes){
        this->nBytes = nBytes;
        this->nFillBits = nFillBits;
        this->tabelaCodigos = tabelaCodigos;
        this->vetorBytes = vetorBytes;
    }
};

// Gera a árvore huffman de codificação via caractere a partir do texto
// Pré-condição: ser passado um texto não-vazio
// Pós-condição: a raíz da árvore construida é retornada
ArvoreHChar construirArvoreHuffmanChar(string text);

// Gera a árvore huffman de codificação via palavra a partir do texto
// Pré-condição: ser passado um texto não-vazio
// Pós-condição: a raíz da árvore construida é retornada
ArvoreHPalavra construirArvoreHuffmanPalavra(string text);

// Gera uma tabela de códigos a partir da árvore de caracteres (tabela hash)
// Pré-condição: Objeto válido da árvore
// Pós-condição: A tabela é criada e preenchida com os caracteres e seus códigos
TabelaHuffmanChar gerarTabelaCodigosChar(ArvoreHChar raiz);

// Gera uma tabela de códigos a partir da árvore de palavras (tabela hash)
// Pré-condição: Objeto válido da árvore
// Pós-condição: A tabela é criada e preenchida com as palavras e seus códigos
TabelaHuffmanPalavra gerarTabelaCodigosPalavra(ArvoreHPalavra raiz);

// Gera uma string binária a partir do conteúdo original do arquivo
// e da tabela de códigos de caracteres
// Pré-condição: O texto ser o mesmo usado para criação da árvore, e uma 
// tabela de códigos válida
// Pós-condição: A string binária é gerada
string gerarBitStringCaractere(string conteudoArq, TabelaHuffmanChar tabelaCodigos);

// Gera uma string binária a partir do conteúdo original do arquivo
// e da tabela de códigos de palavras
// Pré-condição: O texto ser o mesmo usado para criação da árvore, e uma 
// tabela de códigos válida
// Pós-condição: A string binária é gerada
string gerarBitStringPalavra(string conteudoArq, TabelaHuffmanPalavra tabelaCodigos);

// Gera um vetor de bytes a partir da string binária
// Pré-condição: String binária válida, vetor e variável nFillBits terem sido inicializados
// Pós-condição: O vetor é preenchido e a variável nFillBits recebe o número de bits
// de preenchimento no ultimo elemento do vetor
void gerarBitset(string bitString, vector<bitset<8>> &bit_set, short &nFillBits);

// Função auxiliar de decodificação, decodifica a string binária, utilizando da tabela de 
// códigos de caracteres
// Pré-condição: string binária e tabela de códigos válida.
// Pós-condição: o conteúdo decodificado do arquivo é retornado
string decodeBitString(string bitString, TabelaHuffmanChar tabelaCodigos);

// Função auxiliar de decodificação, decodifica a string binária, utilizando da tabela de 
// códigos de palavras
// Pré-condição: string binária e tabela de códigos válida.
// Pós-condição: o conteúdo decodificado do arquivo é retornado
string decodeBitString(string bitString, TabelaHuffmanPalavra tabelaCodigos);

// Função principal de decodificação, recebe a struct do arquivo e transforma o vetor de bits
// novamente em uma string binária, realizando a remoção dos bits de preenchimento
// Pré-condição: Ponteiro válido para o obbjeto do arquivo codificado por caracteres
// Pós-condição: Retorna o resultado da função auxiliar (o texto decodificado)
string decodeArquivoCaractere(ArqHuffmanChar *arq);


// Função principal de decodificação, recebe a struct do arquivo e transforma o vetor de bits
// novamente em uma string binária, realizando a remoção dos bits de preenchimento
// Pré-condição: Ponteiro válido para o obbjeto do arquivo codificado por palavras
// Pós-condição: Retorna o resultado da função auxiliar (o texto decodificado)
string decodeArquivoPalavra(ArqHuffmanPalavra *arq);

#endif