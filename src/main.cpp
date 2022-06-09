#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include "../include/Forca.hpp"

using namespace std;

int main(int argc, char *argv[]) {
  int opcao, dificuldade;
  bool t = true;
  char p;
  
  cout << ">  Lendo os arquivos, por favor aguarde... \n";
  cout << "-------------------------------------------------------------\n";

  Forca *forca = new Forca();

  while (t == true) {
    cout << "\nBem vindo ao Jogo Forca! Por favor, escolha uma das opções:\n";
    cout << "1 - Iniciar Jogo\n";
    cout << "2 - Ver scores anteriores\n";
    cout << "3 - Sair\n";
    cout << "Sua escolha: ";
    cin >> opcao;
    
    if (opcao == 1) {
      cout << "\nVamos iniciar o jogo! Por favor escolha o nível de dificuldade:\n";
      cout << "1 - Fácil\n";
      cout << "2 - Médio\n";
      cout << "3 - Difício\n";
      cout << "Sua escolha: ";
      cin >> dificuldade;

      if (dificuldade == 1) {
        forca->set_dificuldade(dificuldade);
        forca->inicio();
      }
      else if (dificuldade == 2) {
        forca->set_dificuldade(dificuldade);
        forca->inicio();
      }
      else if (dificuldade == 3) {
        forca->set_dificuldade(dificuldade);
        forca->inicio();
      }
      else {
        cout << "Erro na escolha das opções, tente novamente! \n";
      }
    }
    else if (opcao == 2) {
      int op;
      
      //Leitura:
      ifstream finS("data/score.txt");
      char s;
      while (finS.get(s)) { cout << s; }
      finS.close();
      cout << "\n\n";

      cout << "\nVoltar ao menu inicial?\n";
      cout << "1 - Sim \n";
      cout << "2 - Não \n";
      cout << "Sua escolha: ";
      cin >> op;

      if (op == 1) {
        continue;
      }
      else {
        cout << "Jogo finalizado.";
        t=false;
      }
    }
    else if (opcao == 3) {
      cout << "Jogo finalizado..";
      t=false;
    }
    else {
      cout << "Erro na escolha das opções, tente novamente! \n";
    }
  }
  
  return 0;
}

/**
  *@Falta: 
  *Função para retornar o erro na leitura dos arquivos.
  */