/* iaed-23 - ist1102879 - project2
 * 
 * Ficheiro: project1.c
 * Autor: António Dias da Silva
 * Descição: Sistema de gestão de transportes públicos - Funções do primeiro projeto   
*/

/* Bibliotecas */

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include "cabecalho.h"

/* Funcoes de Leitura */

/* Lê o input inteiro e guarda num vetor */
void lePalavraAteFimDeLinha(char str[]) {
	char c = getchar();
	int i = 0;
    while (c == ' ' || c == '\t')
	    c = getchar();
    while (c != '\n') {
	    str[i++] = c;
	    c = getchar();
	}

	str[i] = '\0';
}

/* Guarda num vetor a primeira palavra (argumento) lido e atualiza o buffer, 
retirando-o, mas mantendo o resto, por fim retorna o tamanho da palavra
lida */
void leProximaPalavra(char str[], char buffer[]) {
    int i, k, j;
    /* Encontra o índice i do primeiro caractere não branco no buffer */
    for (i = 0; buffer[i] != '\0'; i++) {
        if (!isspace(buffer[i])) {
            break;
        }
    }

    /* Se o buffer está vazio ou contém apenas espaços em branco, define a 
    string de saída como vazia e retorna */
    if (buffer[i] == '\0') {
        str[0] = '\0';
        return;
    }

    /* Encontra o índice j do próximo caractere em branco no buffer após i */
    for (j = i; buffer[j] != '\0'; j++) {
        if (isspace(buffer[j])) {
            break;
        }
    }

    /* Copia a palavra do buffer para a string de saída */
    k = 0;
    for (; i < j; i++) {
        str[k++] = buffer[i];
    }
    str[k] = '\0';

    /* Encontra o próximo índice j do caractere em branco no buffer 
    após a palavra copiada */
    for (; buffer[j] != '\0'; j++) {
        if (!isspace(buffer[j])) {
            break;
        }
    }

    /* Move o restante do buffer para o início, excluindo a palavra copiada */
    k = 0;
    for (; buffer[j] != '\0'; j++) {
        buffer[k++] = buffer[j];
    }
    buffer[k] = '\0';
}

/* Guarda num vetor a palavra entre aspas e atualiza o buffer, retirando-a */
void tirarPalavraEntreAspas(char *buffer, char *nome) {
    /* Encontra o primeiro e último índice das aspas duplas no buffer */
    char *inicio = strchr(buffer, '"');
    char *fim = strchr(inicio + 1, '"');
    char *next_char = fim + 1;  /* próximo caractere após o último índice das aspas */
    
    if (inicio && fim) {
        int len = fim - inicio - 1;
        strncpy(nome, inicio + 1, len); /* Copia a string entre as aspas para a variável nome */
        nome[len] = '\0';
        
        /* Encontra o próximo caractere não branco após a última aspa */
        while (isspace(*next_char)) {
            ++next_char;
        }
        memmove(inicio, next_char, strlen(next_char) + 1);
    }
}

/* Funções auxiliares */

/* Retorna o numero de palavras num vetor */
int contaPalavras(char buffer[]) {
    int i = 0, contador = 0, estado = FORA;
    while (buffer[i] != '\0') {
        if (buffer[i] == '\n' || buffer[i] == '\t' || buffer[i] == ' ')
            estado = FORA;
        else if (estado == FORA) {
            estado = DENTRO;
            ++contador;
        }
        i++;
    }
    return contador;
}

/* Retira apenas a primeira letra e o espaço */
void removerComandoDoBuffer(char buffer[]) {
    int i;

    for (i = 0; buffer[i] != ' ' && buffer[i] != '\0'; i++);
    
    if (buffer[i] == ' ') {
        memmove(buffer, buffer + i + 1, strlen(buffer) - i);
    }
}

/* Verifica se existem aspas */
int temAspas(char buffer[]){
    if (buffer[0] == '"')
        return 1;
    return 0;
}

/* Algoritmo de ordenação BubbleSort */

/* Função auxiliar que troca a posição de duas carreiras */
void trocaCarreiras(CarreiraNode *a, CarreiraNode *b) {
    Carreira *aux = a->carreira;
    a->carreira = b->carreira;
    b->carreira = aux;
}

