#include "estruturas.h"

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

string decodeBitString(string bitString, TabelaHuffmanChar tabelaCodigos){

    string buffer = "", resultado = "";
    for(char bit : bitString){
        buffer += bit;

        for(auto pair : tabelaCodigos){ // O(n de caracteres diferentes no texto)
            if(pair.second == buffer){
                cout << pair.first;
                resultado += pair.first;
                buffer = "";
            }
        }
    }

    return resultado;
}

string decodeArquivoCaractere(ArqHuffmanChar *arq){

    /* string buffer;

    for(int i = 0; i < arq->nBytes; i++){
        cout << i << endl;
    } */

}