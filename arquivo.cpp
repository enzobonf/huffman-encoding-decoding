#include <iostream>
#include <fstream>
#include "arquivo.h"

using namespace std;

Arquivo::Arquivo(string nomeArq){
    this->nomeArq = nomeArq;
}

void Arquivo::lerArquivo(){
    ifstream fin(this->nomeArq.c_str());
    string arqCompleto; char ch;

    while(fin.get(ch)){
        arqCompleto += ch;
    }

    fin.close();
    this->conteudoArq = arqCompleto;
}

void Arquivo::escreverArquivoBinario(string stringBinaria, string filename){
    ofstream outFile(filename.c_str(), ios::binary);
    outFile.write(stringBinaria.c_str(), stringBinaria.size());
    outFile.close();
}