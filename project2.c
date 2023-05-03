/* iaed-23 - ist1102879 - project2
 * 
 * Ficheiro: project2.c
 * Autor: António Dias da Silva
 * Descição: Sistema de gestão de transportes públicos - Memória Dinânimca   
*/

/* Bibliotecas */

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include "cabecalho.h"

/* Funções de eliminação de dados */

/* Apaga todas as Carreiras do sistema */
void apagarDadosCarreiras(Carreira **headCarreiras) {
    /* Percorre a lista ligada de carreiras */
    Carreira *atualCarreira = *headCarreiras;
    while (atualCarreira != NULL) {
        /* Armazena o ponteiro para a próxima carreira para não perdê-lo */
        Carreira *proximo = atualCarreira->proxima;
        ParagemNode *atualParagemNode = atualCarreira->paragens;
        
        /* Percorre a lista ligada de paragens da carreira */
        while (atualParagemNode != NULL) {
            /* Armazena o ponteiro para o próximo nó da lista de paragens para não perdê-lo */
            ParagemNode *proximoParagemNode = atualParagemNode->proxima;

            /* Liberta a memória alocada para o nó da lista de paragens */
            free(atualParagemNode);
            atualParagemNode = proximoParagemNode;
        }
        /* Liberta a memória alocada para o nome da carreira */
        free(atualCarreira->nome);
        /* Liberta a memória alocada para a paragem */
        free(atualCarreira);
        atualCarreira = proximo;
    }
    /* Define a cabeça da lista ligada de carreiras como NULL para indicar que está vazia */
    *headCarreiras = NULL;
}

/* Apaga todas as Paragens do sistema */
void apagarDadosParagens(Paragem **headParagens) {
    /* Percorre a lista ligada de paragens */
    Paragem *atualParagem = *headParagens;
    while (atualParagem != NULL) {
        /* Armazena o ponteiro para a próxima paragem para não perdê-lo */
        Paragem *proximo = atualParagem->proxima;
        CarreiraNode *atualCarreiraNode = atualParagem->carreiras;

        /* Percorre a lista ligada de carreiras da paragem */
        while (atualCarreiraNode != NULL) {
            /* Armazena o ponteiro para o próximo nó da lista de carreiras para não perdê-lo */
            CarreiraNode *proximoCarreiraNode = atualCarreiraNode->proxima;

            /* Liberta a memória alocada para o nó da lista de carreiras */
            free(atualCarreiraNode);
            atualCarreiraNode = proximoCarreiraNode;
        }

        /* Liberta a memória alocada para o nome da paragem */
        free(atualParagem->nome);
        /* Liberta a memória alocada para a paragem */
        free(atualParagem);
        atualParagem = proximo;
    }
    /* Define a cabeça da lista ligada de carreiras como NULL para indicar que está vazia */
    *headParagens = NULL;
}

/* Apaga todas as Ligações do sistema */
void apagarDadosLigacoes(Ligacao **headLigacao) {
    /* Apagar as ligações */
    Ligacao *ligacaoAtual = *headLigacao;
    while (ligacaoAtual != NULL) {
        Ligacao *aux = ligacaoAtual;
        free(ligacaoAtual->carreiraNome);
        free(ligacaoAtual->paragem1);
        free(ligacaoAtual->paragem2);
        ligacaoAtual = ligacaoAtual->proxima;
        free(aux);
    }
    /* Define a cabeça da lista ligada de Ligacoes como NULL para indicar que está vazia */
    *headLigacao = NULL;
}

/* Apaga todos os dados */
void apagaTodosOsDados(Carreira **headC, Paragem **headP, Ligacao **headL){
    apagarDadosCarreiras(headC);
    apagarDadosLigacoes(headL);
    apagarDadosParagens(headP);
}

/* Funcoes auxiliares */

/* Verifica se existe memória suficiente no programa */
int faltaMemoria(void *ponteiro, Carreira **headC, Paragem **headP,
                Ligacao **headL) {
    if (ponteiro == NULL) { /* Se o ponteiro recebido, estiver com o valor NULL, não há memória */
        printf("No memory\n");
        apagaTodosOsDados(headC, headP, headL);
        free(ponteiro); 
        return 1;
    }
    return 0;
}

