/************************************************
**Universidade do Estado de Mato Grosso- UNEMAT *
**Curso: Bacharel. Ciencia da Computa��o        *
**Disciplina: Etrutura de Dados II              *
**Prof. Me. D�rley Domingos de Almeida          *
**Aluno: Uilliam Pereira de Oliveira            *
************************************************/

#include <stdio.h>
#include <stdlib.h>

/*
---------------------Declara��o de Struct de nossa arvore-----------------------
*/
typedef struct aux
{
	int chave;
	struct aux *esq, *dir;
} NO;

typedef NO* PONT;

/*
---------------------  fun��es que ser�o utilizadas  -------------------------
*/

PONT  inicializa();
PONT adciona(PONT raiz, PONT no);
void menu();
PONT CriaNovoNo (PONT chave);
int numeroNos(PONT raiz);
void Imprimir(PONT raiz);
PONT contem (int ch, PONT raiz);
PONT buscaNo(PONT raiz, int ch, PONT *pai);
PONT removeNO (PONT raiz, int ch);
void printnode (int c, int b);
void desenho(PONT raiz, int b);
int Folhas(PONT raiz);
void posOrdem(PONT raiz);
void preOrdem(PONT raiz);
void emOrdem(PONT raiz);
int altura(PONT raiz);
void menu();


/*
---------------------      Inicializa nossa arvore     -------------------------
*/

//essa fun��o � responsavel por inicializar de fato nosa arvore, retonando um NULL
PONT  inicializa()
{
	return (NULL);
}
/*
---------------------        Fun��o principal          -------------------------
*/
int main()
{
	menu();
	system("pause");
	return 0;
}

/*
---------------------adciona novo/primeiro n� na arvore-------------------------
*/

PONT adciona(PONT raiz, PONT no)
{
	if (raiz == NULL)//se a raiz for NULL, nao tem nada l�, entao inserirmos na raiz
	{
		return(no);
	}
	if(no->chave < raiz->chave)//inserindo sem permitir chaves duplicadas/iguais
	{
		raiz->esq = adciona(raiz->esq, no);//se a chave inserida � menor que a raiz
	}
	else
	{
		raiz->dir = adciona(raiz->dir, no);//se a chave inserida � maior que a raiz
	}
	return(raiz);
}

PONT CriaNovoNo (int ch)
{
	PONT NovoNo = (PONT) malloc(sizeof(NO));//aloca espa�o na memoria para nossa arvore

	if ((NovoNo = (PONT) malloc(sizeof(NO))) == NULL)//se s�o houver espa�o retorna uma mensagem
	{
		printf("\n\tSem memoria disponivel\n\n");
	}
	else
	{
		//caso d� certo a aloca��o, inserimos nossa primeira chave
		//fazendo ele apontar para nulo em ambos os lados.
		NovoNo->chave = ch;
		NovoNo->esq = NULL;
		NovoNo->dir = NULL;


	}
	return (NovoNo);
}
/*
---------------------contar numero de n�s --------------------------------------
*/

int numeroNos(PONT raiz)
{
	if(!raiz)//se nao houver nada na raiz da arvore, retorna zero
	{
		return 0;
	}
	//caso tenha, retorna o numero de n�s da esquerda + 1 (da raiz) + numero de n�s da direita
	return (numeroNos(raiz->esq) + 1 + numeroNos(raiz->dir));
}

/*
---------------------o imprimir/exibir arvore completa--------------------------
*/

void Imprimir(PONT raiz)
{
	if(raiz != NULL)//se raiz for diferente de NULL
	{
		printf("%d", raiz->chave);//imprime a raiz
		printf("(");//Adciona um parenteses
		Imprimir(raiz->esq);//anda na casa da esquerda procurando n�s e adcionando parenteses
		Imprimir(raiz->dir);//anda na casa da direita procurando n�s e adcionando parenteses
		printf(")");//quando acabar de ir para esquerda/direita fecha parenteses
	}
}

/*
---------------------- Impress�o desenhada da arvore  --------------------------
*/
void desenho(PONT raiz, int b)
{
	if(raiz == NULL)//essa parte aqui estava dandoo uma treta, ent�o preferi retirar
		//mas ela fazia o seguinte, onde era NULL, era pra imprimir um asteristico
	{
		//printnode('*', b);
		return;
	}
	desenho(raiz->dir, b + 1);//imprime os n�s da direita antecipando de tracinhos
	printnode(raiz->chave, b);//imprimi n� raiz 
	desenho(raiz->esq, b + 1);//imprime os n�s da esquerda antecipando de tracinhos
}

