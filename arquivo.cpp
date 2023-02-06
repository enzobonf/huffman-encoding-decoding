#include "arquivo.h"
#include "estruturas.h"

using namespace std;

// Construtor da classe arquivo, inicializa o nome do arquivo
// Pré-condição: deve ser passado um nome de arquivo válido
// Pós-condição: o nome do arquivo é colocado no objeto Arquivo.
Arquivo::Arquivo(string nomeArq){
    this->nomeArq = nomeArq;
}

// Lê todo o conteúdo do arquivo
// Pré-condição: o arquivo deve estar inicializado
// Pós-condição: o conteúdo é colocado na variável conteudoArq no objeto
void Arquivo::lerArquivo(){
    ifstream fin(this->nomeArq.c_str());
    string arqCompleto;

    stringstream buffer;
    buffer << fin.rdbuf();

    fin.close();
    buffer.clear();
    this->conteudoArq = buffer.str();
}

// Escreve uma string binária e o cabeçalho de codificação por caractere num arquivo binário
// Pré-condição: a string binária, a tabela de códigos e o nome do arquivo devem ser válidos
// Pós-condição: o arquivo binário é escrito
void Arquivo::escreverArquivoBinarioCaractere(string stringBinaria, TabelaHuffmanChar tabela, string filename){
    vector<bitset<8>> vetorBytes; short nFillBits; 
    gerarBitset(stringBinaria, vetorBytes, nFillBits);

    size_t map_size = tabela.size(), value_size;
    CabecalhoHuffman cab = {vetorBytes.size(), map_size, nFillBits};

    FILE *file = fopen(filename.c_str(), "wb");
    fwrite(&cab, sizeof(CabecalhoHuffman), 1, file);

    for (auto pair : tabela) {
        fwrite(&pair.first, sizeof(char), 1, file);
        value_size = pair.second.length();
        fwrite(&value_size, sizeof(size_t), 1, file);
        fwrite(pair.second.c_str(), value_size, 1, file);
    }

    for(auto& bits : vetorBytes){
        fwrite((const char*)&bits, 1, 1, file);
    }

    fclose(file);
}

// Escreve uma string binária e o cabeçalho de codificação por palavra num arquivo binário
// Pré-condição: a string binária, a tabela de códigos e o nome do arquivo devem ser válidos
// Pós-condição: o arquivo binário é escrito
void Arquivo::escreverArquivoBinarioPalavra(string stringBinaria, TabelaHuffmanPalavra tabela, string filename){
    vector<bitset<8>> vetorBytes; short nFillBits; 
    gerarBitset(stringBinaria, vetorBytes, nFillBits);

    size_t map_size = tabela.size(), key_size, value_size;
    CabecalhoHuffman cab = {vetorBytes.size(), map_size, nFillBits};

    FILE *file = fopen(filename.c_str(), "wb");
    fwrite(&cab, sizeof(CabecalhoHuffman), 1, file);

    cout << "aqui";

    for (auto pair : tabela) {
        key_size = pair.first.length();
        value_size = pair.second.length();

        fwrite(&key_size, sizeof(size_t), 1, file);
        fwrite(pair.first.c_str(), key_size, 1, file);
        fwrite(&value_size, sizeof(size_t), 1, file);
        fwrite(pair.second.c_str(), value_size, 1, file);
    }

    for(auto& bits : vetorBytes){
        fwrite((const char*)&bits, 1, 1, file);
    }

    fclose(file);
}

// Escreve uma string comum (arquivo decodificado) no arquivo
// Pré-condição: string e nome de arquivo válido
// Pós-condição: o conteúdo decodificado é escrito no arquivo
void Arquivo::escreverArquivoDecodificado(string str, string filename){
    ofstream fout(filename.c_str());
    fout.write(str.c_str(), str.size());
    fout.close();
}

// Lê um arquivo binário feito via codificação por caractere
// Pré-condição: o arquivo é um arquivo codificado por caractere válido
// Pós-condição: o objeto do arquivo é retornado com as informações para a decodificação
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

// Lê um arquivo binário feito via codificação por palavra
// Pré-condição: o arquivo é um arquivo codificado por palavra válido
// Pós-condição: o objeto do arquivo é retornado com as informações para a decodificação
ArqHuffmanPalavra* Arquivo::lerArquivoCodificadoPalavra(string filename){

    FILE *file = fopen(filename.c_str(), "rb+");

    CabecalhoHuffman *cab = (CabecalhoHuffman*) malloc(sizeof(CabecalhoHuffman));
    TabelaHuffmanPalavra tabela; 
    vector<bitset<8>> vetorBytes;
    string key, value; size_t key_size, value_size;

    fseek(file, 0, SEEK_SET);
    fread(cab, sizeof(CabecalhoHuffman), 1, file);
    vetorBytes.resize(cab->nBytes);

    cout << "n bytes: " << cab->nBytes << " | tam tabela: " << cab->tamTabela << " | n fill: " << cab->nFillBits << '\n';

    for(int i = 0; i < cab->tamTabela; i++){
        key.resize(MAX_WORD_LENGTH);
        fread(&key_size, sizeof(size_t), 1, file);
        fread((char*)(key.data()), key_size, 1, file);
        key.resize(key_size);

        fread(&value_size, sizeof(size_t), 1, file);
        tabela[key].resize(value_size);
        fread((char*)(tabela[key].data()), value_size, 1, file);
    }

    for(int i = 0; i < cab->nBytes; i++){
        fread(&vetorBytes[i], 1, 1, file);
    }

    fclose(file);

    return new ArqHuffmanPalavra(cab->nBytes, cab->nFillBits, tabela, vetorBytes);
    
}