/* Devolve o tamanho da primeira palavra dentro do buffer */
int comprimentoPalavra(char buffer[]) {
    int tamanho = 0, entreAspas = 0, i;

    for (i = 0; buffer[i] != '\0'; i++) {
        if (buffer[i] == '"' && (i == 0 || buffer[i-1] != '\\')) {
            entreAspas = !entreAspas;
        } else if (!entreAspas && buffer[i] != ' ' && buffer[i] != '\t' && buffer[i] != '\n') {
            tamanho++;
        } else if (entreAspas) {
            tamanho++;
        } else {
            break;
        }
    }
    return tamanho;
}

/* Funções de Paragem */

/* Coloca uma paragem na lista simplesmente ligada */
void pushParagem(Paragem *paragem, Paragem **headParagens) {
    /* se a lista estiver vazia, a nova paragem é a cabeça da lista */
    if (*headParagens == NULL){ 
        /* Caso a lista esteja vazia, a nova paragem é a nova cabeça da lista */
        *headParagens = paragem;
    }
    /* caso contrário, adicionar a nova paragem no final da lista */
    else {
        Paragem *atual = *headParagens;
        while (atual->proxima != NULL) {
            atual = atual->proxima;
        }
        atual->proxima = paragem;
    }
}   

/* Funções de Carreiras */

/* Adiciona uma nova carreira à lista simplesmente ligada de Carreiras */
void pushCarreira(Carreira *carreira, Carreira **headCarreiras) {
    /* Adiciona a nova carreira no fim da lista de carreiras */
    if (*headCarreiras == NULL) {
        /* Se a lista estiver vazia, o novo nó será o primeiro */
        *headCarreiras = carreira;
    }

    else {
        /* Caso contrário, percorre a lista até o último nó e adiciona o novo nó após ele */
        Carreira *atual = *headCarreiras;
        while (atual->proxima != NULL) {
            atual = atual->proxima;
        }
        atual->proxima = carreira;
    }
}


/* Funcoes de Ligacoes */ 

/* Coloca uma ligacao na lista simplesmente ligada */
void pushLigacao(Ligacao *ligacao, Ligacao **headLigacao) {
    /* se a lista estiver vazia, a nova ligacao é a cabeça da lista */
    if (*headLigacao == NULL) {
        /* caso a lista esteja vazia, a nova paragem é a nova cabeça da lista */
        *headLigacao = ligacao;
    /* caso contrário, adicionar a nova paragem no final da lista */
    } else {
        Ligacao *atual = *headLigacao;
        while (atual->proxima != NULL) {
            atual = atual->proxima;
        }
        atual->proxima = ligacao;
    }
}

/* Adiciona a carreira à lista simplesmente ligada de carreiras, da
estrutura de paragens*/
void pushCarreiraNode(Carreira *carreira, Paragem *paragem, Carreira **headC,
                    Paragem **headP, Ligacao **headL) {
    CarreiraNode *node = paragem->carreiras;
    CarreiraNode *novoNo = (CarreiraNode*) malloc(sizeof(CarreiraNode));
    while (node != NULL) {
        if (strcmp(node->carreira->nome, carreira->nome) == 0) {
            /* A carreira já existe, não é necessário adicioná-la novamente */
            free(novoNo);
            return;
        }
        node = node->proxima;
    }

    /* Criar novo CarreiraNode */
    if (faltaMemoria(novoNo, headC, headP, headL)){ /* Verifica a memória */
        exit(0);
    }
    
    novoNo->carreira = carreira;
    novoNo->proxima = NULL;

    /* Adicionar o novo nó no início da lista de carreiras da paragem */
    if (paragem->carreiras == NULL) {
        novoNo->proxima = NULL;
        paragem->carreiras = novoNo;
    } else {
        novoNo->proxima = paragem->carreiras;
        paragem->carreiras = novoNo;
    }
}

/* Adiciona uma paragem à lista simplesmente ligada de paragens na estrutura
de carreira no início da lista*/
void pushParagemNodeInicio(Carreira *carreira, Paragem *paragem, Carreira **headC,
                        Paragem **headP, Ligacao **headL) {
    ParagemNode *paragemNode = (ParagemNode*) malloc(sizeof(ParagemNode));
    if (faltaMemoria(paragemNode, headC, headP, headL)) { /* Verifica a memória */
        exit(0);
    }

    paragemNode->paragem = paragem;
    paragemNode->proxima = carreira->paragens;
    paragemNode->anterior = NULL;

    if (carreira->paragens != NULL) {
        carreira->paragens->anterior = paragemNode;
    }

    carreira->paragens = paragemNode;
}

