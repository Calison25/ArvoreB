#include "main.h"

void start(int param){
    FILE *fp;
	int result, i, encontrou, dia, mes, ano,idade;
	arvoreB* a1 = NULL;
	Contato aux;
	encontrou = 0;

	a1 = carregaArvore();

	switch(param){
        case ALFABETICA:{
            listarEmOrdem(a1);
            break;
        }
        case LETRA:{
            listarPorLetra(a1,'Z');
            break;
        }
        case TELEFONE:{
            listarSeTelefoneTrab(a1);
            break;
        }
        case BUSCARNOME:{
            listarContatoPorNome(a1);
            break;
        }
        case BUSCARID:{
            listarContatoPorID(a1);
            break;
        }
        case IDADE:{
            printf("Informe uma idade");
            printf("\n");
            scanf("%d",&idade);
            fflush(stdin);
            printf("\n");

            listarPorData(a1,0,0,0,IDADE,idade,&encontrou);
            if(!encontrou){
              printf("\nIdade nao encontrada\n");
            }
            break;
        }
        case ESPECIFICA:{
            printf("\nVocê selecionou data especifica");

            printf("\nInforme o dia");
            printf("\n");
            scanf("%d",&dia);
            fflush(stdin);
            printf("\n");

            printf("\nInforme o mes");
            printf("\n");
            scanf("%d",&mes);
            fflush(stdin);
            printf("\n");

            printf("\nInforme o ano");
            printf("\n");
            scanf("%d",&ano);
            fflush(stdin);
            printf("\n");

            listarPorData(a1,dia,mes,ano,ESPECIFICA,0,&encontrou);
            if(!encontrou){
              printf("\nData nao encontrada\n");
            }
            break;
        }
        case QUALQUER:{
            printf("\nInforme um dia, ou um mês, ou um ano que o programa irá te retornar se alguma dessas existir\n");

            printf("\nInforme o dia\n");
            printf("\n");
            scanf("%d",&dia);
            fflush(stdin);
            printf("\n");

            printf("\nInforme o mes\n");
            printf("\n");
            scanf("%d",&mes);
            fflush(stdin);
            printf("\n");

            printf("\nInforme o ano\n");
            printf("\n");
            scanf("%d",&ano);
            fflush(stdin);
            printf("\n");

            listarPorData(a1,dia,mes,ano,QUALQUER,0,&encontrou);
            if(!encontrou){
              printf("\nData nao encontrada\n");
            }
            break;
        }
	}

}


// Busca por ID
int buscaID(arvoreB *no, int infoId) {
	Contato contMeio;
	int meio, i, f;
	i = 0;
	f = no->numContatos-1;

	while (i <= f){
		meio = (i + f)/2;
		contMeio = no->contatos[meio];
		if (contMeio.id == infoId){
			return(meio); //Encontrou. Retorna a posição em que o contato está.
		}
		else if (contMeio.id > infoId){
			f = meio - 1;
		}
		else if (contMeio.id < infoId){
			i = meio + 1;
		}
	}
	return(i); //Não encontrou. Retorna a posição do ponteiro para o filho.
}

// Busca por Nome
int buscaNome(arvoreB *no, Contato info) {
	Contato contMeio;
	int meio, i, f;
	i = 0;
	f = no->numContatos-1;
	while (i <= f){
		meio = (i + f)/2;
		contMeio = no->contatos[meio];
		if ( (strcmp(contMeio.nome,info.nome) == 0) ){
			return(meio); //Encontrou. Retorna a posição em que o contato está.
		}
		else if ( (strcmp(contMeio.nome,info.nome) > 0) ){
			f = meio - 1;
		}
		else if ( (strcmp(contMeio.nome,info.nome) < 0) ){
			i = meio + 1;
		}
	}
	return(i); //Não encontrou. Retorna a posição do ponteiro para o filho.
}

// Busca Contato por ID
Contato buscaContatoPorID(arvoreB *no, int info){
	int pos; //posição retornada pelo busca binária.

	while (no != NULL){
		pos = buscaID(no, info);
		if (pos < no->numContatos && no->contatos[pos].id == info){
			return no->contatos[pos];
		}
		else{
			no = no->filhos[pos];
		}
	}
}

