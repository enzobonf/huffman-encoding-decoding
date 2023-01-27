#include "menu.h"
#include "arquivo.h"

// Pré-condição: Nenhuma
// Pós-condição: As opções do menu são inicializadas
Menu::Menu(){
    this->opcoes = {
        "Codificar arquivo - codificacao por caractere",
        "Decodificar arquivo - codificacao por caractere",
        "Codificar arquivo - codificacao por palavra",
        "Decodificar arquivo - codificacao por palavra"
    };
}

void Menu::novaOpcao(string opcao) {
    this->opcoes.push_back(opcao);
}

void Menu::mostrarOpcoes() {
    cout << "\nSelecione uma das opcoes abaixo\n\n";
    for (int i = 0; i < this->opcoes.size(); i++) {
        cout << i + 1 << " - " << this->opcoes[i] << endl;
    }
    cout << "0 - Sair" << '\n';
}

void Menu::mostrar() {
    int opcao = -1;
    while(opcao != 0){
        this->mostrarOpcoes();
        cin >> opcao;

        switch(opcao){
            case 1:
                codificarArquivoCaractere();
                break;
            case 2:
                decodificarArquivoCaractere();
                break;
            case 3:
                codificarArquivoPalavra();
                break;
            case 4:
                decodificarArquivoPalavra();
                break;
            default:
                break;
        }
    }
}

void codificarArquivoCaractere(){
	string nomeArq, outFile;
	cout << "Digite o nome do arquivo a ser codificado: ";
	cin >> nomeArq;
	outFile = nomeArq + ".huf";

	cout << "Codificando...\n";
    auto start = std::chrono::high_resolution_clock::now();
	Arquivo *arq = new Arquivo(nomeArq);
	arq->lerArquivo();

	ArvoreHChar raiz = construirArvoreHuffmanChar(arq->conteudoArq);
	auto tabelaCodigos = gerarTabelaCodigosChar(raiz);

	string stringBinaria = gerarBitStringCaractere(arq->conteudoArq, tabelaCodigos);
	Arquivo::escreverArquivoBinario(stringBinaria, tabelaCodigos, outFile);

	cout << "\nArquivo codificado com sucesso!\n";
    auto end = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::microseconds>(end - start);
    cout << "Tempo de execucao: " << duration.count() / (1000000.0) << " segundos" << '\n';
}

void decodificarArquivoCaractere(){

	string nomeArq, outFile;
	cout << "Digite o nome do arquivo a ser decodificado: ";
	cin >> nomeArq;
	
	cout << "Decodificando...\n";
    auto start = std::chrono::high_resolution_clock::now();

	ArqHuffmanChar *arquivoLido = Arquivo::lerArquivoCodificadoCaractere(nomeArq);

    //cout << arquivoLido->vetorBytes[58929461][1] << '\n';

	auto arquivoDecodificado = decodeArquivoCaractere(arquivoLido);
	Arquivo::escreverArquivoDecodificado(arquivoDecodificado, nomeArq + ".decoded");

	cout << "\nArquivo decodificado com sucesso!\n";

    auto end = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::microseconds>(end - start);
    cout << "Tempo de execucao: " << duration.count() / (1000000.0) << " segundos" << '\n';
}

void codificarArquivoPalavra(){
    
    string nomeArq, outFile;
	cout << "Digite o nome do arquivo a ser codificado: ";
	cin >> nomeArq;
	outFile = nomeArq + ".huf";

	cout << "Codificando...\n";
    auto start = std::chrono::high_resolution_clock::now();
	Arquivo *arq = new Arquivo(nomeArq);
	arq->lerArquivo();

    ArvoreHPalavra raiz = construirArvoreHuffmanPalavra(arq->conteudoArq);
    auto tabelaCodigos = gerarTabelaCodigosPalavra(raiz);

    string stringBinaria = gerarBitStringPalavra(arq->conteudoArq, tabelaCodigos);
    cout << stringBinaria.length() / 8 << endl;
	Arquivo::escreverArquivoBinario(stringBinaria, tabelaCodigos, outFile);

}

void decodificarArquivoPalavra(){

	string nomeArq, outFile;
	cout << "Digite o nome do arquivo a ser decodificado: ";
	cin >> nomeArq;
	
	cout << "Decodificando...\n";
    auto start = std::chrono::high_resolution_clock::now();

	ArqHuffmanPalavra *arquivoLido = Arquivo::lerArquivoCodificadoPalavra(nomeArq);

    //cout << arquivoLido->vetorBytes[58929461][1] << '\n';

	auto arquivoDecodificado = decodeArquivoPalavra(arquivoLido);
	Arquivo::escreverArquivoDecodificado(arquivoDecodificado, nomeArq + ".decoded");

	cout << "\nArquivo decodificado com sucesso!\n";

    auto end = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::microseconds>(end - start);
    cout << "Tempo de execucao: " << duration.count() / (1000000.0) << " segundos" << '\n';
}