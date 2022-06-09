#ifndef FORCA.HPP
#define FORCA.HPP

#include <iostream>
#include <fstream>
#include <vector>

class Forca {
  public:
    enum Dificuldade{ FACIL=1, MEDIO=2, DIFICIL=3 };

  private:
    std::vector<std::string> m_palavras; //<! estrutura para carregar as palavras para o jogo
    std::vector<std::string> m_palavras_certas; //<! estrutura para carregar as palavras que foram acertadas durante o jogo
    std::vector<std::string> chutes; //<! armazena os palpites dados durante o jogo
    Dificuldade d = Dificuldade::FACIL; //<! dificuldade do jogo
    std::string m_palavra_atual; //<! palavra sendo testada atualmente
    int m_tentativas_restantes = 6; //<! tentativas restantes
    int quantidade_palavras_certas = 0; //<! salvar o numero de palavras em que acertou.
    int quantidade_palavras; //<! salvar o numero de palavras lida no arquivo.
    int pontos = 0; //<! Pontução a ser salva no score
    int acertos = 0; //<! verificar quantidade de acertos nos palpites.
    bool errou = false; //<! verificar se errou algum dos palpites.

  public:
    /**
      * Cria a classe Forca
      * O construtor inicializa o jogo chamando o método inicio() na função princial.
      */
    Forca();

    /**
      * Valida os arquivos de entrada de acordo com as especificações.
      * Ao validar os arquivos, no caso de arquivos inválidos, este método deve retornar a
      * razão correspondente de acordo com as especificações.
      * @return {T,""} se os arquivos estiverem válidos, {F,"razão"} caso contrário.
      */
    std::pair<bool, std::string> eh_validoP(std::string p);

    /**
      * Valida os arquivos de score de entrada de acordo com as especificações.
      * Ao validar os arquivos, no caso de arquivos inválidos, este método deve retornar a
      * razão correspondente de acordo com as especificações.
      * @return {T,""} se os arquivos estiverem válidos, {F,"razão"} caso contrário.
      */
    std::pair<bool, std::string> eh_validoS(std::string s);

    /**
      * Imprimi a mensagem de erro referente a análise dos arquivos e finaliza o programa.
      */
    void falha_leitura (std::string mens_erro);

    /**
    * Carrega os arquivos de palavras preenchendo a estrutura m_palavras
    */
    void carrega_arquivos(std::vector<std::string> p);

    /**
      * Constroi o desenho da forca a medida em que se erra os palpites.
      */
    void construir_forca();

    /**
      * Modifica a dificuldade do jogo.
      * De acordo com a dificuldade configurada, o método proxima_palavra retornará palavras
      * de forma diferente.
      * Parâmetro d a dificuldade desejada
      * Método proxima_palavra
      */
    void set_dificuldade(int d);

    /**
      * Retorna a próxima palavra de acordo com a dificuldade atual.
      * Este método deve atualizar o atributo m_palavra_atual. O método também deve sortear as
      * letras que devem aparecer dependendo do nível de dificuldade.
      * @return a próxima palavra do conjunto de palavras disponível de acordo com a dificuldade atual.
      */
    std::string proxima_palavra();

    /**
      * Retorna a palavra atual que está sendo jogada.
      * @return o valor do atributo m_palavra_atual.
      */
    std::string get_palavra_atual();

    /**
      *Testa se uma letra pertence à palavra atual, retorna T se a letra pertence.
      * Este método testa se uma letra pertence à palavra atual e retorna True caso pertença.
      * Caso contrário, o método deve atualizar o atributo m_tentativas_restantes, decrementando
      * em 1, e retornar False.
      * @param palpite uma letra, que deve ser testada se pertence à palavra.
      * @return T se a palpite pertence à palavra, F caso contrário.
      */
    bool palpite(std::string palpite, std::string &palavra);

    /**
      * Em caso de Game Over este método deve retornar T.
      * @return T caso o m_tentativas_restantes do jogo esteja igual a 0, F caso contrário.
      */
    bool game_over();

    /**
      * Método para inicializar o jogo com a leitura dos aquivos e chamando o método start().
      */
    void inicio ();

    /**
      * Método que executa o jogo, validando os palpites de entrada e verificando se o jogadar ganhou ou perdeu.
      */
    void start ();

    /**
      * Este método atualiza o arquivo de score salvando o nível e nome do jogador, assim como as palavras que acerou e sua pontuação durante o jogo
      */
    void gravar_score ();

    /**
      * Atualiza o número de tentativas restantes.
      * Este método é útil no caso do jogador escolher continuar o jogo.
      * @param tentativas atualiza o valor da variável m_tentativas_restantes.
      */
    void set_tentativas_restantes(int tentativas);

    /**
      * Retorna a quantidade de tentativas restantes.
      * @return a quantidade de tentativas restantes.
      */
    int get_tentativas_restantes();

    /**
      * Transforma a palavra em maiuscula.
      * @return palavra.
      */
    std::string upper(std::string palavra);
};

#endif //FORCA.HPP