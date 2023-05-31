// ALUNO : Mateus Felipe Dias TURMA : SI 201
// TRABALHO PRATICO AEDS III - GRAFOS 

#include <iostream>
#include <locale.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

using namespace std;

//armazena as informaçoes mais relevantes sobre o grafo
typedef struct TG {
  int ContVert; // quantidade de vertices
  int ContAres; // quantidades de arestas
  int **MatrizG; // Matriz para guardas as arestas presente nos grafos
  int **ContCordenada; // Matriz para guardas as cordenadas dos grafos
} TG;

void importar(TG *grafo, char NameFolder[]);
void vazio(TG *grafo);
void mostrarGraficamente(TG *grafo);
bool consultarSeAdjacente(TG *grafo, int u, int v);
void inserAresta(TG *grafo, int u, int v, int peso);
void removerAresta(TG *grafo, int u, int v);
void editarCoordenadaDoVertice(TG *grafo, int Vert);
void listaCompletaDeAdjacentesDoVertice(TG *grafo, int Vert);
int  primeiroAdjacenteDoVertice(TG *grafo, int Vert);
int  proximoAdjacenteDoVertice(TG *grafo, int Vert, int Novo);
void exportar(TG *grafo, char NameFolder[]);

int main() {
    
  unsigned int microseconds;

  TG grafo;
  int dir, escolha, resultado;
  int Vert, u, v, Novo, peso;
  int Base, Dest;
  char NameFolder[255];

  do {
    printf("  -----------------------------------------------------");
    printf("\n|                       MENU                        |");
    printf("\n|                                                   |");
    printf("\n|  1  - Importar um grafo                           |");
    printf("\n|  2  - Criar Grafo Vazio                           |");
    printf("\n|  3  - Exibir Adjacentes                           |");
    printf("\n|  4  - Consultar se um vertice e adjacente ao outro|");
    printf("\n|  5  - Inserir aresta                              |");
    printf("\n|  6  - Remover aresta                              |");
    printf("\n|  7  - Editar ContCordenada de um vértice          |");
    printf("\n|  8  - Consultar o primeiro adjacente um vértice   |");
    printf("\n|  9  - Consultar o próximo adjacente de um vértic  |");
    printf("\n|  10 - Consultar a lista completa de ajacentes     |");
    printf("\n|  11 - Exportar o grafo para um arquivo de texto   |");
    printf("\n|  12 - Encerrar programa                           |");
    printf("\n-----------------------------------------------------");
    printf("\n          ");
    scanf("%d", &escolha);
    system("clear");

    switch (escolha) {
        
    // importar um grafo de um arquivo de texto;
    case 1:
      printf("\nDigite o nome do arquivo juntamente com sua extensão : ");
      scanf("%s", &NameFolder);
      system("clear");
      printf("\nO grafo e direcionado ou não ? 1 SIM / 2 NÃO\n") ; 
      scanf ("%d",dir); 

      importar(&grafo, NameFolder);
      break;

    // criar um grafo vazio a partir de um número de vértices informado pelo
    // usuário;
    case 2:
      printf("Quantos vertices tem o grafo ? : ");
      scanf("%d", &grafo.ContVert);
      system("clear");
      vazio(&grafo);
      break;

    // imprimir grafo
    case 3:
      mostrarGraficamente(&grafo);
      break;

    // Consultar se um vertice e adjacente ao outro
    case 4:
      printf("Vértice X : ");
      scanf("%d", &u);
      printf("Vértice Y : ");
      scanf("%d", &v);
      system("clear");

      if (consultarSeAdjacente(&grafo, u, v)) {
        printf ("Existe adjacentes entre os vertices %d e %d",u ,v) ; 
      } else {
        printf ("Nao Existe adjacentes entre os vertices %d e %d",u ,v) ; 
      }
      break;

    // Inserir aresta
    case 5:
      printf("Vértice X : ");
      scanf("%d", &u);
      printf("Vértice Y : ");
      scanf("%d", &v);
      printf("Peso: ");
      scanf("%d", &peso);
      system("clear");

      inserAresta(&grafo, u, v, peso);
      break;

    // Remover aresta
    case 6:
      printf("Vértice X : ");
      scanf("%d", &u);
      printf("Vértice Y : ");
      scanf("%d", &v);
      system("clear");

      removerAresta(&grafo, u, v);
      break;

    // Editar coordenada de um vértice
    case 7:

      printf("Qual o vertice ?");
      scanf("%d", &Vert);
      system("clear");
      editarCoordenadaDoVertice(&grafo, Vert);
      break;

    // Consultar se um vertice e adjacente ao outro
    case 8:
      printf ("Qual vertice consultar ? : ");
      scanf("%d", &Vert);
      system("clear");

      resultado = primeiroAdjacenteDoVertice(&grafo, Vert);

      if (resultado == -1) {
        cout << "O vértice " << Vert << " não tem adjacente!" << endl;
      } else {
        cout << "O primeiro adjacente do vértice " << Vert << " é " << resultado
             << endl;
      }

    // Consultar o proximo adjacente de um vertice
    case 9:
      printf ("Qual vertice consultar ? : ");
      scanf("%d", &Vert);
      printf ("Qual vertice inicial a consultar ? : ");
      scanf("%d", &Novo);
      system("clear");

      resultado = proximoAdjacenteDoVertice(&grafo, Vert, Novo);

      if (resultado != -1) {
          
        printf ("\nO proximo adjacente do vertice é : %d", Vert); 
        printf ("\nSaiu do vertice %d", Novo);
        printf ("\n%d",resultado);
      }
      else{
        printf ("O vertice %d, não tem adjacente partindo de %d ", Vert, Novo); 
      }

    // Consultar a lista de adjacentes
    case 10:
      printf ("Qual o vértice inicial a ser consultado ? : ");
      scanf("%d", &Vert);
      system("clear");

      listaCompletaDeAdjacentesDoVertice(&grafo, Vert);
      break;

    // Exportar o grafo para um arquivo de texto
    case 11:
      printf("Digite o nome do arquivo juntamente com sua extensão : ");
      scanf("%s", &NameFolder);
      system("clear");
      exportar(&grafo, NameFolder);
      break;
    
    //Em caso de opção de entrada envalida
    default:
      printf("ERRO !, tente novamente.");
      usleep(2000);
      system("clear");
      break;
    }

  } while (escolha != 14);

  return 0;
}