// Busca Contato por Nome
Contato buscaContatoPorNome(arvoreB *no, char nome[]){
	int pos; //posição retornada pelo busca binária.
	Contato c;

	strcpy(c.nome, nome);

	while (no != NULL){
		pos = buscaNome(no, c);
		if (pos < no->numContatos && (strcmp(no->contatos[pos].nome, nome) == 0)){
			return no->contatos[pos];
		}
		else{
			no = no->filhos[pos];
		}
	}
}

//Insere um contato e o ponteiro para o filho da direita em um nó
void insereContatoID (arvoreB *arvB, Contato info, arvoreB *filhoDir){
	int x, pos;

	//busca para obter a posição ideal para inserir o novo contato
	pos = buscaID(arvB, info.id);
	x = arvB->numContatos;

	//realiza o remanejamento para manter os contatos ordenados
	while ((x > pos) && (info.id = arvB->contatos[x-1].id)){
		arvB->contatos[x] = arvB->contatos[x-1];
		arvB->filhos[x+1] = arvB->filhos[x];
    	x--;
	}

	//insere o contato na posição ideal
	arvB->contatos[pos] = info;
  	arvB->filhos[pos+1] = filhoDir;
  	arvB->numContatos++;
}

void insereContatoNome (arvoreB *arvB, Contato info, arvoreB *filhoDir){
	int x, pos;

	//busca para obter a posição ideal para inserir o novo contato
	pos = buscaNome(arvB, info);
	x = arvB->numContatos;

	//realiza o remanejamento para manter os contatos ordenados
	while ((x > pos) && (strcmp(info.nome, arvB->contatos[x-1].nome) == -1)){
		arvB->contatos[x] = arvB->contatos[x-1];
		arvB->filhos[x+1] = arvB->filhos[x];
    	x--;
	}
	//insere o contato na posição ideal
	arvB->contatos[pos] = info;
  	arvB->filhos[pos+1] = filhoDir;
  	arvB->numContatos++;
}

//Realiza a busca do nó para inserir o contato e faz as subdivisões quando necessárias
arvoreB *insereID(arvoreB *arvB, Contato info, Bool *h, Contato *infoRetorno){
	int i,pos;
	Contato infoMediano; //auxiliar para armazenar o contato que irá subir para o pai
	arvoreB *temp, *filhoDir; //ponteiro para o filho direita do contato
	Contato infoNULL;

	if (arvB == NULL){
	//O nó anterior é o ideal para inserir o novo contato (chegou em um nó folha)
		*h = TRUE;
		*infoRetorno = info;
		return(NULL);
	}
	else {
		pos = buscaID(arvB, info.id);
		if ((arvB->numContatos > pos) && (arvB->contatos[pos].id = info.id)){
			printf("Contato ja contido na arvore");
			*h = FALSE;
		}
		else {
		//desce na árvore até encontrar o nó folha para inserir o contato.
			filhoDir = insereID(arvB->filhos[pos],info,h,infoRetorno);
			if (*h){
			//Se true deve inserir a infoRetorno no nó.
				if (arvB->numContatos < MAX_CONTATOS){
				//Tem espaço na página
					insereContatoID(arvB, *infoRetorno, filhoDir);
					*h = FALSE;
				}
				else {
				//Overflow. Precisa subdividir
					temp = (arvoreB *) malloc (sizeof(arvoreB));
					temp->numContatos = 0;

					//inicializa filhos com NULL
					for (i = 0; i < MAX_FILHOS; i++){
						temp->filhos[i] = NULL;
					}

					//elemento mediano que vai subir para o pai
					infoMediano = arvB->contatos[MIN_OCUP];

					//insere metade do nó arvB no temp (efetua subdivisão)
					temp->filhos[0] = arvB->filhos[MIN_OCUP+1];

					for (i = MIN_OCUP + 1; i < MAX_CONTATOS; i++){
						insereContatoID(temp, arvB->contatos[i], arvB->filhos[i+1]);
					}

					//atualiza nó arvB.
					for (i = MIN_OCUP; i<MAX_CONTATOS; i++){
						arvB->contatos[i] = infoNULL;
						arvB->filhos[i+1] = NULL;
					}

					arvB->numContatos = MIN_OCUP;

					//Verifica em qual nó será inserida o novo contato
					if (pos <= MIN_OCUP){
						insereContatoID(arvB, *infoRetorno, filhoDir);
					}
					else{
						insereContatoID(temp, *infoRetorno, filhoDir);
					}

					//retorna o mediano para inserí-lo no nó pai e o temp como filho direito do mediano.
					*infoRetorno = infoMediano;
					return(temp);
				}
			}
		}
	}
}

