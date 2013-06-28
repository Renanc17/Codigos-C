#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <time.h>

typedef struct elemento {
  char *nome;
  int status;
	time_t tempoEntradaFila;
	time_t tempoChegadaCaixa;
	time_t tempoSaida;
	struct elemento *prox;
} no;

no *inicio, *novo, *final, *aux, *aux1;
int criado = 0;
time_t tempoFila, tempoAtendimento,tempoTotal;
struct tm * fila,* atendimento,* total;
//----------protÃ³tipos------

void insere();
void imprimir();
void imprimirDoFinal();
void comprimento();
void atender();

//-------------FunÃ§Ã£o criar----------

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
		printf(" (S)-Sair\n\n");
		i = getch();

		switch (i) {

		case '1':
            if(inicio == NULL)
            printf("Fila Vazia!");
            else
            atender();       
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

		case 'S':
		case 's':
			exit(0);
		 default:
           system("cls");
		}
       
        
	}
}

//------------imprime------------

void imprimir() {
	aux = inicio;
    int pos = 0;
	if (aux != NULL ) {
		while (aux != NULL ) {
			printf("%d - %s - ", ++pos, aux->nome);
			if(aux->status == 1)
			printf("Preferencial\n");
			else
			printf("Normal\n");
			aux = aux->prox;
		}
		printf("\n\n");
	} else
		printf("Lista Vazia");

	printf("\n");
}

void imprimirDoFinal() {
	aux = inicio;
	int pos = 1;
	if (aux != NULL ) {
    	while(aux->prox != NULL){
        	pos++;
        	aux = aux->prox;
        }
    }
	aux=inicio;
	aux1 = final;

	if (aux != NULL ) {
		while (aux1 != inicio) {
			while (aux->prox != aux1) {
				aux = aux->prox;
			}

			printf("%d - %s - ", pos--, aux1->nome);
			if(aux1->status == 1)
			printf("Preferencial\n");
			else
			printf("Normal\n");
			aux1 = aux;
			aux = inicio;
		}
		printf("%d - %s - ", pos--, aux1->nome);
		if(aux1->status == 1)
		printf("Preferencial\n");
		else
		printf("Normal\n");
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
//--------------Insere Clientes na Fila-------------------
void insere() {
    char *nome = (char*) malloc(100);
    int status;
  
	if (criado == 1) {
		printf("Entre com o nome do cliente:\n");
		scanf("%s", nome);

		printf("O cliente eh preferencial? (1 - SIM | 2 - NAO) \n");
		scanf("%i", &status);

		novo = (no *) malloc(sizeof(no));
		novo->nome = nome;
		novo->status = status;
        time(&novo->tempoEntradaFila); //Guarda a hora em que o cliente entrou na fila
		if (inicio == NULL ) {
			inicio = final = novo;
			novo->prox = NULL;
		    
        }else{
            if(novo->status == 1) {
                if(inicio->status == 1 && final->status == 1) { //insere um preferencial em uma lista que sÃ³ exista preferenciais (insere no fim)
                    final->prox = novo;
                    novo->prox = NULL;
                    final = novo;
                } else if(inicio->status == 2){ //insere um preferencial em uma lista que sÃ³ exista nÃ£o-preferenciais (insere no inicio)
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
            } else{ // insere um nÃ£o-preferencial em uma lista (insere no fim)
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
//----------------------- Atendimento ----------------------------
void atender(){
    char i; 
    system("cls");    
    
    
	while (inicio != NULL) {                    
    time(&inicio->tempoChegadaCaixa);//Guarda o tempo que o cliente começou a utilizar o caixa;
    
    do{       
    printf("Cliente em atendimento: %s\n\n",inicio->nome);
	printf(" (1)-Saca\n");
	printf(" (2)-Deposita \n");
	printf(" (3)-Extrato\n");
	printf(" (4)-Proximo Cliente\n");
        i = getch();

		switch (i) {  
        case '1':
             printf("Cliente %s sacou dinheiro.",inicio->nome);
             getch();
             system("cls");
             break;
        
        case '2':
             printf("Cliente %s depositou dinheiro.",inicio->nome);
             getch();
             system("cls");
             break;
        
        case '3':
             printf("Cliente %s tirou extrato.",inicio->nome);
             getch();
             system("cls");
              break;
        
        case '4':
             system("cls");
             time(&inicio->tempoSaida);//Guarda o tempo de saída do caixa;
             
             //imprime o tempo de fila, de caixa e o total gasto.
             printf("\nCliente %s ficou: \n",inicio->nome);
             
             tempoFila = inicio->tempoChegadaCaixa - inicio->tempoEntradaFila; 
             fila = gmtime(&tempoFila);
             printf("%02d:%02d:%02d na fila\n", fila->tm_hour, fila->tm_min, fila->tm_sec );                    
                     
             tempoAtendimento = inicio->tempoSaida - inicio->tempoChegadaCaixa ;
             atendimento = gmtime(&tempoAtendimento);
             printf("%02d:%02d:%02d no caixa\n", atendimento->tm_hour, atendimento->tm_min, atendimento->tm_sec);                  
                    
             tempoTotal = inicio->tempoSaida - inicio->tempoEntradaFila;
             total = gmtime(&tempoTotal);         
             printf("%02d:%02d:%02d no total\n", total->tm_hour, total->tm_min, total->tm_sec );
          
             if(inicio == final){
                printf("\nFim da fila!");
                inicio = NULL;
                break;  
             }  
                   
             getch();
             aux = inicio;
             inicio = inicio->prox;
             free(aux->nome);
             free(aux);
             system("cls");
             break;
             
        default:
             system("cls");
             } 
        }while(i != '4');
    }
}
