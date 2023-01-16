#include <iostream>
#include <fstream>
#include "arquivo.h"

using namespace std;

Arquivo::Arquivo(string nomeArq){
    this->nomeArq = nomeArq;
}

void Arquivo::lerArquivo(){
    ifstream fin(this->nomeArq.c_str());
    string arqCompleto;
    char ch;

    while(fin.get(ch)){
        arqCompleto += ch;
    }

    cout << arqCompleto << endl;
    this->conteudoArq = arqCompleto;
}