arvoreB *insereNome(arvoreB *arvB, Contato info, Bool *h, Contato *infoRetorno){
	int i, pos;
	Contato infoMediano; //auxiliar para armazenar o contato que irá subir para o pai
	arvoreB *temp, *filhoDir; //ponteiro para o filho direita do contato
	Contato infoNULL;

	if (arvB == NULL){
	//O nó anterior é o ideal para inserir o novo contato (chegou em um nó folha)
		*h = TRUE;
		*infoRetorno = info;
		return(NULL);
	}
	else {
        pos = buscaNome(arvB, info);
		if ((arvB->numContatos > pos) && (strcmp(arvB->contatos[pos-1].nome,info.nome) == 0)){
			printf("Contato ja contido na arvore");
			*h = FALSE;
		}
		else {
		//desce na árvore até encontrar o nó folha para inserir o contato.
			filhoDir = insereNome(arvB->filhos[pos],info,h,infoRetorno);
			if (*h){
			//Se true deve inserir a infoRetorno no nó.
				if (arvB->numContatos < MAX_CONTATOS){
				//Tem espaço na página
					insereContatoNome(arvB, *infoRetorno, filhoDir);
					*h = FALSE;
				}
				else {
				//Overflow. Precisa subdividir
					temp = (arvoreB *) malloc (sizeof(arvoreB));
					temp->numContatos = 0;

					//inicializa filhos com NULL
					for (i = 0; i < MAX_FILHOS; i++){
						temp->filhos[i] = NULL;
					}

					//elemento mediano que vai subir para o pai
					infoMediano = arvB->contatos[MIN_OCUP];

					//insere metade do nó arvB no temp (efetua subdivisão)
					temp->filhos[0] = arvB->filhos[MIN_OCUP+1];

					for (i = MIN_OCUP + 1; i < MAX_CONTATOS; i++){
						insereContatoNome(temp, arvB->contatos[i], arvB->filhos[i+1]);
					}

					//atualiza nó arvB.
					for (i = MIN_OCUP; i<MAX_CONTATOS; i++){
						arvB->contatos[i] = infoNULL;
						arvB->filhos[i+1] = NULL;
					}

					arvB->numContatos = MIN_OCUP;

					//Verifica em qual nó será inserida o novo contato
					if (pos <= MIN_OCUP){
						insereContatoNome(arvB, *infoRetorno, filhoDir);
					}
					else{
						insereContatoNome(temp, *infoRetorno, filhoDir);
					}

					//retorna o mediano para inserí-lo no nó pai e o temp como filho direito do mediano.
					*infoRetorno = infoMediano;
					return(temp);
				}
			}
		}
	}
}

arvoreB *insereArvoreBID(arvoreB *arvB, Contato info){
	Bool h;
	int i;
	Contato infoRetorno;
	arvoreB *filhoDir, *novaArvB;

	filhoDir = insereID(arvB,info,&h,&infoRetorno);
	if (h){
	//Aumentará a altura da árvore
		novaArvB = (arvoreB *) malloc (sizeof(arvoreB));
		novaArvB->numContatos = 1;
		novaArvB->contatos[0] = infoRetorno;
		novaArvB->filhos[0] = arvB;
		novaArvB->filhos[1] = filhoDir;
		for (i = 2; i <= MAX_CONTATOS; i++){
			novaArvB->filhos[i] = NULL;
		}
		return(novaArvB);
	}
	else{
		return(arvB);
	}
}