void printnode (int chave, int b)//essa fun��o auxiliar ajuda no desenho, imprimindo os tracinhos
{
	int i;
	for(i = 0; i < b; i++)
	{
		printf("---");
	}
	printf("%i\n", chave);

}
/*
---------------------Buscar chave pesquisada na arvore--------------------------
*/
PONT contem (int ch, PONT raiz)//Buscar n�s na arvore
{
	if(raiz == NULL)//se a raiz for NULL, n�o h� nada 
	{
		return (NULL);//retorna NULL
	}
	if(raiz->chave == ch)//se a chave procurada for igual ao valor da raiz
	{
		return (raiz);//retorna o valor da raiz
	}
	if(raiz->chave > ch)//se a raiz for menor que a chave procurada
	{
		return contem(ch, raiz->esq);//ele verifica a esqueda da raiz

	}
	return contem(ch, raiz->dir);//ou ele verifica a direita da raiz

}

/*
Busca binaria nao recursiva. Devolve o ponteiro do n� buscado.
Abastece pai com o ponteiro para o pai n� deste.
*/ 

PONT buscaNo(PONT raiz, int ch, PONT *pai)//metodo auxiliar que busca um no com determinada chave,
//caso ache, guarda o valor em *pai
{
	PONT atual = raiz;// cria um ponteiro auxiliar qu lev o valor da raiz
	*pai = NULL;//pai revebe valor NULL

	while(atual)//enquanto este ponteiro for valido
	{
		if (atual->chave == ch)//se o ponteiro for igual a chave buscada
		{
			return(atual);//retorna ele
		}
		*pai = atual;//e o pai j� recebe este valor achado

		if (ch < atual->chave)//sen�o repito o processo com a esquerda e a direita
		{
			atual = atual->esq;
		}
		else
		{
			atual = atual->dir;
		}
	}
	return (NULL);//se procurei em todos e n�o encontrei, retorna NULL
}

// chegamos na parte mair dificil do codigo.....

PONT removeNO (PONT raiz, int ch)
{
	PONT pai, no, p, q;
	no = buscaNo (raiz, ch, &pai);//primeiro busca o n� que procuramos, e abaste�o "pai" com seu endere�o

	if (no == NULL)//se o n� buscado for NULL, retorna a raiz e n�o remove nada
	{
		return (raiz);
	}
	if (!no->esq || !no->dir)//aqui h� o teste para ver se o no que estamos mechendo
                             //possui somente um filho
	{
		if(!no->esq)//caso n�o tenha filho na esquerda
		{
			q = no->dir;
		}
		else//caso contrario
		{
			q = no->esq;
		}
	}
	else//caso nosso no a ser removido tenha dois filhos
	{
		p = no;// "p" recebe "n�"
		q = no->esq;// e "q" recebe o filho da esquerda do n�
		
		while(q->dir)//este la�o serve para percorre o mais a direita possivel e um n�
		{
			p = q;//enquanto houver filhos na direita, "p" recebe "q"
			q = q->dir;// e "q" recebe o filho da direita de "q"
		}
		if(p != no)//aqui testamos se o n� "pa"i � diferente do "no" que queremos remover
		{
			p->dir = q->esq;//caso sim, o "lado" direitro de "p" assume/recebe o filho da esquerda de "q"
			q->esq = no->esq;//conctamos o lado esquerdo de "q" no filho da esuqerda de "n�"
			// dessa forma estaremos as devidas conex�es com os filhos do n� retirado
		}
		q->dir = no->dir;//e o lado direito de "q" recebe o filho da esquerda de nosso n� a ser removido
	}
	if(!pai)// aqui testamos se estamo mexendo com o n� pai
	{
		free(no);
		return (q);
	}
	if(ch < pai->chave)//aqui testamos/verificamos se estamos modificando o lado direito ou esquerdo da arvore
	{
		pai->esq = q;//o "pai" receber� o n� "q" q assumir� sua nova posi��o na arvore
	}
	else
	{
		pai->dir = q;//o "pai" receber� o n� "q" q assumir� sua nova posi��o na arvore
		free(no);//aqui de fato � que excluimos/liberamos o n� que queriamos remover
	}
	return(raiz);

}
/*
---------------------- Impress�o -----------------------------------------------
*/
void emOrdem(PONT raiz)
{
	if (raiz != NULL)
	{
		emOrdem(raiz->esq);
		printf("\n%d", raiz->chave);
		emOrdem(raiz->dir);

	}
}

void preOrdem(PONT raiz)
{
	if (raiz != NULL)
	{
		printf("\n%d", raiz->chave);
		preOrdem(raiz->esq);
		preOrdem(raiz->dir);

	}
}