/* Adiciona uma paragem à lista simplesmente ligada de paragens na estrutura
de carreira no fim da lista*/
void pushParagemNode(Carreira *carreira, Paragem *paragem, Carreira **headC, 
                    Paragem **headP, Ligacao **headL){
    ParagemNode *novoNo = (ParagemNode*) malloc(sizeof(ParagemNode));
    if(faltaMemoria(novoNo, headC, headP, headL)) { /* Verifica a memória */
        exit(0);
    }

    novoNo->paragem = paragem;
    novoNo->anterior = NULL;
    novoNo->proxima = NULL;

    if (carreira->paragens == NULL) {
        carreira->paragens = novoNo;
    } else {
        ParagemNode *ultimaParagem = carreira->paragens;
        while (ultimaParagem->proxima != NULL) {
            ultimaParagem = ultimaParagem->proxima;
        }
        ultimaParagem->proxima = novoNo;
        novoNo->anterior = ultimaParagem;
    }
}


/* Funções para remover carreiras */

/* Remove uma carreira da lista ligada de Carreiras */
void popCarreira(Carreira *carreira, Carreira **headCarreiras) {
    /* Verifica se a carreira a ser removida é a cabeça da lista */
    if (carreira == *headCarreiras) {
        /* Se sim, atualiza a cabeça da lista para a próxima carreira */
        *headCarreiras = carreira->proxima;
    } 
    else {
        /* Caso contrário, é necessário percorrer a lista até 
        encontrar a carreira anterior à que será removida */
        Carreira *anterior = *headCarreiras;
        while (anterior->proxima != carreira) {
            anterior = anterior->proxima;
        }
        anterior->proxima = carreira->proxima;
    }
}

/* Comando para remover Carreira */

/* Remove a carreira removida de todas as paragens que passam por esta */
void removeCarreiraDeParagem(Carreira *carreira, Paragem *paragem) {
    /* Procurar a carreira na lista de carreiras da paragem */
    CarreiraNode *carreiraNode = paragem->carreiras;
    CarreiraNode *prevCarreiraNode = NULL;

    while (carreiraNode != NULL && carreiraNode->carreira != carreira) {
        prevCarreiraNode = carreiraNode;
        carreiraNode = carreiraNode->proxima;
    }

    /* Se não encontrar a carreira na lista, retorna */
    if (carreiraNode == NULL) {
        return;
    }

    /* Remover a carreira da lista de carreiras da paragem*/
    if (prevCarreiraNode != NULL) {
        prevCarreiraNode->proxima = carreiraNode->proxima;
    } else {
        paragem->carreiras = carreiraNode->proxima;
    }

    /* Liberar a memória alocada para o CarreiraNode */
    free(carreiraNode);
}

/* Limpa a lista de paragens da carreira que foi removida */
void limpaParagensDeCarreira(Carreira *carreira) {
    ParagemNode *pn = carreira->paragens;
    while (pn != NULL) {
        ParagemNode *atual = pn;
        CarreiraNode *cn = atual->paragem->carreiras;
        pn = pn->proxima;
        /* Remover carreira da lista de carreiras da paragem */
        if (cn != NULL && cn->carreira == carreira) {
            /* Se a carreira a remover for a primeira na lista de carreiras da
            paragem,atualiza-se o ponteiro da paragem para apontar para a 
            próxima carreira da lista */
            atual->paragem->carreiras = cn->proxima;
            free(cn);
        } else {
            /* Se a carreira a remover não for a primeira na lista, percorre-se a lista
            de carreiras até encontrá-la */
            while (cn != NULL && cn->proxima != NULL) {
                if (cn->proxima->carreira == carreira) {
                    CarreiraNode *aux = cn->proxima;
                    cn->proxima = aux->proxima;
                    free(aux);
                    break;
                }
                cn = cn->proxima;
            }
        }
        free(atual);
    }
    carreira->paragens = NULL;
}

