#include "arquivo.h"
#include "estruturas.h"
#include <chrono>

using namespace std;

int main() {

  setlocale(LC_ALL, "utf-16");

  Arquivo *arq = new Arquivo("arquivo.cpp");
  string filename = "out.bin";
  arq->lerArquivo();

  //auto start = std::chrono::high_resolution_clock::now();

  ArvoreHChar raiz = construirArvoreHuffmanChar(arq->conteudoArq);
  auto tabelaCodigos = gerarTabelaCodigosChar(raiz);
  string stringBinaria = gerarBitString(arq->conteudoArq, tabelaCodigos);
  Arquivo::escreverArquivoBinario(stringBinaria, tabelaCodigos, filename);


 	ArqHuffmanChar *arquivoLido = Arquivo::lerArquivoCodificadoCaractere(filename);
  auto arquivoDecodificado = decodeArquivoCaractere(arquivoLido);

  Arquivo::escreverArquivoDecodificado(arquivoDecodificado, "teste/teste.txt");

  /* auto end = std::chrono::high_resolution_clock::now();
  auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
  std::cout << "Tempo de execucao: " << duration.count() / (1000000.0) << " segundos" << std::endl; */
  
  
  /* cout << endl;
  for(auto pair : arquivoLido->tabelaCodigos){ // O(n de caracteres diferentes no texto)
      cout << "key: " << pair.first << " | value: " << pair.second << endl;
  } */

}