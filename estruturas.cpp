#include "estruturas.h"

ArvoreHChar construirArvoreHuffmanChar(string text){
    unordered_map<char, int> freq;
    for(char ch : text){ // O(tamanho do texto em caracteres)
        freq[ch]++;
    }

    priority_queue<No*, vector<No*>, Compare<No*>> fila;

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

ArvoreHPalavra construirArvoreHuffmanPalavra(string text){
    unordered_map<string, int> freq;
    string str, delimiters = ".,;:!/?\"=<>()#@-*\n";

    string palavra; size_t len = text.size();
    for(size_t i = 0; i < len; i++){
        if(text[i] == ' ' || delimiters.find_first_of(text[i]) != string::npos){
            string del = text.substr(i, 1); // delimitador convertido para string
            if(palavra.length() > 0) 
                freq[palavra]++;
            freq[del]++;
            palavra = "";
        }
        else {
            palavra += text[i];
            if(i == len - 1){
                freq[palavra]++;
            }
        }
    }

    priority_queue<NoPalavra*, vector<NoPalavra*>, Compare<NoPalavra*>> fila;

    for(auto pair : freq){ // O(n de caracteres diferentes no texto)
        // first = caractere | second = frequencia
        //cout << "word: " << pair.first << " | freq: " << pair.second << '\n';
        fila.push(new NoPalavra(pair.first, pair.second));
    }

    while(fila.size() != 1){
        NoPalavra *esq = fila.top(); fila.pop();
        NoPalavra *dir = fila.top(); fila.pop();
        int soma = esq->freq + dir->freq;
        fila.push(new NoPalavra("\0", soma, esq, dir));
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

void gerarTabelaCodigosPalavraAux(ArvoreHPalavra raiz, string str, TabelaHuffmanPalavra &tabelaCodigos){

    if(raiz == nullptr) return;

    if(!raiz->esq && !raiz->dir){ // folha
        tabelaCodigos[raiz->palavra] = str; //adiciona o código na tabela;
        //cout << "word: " << raiz->palavra << " | cod: " << str << '\n';
    }

    gerarTabelaCodigosPalavraAux(raiz->esq, str + "0", tabelaCodigos);
    gerarTabelaCodigosPalavraAux(raiz->dir, str + "1", tabelaCodigos);

}

TabelaHuffmanPalavra gerarTabelaCodigosPalavra(ArvoreHPalavra raiz){

    unordered_map<string, string> tabelaCodigos;
    string str = "";
    gerarTabelaCodigosPalavraAux(raiz, str, tabelaCodigos);

    return tabelaCodigos;

}

string gerarBitStringCaractere(string conteudoArq, TabelaHuffmanChar tabelaCodigos){
    string encodedText = "";

    for(char ch : conteudoArq){
        if(ch) encodedText += tabelaCodigos[ch];
    }

    return encodedText;
}

string gerarBitStringPalavra(string conteudoArq, TabelaHuffmanPalavra tabelaCodigos){
    string encodedText = "", str = "", delimiters = ".,;:!/?\"=<>()#@-*\n";

    string palavra; size_t len = conteudoArq.size();
    for(size_t i = 0; i < len; i++){
        if(conteudoArq[i] == ' ' || delimiters.find_first_of(conteudoArq[i]) != string::npos){
            string del = conteudoArq.substr(i, 1); // delimitador convertido para string
            if(palavra.length() > 0) {
                encodedText += tabelaCodigos[palavra];
            }
            encodedText += tabelaCodigos[del];
            palavra = "";
        }
        else {
            palavra += conteudoArq[i];
            if(i == len - 1) {
                encodedText += tabelaCodigos[palavra];
            }
        }
    }

    return encodedText;
}


void gerarBitset(string bitString, vector<bitset<8>> &bit_set, short &nFillBits){
    string byteStr = "";
    size_t sizeStr = bitString.size();
    //nFillBits = sizeStr % 8;
    nFillBits = (8 - (sizeStr % 8)) % 8;
    
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
    string buffer = "", resultado = ""; char buscaTabela;
    auto tabelaInvertida = inverterTabela(tabelaCodigos);
    for(char bit : bitString){
        buffer += bit;

        buscaTabela = tabelaInvertida[buffer];
        if(buscaTabela){
            resultado += buscaTabela;
            buffer = "";
        }
    }

    return resultado;
}

string decodeBitString(string bitString, TabelaHuffmanPalavra tabelaCodigos){
    string buffer = "", resultado = "", buscaTabela;
    auto start = std::chrono::high_resolution_clock::now();
    auto tabelaInvertida = inverterTabela(tabelaCodigos);
    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<chrono::microseconds>(end - start);
    cout << "Tempo de inverter tabela: " << duration.count() / (1000000.0) << " segundos" << '\n';

    for(char bit : bitString){
        buffer += bit;
        if(tabelaInvertida[buffer].length() > 0){
            resultado += tabelaInvertida[buffer];
            buffer = "";
        }
    }

    return resultado;
}

string decodeArquivoCaractere(ArqHuffmanChar *arq){
    string buffer; auto vetorBytes = arq->vetorBytes;
    vetorBytes[arq->nBytes -1] <<= arq->nFillBits;
    // shift-left nos bits de preenchimento
    
    for(int i = 0; i < arq->nBytes; i++){
        buffer += vetorBytes[i].to_string();
    }

    if(arq->nFillBits){
        buffer.erase(buffer.length() - arq->nFillBits, arq->nFillBits);
    } // caso tivessem bits de preenchimento, retira os do fim do buffer após o shift-left
         
    return decodeBitString(buffer, arq->tabelaCodigos);
}

string decodeArquivoPalavra(ArqHuffmanPalavra *arq){
    string buffer; auto vetorBytes = arq->vetorBytes;
    vetorBytes[arq->nBytes -1] <<= arq->nFillBits;
    // shift-left nos bits de preenchimento

    for(int i = 0; i < arq->nBytes; i++){
        buffer += vetorBytes[i].to_string();
    }

    if(arq->nFillBits){
        buffer.erase(buffer.length() - arq->nFillBits, arq->nFillBits);
    } // caso tivessem bits de preenchimento, retira os do fim do buffer após o shift-left
         
    return decodeBitString(buffer, arq->tabelaCodigos);
}