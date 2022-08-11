#include<stdio.h>
#include<string.h>
#include<stdlib.h>

typedef struct{ 
    int pReal;
    float pImag;
}Complexo;

void empilhe(Complexo **cPilha, Complexo umC, int *tPilha){
    (*tPilha)++;
    (*cPilha) = (Complexo*) realloc((*cPilha), (*tPilha) * sizeof(Complexo));
    if(*cPilha == NULL){printf("ERRO DE ALOCACAO"); exit(1);}
    printf("Digite a parte real do numero complexo:");
    scanf("%d", &umC.pReal);
    printf("Digite a parte imaginaria do numero complexo:");
    scanf("%f", &umC.pImag);
    (*cPilha)[(*tPilha) - 1] = umC;
}

Complexo desempilhe(Complexo **cPilha, int *tPilha){
    (*tPilha)--;
    *cPilha = (Complexo*) realloc((*cPilha), (*tPilha) * sizeof(Complexo));
}

Complexo topo(Complexo *cPilha, int tPilha){
    return cPilha[tPilha - 1];
}

int pilhaVazia(Complexo *cPilha, int tPilha){
    if(cPilha == NULL || tPilha == 0){
        return 1;
    }
    else{
        return 0;
    }
}

void salvePilha(Complexo *cPilha, int tPilha){
    FILE *arq;
    if((arq = fopen("pilhas.bin", "wb")) != NULL){
        fwrite(&tPilha,sizeof(int), 1, arq);
        fwrite(cPilha, sizeof(Complexo), tPilha, arq);
        fclose(arq);
    }
}

Complexo *recuperePilha(int *tPilha){
    FILE *arq;
    Complexo *recuperado;
    if((arq = fopen("pilhas.bin", "rb")) != NULL){
        fread(tPilha, sizeof(int), 1, arq);
        recuperado = (Complexo*) calloc((*tPilha) , sizeof(Complexo)); 
        if(recuperado == NULL){printf("ERRO DE ALOCACAO");fclose(arq);exit(1);}
        fread(recuperado, sizeof(Complexo), tPilha, arq);
        fclose(arq);
    }
    return recuperado;
}

int main(){
Complexo *cPilha = NULL;
Complexo umC;
Complexo pilhaTopo;
int tPilha = 0;
int tmp;
printf("Escolha uma opcao:\n 1) Empilhe.\n 2) Desempilhe.\n 3) Topo.\n 4) Estado da pilha.\n 5) Salvar pilha.\n 6) Recuperar pilha.\n 7) Sair.\n");
scanf("%d", &tmp);
while(tmp != 7){
if(tmp == 1){
    empilhe(&cPilha, umC, &tPilha);
}

else if(tmp == 2){
    desempilhe(&cPilha, &tPilha);
}

else if(tmp == 3){
   pilhaTopo = topo(cPilha, tPilha);
   if(tPilha > 0){
   printf("Numero real do topo: %d\n", pilhaTopo.pReal);
   printf("Numero imaginario do topo: %f\n", pilhaTopo.pImag);
   }
   else{
       printf("Sem topo. Pilha vazia.\n");
   }
}

else if(tmp == 4){
    if(pilhaVazia(cPilha, tPilha) == 1){
        printf("Pilha vazia.\n");
    }
    else{
        printf("A pilha tem %d complexos.\n", tPilha);
    }
}

else if(tmp == 5){
    salvePilha(cPilha, tPilha);
}

else if(tmp == 6){
    cPilha = recuperePilha(&tPilha);
}

printf("Escolha uma opcao:\n 1) Empilhe.\n 2) Desempilhe.\n 3) Topo.\n 4) Estado da pilha.\n 5) Salvar pilha.\n 6) Recuperar pilha.\n 7) Sair.\n");
scanf("%d", &tmp);
}
return 0;
}