#include "menu.h"
#include "arquivo.h"

// Construtor padrão do menu
// Pré-condição: Nenhuma
// Pós-condição: Um objeto do tipo Menu com as opções padrão é criado e inicializado.
Menu::Menu(){
    this->opcoes = {
        "Codificar arquivo - codificacao por caractere",
        "Decodificar arquivo - codificacao por caractere",
        "Codificar arquivo - codificacao por palavra",
        "Decodificar arquivo - codificacao por palavra"
    };
}

// Adiciona uma nova opção ao menu.
// Pré-condição: opcao é uma string válida.
// Pós-condição: A string opcao é adicionada ao vetor de opções do menu
void Menu::novaOpcao(string opcao) {
    this->opcoes.push_back(opcao);
}

 // Mostra as opções do menu.
// Pré-condição: O menu deve estar inicializado
// Pós-condição: As opções do menu são exibidas na tela.
void Menu::mostrarOpcoes() {
    cout << "\nSelecione uma das opcoes abaixo\n\n";
    for (int i = 0; i < this->opcoes.size(); i++) {
        cout << i + 1 << " - " << this->opcoes[i] << endl;
    }
    cout << "0 - Sair" << '\n';
}

// Mostra as opções do menu.
// Pré-condição: O menu deve estar inicializado
// Pós-condição: As opções do menu são exibidas na tela, 
// e a opção do usuário é pedida
void Menu::mostrar() {
    int opcao = -1;
    while(opcao != 0){
        this->mostrarOpcoes();
        cin >> opcao;

        switch(opcao){
            case 1:
                this->codificarArquivoCaractere();
                break;
            case 2:
                this->decodificarArquivoCaractere();
                break;
            case 3:
                this->codificarArquivoPalavra();
                break;
            case 4:
                this->decodificarArquivoPalavra();
                break;
            default:
                break;
        }
    }
}

void Menu::startCronometro(){
    this->start = std::chrono::high_resolution_clock::now();
}

void Menu::stopCronometro(){
    this->end = std::chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::microseconds>(end - this->start);
    cout << "Tempo de execucao: " << duration.count() / (1000000.0) << " segundos" << '\n';
}

// Encaminha a codificação por caractere
// Pré-condição: O menu deve estar inicializado
// Pós-condição: arquivo codificado é salvo
void Menu::codificarArquivoCaractere(){
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
	Arquivo::escreverArquivoBinarioCaractere(stringBinaria, tabelaCodigos, outFile);

	cout << "\nArquivo codificado com sucesso!\n";
    auto end = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::microseconds>(end - start);
    cout << "Tempo de execucao: " << duration.count() / (1000000.0) << " segundos" << '\n';
}

// Encaminha a decodificação por caractere
// Pré-condição: O menu deve estar inicializado
// Pós-condição: arquivo decodificado é salvo
void Menu::decodificarArquivoCaractere(){
	string nomeArq, outFile;
	cout << "Digite o nome do arquivo a ser decodificado: ";
	cin >> nomeArq;
	
	cout << "Decodificando...\n";
    auto start = std::chrono::high_resolution_clock::now();

	ArqHuffmanChar *arquivoLido = Arquivo::lerArquivoCodificadoCaractere(nomeArq);
	auto arquivoDecodificado = decodeArquivoCaractere(arquivoLido);
	Arquivo::escreverArquivoDecodificado(arquivoDecodificado, nomeArq + ".decoded");

	cout << "\nArquivo decodificado com sucesso!\n";

    auto end = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::microseconds>(end - start);
    cout << "Tempo de execucao: " << duration.count() / (1000000.0) << " segundos" << '\n';
}

// Encaminha a codificação por palavra
// Pré-condição: O menu deve estar inicializado
// Pós-condição: arquivo ccodificado é salvo
void Menu::codificarArquivoPalavra(){
    string nomeArq = "salve.txt", outFile;
	cout << "Digite o nome do arquivo a ser codificado: ";
	cin >> nomeArq;
	outFile = nomeArq + ".huf";

	cout << "Codificando...\n";
    this->startCronometro();
	Arquivo *arq = new Arquivo(nomeArq);
	arq->lerArquivo();

    ArvoreHPalavra raiz = construirArvoreHuffmanPalavra(arq->conteudoArq);
    auto tabelaCodigos = gerarTabelaCodigosPalavra(raiz);

    string stringBinaria = gerarBitStringPalavra(arq->conteudoArq, tabelaCodigos);
	Arquivo::escreverArquivoBinarioPalavra(stringBinaria, tabelaCodigos, outFile);

    cout << "\nArquivo codificado com sucesso!\n";
    this->stopCronometro();
}

// Encaminha a decodificação por palavra
// Pré-condição: O menu deve estar inicializado
// Pós-condição: arquivo decodificado é salvo
void Menu::decodificarArquivoPalavra(){
	string nomeArq = "salve.txt.huf", outFile;
	cout << "Digite o nome do arquivo a ser decodificado: ";
	cin >> nomeArq;
	
	cout << "Decodificando...\n";
    this->startCronometro();

	ArqHuffmanPalavra *arquivoLido = Arquivo::lerArquivoCodificadoPalavra(nomeArq);
	auto arquivoDecodificado = decodeArquivoPalavra(arquivoLido);
	Arquivo::escreverArquivoDecodificado(arquivoDecodificado, nomeArq + ".decoded");

	cout << "\nArquivo decodificado com sucesso!\n";
    this->stopCronometro();
}