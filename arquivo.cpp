#include <iostream>
#include <fstream>
#include <cmath>
#include <vector>
#include <bitset>
#include <cstdio>
#include <string.h>

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
    string byteStr = "";
    size_t sizeStr = str.length();
    
    for(int i = 0; i < str.size(); i += 8){
        bit_set.push_back(bitset<8>(str.substr(i, 8)));
    }
}

void Arquivo::escreverArquivoBinario(string stringBinaria, TabelaHuffman tabela, string filename){
    vector<bitset<8>> vetorBits;

    gerarBitset(stringBinaria, vetorBits);
    cout << vetorBits.size();

    unsigned int map_size = tabela.size();
    CabecalhoHuffman cab = {vetorBits.size(), map_size};

    FILE *file = fopen("out.bin", "wb");
    fwrite(&cab, sizeof(CabecalhoHuffman), 1, file);

    for (auto pair : tabela) {
        fwrite(&pair.first, sizeof(char), 1, file);
        size_t value_size = pair.second.size();
        fwrite(&value_size, sizeof(size_t), 1, file);
        fwrite(pair.second.c_str(), value_size, 1, file);
    }

    for(auto& bits : vetorBits){
        fwrite((const char*)&bits, 1, 1, file);
    }

    fclose(file);
}

ArquivoHuffman Arquivo::lerArquivoBinario(){
    //ifstream fin("out.bin", ios::binary);
    FILE *file = fopen("out.bin", "rb+");

    int i = 0;

    CabecalhoHuffman *cab = (CabecalhoHuffman*) malloc(sizeof(CabecalhoHuffman));
    size_t map_size;

    fseek(file, 0, SEEK_SET);
    fread(cab, sizeof(CabecalhoHuffman), 1, file);

    cout << "n bytes: " << cab->nBytes << " | size: " << cab->tamTabela << endl;

    TabelaHuffman tabela; vector<bitset<8>> vetorBits;
    vetorBits.resize(cab->nBytes);

    for(int i = 0; i < cab->tamTabela; i++){
        char key; size_t value_size; string value;

        fread(&key, sizeof(char), 1, file);
        fread(&value_size, sizeof(size_t), 1, file);

        value.resize(value_size);
        fread((char*)(value.data()), value_size, 1, file);
        tabela[key] = value;
    }

    for(int i = 0; i < cab->nBytes; i++){
        fread(&vetorBits[i], 1, 1, file);
    }

    fclose(file);

    return {cab->nBytes, tabela, vetorBits};
    
}