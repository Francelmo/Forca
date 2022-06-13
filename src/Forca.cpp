#include <iostream>
#include <fstream>
#include <algorithm>
#include <vector>
#include <string>
#include <cstdlib>
#include <ctime>
#include <cstring>
#include "../include/Forca.hpp"

using namespace std;

/**
  * Cria a classe Forca
  * O construtor inicializa o jogo chamando o método inicio() na função princial.
  */
Forca::Forca () {
  m_tentativas_restantes = 6;
  quantidade_palavras_certas = 0;
  pontos = 0;
  acertos = 0;
  errou = false;
}

/**
  * Método para inicializar o jogo com a leitura dos aquivos e chamando o método start().
  */
void Forca::inicio () {
  char p[50], s[50];
  bool valida;
  string palavra, score;
  pair<bool, string> verifica;
  vector<string> palavras, scores;

  //Leitura dos arquivos.
  ifstream finP ("data/palavras.txt");
  ifstream finS ("data/score.txt");

  while(finP.getline(p, 50)) {
    palavra = p;
    palavras.push_back(palavra);
  }

  while(finS.getline(s, 50)) {
    score = s;
    scores.push_back(score);
  }

  for (vector<string>::iterator it = palavras.begin(); it != palavras.end(); ++it) {
    verifica = eh_validoP(*it);
    valida = verifica.first;
    if (valida == false) {
      falha_leitura (verifica.second);
    }
    else {
      continue;
    }
  }
  for (vector<string>::iterator it = scores.begin(); it != scores.end(); ++it) {
    verifica = eh_validoS(*it);
    valida = verifica.first;
    if (valida == false) {
      falha_leitura (verifica.second);
    }
    else {
      continue;
    }
  }

  carrega_arquivos (palavras);
  start();
}

/**
  * Valida os arquivos de palavras de entrada de acordo com as especificações.
  * Ao validar os arquivos, no caso de arquivos inválidos, este método deve retornar a
  * razão correspondente de acordo com as especificações.
  * @return {T,""} se os arquivos estiverem válidos, {F,"razão"} caso contrário.
  */
pair<bool, string> Forca::eh_validoP (string p) {
  int tam;
  bool aux=true;
  pair<bool, string> verifica;

  tam = p.length();

  for (int i=0; i<tam; i++) {
    if (p[i] < 65 || p[i] > 90) {
      if(p[i] < 97 || p[i] > 122) {
        if(p[i] != '-') {
          aux = false;
          break;
        }
      }
    }
  }

  if (aux == false) {
    verifica = make_pair(false, "Palavra com caracteres diferentes de [a - z] ou [A - Z] ou hífen ‘-’.\n");
  }
  else if (p.length() < 4) {
    verifica = make_pair(false, "Palavra menor que quatro caracteres.\n");
  }
  else {
    verifica = make_pair(true, "");  
  }
  
  return verifica;
}

/**
  * Valida os arquivos de score de entrada de acordo com as especificações.
  * Ao validar os arquivos, no caso de arquivos inválidos, este método deve retornar a
  * razão correspondente de acordo com as especificações.
  * @return {T,""} se os arquivos estiverem válidos, {F,"razão"} caso contrário.
  */
pair<bool, string> Forca::eh_validoS (string s) {
  bool t=true, erro_campo=false;
  int cont=0, j=1, tam;
  char *pch, score[50];
  pair<bool, string> verifica;

  tam = s.length();

  for (int i=0; i<tam; i++) {
      score[i] = s[i]; /*!< converter string -> char */
  }

  pch = strtok (score, ";");

  //Testar se há algum campo importante vazio.
  while ((pch!=NULL) && (t==true)) {
    string teste = pch;
    
    if (j==1) {
      if (teste.compare(0, 1, " ") == 0) {
        erro_campo = true;
        t=false;
      }
    }
    else if (j==2) {
      if (teste.compare(" ") == 0) {
        erro_campo = true;
        t=false;
      }
    }
    else if (j==3) {
      t=false;
    }
    
    pch = strtok (NULL, ";");
    j++;
  }

  //Testar quantidade de ';'.
  for (int i=0; i<tam; i++) {
    if (s[i] == ';') {
      cont++;
    }
  }
  
  if (cont > 3) {
    verifica = make_pair(false, "Presença de mais de 3 “;” em alguma linha do score.\n");
  }
  else if (erro_campo == true) {
    verifica = make_pair(false, "campo 'Nível' ou 'Nome' estão vazio em alguma linha do score.\n");
  }
  else {
    verifica = make_pair(true, "");  
  }
  
  return verifica;
}

