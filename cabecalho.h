/* iaed-23 - ist1102879 - project2
 * 
 * Ficheiro: cabecalho.c
 * Autor: António Dias da Silva
 * Descição: Estruturas, variáveis e funções utilizadas no projeto   
*/

#ifndef CABECALHO_H
#define CABECALHO_H


/* Variáveis úteis */

#define BUFFER_SIZE 65536       /* Tamanho do "buffer" */

#define DENTRO 1                /* Estado: dentro */
#define FORA 0                  /* Estado: fora */

/* Tipos de Dados */

/* Carreira */
typedef struct Carreira{
    char *nome;    
    double custo;
    double duracao;
    struct ParagemNode *paragens;
    struct Carreira *proxima;
} Carreira;

/* Lista Ligada de Carreiras da Estrutura de Paragem */
typedef struct CarreiraNode {
    Carreira *carreira;
    struct CarreiraNode *proxima;
} CarreiraNode;

/* Paragem */
typedef struct Paragem{
    char *nome;
    double latitude;
    double longitude;
    struct CarreiraNode *carreiras;
    struct Paragem *proxima;
} Paragem;

/* Lista Ligada de Paragens da Estrutura de Carreira */
typedef struct ParagemNode {
    Paragem *paragem;
    struct ParagemNode *proxima;
    struct ParagemNode *anterior;
} ParagemNode;

/* Ligação */
typedef struct Ligacao{
    char *carreiraNome;
    char *paragem1;
    char *paragem2;
    double custo;
    double duracao;
    struct Ligacao *proxima;
} Ligacao;

/* Funções de Leitura */

void lePalavraAteFimDeLinha(char str[]);
void leProximaPalavra(char str[], char buffer[]);

/* Funções de eliminação de dados */

void apagarDadosCarreiras(Carreira **headCarreiras);
void apagarDadosParagens(Paragem **headParagens);
void apagarDadosLigacoes(Ligacao **headLigacao);
void apagaTodosOsDados(Carreira **headC, Paragem **headP, Ligacao **headL);

/* Funções auxiliares */

int contaPalavras(char buffer[]);
void removerComandoDoBuffer(char buffer[]);
int temAspas(char buffer[]);
int faltaMemoria(void *ponteiro, Carreira **headC, Paragem **headP, Ligacao **headL);
int comprimentoPalavra(char buffer[]);

/* Funções de Ordenação */

void trocaCarreiras(CarreiraNode *a, CarreiraNode *b);
void bubbleSort(CarreiraNode *inicio);

/* Funções de Paragem */

Paragem *encontraParagem(char *nome, Paragem **headParagens);
int numCarreirasParagem(Paragem *paragem);
void infoParagem(char buffer[], Paragem **headP);
void listaParagens(Paragem **headParagens);
void pushParagem(Paragem *paragem, Paragem **headParagens);
void paragemComAspas(char buffer[], Paragem *novaParagem, Carreira **headC, 
                    Paragem **headP, Ligacao **headL);
void adicionaParagem(char buffer[], Carreira **headC, Paragem **headP,
                    Ligacao **headL);

/* Funções de Carreira */

Carreira *encontraCarreira(char *nome, Carreira **headCarreiras);
int numParagensCarreira(Carreira *carreira);
void mostraCarreiras(Carreira *carreira);
void listaCarreiras(Carreira **headCarreiras);
void infoCarreira(Carreira *carreira);
void pushCarreira(Carreira *carreira, Carreira **headCarreiras);
void adicionaCarreira(char buffer[], Carreira **headC, Paragem **headP,
                    Ligacao **headL);
void verificaCarreira(char buffer[], Carreira **headC, Paragem **headP,
                    Ligacao **headL);
int verificaErroInverso (char buffer[]);
void listaParagensInverso(Carreira *carreira);
void inversoInfoCarreira(char buffer[], Carreira **headC, Paragem **headP,
                        Ligacao **headL);


/* Funções de Ligação */

void pushLigacao(Ligacao *ligacao, Ligacao **headLigacao);
void pushCarreiraNode(Carreira *carreira, Paragem *paragem, Carreira **headC,
                    Paragem **headP, Ligacao **headL);
void pushParagemNodeInicio(Carreira *carreira, Paragem *paragem, Carreira **headC,
                        Paragem **headP, Ligacao **headL);
void pushParagemNode(Carreira *carreira, Paragem *paragem, Carreira **headC, 
                    Paragem **headP, Ligacao **headL);
void primeiraLigacao (Ligacao *ligacao, Carreira *carreira, Paragem *paragem1, 
                    Paragem *paragem2, Carreira **headC, Paragem **headP, 
                    Ligacao **headL);
void criaLigacao(Ligacao *ligacao, Carreira **headC, Paragem **headP, 
                Ligacao **headL);
int erroLigacao(Carreira *carreira, Paragem *paragem1, Paragem *paragem2);
int erroValoresNegativos(float custo, float duracao);


/* Funções das Interseções */

void mostrarIntersecoes (Paragem *paragem);


/* Funções para remover carreiras */ 

void popCarreira(Carreira *carreira, Carreira **headCarreiras);
void removeCarreiraDeParagem(Carreira *carreira, Paragem *paragem);
void limpaParagensDeCarreira(Carreira *carreira);
int carreiraEstaNaParagem(Carreira *carreira, Paragem *paragem);


/* Funções para eliminar paragens */

Ligacao *encontraLigacao(char *carreiraNome, char *paragem, int modo,
                        Ligacao **headLigacao);
void popParagem (Paragem *paragem, Paragem **headParagens);
int verificaSeEExtremo (Carreira *carreira, Paragem *paragem);
void popLigacao(Ligacao *ligacao, Ligacao **headLigacao);
void removeTodasCarreirasDeParagem(Paragem *paragem);
void removeParagemDeCarreira(ParagemNode *pn, Carreira *carreira);


/* Funções de eliminação de dados */

void apagarDadosCarreiras(Carreira **headCarreiras);
void apagarDadosParagens(Paragem **headParagens);
void apagarDadosLigacoes(Ligacao **headLigacao);


/* Funções da main */

void comandoParagens(char buffer[], Carreira **headC, Paragem **headP,
                    Ligacao **headL);
void comandoCarreiras(char buffer[], Carreira **headC, Paragem **headP,
                    Ligacao **headL);
void comandoLigacoes(char buffer[], Carreira **headC, Paragem **headP, 
                    Ligacao **headL);
void comandoIntersecoes(Paragem **headParagens);
void removerCarreira(char buffer[], Carreira **headCarreiras, Paragem **headParagens);
void eliminaParagem(char buffer[], Paragem **headP, Ligacao **headL);
void apagaTodosOsDados(Carreira **headC, Paragem **headP, Ligacao **headL);


#endif
