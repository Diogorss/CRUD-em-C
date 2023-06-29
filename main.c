#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void opcaoa(FILE **arq, int *fim){
  char nome[30];
  char genero[15];
  int idade;
  char resp1[4];
  char resp2[4];
  char resp3[4];
  char resp4[4];

  *arq = fopen("arq.txt", "a");       //criaçã9o do arquivo no modo escrita no final do texto
  if(*arq == NULL){             //verificação de abertura do arquivo(padrão em todas as funções)
    printf("Erro ao abrir arquivo\n");
  }
  else{     //programa faz as perguntas, armazena em variáveis que serão gravadas no arquivo
    printf("Insira seu nome:\n");
    scanf(" %[^\n]", nome);
    fprintf(*arq, "Nome: %s\n", nome);
    printf("Insira sua idade:\n");
    scanf("%d", &idade);
    fprintf(*arq, "Idade: %d\n", idade);
    printf("Insira seu gênero(masculino, feminino ou outro):\n");
    scanf(" %s", genero);
    fprintf(*arq, "Gênero: %s\n" ,genero);
    printf("Você já testemunhou algum ato de corrupção em sua comunidade?\n");
    scanf(" %s", resp1);
    fprintf(*arq, "Já testemunhou atos de corrupção? - %s\n", resp1);
    
    printf("Você já sofreu exclusão ou discriminação devido à sua condição socioeconômica?\n");
    scanf(" %s", resp2);
    fprintf(*arq, "Já sofreu exclusão ou discriminação devido à sua condição socioeconômica? - %s\n", resp2);
    
    printf("Você já enfrentou discriminação por conta da religião ou crenças pessoais?\n");
    scanf(" %s", resp3);
    fprintf(*arq, "Já enfrentou discriminação por conta da religião ou crenças pessoais? - %s\n", resp3);
    
    printf("Você já teve seus direitos de liberdade de expressão cerceados em um contexto político ou social?\n");
    scanf(" %s", resp4);
    fprintf(*arq, "Teve seus direitos de liberdade de expressão cerceados em um contexto político ou social? - %s\n", resp4);
    fprintf(*arq, "\n\n\n");
    fclose(*arq);  //encerra operações no arquivo
    
  }
}

void opcaob(FILE **arq){
  printf("Dados dos respondentes:\n\n");
  *arq = fopen("arq.txt", "r");
  if(*arq == NULL){
    printf("Erro ao abrir arquivo\n");
  }
  else{
    char car;
    while((car = fgetc(*arq)) != EOF){ //ler caracter do arquivo enquanto não for nulo
      putchar(car); //imprime no console
      
    }
  }
  
}

void opcaoc(FILE **arq){
  *arq = fopen("arq.txt", "r");
  if(*arq == NULL){
    printf("Erro ao abir arquivo\n");
  }
  else{
    char nome[30];
    printf("Digite o nome da pessoa que deseja buscar\n");
    scanf(" %[^\n]", nome); //entrada do nome, podendo ser nome composto
    char palavra[100];
    int encontrou = 0;
    while(fgets(palavra, sizeof(palavra), *arq) != NULL){ //percorre o arquivo
      if(strstr(palavra, nome) != NULL){ //verifica se há a string nome dentro das strings do                                               arquivo
        encontrou = 1; //variável para facilitar o controle da busca
        char car[100];      //linhas abaixo do nome
        for(int i =0; i <= 6; i++ ){ 
          if(fgets(palavra, sizeof(palavra), *arq) != NULL){
            printf("%s", palavra); //imprimir as 6 linhas abaixo do nome
          }
        }
        break;
      }
    }
    if(encontrou == 0){ //caso a palavra não tenha sido encontrada
      printf("Nome não encontrado\n");
    }
  }
  fclose(*arq);
}

