#include "arquivo.h"
#include "estruturas.h"

using namespace std;

int main() {

  setlocale(LC_ALL, "utf-8");

  Arquivo *arq = new Arquivo("p.txt");
  string filename = "out.bin";
  arq->lerArquivo();

  ArvoreHChar raiz = construirArvoreHuffmanChar(arq->conteudoArq);
  auto tabelaCodigos = gerarTabelaCodigosChar(raiz);

  string stringBinaria = gerarBitString(arq->conteudoArq, tabelaCodigos);
  //cout << stringBinaria << endl;
  Arquivo::escreverArquivoBinario(stringBinaria, tabelaCodigos, filename);


 	ArqHuffmanChar *arquivoLido = Arquivo::lerArquivoCodificadoCaractere(filename);
  
  /* for(auto pair : arquivoLido->tabelaCodigos){ // O(n de caracteres diferentes no texto)
      cout << "key: " << pair.first << " | value: " << pair.second << endl;
  } */

	cout << "-------------------" << endl;

}