/* Verifica se a carreira está presente na lista de carreiras da paragem */
int carreiraEstaNaParagem(Carreira *carreira, Paragem *paragem) {
    CarreiraNode *cn = paragem->carreiras;
    while (cn != NULL) {
        if (cn->carreira == carreira) { /* Verifica se a carreira passa nessa paragem */
            return 1;
        }
        cn = cn->proxima;
    }
    return 0; /* Se a carreira não estiver na lista de carreiras da paragem, retorna 0 */
}

/* Comando para remover a carreira */
void removerCarreira(char buffer[], Carreira **headCarreiras, Paragem **headParagens) {
    Carreira *carreira;
    Paragem *paragem = *headParagens;
    removerComandoDoBuffer(buffer);

    /* Obtem o ponteiro da carreira, caso esta exista */
    carreira = encontraCarreira(buffer, headCarreiras);
    if (carreira == NULL) {
        printf("%s: no such line.\n", buffer);
        return;
    }

    /* Remover carreira de todas as paragens em que está presente */
    while (paragem != NULL) {
        if (carreiraEstaNaParagem(carreira, paragem)) {
            removeCarreiraDeParagem(carreira, paragem);
        }
        paragem = paragem->proxima;
    }

    /* Limpar a lista de paragens por onde a carreira passa */
    limpaParagensDeCarreira(carreira);

    /* Apaga da lista ligada de todas as carreiras */
    popCarreira(carreira, headCarreiras);
    free(carreira->nome);
    free(carreira);
}


/* Comando para eliminar uma paragem */

/* Retorna um ponteiro para a Ligacao, caso esta exista. Recebe o nome da
carreira, os nomes da paragem e um modo. Caso o modo seja 1 a ligacao que
queremos é a que formou o primeiro extremo. Caso o modo seja 2 a ligacao
que queremos é a que formou o segundo extremo */
Ligacao *encontraLigacao(char *carreiraNome, char *paragem, int modo,
                        Ligacao **headLigacao) {
    Ligacao *l;
    for (l = *headLigacao; l != NULL; l = l->proxima) {
        if (strcmp(l->carreiraNome, carreiraNome) == 0 && 
        strcmp(l->paragem1, paragem) == 0 && modo == 1) {
            return l;
        }
        if (strcmp(l->carreiraNome, carreiraNome) == 0 && 
        strcmp(l->paragem2, paragem) == 0 && modo == 2) {
            return l;
        }
        if (strcmp(l->carreiraNome, carreiraNome) == 0 &&
        (strcmp(l->paragem1, paragem) == 0 || strcmp(l->paragem2, paragem))) {
            return l;
        }
    }
    return NULL;
}

/* Remove uma Paragem da lista ligada de Paragens */
void popParagem (Paragem *paragem, Paragem **headParagens) {
    /* Verifica se a paragem a ser removida é a cabeça da lista */
    if (paragem == *headParagens) {
        /* Se sim, atualiza a cabeça da lista para a próxima paragem */
        *headParagens = paragem->proxima;
        /* Caso contrário, é necessário percorrer a lista até 
        encontrar a paragem anterior à que será removida */
    } else {
        Paragem *anterior = *headParagens;
        while (anterior->proxima != paragem) {
            anterior = anterior->proxima;
        }
        anterior->proxima = paragem->proxima;
    }
}

/* Verifica se a paragem recebida como argumento, caso seja extremo e seja a
primeira paragem, retorna 1. Caso seja extremo e seja a última paragem retorna
2. Se não for extremo, retorna 0. */
int verificaSeEExtremo (Carreira *carreira, Paragem *paragem) {
    ParagemNode *pn = carreira->paragens;
    if (carreira->paragens->paragem == paragem) {
        return 1; /* É a primeira paragem da carreira */
    } 
    while (pn->proxima != NULL){
        pn = pn->proxima;
    }
    if (pn->paragem == paragem) {
        return 2; /* É a última paragem da carreira */
    } else {
        return 0; /* Não é um extremo da carreira */
    } 
}

/* Remove uma Ligacao da lista ligada de ligacoes */
void popLigacao(Ligacao *ligacao, Ligacao **headLigacao) {
    /* Verifica se a ligacao a ser removida é a cabeça da lista */
    if (ligacao == *headLigacao) {
        /* Se sim, atualiza a cabeça da lista para a próxima ligacao */
        *headLigacao = ligacao->proxima;
        /* Caso contrário, é necessário percorrer a lista até 
        encontrar a ligacao anterior à que será removida */
    } else {
        Ligacao *anterior = *headLigacao;
        while (anterior->proxima != ligacao) {
            anterior = anterior->proxima;
        }
        anterior->proxima = ligacao->proxima;
    }
}