void opcaod(FILE **arq){
  *arq = fopen("arq.txt", "r");
  if(*arq == NULL){
    printf("Erro ao abrir arquivo\n");
  }
  else{
    //contabilizar total
    char palavra[100];
    int total = 0;
    int corrupcao = 0, socioeconomico = 0, religiao = 0, liberdade = 0;
    while(fscanf(*arq, "%s", palavra) == 1){ //percorre o arquivo até encontrar sim ou Sim
      if(strcmp(palavra, "sim") == 0 || strcmp(palavra, "Sim") == 0){
        total++; //a cada sim ou Sim, a variável contabiliza uma unidade
      }
    }
  //contabilizar cada infração
    *arq = fopen("arq.txt", "r");
    while(fgets(palavra, sizeof(palavra), *arq) != NULL){
      if(strstr(palavra, "testemunhou") != NULL && (strstr(palavra, "sim") != NULL || strstr(palavra, "Sim") != NULL)){
          corrupcao++;
      }
    }
    *arq = fopen("arq.txt", "r");
    while(fgets(palavra, sizeof(palavra), *arq) != NULL){
      if(strstr(palavra, "devido") != NULL && (strstr(palavra, "sim") != NULL || strstr(palavra, "Sim") != NULL)){
        socioeconomico++;
      }
    }
    *arq = fopen("arq.txt", "r");
    while(fgets(palavra, sizeof(palavra), *arq) != NULL){
      if(strstr(palavra, "conta") != NULL && (strstr(palavra, "sim") != NULL || strstr(palavra, "Sim") != NULL)){
        religiao++;
      }
    }
    *arq = fopen("arq.txt", "r");
    while(fgets(palavra, sizeof(palavra), *arq) != NULL){
      if(strstr(palavra, "contexto") != NULL && (strstr(palavra, "sim") != NULL || strstr(palavra, "Sim") != NULL)){
        liberdade++;
      }
    }

    //contabilizar por gênero
    int masculino=0, feminino = 0, outro = 0;
    *arq = fopen("arq.txt", "r");
    while(fgets(palavra, sizeof(palavra), *arq) != NULL){ //percorre o arquivo
      if(strstr(palavra, "masculino") != NULL || strstr(palavra, "Masculino") != NULL){ 
        for(int i =0; i <= 6; i++ ){ 
          if(fgets(palavra, sizeof(palavra), *arq) != NULL){
              if(strstr(palavra, "sim") != NULL || strstr(palavra, "Sim") != NULL){
                  masculino++; //a cada sim ou Sim, a variável contabiliza uma unidade
              }
            }
        }
      }
      else if(strstr(palavra, "feminino") != NULL || strstr(palavra, "Feminino") != NULL){ 
        for(int i =0; i <= 6; i++ ){ 
          if(fgets(palavra, sizeof(palavra), *arq) != NULL){
              if(strstr(palavra, "sim") != NULL || strstr(palavra, "Sim") != NULL){
                  feminino++; //a cada sim ou Sim, a variável contabiliza uma unidade
              }
            }
        }
      }
      else if(strstr(palavra, "outro") != NULL || strstr(palavra, "Outro") != NULL){ 
        for(int i =0; i <= 6; i++ ){ 
          if(fgets(palavra, sizeof(palavra), *arq) != NULL){
              if(strstr(palavra, "sim") != NULL || strstr(palavra, "Sim") != NULL){
                  outro++; //a cada sim ou Sim, a variável contabiliza uma unidade
              }
            }
        }
      }
    }
    
    // contabilizar de acordo com a idade
    int idade=0;
    int totalmaior=0, totalmenor=0;
    *arq = fopen("arq.txt", "r");
    while(fgets(palavra, sizeof(palavra), *arq) != NULL){
      if(strstr(palavra, "Idade") != NULL ){
        sscanf(palavra, "Idade: %d", &idade); //valores lidos na string
        if(idade >= 18){
          for(int i =0; i <= 6; i++ ){ 
            if(fgets(palavra, sizeof(palavra), *arq) != NULL){
              if(strstr(palavra, "sim") != NULL || strstr(palavra, "Sim") != NULL){
                  totalmaior++; //a cada sim ou Sim, a variável contabiliza uma unidade
              }
            }
          }
        }
        else if(idade < 18){
          for(int i =0; i <= 6; i++ ){ 
            if(fgets(palavra, sizeof(palavra), *arq) != NULL){
              if(strstr(palavra, "sim") != NULL || strstr(palavra, "Sim") != NULL){
                  totalmenor++; //a cada sim ou Sim, a variável contabiliza uma unidade
              }
            }
          }
        }
      }
    }
    
    
    printf("\nTotal de infrações: %d\n", total);
    printf("Atos de corrupção: %d\n", corrupcao);
    printf("Discriminações devido a condição socioeconômica: %d\n", socioeconomico);
    printf("Discriminações por conta de crenças pessoais: %d\n", religiao);
    printf("Direito de liberdade de expressão restringido: %d\n", liberdade);
    printf("Total de infrações para homens: %d\n", masculino);
    printf("Total de infrações para mulheres: %d\n", feminino);
    printf("Total de infrações para outros: %d\n", outro);
    printf("Infrações para maiores de idade: %d\n", totalmaior);
    printf("Infrações para menores de idade: %d\n\n\n", totalmenor);
  }
  
}
  


int opcaoe(int fim, FILE **arq){
  fim = 1;
  printf("Fim\n");
  fopen("arq.txt", "w"); //abertura de um arquivo no modo w permite a escrita apos limpar o                                     arquivo
  if(*arq != NULL)
    fclose(*arq);      //fechar o arquivo após a limpa
  return fim;
}


int main(void) {
  char opcao;
  int fim = 0;
  FILE *arq;
  while(fim == 0){
    printf("Bem vindo(a) a pesquisa\n");
    printf("Selecione uma das opções abaixo:\n\n\n");
    printf("a - Responder a pesquisa\n");
    printf("b - Listar dados dos respondentes\n");
    printf("c - Listar dados individuais\n");
    printf("d - Listar estatísticas\n");
    printf("e - Fim\n");
    scanf(" %c", &opcao);
    switch(opcao){
      case 'a' :
        opcaoa(&arq, &fim);
        system("clear");
        break;
      case 'b' :
        system("clear");
        opcaob(&arq);
        break;
      case 'c' :
        system("clear");
        opcaoc(&arq);
        break;
      case 'd' :
        opcaod(&arq);
        break;
      case 'e' :
        fim = opcaoe(fim, &arq);
        break;
    }
  }
  return 0;
}