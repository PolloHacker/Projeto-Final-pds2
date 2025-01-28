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

  - PrintBanner()
  - handleLoadPlayers()
  - handleCreatePlayer()
  - handleRemovePlayer()
  - handleListPlayers()
  - handlePlayGame()

### StringUtils

- Utilitários para a manipulação de strings

- **Métodos principais:**

  - IsInvalidNickname()
  - IsInvalidName()
  - IsValidMoveInput()
### Exceções

- **InexistentPlayerException**: Exceção lançada quando um jogador não é encontrado no sistema.
- **InvalidInputException**: Exceção lançada quando a entrada fornecida pelo usuário é inválida.
- **PlayerNotInListException**: Exceção lançada quando um jogador não está na lista de jogadores.
- **PlayerAlreadyExistException**: Exceção lançada ao tentar criar um perfil de jogador repetido.

## Compilação e Execução

### Pré-requisitos

- Linux ou Windows
- Compilador C++ compatível com C++11 (ex.: g++)
- Make instalado

- Clone o repositório:

  ```bash
    git clone https://github.com/PolloHacker/Projeto-Final-pds2.git
    cd <NOME_DO_DIRETORIO>
  ```

- Compile o projeto:
  ```bash
    make
  ```

- Execute o programa:
  ```bash
    ./tp
    ```

- Limpe os arquivos gerados (remove o executável também):
  ```bash
    make clean
  ```

## Inputs

Os inputs foram estabelecidos pelos desenvolvedores desse projeto, seguindo esse padrão:

### Cadastro de Jogadores

**Carregar execuções anteriores**
- `CA`
   - Sucesso: `[!] - Jogadores carregados com sucesso`, `[!] - Os jogadores já foram carregados`

**Cadastrar Jogador**: 
- `CJ`
-  `Insira o Nome do Jogador: <Nome>`
-  `Insira o Apelido do Jogador: <Apelido>`
   - Sucesso: `[!] - Jogador criado com sucesso`
   - Erros: `ERRO: Nome inávlido, digite o nome do jogador novamente`, `ERRO: Apelido inávlido, digite o Apelido do jogador novamente`  

**Remover Jogador**: 
- `RJ`
- `Digite o Apelido do Jogador a ser removido: <Apelido>`
   - Sucesso: `[!] - Jogador removido com sucesso`
   - Erro: `[X] - O jogador não existe`

- **Listar Jogadores**:  
- `LJ`
- `Digite o tipo de listagem (A - Apelido, N - Nome, C - Lista completa): <A|N|C>`
   - Sucesso: *printa a lista dos jogadores de acordo com o método solicitado pelo usuário*.
   - Erro: `[X] - Tipo de listagem inválido.`

### Execução de Partidas

- **Executar Partida**: 
- `EP` 
- `Digite o tipo de jogo (R - Reversi, L - Lig4, V - Velha): <(R|L|V)>`
- `Digite o apelido do jogador 1: <Apelido>`
- `Digite o apelido do jogador 2: <Apelido>`
   - Sucesso: Inicia o jogo selecionado com os jogadores 1 e 2.
   - Erro: `[X] - Tipo de jogo inválido`, `[X] - Jogador 1|2 não encontrado.\nDigite o apelido do jogador 1|2 novamente:`

- **Finalizar Sistema**: `FS`

## Inputs durante os Jogos

- **Jogada no TicTacToe**: 
  - `Digite a linha e a coluna da jogada: <Linha> <Coluna>`
  - Exemplo: `<0> <2>`
  - Erros: `[X] - Digite apenas números`, `[X] - Fora dos limites`, `[X] - Posicao ocupada`

- **Jogada no Lig 4**: 
  - `Digite a coluna da jogada: <Coluna>`
  - Exemplo: `<1>`
  - Erros: `[X] - Digite apenas números`, `[X] - Fora dos limites`, `[X] - Posicao ocupada`

- **Jogada no Reversi**: 
  - `Digite a linha e a coluna da jogada: <Linha>` `<Coluna>`
  - Exemplo: `<0> <2>`
  - Erros: `[X] - Digite apenas números`, `[X] - Fora dos limites`, `[X] - Posicao ocupada`, `[X] - Jogada invalida`

(Ao final de cada partida o jogador deve pressionar ENTER para retornar ao começo)

## Documentação (online)

- Acesse o link: https://pollohacker.github.io/Projeto-Final-pds2/

## Durante o desenvolvimento deste projeto, a equipe enfrentou alguns desafios:

- Uso de Makefile: Como demoramos a criar o Makefile, já que criamos apenas no final do projeto, observamos que perdemos muito tempo de compilação, já que estavamos sempre recompilando todos os arquivos para realizar os testes.

- Realização dos Testes: Compreender e executar os testes se mostrou um processo desafiador. Houve dificuldades em entender a estrutura e como conseguir integrá-los no nosso processo de desenvolvimento.

- Dificuldades na lógica do reversi: Ao desenvolver a função de checkDiretions, usada para verificar as jogadas, encontramos problemas que foram um desafio a mais para nosso desenvolvimento, sendo necessário várias horas para encontrar e solucionar o erro.

Essas dificuldades, embora desafiadoras, contribuíram para um grande aprendizado por parte de toda a equipe.

## Aprendizados com o projeto

Este projeto foi uma oportunidade valiosa para aprimorar nossas habilidades em programação, colaboração e gerenciamento de projetos. Os principais aprendizados incluem:

- Uso de técnicas de Modularização de projetos em C++ (CRC cards).
- Programação orientada a objetos em C++.
- Colaboração efetiva em um projeto conjunto.
- Comunicação.
- Uso de Git e GitHub para controle de versão.
- Práticas de programação defensiva e tratamento de exceções.
- Criação e manutenção de Makefile.
- Geração de documentação utilizando Doxygen.
- Criação de testes.

## Github dos contribuintes

[Github Isaac Reyes](https://github.com/PolloHacker)  
[Github Mateus Rabelo](https://github.com/MateusMelo6)  
[Github Felipe Almeida](https://github.com/Filpeee)  
[Github João Pedro Martins](https://github.com/ArenaDaSelva)