#include "arquivo.cpp"
#include "estruturas.cpp"
#include <cstdlib>

using namespace std;

int main() {

  setlocale(LC_ALL, "utf-8");

  Arquivo *arq = new Arquivo("salve.txt");
  arq->lerArquivo();

  construirArvoreHuffman(arq->conteudoArq);
  
}