/* Limpa a lista de carreiras da paragem dada como arguemnto */
void removeTodasCarreirasDeParagem(Paragem *paragem) {
    CarreiraNode *cn = paragem->carreiras;
    while (cn != NULL) {
        CarreiraNode *temp = cn;
        cn = cn->proxima;
        free(temp);
    }
    paragem->carreiras = NULL;
}

/* Remove uma paragem da lista de paragens da Carreira */
void removeParagemDeCarreira(ParagemNode *pn, Carreira *carreira) {
    ParagemNode *prevPn = NULL;
    ParagemNode *tempPn = carreira->paragens;
    
    /* Procura todos os nós que contêm a paragem e remove */
    while (tempPn != NULL) {
        /* Atualiza o ponteiro da lista de paragens */
        if (tempPn == pn) { 
            ParagemNode *temp = tempPn;
            if (prevPn == NULL) {
                carreira->paragens = tempPn->proxima;
            } else {
                prevPn->proxima = tempPn->proxima;
            }
            /* Remove o nó da lista e liberta a memória */
            tempPn = tempPn->proxima;
            free(temp);
        } else {
            prevPn = tempPn;
            tempPn = tempPn->proxima;
        }
    }
}

/* Comando para eliminar a paragem */
void eliminaParagem(char buffer[], Paragem **headP, Ligacao **headL) {
    Paragem *paragem;
    CarreiraNode *cn;
    int numParagens = 0;
    removerComandoDoBuffer(buffer);
    /* Obtem o ponteiro para a paragem, caso esta exista */
    paragem = encontraParagem(buffer, headP);
    if (paragem == NULL){
        printf("%s: no such stop.\n", buffer);
        return;
    }
    
    /* Remover paragem de todas as carreiras em que está presente */
    cn = paragem->carreiras;
    while (cn != NULL) {
        Carreira *carreira = cn->carreira;
        ParagemNode *pn = carreira->paragens;
        ParagemNode *prevPn = NULL; /* Ponteiro para o nó anterior */
        numParagens = numParagensCarreira(carreira);
        /* Procura a paragem na lista de paragens da carreira */
        while (pn != NULL) {
            if (pn->paragem == paragem) {
                ParagemNode *tempPn = pn;
                /* Verifica se a paragem é um extremo */
                int verificao = verificaSeEExtremo(carreira, pn->paragem);
                if (verificao > 0 && numParagens > 1) {
                    /* Se for, obtem a ligacao correspondente ao extremo */
                    Ligacao *ligacao = encontraLigacao(carreira->nome, 
                                    pn->paragem->nome, verificao, headL);
                    /* Atualiza o custo e a duracao */
                    carreira->custo -= ligacao->custo;
                    carreira->duracao -= ligacao->duracao;
                    /* Remove a ligacao */
                    popLigacao(ligacao, headL);
                    free(ligacao);
                }
                else if (numParagens > 1){
                    Ligacao *ligacao = encontraLigacao(carreira->nome,
                                        pn->paragem->nome, 0, headL);
                    /* Remove a ligacao */
                    popLigacao(ligacao, headL);
                    free(ligacao);                  
                }
                /* Remove a paragem da lista de paragens da carreira */
                if (prevPn == NULL) {
                    carreira->paragens = pn->proxima;
                } else {
                    prevPn->proxima = pn->proxima;
                }
                pn = pn->proxima;
                free(tempPn);
            } else {
                prevPn = pn; /* Guarda o nó anterior */
                pn = pn->proxima;
            }
        }
        numParagens = numParagensCarreira(carreira);
        if (numParagens == 1) {
            /* Se a carreira ficou com apenas uma paragem, remove essa paragem */
            ParagemNode *paragemUnica = carreira->paragens;
            removeParagemDeCarreira(paragemUnica, carreira);
            carreira->custo = 0;
            carreira->duracao = 0;
        }
        cn = cn->proxima;
    }
    
    /* Remover a paragem da lista de paragens */
    removeTodasCarreirasDeParagem(paragem);
    popParagem(paragem, headP);
    free(paragem->nome);
    free(paragem);
}
