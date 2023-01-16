#include "arquivo.cpp"
#include "estruturas.cpp"
#include <cstdlib>

using namespace std;

int main() {

  setlocale(LC_ALL, "utf-8");

  Arquivo *arq = new Arquivo("salve.txt");
  arq->lerArquivo();

  ArvoreH raiz = construirArvoreHuffman(arq->conteudoArq);
  auto tabelaCodigos = encodeHuffmanTree(raiz);

  string arquivoEncoded = encodeArquivo(arq->conteudoArq, tabelaCodigos);
  cout << arquivoEncoded.length();

  Arquivo::escreverArquivoBinario(arquivoEncoded, "out.bin");
  
}