void mostrarGraficamente(TG *grafo) {

  //função de mostrar o grafo 
  for (int j = 0; j < grafo->ContVert; j++) {
    if (j == 0) {
      cout << "    ";
    }
    printf ("%d     ", j) ; 
  }
  printf ("\n") ; 
  for (int j = 0; j < grafo->ContVert; j++) {
    if (j == 0) {
      printf ("\n") ;
    }
    printf ("     ", j) ; 
  }
  printf ("\n") ; 
  for (int i = 0; i < grafo->ContVert; i++) {
    printf ("%d - ",i) ; 
   
    for (int j = 0; j < grafo->ContVert; j++) {
      printf (" %d  \t ",grafo->MatrizG[i][j] ); 
      
    }
    printf ("\n") ;
  }
}

void importar(TG *grafo, char NameFolder[]) {
  FILE *folder; // abre o arquivo 
  int a, a2, a3;

   folder = fopen(NameFolder, "r");

  if (folder != NULL) { // verifica se o arquivo não esta nulo 
    fscanf(folder, "%d", &grafo->ContVert); // faz a leitura para verificar a quantidade de vertices

    grafo->MatrizG = (int **)malloc(grafo->ContVert * sizeof(int *));
    for (int i = 0; i < grafo->ContVert; i++) { //alocação de memoria para matriz 
      grafo->MatrizG[i] = (int *)calloc(grafo->ContVert, sizeof(int));
    }

    grafo->ContCordenada = (int **)malloc(grafo->ContVert * sizeof(int *));
    for (int i = 0; i < grafo->ContVert; i++) { //alocação de memoria para coodenada
      grafo->ContCordenada[i] = (int *)malloc(2 * sizeof(int));
    }

    for (int i = 0; i < grafo->ContVert; i++) {
      fscanf(folder, "%d %d %d", &a, &grafo->ContCordenada[i][0], // reaiza a leitura dos vertices e as armazena na matriz 
             &grafo->ContCordenada[i][1]);
    }

    fscanf(folder, "%d", &grafo->ContAres);
    grafo->ContAres = grafo->ContAres * 2; // Realiza a contagem da quantidade de arestas

    for (int i = 0; i < grafo->ContAres; i++) {
      fscanf(folder, "%d %d %d", &a, &a2, &a3); //Faz a transição dos elementos dos arquivos para a matriz 
      grafo->MatrizG[a][a2] = a3;
      grafo->MatrizG[a2][a] = a3;
    }

    printf ("Arquivo criado com sucesso ! ");
    usleep(2000);
    system("clear");
  } else { // se o arquivo for nulo 
    printf ("ERRO \n");
    usleep(2000);
    system("clear");
  }

  fclose(folder);
}