/* Ordena as carreiras por ordem alfabética */
void bubbleSort(CarreiraNode *inicio) {
    int trocado;
    CarreiraNode *ptr1;
    CarreiraNode *lptr = NULL;

    /* Se a lista estiver vazia, não há nada a fazer */
    if (inicio == NULL) {
        return;
    }

    do {
        trocado = 0;
        ptr1 = inicio;

        while (ptr1->proxima != lptr) {
            /* Compara o nome da carreira atual com o nome da próxima carreira */
            if (strcmp(ptr1->carreira->nome, ptr1->proxima->carreira->nome) > 0) {
                /* Se estiverem fora de ordem, troca as carreiras de posição */
                trocaCarreiras(ptr1, ptr1->proxima);
                trocado = 1;
            }
            ptr1 = ptr1->proxima;
        }
        lptr = ptr1;
    } while (trocado);
}

/* Funções de Paragem */

/* Retorna um ponteiro para a Paragem, caso esta exista */
Paragem *encontraParagem(char *nome, Paragem **headParagens) {
    Paragem *p;
    for (p = *headParagens; p != NULL; p = p->proxima) {
        if (strcmp(p->nome, nome) == 0) {
            return p;
        }       
    }
    return NULL;
}

/* Retorna o numero de carreiras que passam na paragem recebida
como argumento */
int numCarreirasParagem(Paragem *paragem) {
    int count = 0;
    CarreiraNode *cn = paragem->carreiras;
    while (cn != NULL) {
        count++;
        cn = cn->proxima;
    }
    return count;
}

/* Imprime a informação relativa à paragem do argumento */
void infoParagem(char buffer[], Paragem **headP) {
    Paragem *Paragem;

    removerComandoDoBuffer(buffer);
    Paragem = encontraParagem(buffer, headP);
    if (Paragem == NULL){
        printf ("%s: no such stop.\n", buffer);
    }

    else {
        printf ("%16.12f %16.12f\n", Paragem->latitude,
                Paragem->longitude);
    }
}

/* Lista as paragens existentes */
void listaParagens(Paragem **headParagens) {
    Paragem* atual = *headParagens;
    while (atual != NULL) {
        int numCarreiras = numCarreirasParagem(atual);
        printf("%s: %16.12f %16.12f %d\n", atual->nome, atual->latitude, 
                atual->longitude, numCarreiras);
        atual = atual->proxima;
    }
}

/* Cria a Paragem com nome entre aspas */
void paragemComAspas(char buffer[], Paragem *novaParagem, Carreira **headC, 
                    Paragem **headP, Ligacao **headL) {
    char *latitude;
    int tamanho;
    tamanho = comprimentoPalavra(buffer);
    
    novaParagem->nome = (char*) malloc(sizeof(char) * (tamanho + 1));
    if (faltaMemoria(novaParagem->nome, headC, headP, headL)) { /* Verifica a memória */
        free(novaParagem);
        exit(0);
    }

    tirarPalavraEntreAspas(buffer, novaParagem->nome);

    if (encontraParagem(novaParagem->nome, headP) != NULL){
        printf ("%s: stop already exists.\n", novaParagem->nome);
        free(novaParagem->nome);
        free(novaParagem);
        return;
    }

    tamanho = comprimentoPalavra(buffer);
    latitude = (char*) malloc(sizeof(char) * (tamanho + 1));
    if (faltaMemoria(latitude, headC, headP, headL)) { /* Verifica a memória */
        free(novaParagem->nome);
        free(novaParagem);
        exit(0);
    }

    leProximaPalavra(latitude, buffer);
    novaParagem->latitude = atof(latitude);
    free(latitude);
    
    novaParagem->longitude = atof(buffer);

    novaParagem->carreiras = NULL;
    novaParagem->proxima = NULL;

    pushParagem(novaParagem, headP);
}

