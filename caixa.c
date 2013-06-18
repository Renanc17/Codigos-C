#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <time.h>
typedef struct elemento {
  char *nome;
	int status;
	time_t tempoFila;
	time_t tempoAtend;
	time_t tempoTotal;
	struct elemento *prox;

} no;

no *inicio, *novo, *final, *aux, *aux1;
int criado = 0;
//----------protótipos------

void insere();
void imprimir();
void imprimirDoFinal();
void comprimento();
//void excluirInicio();
//void insmeio(no*t, int x);
//void remmeio(no*t);
//void removeFim();

//-------------Função criar----------

void criar() {
	inicio = final = NULL;
	criado = 1;
	printf("\n Fila Iniciada\n\n");
}

main() {

	char i;
	int ax, auxinf;
	criar();
	while (i != '\n') {
		printf(" (1)-Iniciar atendimento\n");
		printf(" (2)-Insere na fila \n");
		printf(" (3)-Imprime a fila\n");
		printf(" (4)-Imprime a lista ao contrario\n");
		printf(" (5)-Imprime o comprimento da lista\n");
//		printf(" (5)-Retira um elemento do inicia da lista\n");
//		printf(" (6)-Insere no interior da lista\n");
//		printf(" (7)-Insere no fim da lista\n");
//		printf(" (8)-Remove no fim da lista\n");
//		printf(" (9)-Remove no interior da lista\n");
		printf(" (S)-Sair\n");
		i = getch();

		switch (i) {

		case '1':
			getch();
			system("cls");
			break;

		case '2':
			insere();
			break;

		case '3':
			imprimir();
			getch();
			system("cls");
			break;

		case '4':
			imprimirDoFinal();
			getch();
			system("cls");
			break;

		case '5':
			comprimento();
			break;

//		case '6':
//
//			aux = inicio;
//			printf("Digite o valor a ser encontrado");
//			scanf("%d", &auxinf);
//			printf("Digite o valor a ser inserido");
//			scanf("%d", &ax);
//			while (aux != NULL ) {
//				if (aux->info == auxinf) {
//					insmeio(aux, ax);
//					break;
//				}
//				aux = aux->prox;
//			}
//			break;

//		case '7':
//			insereFim();
//			break;
//
//		case '8':
//			removeFim();
//			break;

//		case '9':
//
//			aux = inicio;
//			printf("Digite o valor a ser removido");
//			scanf("%d", &ax);
//			while (aux != NULL ) {
//				if (aux->info == ax) {
//					remmeio(aux);
//					break;
//				}
//				aux = aux->prox;
//			}
//			break;

		case 'S':
		case 's':
			exit(0);
		}

	}
}

//------------imprime------------

void imprimir() {
	aux = inicio;

	if (aux != NULL ) {
		while (aux != NULL ) {
			printf("%s", aux->nome);
			printf(" - ");
			//printf("%d\t", aux->status);
			//printf("|||");
//			printf("%s\t", asctime(localtime(aux->tempoTotal)));
			aux = aux->prox;
		}
		printf("\n\n");
	} else
		printf("Lista Vazia");

	printf("\n");
}

void imprimirDoFinal() {
	aux = inicio;
	aux1 = final;

	if (aux != NULL ) {
		while (aux1 != inicio) {
			while (aux->prox != aux1) {
				aux = aux->prox;
			}

			printf("%s|", aux1->nome);
			printf("%d\t", aux1->status);
			aux1 = aux;
			aux = inicio;
		}
		printf("%s|", inicio->nome);
		printf("%d", inicio->status);
		printf("\n\n");
	} else
		printf("Lista Vazia");

	printf("\n");
}

//----------- tamanho------------

void comprimento() {
	int cont = 0;
	aux = inicio;
	while (aux != NULL ) {
		cont++;
		aux = aux->prox;
	}

	printf("\nO tamanho da lista eh: %d", cont);
	getch();
	system("cls");
}

//--------retira inicio----------

/*void excluirInicio() {
	if (inicio != NULL ) {

		aux = inicio;
		inicio = aux->prox;
//		printf("\nValor a ser excluido %d", aux->info);
		free(aux);
		getch();
		system("cls");
	} else {
		printf("Lista Vazia");
		getch();
		system("cls");
	}
}*/

void insere() {
    char *nome = (char*) malloc(100);
    int status;
   	time_t tempoAtual;

	if (criado == 1) {
		printf("Entre com o nome do cliente:\n");
		scanf("%s", nome);

		printf("O cliente eh preferencial? (1 - SIM | 2 - NAO) \n");
		scanf("%i", &status);

		novo = (no *) malloc(sizeof(no));
		novo->nome = nome;
		novo->status = status;

		if (inicio == NULL ) {
			inicio = final = novo;
			novo->prox = NULL;
        }else{
            if(novo->status == 1) {
                if(inicio->status == 1 && final->status == 1) { //insere um preferencial em uma lista que só exista preferenciais (insere no fim)
                    final->prox = novo;
                    novo->prox = NULL;
                    final = novo;
                } else if(inicio->status == 2){ //insere um preferencial em uma lista que só exista não-preferenciais (insere no inicio)
                    novo->prox = inicio;
                    inicio = novo;
                } else if(inicio->status == 1 && final->status == 2){ //insere um preferencial em uma lista que exista ambos os tipos (insere no meio)
                    aux=inicio;
                    while(aux->prox->status == 1){
                    aux=aux->prox;
                    }
                    novo->prox = aux->prox;
                    aux->prox = novo;
                }
            } else{ // insere um não-preferencial em uma lista (insere no fim)
              final->prox = novo;
              novo->prox = NULL;
              final = novo;
              }

}
	} else {
		printf("Crie a lista primeiro\n");
		getch();
	}

	system("cls");
}

/*void removeFim() {
	if (inicio != NULL ) {

		aux = inicio;
		if (inicio != final) {
			while (aux->prox != final)
				aux = aux->prox;

//			printf("\nValor a ser excluido %d", final->info);
			free(final);
			final = aux;
			final->prox = NULL;
		} else {
//			printf("\nValor a ser excluido %d", final->info);
			free(final);
			inicio = final = NULL;
		}
		getch();
		system("cls");
	} else {
		printf("Lista Vazia");
		getch();
		system("cls");
	}
}*/
