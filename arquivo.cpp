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

void Arquivo::escreverArquivoBinario(string stringBinaria, TabelaHuffmanChar tabela, string filename){
    vector<bitset<8>> vetorBytes;
    gerarBitset(stringBinaria, vetorBytes);

    unsigned int map_size = tabela.size();
    CabecalhoHuffman cab = {vetorBytes.size(), map_size};

    FILE *file = fopen(filename.c_str(), "wb");
    fwrite(&cab, sizeof(CabecalhoHuffman), 1, file);

    for (auto pair : tabela) {
        fwrite(&pair.first, sizeof(char), 1, file);
        size_t value_size = pair.second.length();
        fwrite(&value_size, sizeof(size_t), 1, file);
        //cout << "key: " << pair.first << " | value: " << pair.second.c_str() << " | value size: " << value_size << endl;
        fwrite(pair.second.c_str(), value_size, 1, file);
    }

    /* int bytes = 0;

    for(int i = 0; i < stringBinaria.size(); i += 8, bytes++){
        string byte = stringBinaria.substr(i, 8);
        fwrite((const char*)(byte.c_str()), 1, 1, file);
    }

    cout << bytes; */

    for(auto& bits : vetorBytes){
        fwrite((const char*)&bits, 1, 1, file);
    }

    fclose(file);
}

ArqHuffmanChar* Arquivo::lerArquivoCodificadoCaractere(string filename){

    FILE *file = fopen(filename.c_str(), "rb+");

    CabecalhoHuffman *cab = (CabecalhoHuffman*) malloc(sizeof(CabecalhoHuffman));
    TabelaHuffmanChar tabela; 
    vector<bitset<8>> vetorBytes;
    char key; size_t value_size; string value;

    fseek(file, 0, SEEK_SET);
    fread(cab, sizeof(CabecalhoHuffman), 1, file);
    vetorBytes.resize(cab->nBytes);

    cout << "n bytes: " << cab->nBytes << " | tam tabela: " << cab->tamTabela << endl;

    for(int i = 0; i < cab->tamTabela; i++){
        fread(&key, sizeof(char), 1, file);
        fread(&value_size, sizeof(size_t), 1, file);

        tabela[key].resize(value_size);
        fread((char*)(tabela[key].data()), value_size, 1, file);
    }

    for(auto pair : tabela){ // O(n de caracteres diferentes no texto)
      cout << "key: " << pair.first << " | value: " << pair.second << endl;
    }

    string buffer;

    for(int i = 0; i < cab->nBytes; i++){
        fread(&vetorBytes[i], 1, 1, file);
        buffer += vetorBytes[i].to_string();
    }

    decodeBitString(buffer, tabela);

    //cout << buffer << endl;

    fclose(file);

    return new ArqHuffmanChar(cab->nBytes, tabela, vetorBytes);
    
}