/* Cria uma nova Paragem e adiciona na lista */
void adicionaParagem(char buffer[], Carreira **headC, Paragem **headP,
                    Ligacao **headL) {
    Paragem *novaParagem = (Paragem*) malloc(sizeof(Paragem));
    if (faltaMemoria(novaParagem, headC, headP, headL)) { /* Verifica a memória */
        exit(0);
    }
    removerComandoDoBuffer(buffer);

    if (temAspas(buffer) == 1){
        paragemComAspas(buffer, novaParagem, headC, headP, headL);
    }
    
    else {
        char* latitude;
        int tamanho;
        tamanho = comprimentoPalavra(buffer);

        novaParagem->nome = (char*) malloc(sizeof(char) * (tamanho + 1));
        if (faltaMemoria(novaParagem->nome, headC, headP, headL)) { /* Verifica a memória */
            free(novaParagem);
            exit(0);
        }
        leProximaPalavra(novaParagem->nome, buffer);

        if (encontraParagem(novaParagem->nome, headP) != NULL){
            printf ("%s: stop already exists.\n", novaParagem->nome);
            free(novaParagem->nome);
            free(novaParagem);
            return;
        }

        tamanho = comprimentoPalavra(buffer);
        latitude = (char*) malloc(sizeof(char) * (tamanho + 1));
        if (faltaMemoria(latitude, headC, headP, headL)) { /* Verifica a memória */
            free(novaParagem->nome);
            free(novaParagem);
            exit(0);
        }

        leProximaPalavra(latitude, buffer);
        novaParagem->latitude = atof(latitude);
        free(latitude);
        
        novaParagem->longitude = atof(buffer);

        novaParagem->carreiras = NULL;
        novaParagem->proxima = NULL;

        pushParagem(novaParagem, headP);
    }
}

/* Consoante o número de argumentos, executa os comandos */
void comandoParagens(char buffer[], Carreira **headC, Paragem **headP,
                    Ligacao **headL) {

    int n = contaPalavras(buffer);

    if (n == 1){
        listaParagens(headP);
    }

    else if (n == 2){
        infoParagem(buffer, headP);
    }

    else if (n >= 4){
        adicionaParagem(buffer, headC, headP, headL);
    }

    else {
        printf ("Invalid comand: %s\n", buffer);
    }
}


/* Funções de Carreira */

/* Retorna um ponteiro para a Carreira, caso esta exista */
Carreira *encontraCarreira(char *nome, Carreira **headCarreiras) {
    Carreira *c;
    for (c = *headCarreiras; c != NULL; c = c->proxima) {
        if (strcmp(c->nome, nome) == 0) {
            return c;
        }       
    }
    return NULL;
}

/* Retorna o numero de paragens que passam por uma determinada carreira */
int numParagensCarreira(Carreira *carreira) {
    int numParagens = 0;
    ParagemNode *atual = carreira->paragens;

    while (atual != NULL) {
        numParagens++;
        atual = atual->proxima;
    }
    return numParagens;
}

/* Imprime as informações relativas à carreira, dada como argumento */
void mostraCarreiras(Carreira *carreira) {
    int numParagens = numParagensCarreira(carreira);
    ParagemNode *ultimaParagem = carreira->paragens;

    printf("%s ", carreira->nome);

    if (carreira->paragens != NULL) {
        printf("%s ", carreira->paragens->paragem->nome);
        
        while (ultimaParagem->proxima != NULL){
            ultimaParagem = ultimaParagem->proxima;
        }
        printf("%s ", ultimaParagem->paragem->nome);
    }
    printf("%d %.2f %.2f\n", numParagens, carreira->custo, carreira->duracao); 
}

/* Lista as Carreiras existentes */
void listaCarreiras(Carreira **headCarreiras) {
    Carreira *c = *headCarreiras;
    while (c != NULL) {
        mostraCarreiras(c);
        c = c->proxima;
    }
}

/* Imprime todas as Paragens pela ordem onde passa a carreira */
void infoCarreira(Carreira *carreira) {
    ParagemNode *noAtual = carreira->paragens;
    int numParagens = numParagensCarreira(carreira);

    if (noAtual == NULL) {
        return;
    }

    if (numParagens == 1) {
        printf("%s, %s", noAtual->paragem->nome, noAtual->paragem->nome);
    }
    
    else {
        while (noAtual != NULL) {
            printf("%s", noAtual->paragem->nome);
            noAtual = noAtual->proxima;

            if (noAtual != NULL) {
                printf(", ");
            }
        }
    }
    
    printf("\n");
}

/* Cria uma nova Carreira e adiciona no vetor global de Carreiras*/
void adicionaCarreira(char buffer[], Carreira **headC, Paragem **headP,
                    Ligacao **headL) {
    int tamanho;
    Carreira *novaCarreira = (Carreira*) malloc(sizeof(Carreira));
    if (faltaMemoria(novaCarreira, headC, headP, headL)) {
        exit(0);
    }
    
    tamanho = comprimentoPalavra(buffer);
    novaCarreira->nome = (char*) malloc(sizeof(char) * (tamanho + 1));
    if (faltaMemoria(novaCarreira->nome, headC, headP, headL)) {
        free(novaCarreira);
        exit(0);
    }
    
    strcpy(novaCarreira->nome, buffer);

    /* Inicialização das variáveis */
    novaCarreira->duracao = 0;
    novaCarreira->custo = 0;
    novaCarreira->paragens = NULL;
    novaCarreira->proxima = NULL;

    pushCarreira(novaCarreira, headC);
}

