#include "estruturas.h"
#include <chrono>

ArvoreHChar construirArvoreHuffmanChar(string text){
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

void gerarTabelaCodigosCharAux(ArvoreHChar raiz, string str, TabelaHuffmanChar &tabelaCodigos){

    if(raiz == nullptr) return;

    if(!raiz->esq && !raiz->dir){ // folha
        tabelaCodigos[raiz->ch] = str; //adiciona o código na tabela;
    }

    gerarTabelaCodigosCharAux(raiz->esq, str + "0", tabelaCodigos);
    gerarTabelaCodigosCharAux(raiz->dir, str + "1", tabelaCodigos);

}

TabelaHuffmanChar gerarTabelaCodigosChar(ArvoreHChar raiz){

    unordered_map<char, string> tabelaCodigos;
    string str = "";
    gerarTabelaCodigosCharAux(raiz, str, tabelaCodigos);

    return tabelaCodigos;

}

string gerarBitString(string conteudoArq, TabelaHuffmanChar tabelaCodigos){
    string encodedText = "";

    for(char ch : conteudoArq){
        if(ch) encodedText += tabelaCodigos[ch];
    }

    return encodedText;
}


void gerarBitset(string bitString, vector<bitset<8>> &bit_set, short &nFillBits){
    string byteStr = "";
    size_t sizeStr = bitString.size();
    nFillBits = sizeStr % 8;
    bitString += string(nFillBits, '0'); // completa o último byte com zeros à direita caso seja preciso
    
    for(int i = 0; i < sizeStr; i += 8){
        bit_set.push_back(bitset<8>(bitString.substr(i, 8)));
    }
}

template <typename TKey, typename TValue>
unordered_map<TKey, TValue> inverterTabela(unordered_map<TValue, TKey> tabelaCodigos){
    unordered_map<TKey, TValue> inverted;
    for(auto pair : tabelaCodigos){ // O(n de caracteres diferentes no texto original)
        inverted.insert({pair.second, pair.first});
    }
    return inverted;
}

string decodeBitString(string bitString, TabelaHuffmanChar tabelaCodigos){
    string buffer = "", resultado = "";
    auto tabelaInvertida = inverterTabela(tabelaCodigos);
    for(char bit : bitString){
        buffer += bit;

        if(tabelaInvertida[buffer]){
            resultado += tabelaInvertida[buffer];
            buffer = "";
        }
    }

    return resultado;
}

string decodeArquivoCaractere(ArqHuffmanChar *arq){
    string buffer; auto vetorBytes = arq->vetorBytes;
    for(int i = 0; i < arq->nBytes; i++){
        buffer += vetorBytes[i].to_string();
    }

    /* if(arq->nFillBits)
         buffer.erase(buffer.length() - (arq->nFillBits-1)); */
         
    return decodeBitString(buffer, arq->tabelaCodigos);
}