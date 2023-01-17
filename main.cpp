#include "arquivo.h"
#include "estruturas.h"

using namespace std;

int main() {

  setlocale(LC_ALL, "utf-8");

  Arquivo *arq = new Arquivo("salve.txt");
  arq->lerArquivo();

  ArvoreH raiz = construirArvoreHuffman(arq->conteudoArq);
  auto tabelaCodigos = gerarTabelaCodigos(raiz);

  string stringBinaria = gerarBitString(arq->conteudoArq, tabelaCodigos);
  
  //cout << decodeArquivo(stringBinaria, tabelaCodigos)[0];

  //Arquivo::escreverArquivoBinario(stringBinaria, tabelaCodigos, "out.bin");
  Arquivo::lerArquivoBinario();

  //cout << sizeof(CabecalhoHuffman);
  
}