/* Verifica se a Carreira existe, se não existir cria uma nova, caso
contrário imprime as suas paragens */
void verificaCarreira(char buffer[], Carreira **headC, Paragem **headP,
                    Ligacao **headL) {

    Carreira *carreira;
    removerComandoDoBuffer(buffer);
    carreira = encontraCarreira(buffer, headC);

    if (carreira == NULL) {
        adicionaCarreira(buffer, headC, headP, headL);
    }

    else {
        infoCarreira(carreira);
    }
}

/* Verifica um potencial erro na abreviatura da palavra inverso */
int verificaErroInverso (char buffer[]) {
    int tamanho, condicao;
    char inverso[] = "inverso";

    tamanho = strlen(buffer);
    if (tamanho < 3 || tamanho > 7) {
        return 1;
    }

    /* Verifica se os caracteres até ao tamanho, são iguais */
    condicao = strncmp(inverso, buffer, tamanho);
    if (condicao != 0) {
        return 1;
    }
    
    return 0;
}

/* Lista as Paragens da Carreira por ordem inversa */
void listaParagensInverso(Carreira *carreira) {
    ParagemNode *atual = carreira->paragens;

    /* Percorrer a lista de paragens até chegar ao fim */
    while (atual->proxima != NULL) {
        atual = atual->proxima;
    }

    /* Agora que estamos no fim, vamos dar print de todas as paragens em ordem inversa */
    while (atual != NULL) {
        printf("%s", atual->paragem->nome);

        if (atual->anterior != NULL) {
            printf(", ");
        }

        atual = atual->anterior;
    }
    printf("\n");
}

/* Imprime as Paragens da Carreira por ordem inversa */
void inversoInfoCarreira(char buffer[], Carreira **headC, Paragem **headP,
                        Ligacao **headL) {
    Carreira *carreira;
    int tamanho;
    char *nome;

    removerComandoDoBuffer(buffer);

    tamanho = comprimentoPalavra(buffer);
    nome = (char*) malloc(sizeof(char) * (tamanho + 1));
    if (faltaMemoria(nome, headC, headP, headL)) { /* Verifica a memória */
        exit(0);
    }

    leProximaPalavra(nome, buffer);

    carreira = encontraCarreira(nome, headC);
    if (carreira == NULL) {
        return;
    }

    if (verificaErroInverso(buffer)) {
        printf ("incorrect sort option.\n");
    }

    else {
        listaParagensInverso(carreira);
    }
}

/* Consoante o número de argumentos, executa os comandos */
void comandoCarreiras(char buffer[], Carreira **headC, Paragem **headP,
                    Ligacao **headL) {

    int n = contaPalavras(buffer);

    if (n == 1) {
        listaCarreiras(headC);
    }

    else if (n == 2) {
        verificaCarreira(buffer, headC, headP, headL);
    }

    else if (n == 3) {
        inversoInfoCarreira(buffer, headC, headP, headL);
    }

    else {
        printf ("Invalid comand: %s\n", buffer);
    }
}


/* Funções de Ligação */

/* Cria a primeira Ligação */
void primeiraLigacao (Ligacao *ligacao, Carreira *carreira, Paragem *paragem1, 
                    Paragem *paragem2, Carreira **headC, Paragem **headP, 
                    Ligacao **headL) {
    pushParagemNode(carreira, paragem1, headC, headP, headL);
    pushParagemNode(carreira, paragem2, headC, headP, headL);
    pushCarreiraNode(carreira, paragem1, headC, headP, headL);
    pushCarreiraNode(carreira, paragem2, headC, headP, headL);

    carreira->custo += ligacao->custo;
    carreira->duracao += ligacao->duracao;

    pushLigacao(ligacao, headL);
}

