#include "arquivo.h"
#include "estruturas.h"

using namespace std;

Arquivo::Arquivo(string nomeArq){
    this->nomeArq = nomeArq;
}

void Arquivo::lerArquivo(){
    ifstream fin(this->nomeArq.c_str());
    string arqCompleto;

    std::stringstream buffer;
    buffer << fin.rdbuf();
    
    fin.close();
    buffer.clear();
    this->conteudoArq = buffer.str();
}

void Arquivo::escreverArquivoBinario(string stringBinaria, TabelaHuffmanChar tabela, string filename){
    vector<bitset<8>> vetorBytes; short nFillBits; 
    gerarBitset(stringBinaria, vetorBytes, nFillBits);

    unsigned int map_size = tabela.size();
    CabecalhoHuffman cab = {vetorBytes.size(), map_size, nFillBits};

    FILE *file = fopen(filename.c_str(), "wb");
    fwrite(&cab, sizeof(CabecalhoHuffman), 1, file);

    for (auto pair : tabela) {
        fwrite(&pair.first, sizeof(char), 1, file);
        size_t value_size = pair.second.length();
        fwrite(&value_size, sizeof(size_t), 1, file);
        fwrite(pair.second.c_str(), value_size, 1, file);
    }

    for(auto& bits : vetorBytes){
        fwrite((const char*)&bits, 1, 1, file);
    }

    fclose(file);
}

void Arquivo::escreverArquivoDecodificado(string str, string filename){
    ofstream fout(filename.c_str());
    fout.write(str.c_str(), str.size());
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

    cout << "n bytes: " << cab->nBytes << " | tam tabela: " << cab->tamTabela << " | n fill: " << cab->nFillBits << '\n';

    for(int i = 0; i < cab->tamTabela; i++){
        fread(&key, sizeof(char), 1, file);
        fread(&value_size, sizeof(size_t), 1, file);

        tabela[key].resize(value_size);
        fread((char*)(tabela[key].data()), value_size, 1, file);
    }

    for(int i = 0; i < cab->nBytes; i++){
        fread(&vetorBytes[i], 1, 1, file);
    }

    fclose(file);

    return new ArqHuffmanChar(cab->nBytes, cab->nFillBits, tabela, vetorBytes);
    
}