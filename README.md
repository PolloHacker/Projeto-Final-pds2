# Jogos de Tabuleiro

## Descrição do projeto

O projeto Jogos de Tabuleiro é uma aplicação desenvolvida como trabalho final da disciplina de Programação e Desenvolvimento de Software II (PDS II) do curso de Ciência de Dados na UFMG. Este projeto implementa um sistema para jogar diferentes jogos, proporcionando funcionalidades cadastro de jogadores, exclusão de jogadores, estatísica dos jogadores e a listagem dos jogadores. Os jogos disponibilizados para serem jogados são:

- Lig4
- Reversi
- Tic Tac Toe

## Equipe

Trabalho feito colaborativamente pelos membros:

- Isaac Reyes
- Felipe Almeida
- Mateus Rabelo
- João Pedro Martins

## Tecnologias Utilizadas

- `Linguagem:` C++
- `Compilação:` Makefile  
- `Documentação:` Doxygen e README  
- `Testes:` Biblioteca doctest  
- `Controle de Versão:` Git
  
## Funcionalidades extras implementadas

- Listar todos os jogadores ordenando-os por id, nome ou apelido
- Listar estatisiticas detalhadas de cada jogador, procurando-o por nome ou apelido
- Sistema de persistêcia de dados, permitindo ao usuário carregar dados salvos anteriormente
- Salvamento automático de informações
- Site com a documentação

## Estrutura do Projeto

O projeto foi organizado em diferentes classes, cada uma com suas responsabilidades:

### Classes Principais

### Board

- Responsável por representar o tabuleiro do jogo. Contém métodos para manipulação e consulta do estado do tabuleiro.

- **Métodos principais:**

  - getCols()
  - getElementAt()
  - setPosition()
  - isBoardFull()
  - isWithinBounds()

### Player

- Representa um jogador no sistema. Armazena informações como nome, apelido e estatísticas de vitórias e derrotas.

- **Métodos principais:**

  - getName()
  - getNickname()
  - getTotalWins()
  - getTotalLoses()

### Stats

- Armazena e manipula as estatísticas dos jogadores, como vitórias e derrotas em diferentes jogos.

- **Métodos principais:**

  - incrementWins()
  - incrementLoses()
  - getWins()
  - getLoses()

### PlayerManager

- Gerencia os jogadores, incluindo cadastro, remoção e listagem. Também é responsável por atualizar as estatísticas dos jogadores.

- **Métodos principais:**

  - addPlayer()
  - removePlayer()
  - listPlayers()
  - updatePlayerStats()
  - printTable()

### ExecUtils

- Utilitários para execução de comandos e interação com o usuário.

- **Métodos principais:**

  - PrintBanner(): Imprime o banner do trabalho com os comandos.
  - handleLoadPlayers(): Lida com o carregamento de jogadores no PlayerManager.
  - handleCreatePlayer(): Lida com a criação de um novo jogador.
  - handleRemovePlayer(): Lida com a remoção de um jogador existente.
  - handleListPlayers(): Lida com a listagem de todos os jogadores.
  - handlePlayGame(): Lida com o processo de jogar um jogo.

### StringUtils

- Utilitários para a manipulação de strings

- **Métodos principais:**

  - IsInvalidNickname(): Verifica se uma string é um apelido válido
  - IsInvalidName(): Verifica se uma string é um nome válido
  - IsValidMoveInput(): Verifica se o movimento que o usuário informou é valido

### Exceções

- **InexistentPlayerException**: Exceção lançada quando um jogador não é encontrado no sistema.
- **InvalidInputException**: Exceção lançada quando a entrada fornecida pelo usuário é inválida.
- **PlayerNotInListException**: Exceção lançada quando um jogador não está na lista de jogadores.

## Inputs

Os inputs foram os estabelecidos pelo enunciado, com as entradas e as eventuais mensagens de erro:

### Cadastro de Jogadores

- **Cadastrar Jogador**:
  - (obs. Considere que `<Apelido>` é composto por uma única palavra)
  - Sucesso: `Jogador <Apelido> cadastrado com sucesso`
  - Erros: `ERRO: entrada inválida`, `ERRO: jogador repetido`  

- **Remover Jogador**: `RJ <Apelido>`
  - Sucesso: `Jogador <Apelido> removido com sucesso`
  - Erro: `ERRO: entrada inválida`, `ERRO: jogador não encontrado`

- **Listar Jogadores**:  `LJ A|N` `<Apelido> <Nome>`
  - Sucesso: lista de todos os jogadores ordenados por Apelido ou Nome, seguido pelo número de vitórias e derrotas em cada jogo
  - *Exemplo:*
    - `<Apelido>` `<Nome>`
    - REVERSI - V: <#vitorias> D: <#derrotas>
    - LIG4 - V: <#vitorias> D: <#derrotas>
    - TIC TAC TOE - V: <#vitorias> D: <#derrotas>
    - CAMPO MINADO - V: <#vitorias> D: <#derrotas>
    - MEMORIA - V: <#vitorias> D: <#derrotas>
  - Erro: `ERRO: entrada inválida`, `ERRO: comando inválido; escolha ordenar por (A)pelido ou (N)ome!`

### Execução de Partidas