/**
  * Imprimi a mensagem de erro referente a análise dos arquivos e finaliza o programa.
  */
void Forca::falha_leitura (string mens_erro) {
    cout << mens_erro << "\n";
    exit(1);
  }

/**
  * Carrega os arquivos de palavras preenchendo a estrutura m_palavras
  */
void Forca::carrega_arquivos (vector<string> p) {
  for (vector<string>::iterator it = p.begin(); it != p.end(); ++it) {
    m_palavras.push_back(*it);
  }

  for (vector<string>::iterator it = m_palavras.begin(); it != m_palavras.end(); ++it) {
    *it = upper(*it);
  }

  quantidade_palavras = m_palavras.size();

  proxima_palavra ();
}

/**
  * Constroi o desenho da forca a medida em que se erra os palpites.
  */
void Forca::construir_forca () {
  if (m_tentativas_restantes == 5) {
    cout << " o \n";
    cout << "\n\n\n\n";
  }
  else if (m_tentativas_restantes == 4) {
    cout << " o \n";
    cout << "/  \n";
    cout << "\n\n\n\n";
  }
  else if (m_tentativas_restantes == 3) {
    cout << " o \n";
    cout << "/|  \n";
    cout << "\n\n\n\n";
  }
  else if (m_tentativas_restantes == 2) {
    cout << " o \n";
    cout << "/|\\  \n";
    cout << "\n\n\n\n";
  }
  else if (m_tentativas_restantes == 1) {
    cout << " o\n";
    cout << "/|\\ \n";
    cout << "/  \n";
    cout << "\n\n\n\n";
  }
  else if (m_tentativas_restantes == 0) {
    cout << "Vixe, Fim de Jogo!\n";
    cout << " o\n";
    cout << "/|\\ \n";
    cout << "/ \\\n";
    cout << "\n\n\n\n";
  }
}

/**
  * Modifica a dificuldade do jogo.
  * De acordo com a dificuldade configurada, o método proxima_palavra retornará palavras
  * de forma diferente.
  * Parâmetro d a dificuldade desejada
  * Método proxima_palavra
  */
void Forca::set_dificuldade (int d) {
  if (d == 1) {
    this->d = FACIL;
  }
  else if (d == 2) {
    this->d = MEDIO;
  }
  else if (d == 3) {
    this->d = DIFICIL;
  }
}
    
/**
  * Retorna a próxima palavra de acordo com a dificuldade atual.
  * Este método deve atualizar o atributo m_palavra_atual e retornar a palavra no formato
  * "_ _ _ _ ... _" dependendo do tamanho de m_palavra_atual. O método também deve sortear as
  * letras que devem aparecer dependendo do nível de dificuldade.
  * @return a próxima palavra do conjunto de palavras disponível de acordo com a dificuldade atual.
  */
string Forca::proxima_palavra () {
  int i;
  unsigned seed = time(0);
  
  srand(seed);
    
  i = rand()%m_palavras.size();
  m_palavra_atual = m_palavras[i];

  return m_palavra_atual;
}
    
/**
  * Retorna a palavra atual que está sendo jogada.
  * @return o valor do atributo m_palavra_atual.
  */
string Forca::get_palavra_atual () {
  return m_palavra_atual; 
}
    
/**Testa se uma letra pertence à palavra atual, retorna T se a letra pertence.
  * Este método testa se uma letra pertence à palavra atual e retorna True caso pertença.
  * Caso contrário, o método deve atualizar o atributo m_tentativas_restantes, decrementando
  * em 1, e retornar False.
  * @param palpite uma letra, que deve ser testada se pertence à palavra.
  * @return T se a palpite pertence à palavra, F caso contrário.
  */
bool Forca::palpite (string palpite, string &palavra) {
  int tam;
  char letra;
  bool verifica = false;

  tam = m_palavra_atual.length();

  for (int i=0; i<tam; i++) {
    if (m_palavra_atual.compare(i, 1, palpite) == 0)
    {      
      letra = palpite[0];
      palavra[i] = letra;
      verifica = true;
      acertos++;
      pontos++;
    }
  }
  
  if (verifica == true) {
    return verifica;
  }
  else {
    m_tentativas_restantes--;
    pontos--;
    return verifica;
  }
}
    