void vazio(TG *grafo) {
    
  //Depois do usuario imformar a quantidade de vertices que o grafo vai possuir o programa executa o comando para criar o grafo vazio
  grafo->MatrizG = (int **)malloc(grafo->ContVert * sizeof(int *));
  for (int i = 0; i < grafo->ContVert; i++) { //Mesma algoritmo utilizado anteriormente para alocação de memoria para a matriz
    grafo->MatrizG[i] = (int *)calloc(grafo->ContVert, sizeof(int));
  }

  grafo->ContCordenada = (int **)malloc(grafo->ContVert * sizeof(int *));
  for (int i = 0; i < grafo->ContVert; i++) { //Mesma algoritmo utilizado anteriormente para alocação de memoria para as coordenadas
    grafo->ContCordenada[i] = (int *)calloc(2, sizeof(int));
  }

  grafo->ContAres = 0;
}

bool consultarSeAdjacente(TG *grafo, int u, int v) {
  if (grafo->MatrizG[u][v] != 0) {
    return true;
  } else {
    return false;
  }
}

void inserAresta(TG *grafo, int u, int v, int peso) {
  if (peso > 0) { // verifica se o peso e menor ou = 0, se for  
    if (u >= grafo->ContVert || v >= grafo->ContVert) {
      printf ("\nNão e possivel adicionar arestas menores ou igual a 0 !");
      usleep(2000);
      system("clear");
    } else {
      if (grafo->MatrizG[u][v] == 0) { //Coloca a matriz na posição u e v com valor 0 
        grafo->MatrizG[u][v] = peso; //verifica se a posição esta vazia se estiver a mensagem de "Adicionado com Sucesso" aparece
        grafo->MatrizG[v][u] = peso; 
        grafo->ContAres = grafo->ContAres + 2;
        printf ("Adicionado com Sucesso");
        usleep(2000);
        system("clear");
      } else {
        printf ("Deculpe, a posição desejada ja está ocupada"); // Se a posição não estiver vazia vai apararecer a mensagem de ("Deculpe, a posição desejada ja está ocupada")
        usleep(2000);
        system("clear");
      }
    }
  } else {
    cout << "Impossível colocar peso menor ou igual que 0!" << endl;
    usleep(2000);
    system("clear");
  }
}

void removerAresta(TG *grafo, int u, int v) {
    // dentro do switch case e perguntado para o usuario a posição desejada
  if (grafo->MatrizG[u][v] != 0) { //verifica se a posição desejada não está vazia
    grafo->MatrizG[u][v] = 0; //Se a posição não estiver vazia fazemos a remoção da aresta
    grafo->ContAres = grafo->ContAres - 1;
    printf ("Aresta removida co sucesso !") ;
    usleep(2000);
    system("clear");
  } else {
    printf ("descupe, posição invalida por estar vazia!" );//se estiver vazia aparece a mensagem para o usuario
    usleep(2000);
    system("clear");
  }
}

void editarCoordenadaDoVertice(TG *grafo, int Vert) {
  int ContCordenadaX, ContCordenadaY;

  if (Vert >= 0 && Vert < grafo->ContVert) {
    printf ("Qual cordenada você quer editar ? ");  // usuario informa o vertice que quer editar
    printf ("Cordenada X : ");
    scanf ("%d",&ContCordenadaX); //arnazena as cordenadas para efetuar a troca
    printf ("Cordenada Y : ");
    scanf ("%d",&ContCordenadaY); 
    system("clear");

    grafo->ContCordenada[Vert][0] = ContCordenadaX; // verifica se a cordenada x que o usuario escolheu e valida 
    grafo->ContCordenada[Vert][1] = ContCordenadaY; // verifica se a cordenada y que o usuario escolheu e valida 
  } else {
    printf ("Desculpe, Cordenada do inexistente!"); // se a cordenada informada pelo usuario for inexistente a mensagem e mostrada
    usleep(2000);
    system("clear");
  }
}