arvoreB *insereArvoreBNome(arvoreB *arvB, Contato info){
	Bool h;
	int i;
	Contato infoRetorno;
	arvoreB *filhoDir, *novaArvB;

	filhoDir = insereNome(arvB,info,&h,&infoRetorno);
	if (h){
	//Aumentará a altura da árvore
		novaArvB = (arvoreB *) malloc (sizeof(arvoreB));
		novaArvB->numContatos = 1;
		novaArvB->contatos[0] = infoRetorno;
		novaArvB->filhos[0] = arvB;
		novaArvB->filhos[1] = filhoDir;
		for (i = 2; i <= MAX_CONTATOS; i++){
			novaArvB->filhos[i] = NULL;
		}
		return(novaArvB);
	}
	else{
		return(arvB);
	}
}

void listarEmOrdem(arvoreB *arvB){
	int i;
	if (arvB != NULL){
		for (i = 0; i < arvB->numContatos; i++){
			listarEmOrdem(arvB->filhos[i]);
			printf("\n\t %d => %s - %d/%d/%d\n", arvB->contatos[i].id, arvB->contatos[i].nome, arvB->contatos[i].dataNascimento.dia,arvB->contatos[i].dataNascimento.mes,arvB->contatos[i].dataNascimento.ano);
		}
		listarEmOrdem(arvB->filhos[i]);
	}
}

void listarPorLetra(arvoreB *arvB, char letra){
	int i;
	if (arvB != NULL){
		for (i = 0; i < arvB->numContatos; i++){
			listarPorLetra(arvB->filhos[i], letra);
			if(arvB->contatos[i].nome[0] == letra){
                printf("\n\t %d => %s - %d\n", arvB->contatos[i].id, arvB->contatos[i].nome, arvB->contatos[i].fone_comercial);
			}
		}
		listarPorLetra(arvB->filhos[i], letra);
	}
}

void listarPorData(arvoreB *arvB,int dia, int mes, int ano,int tipo,int idade, int *encontrou){
	int i,idadeContato;
	if (arvB != NULL){
		for (i = 0; i < arvB->numContatos; i++){
			listarPorData(arvB->filhos[i], dia,mes,ano,tipo,idade,&(*encontrou));
			if(tipo == QUALQUER){
              if( (arvB->contatos[i].dataNascimento.dia == dia) || (arvB->contatos[i].dataNascimento.mes == mes) || (arvB->contatos[i].dataNascimento.ano == ano)){
                (*encontrou) = 1;
                printf("\n\t %d => %s - %d - %d/%d/%d\n", arvB->contatos[i].id, arvB->contatos[i].nome, arvB->contatos[i].fone_comercial,arvB->contatos[i].dataNascimento.dia,arvB->contatos[i].dataNascimento.mes,arvB->contatos[i].dataNascimento.ano);
              }
			}else if(tipo == ESPECIFICA){
              if( (arvB->contatos[i].dataNascimento.dia == dia) && (arvB->contatos[i].dataNascimento.mes == mes) && (arvB->contatos[i].dataNascimento.ano == ano)){
                (*encontrou) = 1;
                printf("\n\t %d => %s - %d - %d/%d/%d \n", arvB->contatos[i].id, arvB->contatos[i].nome, arvB->contatos[i].fone_comercial,arvB->contatos[i].dataNascimento.dia,arvB->contatos[i].dataNascimento.mes,arvB->contatos[i].dataNascimento.ano);
              }
			}else if(tipo == IDADE){
              idadeContato = 2016 - arvB->contatos[i].dataNascimento.ano;
              if( idade == idadeContato){
                (*encontrou) = 1;
                printf("\n\t %d => %s - %d - %d/%d/%d \n", arvB->contatos[i].id, arvB->contatos[i].nome, arvB->contatos[i].fone_comercial,arvB->contatos[i].dataNascimento.dia,arvB->contatos[i].dataNascimento.mes,arvB->contatos[i].dataNascimento.ano);
              }
			}
		}
		listarPorData(arvB->filhos[i], dia,mes,ano,tipo,idade,&(*encontrou));
	}
}