/**
  * Em caso de Game Over este método deve retornar T.
  * @return T caso o m_tentativas_restantes do jogo esteja igual a 0, F caso contrário.
  */
bool Forca::game_over () {
  if (m_tentativas_restantes == 0) {
    return true;
  }
  else {
    return false;
  }
}

/**
  * Método que executa o jogo, validando os palpites de entrada e verificando se o jogadar ganhou ou perdeu.
  */
void Forca::start () {
  int aux=0, tamP;
  string ch, palavra = m_palavra_atual;
  bool teste_palpite, teste_chute=false, teste_vitoria=false, teste_fim=false;

  tamP = m_palavra_atual.length();

  //Nível fácil.
  if (d == 1) {
    int q, tam = palavra.length()/5;

    q = max(1, tam);
    
    for (int i=0; i<tamP; i++) {
      if ((palavra[i]!=65 && palavra[i]!=69 && palavra[i]!=73 && palavra[i]!=79 && palavra[i]!=85) && (q>0)) {
        string l;
        l.insert(0, palavra, i, 1);
        string le = l;
        
        chutes.push_back(le);
        q--;
        palavra[i] =  '_';
      }
      else {
        palavra[i] =  '_';
      }
    }
    for (vector<string>::iterator it=chutes.begin(); it!=chutes.end(); ++it) {
      string le = *it;
      char l = le[0];
      
      for (int i=0; i<tamP; i++) {
        if (m_palavra_atual.compare(i, 1, le) == 0)
        {
          palavra[i] = l;
          acertos++;
        }
      }
    }
  }
  else if (d == 2) { //Nível médio.
    int j;
    vector<string> vogais;
    
    for (int i=0; i<tamP; i++) {
      if ((palavra[i]==65 || palavra[i]==69 || palavra[i]==73 || palavra[i]==79 || palavra[i]==85)) 
      {
        string v;
        v.insert(0, palavra, i, 1);
        string vo = v;
        
        vogais.push_back(vo);
        palavra[i] =  '_';
      }
      else {
        palavra[i] =  '_';
      }
    }

    unsigned seed = time(0);
  
    srand(seed);
    
    j = rand()%vogais.size(); /*!< Escolher vogal de forma aleatória. */
    
    for (int i=0; i<tamP; i++) {
      if (m_palavra_atual.compare(i, 1, vogais[j]) == 0)
      {
        string vo = vogais[j];
        char l = vo[0];
        
        palavra[i] = l;
        acertos++;

        chutes.push_back(vo);
      }
    }

    vogais.clear();
  }
  else { //Nível difícil.
    for (int i=0; i<tamP; i++) {
      palavra[i] =  '_';
    }  
  }

  if (d == 1) {
    cout << "\nIniciando o Jogo no nível Fácil, você conhece essa palavra?\n\n\n\n";
  }
  else if (d == 2) {
    cout << "\nIniciando o Jogo no nível Médio, você conhece essa palavra?\n\n\n\n";
  }
  else if (d == 3) {
    cout << "\nIniciando o Jogo no nível Difícil, você conhece essa palavra?\n\n\n\n";
  }
  
  while (game_over() == false && teste_vitoria == false) {
    cout << palavra << "\n";
    cout << "Pontos: " << pontos << "\n";
    cout << "Palpite: ";

    //Validando palpite.
    if (chutes.empty()) {
      cin >> ch;
    }
    else {
      do {
        cin >> ch;
        ch = upper(ch);
        for (vector<string>::iterator it=chutes.begin(); it!=chutes.end(); ++it) {
          if (it->compare(0, 1, ch) == 0) {
            cout << "Palpite dado anteriormente, tente novamente.\n";
            cout << "Palpite: ";
            aux=0;
            break;
          }
          else {
            aux++;
          }
        }

        int tamC = chutes.size();

        if (aux == tamC) {
          teste_chute = true;
          aux=0;
        }
        
      } while (teste_chute == false);
    }
    teste_chute = false;
    
    cout << "\n";

    ch = upper(ch);
    chutes.push_back(ch);
    teste_palpite = palpite (ch, palavra);
    
    if (teste_palpite == true) {
      cout << "Muito bem! A palavra contém a letra " << ch << "!\n\n\n\n";
    }
    else {
      errou = true;
      cout << "Ops, não achei a letra " << ch << "! :<\n";
    }
    construir_forca();
    
    //Verificar se acerou a palavra.
    if (acertos == tamP) {
      if (errou == false) {
        pontos += 1; /*!< Ponto adicional */
      }
      teste_vitoria = true;
      quantidade_palavras_certas++;
      m_tentativas_restantes = 6;
      pontos += 2; /*!< Pontos por acerto */
      m_palavras_certas.push_back(palavra);
    }

    //Verificar se esgotou todas as palavras do jogo.
    if (quantidade_palavras_certas == quantidade_palavras) {
      cout << "Parabéns! Você acertou todas as palavras do jogo!\n";
      teste_fim = true;
      quantidade_palavras_certas=0;
    }
  }

  //Vefiricar vitória
  if (teste_vitoria == true && teste_fim == true) {
    chutes.clear();
    gravar_score ();
  }
  else if (teste_vitoria == true) {
    int op;

    do {
      cout << "Parabéns, você acertou a palavra: " << palavra << "!\n";
      cout << "Quer continuar o jogo?\n";
      cout << "1 - Sim \n";
      cout << "2 - Não \n";
      cout << "Sua escolha: ";
      cin >> op;
      
      if (op==1) {
        chutes.clear();
        errou = false;
        
        for (vector<string>::iterator it=m_palavras.begin(); it!=m_palavras.end(); ++it) {
          if ((it->compare(m_palavra_atual) == 0) && it+1 == m_palavras.end())           {
            m_palavras.erase(it--); /*!< Apagar último elemento do vetor */
          }
          else if (it->compare(m_palavra_atual) == 0)            {
            m_palavras.erase(it);
          }
        }
  
        acertos = 0;
        
        proxima_palavra();
        start();
      }
      else if (op==2) {
          chutes.clear();
          cout << "A partida será encerrada.\n";
          gravar_score();
      }
      else {
        cout << "Erro na escolha das opções! \n";
      }
    } while (op<1 || op>2);
  }
  else if (game_over() == true) { //Verificar game over
    chutes.clear();    
    m_tentativas_restantes = 6;
    cout << "O jogo acabou... a palavra era: "<< m_palavra_atual << "!\n";
    gravar_score ();
  }
}

