#include <iostream>
#include "arvoreB.h"

using namespace std;

int main(int argc, char const *argv[]) {

    if (argc < 2) {
        cout << "Argumentos insuficientes! Passe o nome do arquivo que deseja trabalhar." << endl;
        return 0;
    }
    BTree t(3);
    int ordem_Btree, opcao = 1;
    
    make_Btree(argv[1], &t);

    cout << "Insira a ordem que você deseja que a árvore tenha:" << endl;
    cin >> ordem_Btree;
    cout << "\n------------------------------------------------" << endl;
    cout << "Voce abriu o arquivo " << argv[1] << endl;
    while (opcao != 0) {

        cout << "Selecione a opção desejada abaixo: " << endl;
        cout << "(1) - Mostrar arquivo de índices primário" << endl;
        cout << "(2) - Buscar registro" << endl;
        cout << "(3) - Incluir registro" << endl;
        cout << "(4) - Excluir registro" << endl;
        cout << "(0) - Sair" << endl;
        cin >> opcao;

        switch (opcao) {
            case 1:
                cout << "Você escolheu mostrar arquivo de índices" << endl;
                make_Btree(argv[1], &t);
                //createArqu(&t);
                // quando chama a createArq dps de incuir da seg fault
                system("cat BTree.txt");
                break;
            case 2: {
                string chave;
                int seeks = 0, ponteiro;

                cout << "Você escolheu buscar um registro" << endl;
                cout << "Informe a chave do registro que deseja buscar" << endl;
                cin >> chave;

                ponteiro = retornaPonteiro(t.search(chave, &seeks), chave.c_str());
                recupera_reg(argv[1], ponteiro);
                cout << "Registro recuperado com " << seeks << " seek(s)" << endl;
                
                break;
            }
            case 3:
                cout << "Você escolheu incluir um registro" << endl;
                include_reg(argv[1], &t);
                break;
            case 4:
                cout << "Você escolheu excluir um registro" << endl;
                break;
        } 
    }
    return 0;
}
