#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TAM_ENDERECO 40
#define TAM_NOME 30
#define TAM_EMAIL 60
#define TAM_PROFISSAO 21
#define TAM_CPF 12
#define T 5
#define MAX_CONTATOS 9	//Quantidade máxima de contatos (2 * T - 1)
#define MAX_FILHOS 10 	//Quantidade máxima de filhos (2 * T)
#define MIN_OCUP 4		//Ocupação mínima em cada nó (T - 1)

#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600
#define MAX 500
#define MIN 250


typedef enum boolean {
    TRUE = 1, FALSE = 0
}Bool;

typedef enum{ANULADO,CRIAR,BUSCAR,LISTAGEM,DIFERENCIAL};
typedef enum{ANULADO1,ALFABETICA,LETRA,TELEFONE,BUSCARID,BUSCARNOME,IDADE,QUALQUER,ESPECIFICA,REMOVER};

typedef int BoolDelete;

typedef struct data{
	int dia;
	int mes;
	int ano;
}Data;

typedef struct contato{
	int id;
	int fone_comercial;
    int fone_residencial;
    char nome[TAM_NOME];
    char profissao[TAM_PROFISSAO];
    char endereco[TAM_ENDERECO];
    char email[TAM_EMAIL];
    char cpf[TAM_CPF];
    Data dataNascimento;
}Contato;

typedef struct no_arvoreB arvoreB;

struct no_arvoreB{
	int numContatos;					//Quantidades de contatos contidos no nó
	Contato contatos[MAX_CONTATOS];		//Contatos armazenados no nó
	arvoreB *filhos[MAX_FILHOS];		//Ponteiro para os filhos
};

int buscaID(arvoreB *no, int infoId);
int buscaNome(arvoreB *no, Contato info);
Contato buscaContatoPorID(arvoreB *no, int info);
Contato buscaContatoPorNome(arvoreB *no, char nome[]);
void insereContatoID (arvoreB *arvB, Contato info, arvoreB *filhoDir);
void insereContatoNome (arvoreB *arvB, Contato info, arvoreB *filhoDir);
arvoreB *insereID(arvoreB *arvB, Contato info, Bool *h, Contato *infoRetorno);
arvoreB *insereNome(arvoreB *arvB, Contato info, Bool *h, Contato *infoRetorno);
arvoreB *insereArvoreBID(arvoreB *arvB, Contato info);
arvoreB *insereArvoreBNome(arvoreB *arvB, Contato info);
void listarEmOrdem(arvoreB *arvB);
void listarPorLetra(arvoreB *arvB, char letra);
void listarPorData(arvoreB *arvB,int dia, int mes, int ano,int tipo,int idade,int *encontrou);
void listarSeTelefoneTrab(arvoreB *arvB);
void listarContatoPorID(arvoreB *arvB);
void listarContatoPorNome(arvoreB *arvB);
void gravaRegistro (Contato c,char arquivo[]);
void gravaArvore(arvoreB *arvB,char arquivo[]);
arvoreB* carregaArvore(int param);
int criarArvore();
arvoreB *Delete(int target, arvoreB *root);
BoolDelete RecDelete(int target,arvoreB *p);
BoolDelete SeqSearch(int target,arvoreB *p, int *k);
void Remove(arvoreB *p,int k);
void Successor(arvoreB *p, int k);
void Restore(arvoreB *p, int k);
void Combine(arvoreB *p,int k);
void MoveLeft(arvoreB *p,int k);
void MoveRight(arvoreB *p,int k);