/* Cria as Ligacoes */
void criaLigacao(Ligacao *ligacao, Carreira **headC, Paragem **headP, 
                Ligacao **headL) {
    /* Obtem os ponteiros da carreira e das paragens */
    Carreira *carreira = encontraCarreira(ligacao->carreiraNome, headC);
    Paragem *paragem1 = encontraParagem(ligacao->paragem1, headP);
    Paragem *paragem2 = encontraParagem(ligacao->paragem2, headP);
    ParagemNode *ultimaParagem = carreira->paragens;

    if (carreira->paragens == NULL) {
        primeiraLigacao(ligacao, carreira, paragem1, paragem2,
                    headC, headP, headL);
        return;
    }

    /* Obter a ultima paragem por onde passa a carreira */
    while (ultimaParagem->proxima != NULL) {
        ultimaParagem = ultimaParagem->proxima;
    }

    /* Verifica qual dos dois possíveis inputs foi colocado */
    if (!strcmp(paragem1->nome, ultimaParagem->paragem->nome)) {
        pushParagemNode(carreira, paragem2, headC, headP, headL);
        pushCarreiraNode(carreira, paragem2, headC, headP, headL);
    }

    else {
        pushParagemNodeInicio(carreira, paragem1, headC, headP, headL);
        pushCarreiraNode(carreira, paragem1, headC, headP, headL);
    }

    /* Incremento do custo e duração */
    carreira->custo += ligacao->custo;
    carreira->duracao += ligacao->duracao;

    pushLigacao(ligacao, headL);
}

/* Verifica um potencial erro na criação de uma ligação */
int erroLigacao(Carreira *carreira, Paragem *paragem1, Paragem *paragem2) {
    /* Obter a ultima paragem por onde passa a carreira */
    ParagemNode *ultimaParagem = carreira->paragens;
    while (ultimaParagem->proxima != NULL) {
        ultimaParagem = ultimaParagem->proxima;
    }
    /* As duas únicas possiblidades de input para se formar uma ligação */
    if (!strcmp(paragem1->nome, ultimaParagem->paragem->nome) ||
        !strcmp(paragem2->nome, carreira->paragens->paragem->nome)){
        return 0;
    }
    return 1;
}

/* Verifica um potencial erro nos valores do custo e duração */
int erroValoresNegativos(float custo, float duracao) {
    if (custo < 0 || duracao < 0) {
        return 1;
    }
    return 0;
}

