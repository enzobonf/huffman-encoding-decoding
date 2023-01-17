#include "estruturas.h"

ArvoreH construirArvoreHuffman(string text){
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

void gerarTabelaCodigosAux(ArvoreH raiz, string str, TabelaHuffman &tabelaCodigos){

    if(raiz == nullptr) return;

    if(!raiz->esq && !raiz->dir){ // folha
        //cout << raiz->ch << endl;
        //cout << str << endl;
        tabelaCodigos[raiz->ch] = str; //adiciona o código na tabela;
    }

    gerarTabelaCodigosAux(raiz->esq, str + "0", tabelaCodigos);
    gerarTabelaCodigosAux(raiz->dir, str + "1", tabelaCodigos);

}

TabelaHuffman gerarTabelaCodigos(ArvoreH raiz){

    unordered_map<char, string> tabelaCodigos;
    string str = "";
    gerarTabelaCodigosAux(raiz, str, tabelaCodigos);

    return tabelaCodigos;

}

string gerarBitString(string conteudoArq, TabelaHuffman tabelaCodigos){
    string encodedText = "";

    for(char ch : conteudoArq){
        if(ch) encodedText += tabelaCodigos[ch];
    }

    return encodedText;
}

string decodeArquivo(string bitString, TabelaHuffman tabelaCodigos){

    string buffer = "", resultado = "";
    for(char bit : bitString){
        buffer += bit;

        for(auto pair : tabelaCodigos){ // O(n de caracteres diferentes no texto)
            if(pair.second == buffer){
                resultado += pair.first;
                buffer = "";
            }
        }
    }

    return resultado;
}