- **Executar Partida**: `EP <Jogo: (R|L|T|C|M)> <Apelido Jogador 1> <Apelido Jogador 2>`
  - *Exemplo:* `EP R Ju Babi` (executa o jogo Reversi com jogadora Ju e jogadora Babi)
  - Erros:  `ERRO: entrada inválida`, `ERRO: jogo não encontrado`, `ERRO: São necessários dois jogadores para jogar este jogo`, `ERRO: primeiro jogador não encontrado` , `ERRO: segundo jogador não encontrado`, `Este jogo só possui um jogador`
  - Sucesso: `<Apelido Jogador 1> fez log in!`, `<Apelido Jogador 2> fez log in!` `<Jogo> foi escolhido!`
  - Sucesso: `J - JOGAR` `L - Ler regras do jogo`
    - **Jogar:** `<J>`
    - **Regras:** `<L>` (funcionalidade extra)
    - **Erros:** `ERRO: Regras não encontradas para o jogo selecionado.`
  - OBS: *( R= Reversi | L=Lig4 | T=TicTacToe | C=CampoMinado | M=Memória )*

- **Finalizar Sistema**: `FS`

## Inputs durante os Jogos

- **Jogada no Lig 4**: `<Coluna>`
  - Exemplo: `<1>`
  - Erros: `ERRO: formato incorreto`, `Essa jogada é inválida! Passa a vez!`, `Não existem mais posições disponiveis nessa coluna! Perde a vez!`

- **Jogada no Reversi**: `<Linha>` `<Coluna>`
  - Exemplo: `<0>` `<2>`
  - Erros: `ERRO: formato incorreto`, `ERRO: jogada inválida`

- **Jogada no TicTacToe**: `<Linha>` `<Coluna>`
  - Exemplo: `<0>` `<2>`
  - Erros: `ERRO: formato incorreto`, `Essa jogada é inválida! Passa a vez!`
  -
- **Jogada no Campo Minado**: `<Linha>` `<Coluna>`
  - Exemplo: `<0>` `<2>`
  - Erros: `ERRO: jogada inválida!`,  `ERRO: formato incorreto`

- **Jogada no Jogo da Memória**: `<Linha1>` `<Coluna1>` `<Linha2>` `<Coluna2>`
  - Exemplo: `<0>` `<1>` `<0>` `<2>`
  - Erros: `ERRO: formato incorreto`, `ERRO: jogada inválida`

(Ao final de cada partida o jogador tem a opção de ver o ranking do jogo ou voltar ao menu)

- **Visualizar ranking**: `VR` (funcionalidade extra)
- **Jogar novamente**: `JN`
  - Erros: `ERRO: entrada inválida; escolha (J)ogar (N)ovamente ou (V)er (R)anking!`

## Documentação

O projeto conta com diversas formas de documentação: esse READ-ME e os arquivos gerados pelo Doxygen (html e PDF). Para acessar o html basta ir na pasta `html` dentro do repositório, clicar no arquivo `index.html` com o `<Botão Direito do Mouse>` e selecionar a opção `Open With Live Server`

## Dificuldades encontradas

Durante o desenvolvimento deste projeto, a equipe enfrentou alguns desafios:

- Uso do Git e Github:
  A utilização dessas ferramentas apresentou-se como um desafio para a equipe. No decorrer do projeto, tivemos dificuldades ao lidar com conflitos de merge, em entender o fluxo de trabalho nas branches e na utilização das funcionalidades para manter o código organizado.

- Uso de Makefile:
  O processo de compilação dos arquivos com o Makefile apresentou-se com um desafio na reta final. Algumas das dificuldades enfrentadas foram: erro com o arquivo executável, conjutamente com um erro relacionado ao tipo binário gerado na compilação (Exemplo: Relocation against symbol _zvcampominado can not be used when making a PIE object). Para lidar com o problema utilizamos o comando `make clean` e depois realizamos o processo de compilação novamente com `make`. Além disso acrescentamos no arquivo Makefile a linha: `CFLAGS=-std=c++11 -Wall -fPIC`, caso o problema estivesse relacionado a um trecho que envolva código compartilhado ou parte de uma biblioteca.

- Realização dos Testes:
  Compreender e executar os testes também se mostrou um processo desafiador. Houve dificuldades em entender a estrutura e como conseguir integrá-los no nosso processo de desenvolvimento.

- Salvar informações no arquivo Jogadores.txt:
  No processo de manipulação do arquivo, o grupo apresentou dificuldades para tratar um erro específico ao excluir um jogagor, o que gerava uma linha em branco no final do arquivo,. A presença desta linha acarretava o não funcionamento do executável, exibindo o seguinte errro: `terminate called after throwing an instance of 'std::invalid_argument' what(): stoi Aborted.` Para o bom funcionamento do código, é necessário retirar as linhas vazias do arquivo. O grupo buscou tratar essa dificuldade por meio de uma função que posiciona o cursor no início do arquivo, para assim evitar que ele chegue ao final.

Essas dificuldades, embora desafiadoras, contribuíram para um maior aprendizado por parte de toda a equipe.

## Aprendizados com o projeto

Este projeto foi uma oportunidade valiosa para aprimorar nossas habilidades em programação, colaboração e gerenciamento de projetos. Os principais aprendizados incluem:

- Programação orientada a objetos em C++.
- Colaboração efetiva em um projeto conjunto.
- Comunicação.
- Uso avançado de Git e GitHub para controle de versão.
- Práticas de programação defensiva e tratamento de exceções.
- Criação e manutenção de Makefile.
- Geração de documentação utilizando Doxygen.
- Criação de testes.

## Github dos contribuintes

[Github Isaac Reyes](https://github.com/PolloHacker)  
[Github Mateus Rabelo](https://github.com/MateusMelo6)  
[Github Felipe Almeida](https://github.com/Filpeee)  
[Github João Pedro Martins](https://github.com/ArenaDaSelva)
