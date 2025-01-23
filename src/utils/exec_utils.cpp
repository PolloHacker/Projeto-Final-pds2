#include <iostream>
#include "exec_utils.hpp"


void ExecUtils::PrintBanner() {
    std::cout << 
    "+--------------------------Trabalho----------------------------+\n" <<
    "+ Comandos:                                                    +\n" <<
    "+ CA <nome_do_arquivo.csv> - Carrega execucoes anteriores      +\n" <<
    "+ CJ <apelido> <nome> - Criar jogador                          +\n" <<
    "+ RJ <apelido> - Remover jogador                               +\n" <<
    "+ LJ (A|N) - Listar jogadores                                  +\n" <<
    "+ EP <Jogo: (R|L|V)> <apelido j1> <apelido j2> - Jogar um jogo +\n" <<
    "+ FS - Finalizar sistema                                       +\n" <<
    "+--------------------------------------------------------------+" << std::endl;
}
