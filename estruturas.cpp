#include <iostream>
#include <string>
#include <unordered_map>
#include <queue>
#include <cstdlib>

using namespace std;

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

ArvoreH construirArvoreHuffman(string text){
    unordered_map<char, int> freq;
    for(char ch : text){ // O(tamanho do texto em caracteres)
        freq[ch]++;
    }

    priority_queue<No*, vector<No*>, Compare> fila;

    for(auto pair : freq){ // O(n de caracteres diferentes no texto)
        // first = caractere | second = frequencia
        fila.push(new No(pair.first, pair.second));
    }

    while(fila.size() != 1){
        No *esq = fila.top(); fila.pop();
        No *dir = fila.top(); fila.pop();
        int soma = esq->freq + dir->freq;
        fila.push(new No('\0', soma, esq, dir));
    }

    return fila.top();

}

void encodeHuffmanTreeAux(ArvoreH raiz, string str, TabelaHuffman &tabelaCodigos){

    if(raiz == nullptr) return;

    if(!raiz->esq && !raiz->dir){ // folha
        cout << raiz->ch << endl;
        //cout << str << endl;
        tabelaCodigos[raiz->ch] = str; //adiciona o código na tabela;
    }

    encodeHuffmanTreeAux(raiz->esq, str + "0", tabelaCodigos);
    encodeHuffmanTreeAux(raiz->dir, str + "1", tabelaCodigos);

}

TabelaHuffman encodeHuffmanTree(ArvoreH raiz){

    unordered_map<char, string> tabelaCodigos;
    string str = "";
    encodeHuffmanTreeAux(raiz, str, tabelaCodigos);

    return tabelaCodigos;

}

string encodeArquivo(string conteudoArq, TabelaHuffman tabelaCodigos){

    string encodedText = "";

    for(char ch : conteudoArq){
        encodedText += tabelaCodigos[ch];
    }

    return encodedText;

}