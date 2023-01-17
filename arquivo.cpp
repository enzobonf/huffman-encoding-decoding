#include <iostream>
#include <fstream>
#include <cmath>
#include <vector>
#include <bitset>

#include "arquivo.h"
#include "estruturas.h"

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

void gerarBitset(string str, vector<bitset<8>> &bit_set){
    
    //cout << "str: " << str << endl;
    string byteStr = "";
    size_t sizeStr = str.length();

    int completarZeros = sizeStr < 8 ? 8 - str.length() : 0;

    for(int i = 0; i < completarZeros; i++){
        str += '0';
    }

    for(int i = 0; i < 8 && str[i] != '\0'; i++){
        byteStr += str[i];
    }

    //cout << byteStr << endl;
    bit_set.push_back(bitset<8>(byteStr));

    if(sizeStr > 8){
        gerarBitset(&str[8], bit_set);
    }

}

void Arquivo::escreverArquivoBinario(string stringBinaria, TabelaHuffman tabela, string filename){
    string bit_string = "10101010";
    vector<bitset<8>> vetorBits;

    gerarBitset(stringBinaria, vetorBits);
    ofstream file(filename.c_str(), ios::binary);

    CabecalhoHuffman *cab = new CabecalhoHuffman(vetorBits.size(), tabela);

    file.write((const char*)cab, sizeof(cab));
    
    for(auto& bits : vetorBits){
        file.write((const char*)&bits, 1);
    }

    file.close();
}

void Arquivo::lerArquivoBinario(){
    ifstream fin("out.bin", ios::binary);
    bitset<8> bytee;

    int i = 0;

    CabecalhoHuffman *cb;

    fin.read((char*)&cb, sizeof(cb));

    cout << "n bytes: " << cb->nBytes << endl;
    cout << cb->tabela['L'];

    /* while(!fin.eof()){
        i++;
        fin.read((char*)&bytee, 1);
        cout << bytee.all();
    } */

    //cout << i;
    
}