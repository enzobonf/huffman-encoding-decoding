#include <vector>
#include <iostream>
#include <string>
using namespace std;

class Menu {
    private:
        vector<string> opcoes;
    public:
        void novaOpcao(string opcao){
            opcoes.push_back(opcao);
        }

        int mostrar(){
            cout << "Selecione uma das opcoes abaixo\n\n";
            for(int i = 0; i < opcoes.size(); i++){
                cout << i + 1 << " - " <<  opcoes[i] << endl;
            }
            cout << "0 - Sair" << endl;
            int opcao;
            cin >> opcao;
        }

};