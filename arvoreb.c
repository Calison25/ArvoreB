#include "main.h"

int step = 0;

void start(int param){
	int encontrou, dia, mes, ano, idade, id;
	char letra;
	arvoreB* a1 = NULL;
	Contato aux;
	encontrou = 0;

	a1 = carregaArvore(param);

	switch(param){
        case ALFABETICA:{
            listarEmOrdem(a1);
            break;
        }
        case LETRA:{
            printf("\n\tInforme uma letra\n");
            printf("\n\t\t");
            scanf("%c",&letra);
            fflush(stdin);
            listarPorLetra(a1,letra);
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
            printf("\n\tInforme uma idade\n");
            printf("\n\t\t");
            scanf("%d",&idade);
            fflush(stdin);
            printf("\n");

            listarPorData(a1,0,0,0,IDADE,idade,&encontrou);
            if(!encontrou){
              printf("\n\tIdade nao encontrada\n");
            }
            break;
        }
        case ESPECIFICA:{
            printf("\n\tVoce selecionou data especifica");

            printf("\n\tInforme o dia");
            printf("\n\t\t");
            scanf("%d",&dia);
            fflush(stdin);
            printf("\n");

            printf("\n\tInforme o mes");
            printf("\n\t\t");
            scanf("%d",&mes);
            fflush(stdin);
            printf("\n");

            printf("\n\tInforme o ano");
            printf("\n\t\t");
            scanf("%d",&ano);
            fflush(stdin);
            printf("\n");

            listarPorData(a1,dia,mes,ano,ESPECIFICA,0,&encontrou);
            if(!encontrou){
              printf("\n\tData nao encontrada\n");
            }
            break;
        }
        case QUALQUER:{
            printf("\n\tInforme um dia, ou um mês, ou um ano que o programa irá te retornar se alguma dessas existir\n");

            printf("\n\tInforme o dia\n");
            printf("\n\t\t");
            scanf("%d",&dia);
            fflush(stdin);
            printf("\n");

            printf("\n\tInforme o mes\n");
            printf("\n\t\t");
            scanf("%d",&mes);
            fflush(stdin);
            printf("\n");

            printf("\n\tInforme o ano\n");
            printf("\n\t\t");
            scanf("%d",&ano);
            fflush(stdin);
            printf("\n");

            listarPorData(a1,dia,mes,ano,QUALQUER,0,&encontrou);
            if(!encontrou){
              printf("\n\tData nao encontrada\n");
            }
            break;
        }
        case REMOVER:{
            printf("\n\tInforme o ID do usuario\n");
            printf("\n\t\t");
            scanf("%d",&id);
            fflush(stdin);
            a1 = Delete(id,a1);
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
	strcpy(contMeio.nome,"");
	contMeio.id = 0;
	meio = 0;
    fflush(stdin);
    fflush(stdout);
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
    strcpy(c.nome,"");
    c.id = 0;

	strcpy(c.nome, nome);
    fflush(stdin);
    fflush(stdout);
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
			printf("\n\tContato ja contido na arvore\n");
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
			printf("\n\tContato ja contido na arvore\n");
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
	fflush(stdin);

	c = buscaContatoPorID(arvB, ident);

	if(c.id > 1000 || c.id < 0){
       c.id = 0;
	}

	if (c.id == 0 || c.id != ident){
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
    strcpy(c.nome,"");
    c.id = 0;

	printf("\n\t Informe o nome do contato:\n\t\t");
	gets(nom);
	c = buscaContatoPorNome(arvB, nom);

	if(c.id > 1000 || c.id < 0){
        c.id = 0;
	}

	if (c.id == 0 || (strcmp(c.nome,nom) > 0) ){
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

void gravaRegistro (Contato c,char arquivo[]){
	FILE *fp;
	Contato aux = c;

	fp = fopen(arquivo, "ab");
	if(fp!=NULL){
		fwrite(&aux, sizeof(Contato), 1, fp);
		fclose(fp);
	}
	else{
		printf("\n\tErro na abertura do arquivo\n");
	}
}

void gravaArvore(arvoreB *arvB,char arquivo[]){
	int i;
	if (arvB != NULL){
		for (i = 0; i < arvB->numContatos; i++){
			gravaArvore(arvB->filhos[i],arquivo);
			gravaRegistro(arvB->contatos[i],arquivo);
		}
		gravaArvore(arvB->filhos[i],arquivo);
	}
}

arvoreB* carregaArvore(int param){
	FILE *fp;
	int result, i;
	arvoreB* a1 = NULL;
	Contato aux;
	result = 0;

    if(param == BUSCARID || param == REMOVER){
        fp = fopen("ARVOREID", "rb");
    }else{
        fp = fopen("ARVORENOME", "rb");
    }

	if(fp!=NULL){
		for(i=0;i<1000;i++){
			result+=fread (&aux, sizeof(Contato), 1, fp);
			if(param == BUSCARID || param == REMOVER){
                a1 = insereArvoreBID(a1, aux);
            }else{
                a1 = insereArvoreBNome(a1, aux);
            }
		}
		fclose(fp);
	}
	else{
		printf("\n\tErro na abertura do arquivo\n");
	}

	printf("\n\tNro de elementos lidos: %d\n", result);

	return a1;
}

int criarArvore(){
	FILE *fp;
	int result, i;
	arvoreB* aNome = NULL;
	arvoreB* aID = NULL;
	Contato aux;

	fp = fopen("AGENDA", "rb");

	if (fp!=NULL){
		for(i=0;i<1000;i++){
			result+=fread (&aux, sizeof(Contato), 1, fp);
			aNome = insereArvoreBNome(aNome, aux);
			aID = insereArvoreBID(aID, aux);
		}
		fclose(fp);
	}
	else{
		printf("\n\tErro na abertura do arquivo");
		return 0;
	}

	printf("\n\t ************ AGENDA *************");

	gravaArvore(aNome,"ARVORENOME");
	gravaArvore(aID,"ARVOREID");

	return 1;
}

/* Delete: deletes the key target from the B-tree with the given root */
arvoreB *Delete(int target, arvoreB *root)
{
   arvoreB *p,*t;      /* used to dispose of an empty root */

   t = root;
   if (!RecDelete(target, t))
     printf("\n\tTarget was not in the B-tree.\n");
   else
     if (root->numContatos == 0) {  /*root is empty. */
       p = root;
       root = root->filhos[0];
       free(p);
     }
  return root;
}

/*RecDelete: look for target to delete*/
BoolDelete RecDelete(int target,arvoreB *p)
{
  int k;  /* location of target or of branch on which to search*/
  BoolDelete found;
  printf("\n\t RECDELETE ID: %d", target);

  if (p == NULL)
    return FALSE;    /*Hitting an empty tree is an error */
  else{
       found = SeqSearch(target,p,&k);//procura se esta no nó atual
       if (found)
         if (p->filhos[k-1]){     /* test for NULL??? */
           Successor(p,k);  /*replaces key[k] by its successor*/
           if (!(found = RecDelete(p->contatos[k].id,p->filhos[k])))
             /* We know that the new key[k] is in the leaf. */
             printf("\n\tKey not found.\n");
         }else
              Remove(p,k); /*removes key from position k of *p */
      else                 /*Target was not found in current node.*/
           found = RecDelete(target,p->filhos[k]);//se nao estiver desce para um filho de acordo com o resultado de k que vem da função seqSearch
      /* At this point, the function has returned from a recursive call.*/
      if (p->filhos[k] != NULL)
        if (p->filhos[k]->numContatos < MIN)
          Restore(p,k);
      return found;
     }
}

BoolDelete SeqSearch(int target,arvoreB *p, int *k)
{
  if (target < p->contatos[0].id) {
    *k = 0;
    return FALSE;
  }
   else {
       /* Sequential Search */
       *k = p->numContatos;
       while ((target < p->contatos[*k].id) && *k > 1){
        (*k)--;
         step++;
       }
       return (target == p->contatos[*k].id);
	}
}

/* Remove: removes key[k] and branch[k] from *p */ //so chama remove quando ta na raiz
void Remove(arvoreB *p,int k)
{
  int i;  /* index to move entries */
  for (i=k+1; i <= p->numContatos; i++){
  	    printf("\n\t REMOVE KEY[I-1]]: %s KEY[I]:%s",p->contatos[i-1].nome, p->contatos[i].nome);

    p->contatos[i-1] = p->contatos[i];
	getch();
    p->filhos[i-1] = p->filhos[i];
  }
  p->numContatos--;
}

void Successor(arvoreB *p, int k)
{
  arvoreB *q;  /* used to move down the tree to a leaf */
  for (q = p->filhos[k]; q->filhos[0]; q = q->filhos[0])
    ;
  p->contatos[k] = q->contatos[1];
}

void Restore(arvoreB *p, int k)
{
  if (k == 0)                /* case: leftmost key */
    if (p->filhos[1]->numContatos >MIN)
      MoveLeft(p,1);
    else
      Combine(p,1);
  else if (k == p->numContatos)    /* case: rightmost key */
    if (p->filhos[k-1]->numContatos >MIN)
      MoveRight(p,k);
    else
      Combine(p,k);

  else if (p->filhos[k-1]->numContatos > MIN) /*remaining cases */
         MoveRight(p,k);
  else if (p->filhos[k+1]->numContatos > MIN)
         MoveLeft(p,k+1);
  else
      Combine(p,k);
}

/* MoveRight: move a key to the right. */
void MoveRight(arvoreB *p,int k)
{
  int c;
  arvoreB *t;

  t = p->filhos[k];
  for (c = t->numContatos; c>0; c--){
  /* Shift all keys in the right node one position. */
     t->contatos[c+1] = t->contatos[c];
     t->filhos[c+1]=t->filhos[c];
  }
  t->filhos[1] = t->filhos[0];  /* Move key from parent to right node. */
  t->numContatos++;
  t->contatos[1] = p->contatos[k];
  t = p->filhos [k-1];  /* Move last key of left node into parent. */
  p->contatos[k] = t->contatos[t->numContatos];


  p->filhos[k]->filhos[0] = t->filhos[t->numContatos];
  t->numContatos--;
}

void MoveLeft(arvoreB *p,int k)
{
  int c;
  arvoreB *t;

  /*Move key from parent into left node. */
  t = p->filhos[k-1];
  t->numContatos++;
  t->contatos[t->numContatos] = p->contatos[k];
  t->filhos[t->numContatos] = p->filhos[k]->filhos[0];

  /* Move key from right node into parent. */
  t = p->filhos[k];
  p->contatos[k] = t->contatos[1];
  t->filhos[0] = t->filhos[1];
  t->numContatos--;
  for (c = 1; c <= t->numContatos; c++){
    /* Shift all keys in right node one position leftward. */
    t->contatos[c] = t->contatos[c+1];
    t->filhos[c] = t->filhos[c+1];
  }
}

/* Combine: combine adjacent nodes. */
void Combine(arvoreB *p,int k)
{
    int c;
    arvoreB *q; /*points to the right nodei, which will be emptied and deleted*/
    arvoreB *l;

    q = p->filhos[k];
    l = p->filhos[k-1];  /* Work with the left node. */
    l->numContatos++;          /* Insert the key from the parent. */
    l->contatos[l->numContatos] = p->contatos[k];
    l->filhos[l->numContatos] = q->filhos[0];
    for (c=1; c <= q->numContatos; c++){  /* Insert all keys from right node. */
    l->numContatos++;
    l->contatos[l->numContatos] = q->contatos[c];
    l->filhos[l->numContatos] = q->filhos[c];
    }
    for (c=k; c<p->numContatos; c++){ /* Delete key from parent node. */
    p->contatos[c] = p->contatos[c+1];
    p->filhos[c] = p->filhos[c+1];
    }
    p->numContatos--;
    free(q);    /* Dispose of the empty right node. */
}
