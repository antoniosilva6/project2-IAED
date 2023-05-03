/* iaed-23 - ist1102879 - project2
 * 
 * Ficheiro: main.c
 * Autor: António Dias da Silva
 * Descição: Função main do sistema de gestão de transportes  
*/

/* Bibliotecas */

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include "cabecalho.h"

/* Main */

int main() {  
    char buffer[BUFFER_SIZE];  

    Carreira *headCarreiras = NULL;
    Paragem *headParagens = NULL;
    Ligacao *headLigacao = NULL;

    while(buffer[0] != EOF){
        lePalavraAteFimDeLinha(buffer);

        /* Possíveis casos de "inputs" */
        switch (buffer[0]) {
        case 'q': apagaTodosOsDados(&headCarreiras, &headParagens, &headLigacao);
            return 0;

        case 'c': comandoCarreiras(buffer, &headCarreiras, &headParagens, 
                                &headLigacao);
            memset(buffer, 0, sizeof(buffer));
            break;
        
        case 'p': comandoParagens(buffer, &headCarreiras, &headParagens, 
                                &headLigacao);
            memset(buffer, 0, sizeof(buffer));
            break; 

        case 'l': comandoLigacoes(buffer, &headCarreiras, &headParagens, 
                                &headLigacao);
            memset(buffer, 0, sizeof(buffer));
            break; 

        case 'i': comandoIntersecoes(&headParagens);
            memset(buffer, 0, sizeof(buffer));
            break;

        case 'a': apagaTodosOsDados(&headCarreiras, &headParagens, &headLigacao);
            memset(buffer, 0, sizeof(buffer));
            break;
        
        case 'r': removerCarreira(buffer, &headCarreiras, &headParagens);
            memset(buffer, 0, sizeof(buffer));
            break;

        case 'e': eliminaParagem(buffer, &headParagens, &headLigacao);
            memset(buffer, 0, sizeof(buffer));
            break;

        default: 
            printf ("Invalid comand: %s\n", buffer);
            memset(buffer, 0, sizeof(buffer));
        } 
    }
    return 0;
}