void listarSeTelefoneTrab(arvoreB *arvB){
	int i;
	if (arvB != NULL){
		for (i = 0; i < arvB->numContatos; i++){
			listarSeTelefoneTrab(arvB->filhos[i]);
			if(arvB->contatos[i].fone_comercial != 0){
                printf("\n\t %d => %s - %d\n", arvB->contatos[i].id, arvB->contatos[i].nome, arvB->contatos[i].fone_comercial);
			}
		}
		listarSeTelefoneTrab(arvB->filhos[i]);
	}
}

void listarContatoPorID(arvoreB *arvB){
	int ident;
	Contato c;

	printf("\n\t Informe o ID do contato:\n\t\t");
	scanf("%d", &ident);

	c = buscaContatoPorID(arvB, ident);
	if (c.id == 0){
		printf("\n\tContato nao existe!");
	}
	else{
		printf("\n\t ******* Dados do Contato **********");
		printf("\n\t Id: %d", c.id);
		printf("\n\t Nome: %s", c.nome);
		printf("\n\t Telefone Comercial: %d", c.fone_comercial);
		printf("\n\t Telefone Residencial: %d", c.fone_residencial);
		printf("\n\t CPF: %s", c.cpf);
		printf("\n\t Endereco: %s", c.endereco);
		printf("\n\t Email: %s", c.email);
		printf("\n\t Profissao: %s", c.profissao);
		printf("\n\t Data Nascimento: %d/%d/%d", c.dataNascimento.dia, c.dataNascimento.mes, c.dataNascimento.ano);
	}
}

void listarContatoPorNome(arvoreB *arvB){
	char nom[TAM_NOME];
	Contato c;

	printf("\n\t Informe o nome do contato:\n\t\t");
	gets(nom);

	c = buscaContatoPorNome(arvB, nom);
	if (c.id == 0){
		printf("\n\tContato nao existe!");
	}
	else{
		printf("\n\t ******* Dados do Contato **********");
		printf("\n\t Id: %d", c.id);
		printf("\n\t Nome: %s", c.nome);
		printf("\n\t Telefone Comercial: %d", c.fone_comercial);
		printf("\n\t Telefone Residencial: %d", c.fone_residencial);
		printf("\n\t CPF: %s", c.cpf);
		printf("\n\t Endereco: %s", c.endereco);
		printf("\n\t Email: %s", c.email);
		printf("\n\t Profissao: %s", c.profissao);
		printf("\n\t Data Nascimento: %d/%d/%d", c.dataNascimento.dia, c.dataNascimento.mes, c.dataNascimento.ano);
	}
}

void gravaRegistro (Contato c){
	FILE *fp;
	Contato aux = c;

	fp = fopen("ARVORE", "ab");
	if(fp!=NULL){
		fwrite(&aux, sizeof(Contato), 1, fp);
		fclose(fp);
	}
	else{
		printf("Erro na abertura do arquivo");
	}
}

void gravaArvore(arvoreB *arvB){
	int i;
	if (arvB != NULL){
		for (i = 0; i < arvB->numContatos; i++){
			gravaArvore(arvB->filhos[i]);
			gravaRegistro(arvB->contatos[i]);
		}
		gravaArvore(arvB->filhos[i]);
	}
}

arvoreB* carregaArvore(){
	FILE *fp;
	int result, i;
	arvoreB* a1 = NULL;
	Contato aux;

	fp = fopen("ARVORE", "rb");

	if(fp!=NULL){
		for(i=0;i<1000;i++){
			result+=fread (&aux, sizeof(Contato), 1, fp);
			a1=insereArvoreBNome(a1, aux);
		}
		fclose(fp);
	}
	else{
		printf("Erro na abertura do arquivo");
	}

	printf("\nNro de elementos lidos: %d\n", result);

	return a1;
}

int criarArvore(){
	FILE *fp;
	int result, i;
	arvoreB* a1 = NULL;
	Contato aux;

	fp = fopen("AGENDA", "rb");

	if (fp!=NULL){
		for(i=0;i<1000;i++){
			result+=fread (&aux, sizeof(Contato), 1, fp);
			a1=insereArvoreBNome(a1, aux);
		}
		fclose(fp);
	}
	else{
		printf("Erro na abertura do arquivo");
		return 0;
	}

	printf("\n\t ************ AGENDA *************");

	gravaArvore(a1);

	return 1;
}
