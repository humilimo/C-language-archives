#include<stdio.h>
#include<string.h>
#include<stdlib.h>

typedef struct{
  char racaPet[30];
  char nomePet[30];
}Animal;

typedef struct{
    char nomeDono[30];
    int idade;
    Animal *pet;
}Dono;

int main(){
FILE *arq;
Dono *dono = NULL;
Animal *animal = NULL;
int tmp;
int nDonos = 0;
int nAnimais = 0;
int i;
int index;
int contador = 0;
char printar[1000];
char busca;
printf("Qual sua opcao?\n 1) Cadastrar dono.\n 2) Cadastrar o pet do dono.\n 3) Remover dono.\n 4) Mostrar donos.\n 5) Salvar\n 6) Sair.\n");
scanf("%d", &tmp);
while(tmp != 6){
    if(tmp == 1){
        nDonos++;
        dono = (Dono*) realloc(dono, nDonos * sizeof(Dono));
        if(dono == NULL){printf("ERRO DE ALOCACAO");free(dono);exit(1);}
        printf("Qual e o nome do dono?\n");
        scanf(" %[^\n]", dono[nDonos-1].nomeDono);
        printf("Qual e a sua idade?\n");
        scanf("%d", &dono[nDonos-1].idade); 
    }
    else if(tmp == 2){
        nAnimais++;
        animal = (Animal*) realloc(animal, nAnimais * sizeof(Animal));
        if(animal == NULL){printf("ERRO DE ALOCACAO");free(animal);exit(1);}
        printf("Qual e o nome do pet?\n");
        scanf(" %[^\n]", animal[nAnimais-1].nomePet);
        printf("Qual e a raca do pet?\n");
        scanf(" %[^\n]", animal[nAnimais-1].racaPet);
        dono[nDonos-1].pet = &animal[nAnimais-1];
    }
    else if(tmp == 3){
        contador++;
        printf("Qual dono voce quer remover? (digite o index) \n");
        scanf("%d", &index);
        for(i = index; i < nDonos - 1;i++){
            strcpy(dono[i].nomeDono,dono[i+1].nomeDono);
            dono[i].idade = dono[i+1].idade;
            strcpy(dono[i].pet->nomePet, dono[i+1].pet->nomePet);
            strcpy(dono[i].pet->racaPet, dono[i+1].pet->racaPet);
        }
      dono = (Dono*) realloc(dono, (nDonos - 1) * sizeof(Dono));
      if(dono == NULL){printf("ERRO DE ALOCACAO");free(dono); exit(1);}
    }
    else if (tmp == 4){
if((arq = fopen("petshop.txt", "r")) != NULL){
rewind(arq);
while(!feof(arq)){
fgets(printar, 100, arq);
printf("%s", printar);
}
fclose(arq);
// printf("Dono %d:\n Nome: %s\n Idade: %d\n Nome do pet: %s\n Raca do pet: %s\n", i+1, dono[i].nomeDono, dono[i].idade, dono[i].pet->nomePet, dono[i].pet->racaPet);
}
   }

    else if (tmp == 5){
if((arq = fopen("petshop.txt", "a+")) != NULL){
    while(!feof(arq)){
        fgetc(arq);
    }
for(i = 0; i < nDonos - contador;i++){
fprintf(arq, "Dono %d:\n Nome: %s\n Idade: %d\n Nome do pet: %s\n Raca do pet: %s\n", i+1, dono[i].nomeDono, dono[i].idade, dono[i].pet->nomePet, dono[i].pet->racaPet);
}
fclose(arq);
    }
    }
printf("Qual sua opcao?\n 1) Cadastrar dono.\n 2) Cadastrar o pet do dono.\n 3) Remover dono.\n 4) Mostrar donos.\n 5) Salvar\n 6) Sair.\n");
scanf("%d", &tmp);
}
free(animal);
free(dono);
    return 0;
}