int primeiroAdjacenteDoVertice(TG *grafo, int Vert) {
    //usuario informa qual o vertice ele deseja consultar
  for (int i = 0; i < grafo->ContVert; i++) {
    if (grafo->MatrizG[Vert][i] != 0) {// faz a busca do adjacente, se encontrado mostra o adjacente encontrado
      return i;
    }else {
        printf ("Não existe adjacente") ; 
    }
  }
  return -1;
}

int proximoAdjacenteDoVertice(TG *grafo, int Vert, int Novo) {
    //usuario informa qual o vertice ele deseja consultar e o ponto de inicio
  for (int i = Novo; i < grafo->ContVert; i++) {
    if (grafo->MatrizG[Vert][i] != 0) { // verifica se existe ou não adjacencia 
      return i;
    }
  }
  return -1;
}

void listaCompletaDeAdjacentesDoVertice(TG *grafo, int Vert) {
  //usuario informa qual o vertice ele deseja consultar 
  printf ("Lista de adjacentes : ");
  for (int i = 0; i < grafo->ContVert; i++) { //verifica todos os adjacentes e os mostra se não existir a mensagem e printada
  
    if (grafo->MatrizG[Vert][i] != 0) {
      printf ("%d",i); 
    }
  }
  printf (" ");
}

void exportar(TG *grafo, char NameFolder[]) {
//o usuario escreve o nome do arquivo
  FILE *folder;
  int contpeso = 0;

  folder = fopen(NameFolder, "w");// cria o arquivo com o nome escolhido pelo usuario
  

  if (folder != NULL) { 
      
    fprintf(folder, "%d\n", grafo->ContVert); //armazena a quantidade de vertices do grafo

    for (int i = 0; i < grafo->ContVert; i++) {
      fprintf(folder, "%d %d %d\n", i, grafo->ContCordenada[i][0],// armazena as cordenadas do vertice
              grafo->ContCordenada[i][1]);
    }

    fprintf(folder, "%d\n", grafo->ContAres); //armazena a quantidade de arestas

    for (int i = 0; i < grafo->ContVert; i++) {
      for (int j = 0; j < grafo->ContVert; j++) {
        if (grafo->MatrizG[i][j] != 0) { //armazena no arquivo a posição de cada aresta juntamente com seu peso
          contpeso = grafo->MatrizG[i][j];
          fprintf(folder, "%d %d %d\n", i, j, contpeso);
        }
      }
    }

    printf ("Arquivo salvo!");
    system("clear");
  } else {
    printf ("ERRO"); 
    usleep(2000);
    system("clear");
  }

  fclose(folder);
}

// CALLOC "Seu objetivo é criar um vetor de tamanho dinâmico, ou seja, definido durante a execução do programa."
// MALLOC aloca espaço para um bloco de bytes consecutivos na memória RAM
// USLEEP A função usleep() é uma função embutida que é usada para atrasar a execução do script atual por microssegundos específicos.


/* VIDEOS, SITES E ARQUIVOS UTILIZADOS
https://www.youtube.com/watch?v=aW-YhwSDwxc&list=PL8eBmR3QtPL13Dkn5eEfmG9TmzPpTp0cV&index=67
https://www.youtube.com/watch?v=BwZvcq5K1wU&list=PL8eBmR3QtPL13Dkn5eEfmG9TmzPpTp0cV&index=68
https://www.youtube.com/watch?v=Frmwdter-vQ&t=345s
https://www.youtube.com/watch?v=qDpoK9qx0YU&t=45s
https://www.youtube.com/watch?v=Zl25KC_nW00&t=321s
https://www.youtube.com/watch?v=QoNAGyDMmuE&t=561s
https://gist.github.com/marcoscastro/76634e1d38d0d7eef2e1
https://www.clubedohardware.com.br/forums/topic/1114062-preenchendo-uma-lista-de-adjac%C3%AAncias-em-c/
https://medium.com/@paulomartins_10299/grafos-c%C3%B3digo-das-opera%C3%A7%C3%B5es-b%C3%A1sicas-e91d9a79e828
https://github.com/Nadyan/grafos/blob/master/Tarefa_1_Adjacente_e_Incidente/matrizAdjacenteEIncidente.c
*/
