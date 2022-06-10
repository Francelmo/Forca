    UNIVERSIDADE FEDERAL DO RIO GRANDE DO NORTE    
            INSTITUTO METRÓPOLE DIGITAL 
        IMD0030 - LINGUAGEM DE PROGRAMAÇÃO I
    
    Aluno: Francelmo Guimarães de Farias
    Matrícula: 20190039737 

# Projeto Forca:

## Descrição:
Esse projeto aborda o jogo da forca, implementado para receber um arquivo de texto contendo as palavras a serem sorteadas, assim como um arquivo para a exibição e gravação da pontuação dos jogadores.

O jogo possui três níveis de dificuldades (Fácil, Médio e Difício), com padrões de exibição da palavra secreta de acordo com cada um deles.

Para jogar, é necessário informar letras (maiúsculas ou minúsculas) ou hífem "-" para dar os palpites, se for algo diferente disso, o jogo entenderá como um palpite errado e irá decrementar da pontuação total da partida.

## Compilação:
O projeto foi criado e executado no Replit.com, onde o complitador utiliazado pelo site é o Clang, versão front-end baseado no compliador de código aberto GCC da GNU.

## Configuração da Entrada e Saída de Dados:
Para a entrada de dados, existem dois documentos de texto denominados "palavras.txt" e "score.txt", com o diferencial que o segundo arquivo também é utilizado para a sáida dos dados, como nas seguintes configurações:

Palavras (Exemplo entrada):

    casa
    anos
    pode
    piano
    temos
    final
    Brasil
    inicio
    predio
    mississipi
    guarda-chuva
    paralelepipedo

Scores (Exemplo entrada/saída):

    Nível Fácil; Francelmo; INICIO; 8 pontos
    Nível Fácil; Francelmo; CASA, PODE; 12 pontos
    Nível Médio; Francelmo; ; -3 pontos
    Nível Difícil; Francelmo; CASA; 2 pontos

Para o arquivo palavra.txt não pode ter palavras menores que 3 caracteres e sua composição tem que ser interamente de letras maiúsculas e minúsculas com exceção do hífem '-'.

## Dificuldades Encontradas:
As dificuldades encontradas foram executar trechos do algoritmo totalmente em C++, passando a utilizar o auxílio de bibliotecas em C, como a parte de solicitar uma palavra de forma aleatória, tendo que ser implementado com a função rand(). Assim como strtok() para ajudar na verificação do arquivo score.txt e a função toupper() para passar as palavras para maiúsculas e, com isso, facilitar a validação dos palpites.