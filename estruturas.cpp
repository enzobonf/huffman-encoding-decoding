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
};

struct Compare {
    bool operator()(No *esq, No *dir){
        return esq->freq > dir->freq;
    }
};

void construirArvoreHuffman(string text){
    unordered_map<char, int> freq;
    for(char ch : text){
        freq[ch]++;
    }

    cout << freq['a'] << endl;
}