/**
  * Este método atualiza o arquivo de score salvando o nível e nome do jogador, assim como as palavras que acerou e sua pontuação durante o jogo
  */
void Forca::gravar_score () {
  string nome, buffer;

  getline (cin, buffer); /*!< Lipar o buffer da entrada padrão */
  cout << "Digite o seu nome: ";
  getline(cin, nome);

  //Gravação
  ofstream fout ("data/score.txt", ofstream::app);
  
  fout << "\nNível ";
  if (d == 1) {
    fout << "Fácil";
  }
  else if (d == 2) {
    fout << "Médio";
  }
  else if (d == 3) {
    fout << "Difícil";
  }
  fout << "; " <<  nome << "; ";
  for (vector<string>::iterator it=m_palavras_certas.begin(); it!=m_palavras_certas.end(); ++it) {
    if (*it == m_palavras_certas.back()) {
      fout << *it;
    }
    else {
      fout << *it << ", ";
    }
  }
  fout << "; "<< pontos << " pontos";
  fout.close();

  cout << "\n";

  pontos = 0;
  acertos = 0;
  m_palavras_certas.clear();
}
    
/**
  * Atualiza o número de tentativas restantes.
  * Este método é útil no caso do jogador escolher continuar o jogo.
  * @param tentativas atualiza o valor da variável m_tentativas_restantes.
  */
void Forca::set_tentativas_restantes (int tentativas) {
  m_tentativas_restantes = tentativas;
}
    
/**
  * Retorna a quantidade de tentativas restantes.
  * @return m_tentativas_restantes.
  */
int Forca::get_tentativas_restantes () {
  return m_tentativas_restantes;
}

/**
  * Operador para a função transfom().
  * @return c.
  */
char Forca::lambda (unsigned char c) { return toupper(c); }

/**
  * Transforma a palavra em maiuscula.
  * @return palavra.
  */
string Forca::upper (string palavra) {
  transform (palavra.begin(), palavra.end(), palavra.begin(), lambda);

  return palavra;
}