/* Retira os argumentos necessários para criar as ligações e verifica
potenciais erros na criação destas */
void comandoLigacoes(char buffer[], Carreira **headC, Paragem **headP, 
                    Ligacao **headL) {
    Paragem *paragem1, *paragem2;
    Carreira *carreira;
    char *valor;
    int numLigacoes, tamanho;
    
    Ligacao *ligacao = (Ligacao*) malloc(sizeof(Ligacao));
    if (faltaMemoria(ligacao, headC, headP, headL)) { /* Verifica a memória */
        exit(0);
    }

    removerComandoDoBuffer(buffer);

    tamanho = comprimentoPalavra(buffer);
    ligacao->carreiraNome = (char*) malloc(sizeof(char) * (tamanho + 1));
    if (faltaMemoria(ligacao->carreiraNome, headC, headP, headL)) { /* Verifica a memória */
        free(ligacao);
        exit(0);
    }

    leProximaPalavra(ligacao->carreiraNome, buffer);

    carreira = encontraCarreira(ligacao->carreiraNome, headC);
    if (carreira == NULL) {
        printf ("%s: no such line.\n", ligacao->carreiraNome);
        free(ligacao->carreiraNome);
        free(ligacao);
        return;
    }

    /* Verifica se o nome da 1ªparagem está entre aspas */

    if (temAspas(buffer)) {
        tamanho = comprimentoPalavra(buffer);
        ligacao->paragem1 = (char*) malloc(sizeof(char) * (tamanho + 1));
        if(faltaMemoria(ligacao->paragem1, headC, headP, headL)) { /* Verifica a memória */
            free(ligacao->carreiraNome);
            free(ligacao);
            exit(0);
        }

        tirarPalavraEntreAspas(buffer, ligacao->paragem1);
    }

    else {
        tamanho = comprimentoPalavra(buffer);
        ligacao->paragem1 = (char*) malloc(sizeof(char) * (tamanho + 1));
        if (faltaMemoria(ligacao->paragem1, headC, headP, headL)) {
            free(ligacao->carreiraNome);
            free(ligacao);
            exit(0);
        }

        leProximaPalavra(ligacao->paragem1, buffer);
    }

    paragem1 = encontraParagem(ligacao->paragem1, headP);
    if (paragem1 == NULL) {
        printf ("%s: no such stop.\n", ligacao->paragem1);
        free(ligacao->carreiraNome);
        free(ligacao->paragem1);
        free(ligacao);
        return;
    }

    /* Verifica se o nome da 2ªparagem está entre aspas */
    if (temAspas(buffer)) {
        tamanho = comprimentoPalavra(buffer);
        ligacao->paragem2 = (char*) malloc(sizeof(char) * (tamanho + 1));
        if (faltaMemoria(ligacao->paragem2, headC, headP, headL)) {
            free(ligacao->carreiraNome);
            free(ligacao->paragem1);
            free(ligacao);
            exit(0);
        }

        tirarPalavraEntreAspas(buffer, ligacao->paragem2);
    }

    else {
        tamanho = comprimentoPalavra(buffer);
        ligacao->paragem2 = (char*) malloc(sizeof(char) * (tamanho + 1));
        if (faltaMemoria(ligacao->paragem2, headC, headP, headL)) {
            free(ligacao->carreiraNome);
            free(ligacao->paragem1);
            free(ligacao);
            exit(0);
        }

        leProximaPalavra(ligacao->paragem2, buffer);
    }

    paragem2 = encontraParagem(ligacao->paragem2, headP);
    if (paragem2 == NULL) {
        printf ("%s: no such stop.\n", ligacao->paragem2);
        free(ligacao->carreiraNome);
        free(ligacao->paragem1);
        free(ligacao->paragem2);
        free(ligacao);
        return;
    }

    /* Custo e duração */ 
    tamanho = comprimentoPalavra(buffer);
    valor = (char*) malloc(sizeof(char) * (tamanho +1));    
    if (faltaMemoria(valor, headC, headP, headL)) { /* Verifica a memória */
        free(ligacao->carreiraNome);
        free(ligacao->paragem1);
        free(ligacao->paragem2);
        free(ligacao);
        exit(0);
    }

    leProximaPalavra(valor, buffer);
    ligacao->custo = atof(valor);
    free(valor);

    tamanho = comprimentoPalavra(buffer);
    valor = (char*) malloc(sizeof(char) * (tamanho +1));
    if (faltaMemoria(valor, headC, headP, headL)) { /* Verifica a memória */
        free(ligacao->carreiraNome);
        free(ligacao->paragem1);
        free(ligacao->paragem2);
        free(ligacao);
        exit(0);
    }

    leProximaPalavra(valor, buffer);
    ligacao->duracao = atof(valor);
    free(valor);

    /* Verifica se os valores são negativos */
    if (erroValoresNegativos(ligacao->custo, ligacao->duracao)) {
        printf ("negative cost or duration.\n"); 
        free(ligacao->carreiraNome);
        free(ligacao->paragem1);
        free(ligacao->paragem2);
        free(ligacao);
        return;
    }

    numLigacoes = numParagensCarreira(carreira);
    /* Verfica se a ligação pode ser feita */
    if (numLigacoes != 0 && 
        erroLigacao(carreira, paragem1, paragem2)) {                        
        printf ("link cannot be associated with bus line.\n");
        free(ligacao->carreiraNome);
        free(ligacao->paragem1);
        free(ligacao->paragem2);
        free(ligacao);
        return;
    }
    
    ligacao->proxima = NULL;

    criaLigacao(ligacao, headC, headP, headL);  
}


/* Funções Interseções */

/* Imprime as Interseções */
void mostrarIntersecoes (Paragem *paragem) {
    CarreiraNode *carreiraAtual = paragem->carreiras;
    while (carreiraAtual != NULL) {
        printf("%s", carreiraAtual->carreira->nome);
        if (carreiraAtual->proxima != NULL) {
            printf(" ");
        } else {
            printf("\n");
        }
        carreiraAtual = carreiraAtual->proxima;
    }
}

/* Comando Interseções */
void comandoIntersecoes(Paragem **headParagens) {
    Paragem *paragemAtual = *headParagens;
    while (paragemAtual != NULL) {
        /* Número de carreiras que passam nesta paragem */
        int numCarreiras = numCarreirasParagem(paragemAtual);
        /* Se houver mais do que uma carreira, imprime */
        if (numCarreiras > 1) {
            printf("%s %d: ", paragemAtual->nome, numCarreiras);
            /* Ordena a lista de Carreiras da paragem atual*/
            bubbleSort(paragemAtual->carreiras); 
            /* Imprime as carreiras ordenadas */
            mostrarIntersecoes(paragemAtual);
        }
        paragemAtual = paragemAtual->proxima;
    }
}