void posOrdem(PONT raiz)
{
	if (raiz != NULL)
	{
		posOrdem(raiz->esq);
		posOrdem(raiz->dir);
		printf("\n%d", raiz->chave);

	}
}
/*
---------------------- contagem das folhas -------------------------------------
*/
int Folhas(PONT raiz)
{
	if(raiz == NULL)// se for NULL, n�o h� nada em nossa arvore
	{
		return 0;
	}
	if (raiz->esq == NULL && raiz->dir == NULL)//� cada teste de n�s com ambos os lados nuleos,
	// positivo ele retorna 1
	{
		return 1;
	}
	return Folhas(raiz->esq) + Folhas(raiz->dir);//no final ele retorna a quantidade de n�s folhas em ambos os lados
}
/*
----------------------       Altura da arvore        ---------------------------
*/

int altura(PONT raiz)
{
	int e, d;
	if (raiz == NULL)
	{
		return 1;
	}
	e = altura (raiz->esq);
	d = altura(raiz->dir);
	if ( e > d)
	{
		return e + 1;
	}
	else
	{
		return d + 1;
	}
}


void menu()
{
	int ch, escolha;
	PONT r = inicializa();
	PONT nova;
	system("color f0");

	do
	{
		printf("\n 1 - Adcionar No");
		printf("\n 2 - Buscar No");
		printf("\n 3 - Contagem de Nos");
		printf("\n 4 - Exibir Arvore");
		printf("\n 5 - Remover No");
		printf("\n ===============");
		printf("\n 6 - Exibicao Em Ordem");
		printf("\n 7 - Exibicao Pre_Ordem");
		printf("\n 8 - Exibicao Pos_Ordem");
		printf("\n ===============");
		printf("\n 9 - Contar Folhas");
		printf("\n 10 - Altura da Arvore");
		printf("\n ===============");
		printf("\n 0 - Sair\n");
		printf("\n\tEscolha: ");
		scanf("%d", &escolha);
		system("cls");
		switch(escolha)
		{
		case 1:
		{
			printf("\nDigite um valor inteiro: ");
			fflush(stdin);
			scanf("%d", &ch);
			PONT no = CriaNovoNo (ch);
			r = adciona(r, no);
			printf("\n");
			system("pause");
			system("cls");
		}
		break;
		case 2:
		{
			printf("\nDigite um valor a ser procurado: ");
			fflush(stdin);
			scanf("%d", &ch);
			PONT p = contem(ch, r);
			if ((p != NULL) && ( ch == p->chave))
			{
				printf("\n\tChave [%d] localizada\n" , p->chave);
			}
			else
			{
				printf("\n\tNao existe a chave solicitada");
			}
			printf("\n");
			system("pause");
			system("cls");
		}
		break;
		case 3:
			printf("\n\tPossui: [%d] Nos cadastrados nessa Arvore Binaria\n\n" , numeroNos(r));
			system("pause");
			system("cls");
			break;
		case 4:
			printf("\n\tImpressao parenteseada\n\n");
			Imprimir(r);
			printf("\n\n");
			printf("\n\tImpressao diferenciada\n\n");
			desenho(r, 0);
			printf("\n\n");
			system("pause");
			system("cls");
			break;
		case 5:
		{
			printf("\nDigite o valor a ser deletado: ");
			fflush(stdin);
			scanf("%d", &ch);
			nova = contem(ch, r);
			if( ch == nova->chave)
			{
				removeNO (r, ch);

				printf("\nO no: [%d] foi removido\n" , ch);

			}
			else
			{
				printf("\nValor n�o encontrado na Avore\n");
			}

			printf("\n");
			system("pause");
			system("cls");
		}
		break;
		case 6:
			printf("\n\tExibicao dos elementos da Arvore EM ORDEM \n\n Inciciando do menor valor digitado\n");
			emOrdem(r);
			printf("\n\n");
			system("pause");
			system("cls");
			break;
		case 7:
			printf("\n\tExibicao dos elementos da Arvore em PRE ORDEM \n\n Inciciando do valor da RAIZ\n");
			preOrdem(r);
			printf("\n\n");
			system("pause");
			system("cls");
			break;
		case 8:
			printf("\n\tExibicao dos elementos da Arvore em POS ORDEM \n\n Inciciando dos valores da ESQUERDA\n");
			posOrdem(r);
			printf("\n\n");
			system("pause");
			system("cls");
			break;
		case 9:
			printf("\nContagem das FOLHAS de nossa Arvore\n");
			printf("\n\tPossui: [%d] Folhas", Folhas(r));
			printf("\n\n");
			system("pause");
			system("cls");
			break;
		case 10:
			printf("\n\tAltura da arvore\n\n");
			printf("\t A arvore tem profundidade [%d]", altura(r));
			printf("\n\n");
			system("pause");
			system("cls");
			break;
		case 0:
			printf("\n..........saindo.........\n");
			break;
		default:
			printf("\nOpcao invalida\n");
			break;
		}
	}
	while(escolha != 0);
}
