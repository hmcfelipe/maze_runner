#include <chrono>
#include <stdio.h>
#include <stdlib.h>
#include <stack>
#include <thread>
#include <unistd.h>

using namespace std;

// Exercício 1 ATR Maze Runner 2024/2

// Matriz de char representnado o labirinto
char** maze; // Voce também pode representar o labirinto como um vetor de vetores de char (vector<vector<char>>)

// Numero de linhas e colunas do labirinto
int num_rows = 0;
int num_cols = 0;

// Representação de uma posição
struct pos_t {
	int i;
	int j;
};

// Estrutura de dados contendo as próximas
// posicões a serem exploradas no labirinto
std::stack<pos_t> valid_positions;
/* Inserir elemento: 

	 pos_t pos;
	 pos.i = 1;
	 pos.j = 3;
	 valid_positions.push(pos)
 */
// Retornar o numero de elementos: 
//    valid_positions.size();
// 
// Retornar o elemento no topo: 
//  valid_positions.top(); 
// 
// Remover o primeiro elemento do vetor: 
//    valid_positions.pop();


// Função que le o labirinto de um arquivo texto, carrega em 
// memória e retorna a posição inicial
pos_t load_maze(const char* file_name) {
	pos_t initial_pos;
	// Abre o arquivo para leitura (fopen)

	FILE *arq;
	char ch;
  	arq = fopen (file_name,"r");

	fscanf(arq,"%d %d\n", &num_rows, &num_cols);

	// Aloca a matriz maze (malloc)
	maze = (char**)malloc(num_rows * sizeof(char*));

	for (int i = 0; i < num_rows; ++i)
		// Aloca cada linha da matriz
		maze[i] = (char*)malloc(num_cols * sizeof(char));
	
	for (int i = 0; i < num_rows; ++i) {
		for (int j = 0; j < num_cols; ++j) {
			// Le o valor da linha i+1,j do arquivo e salva na posição maze[i][j]
			// Se o valor for 'e' salvar o valor em initial_pos
			if ((ch = fgetc(arq)) != EOF){
				maze[i][j] = ch;
				if(maze[i][j] == 'e'){
					initial_pos.i = i;
					initial_pos.j = j;
				}
			}
		}
		ch = fgetc(arq);
	}
	return initial_pos;
}

// Função que imprime o labirinto
void print_maze() {
	for (int i = 0; i < num_rows; ++i) {
		for (int j = 0; j < num_cols; ++j) {
			printf("%c", maze[i][j]);
		}
		printf("\n");
	}
}

// Função responsável pela navegação.
// Recebe como entrada a posição initial e retorna um booleando indicando se a saída foi encontrada
bool walk(pos_t pos) {

	if(maze[pos.i][pos.j] == 's')
		{
			print_maze();
			maze[pos.i][pos.j] = '-';
			usleep(50000);
			return true;
		}

	pos_t nova_posicao;

	print_maze();
	maze[pos.i][pos.j] = '-';
	usleep(50000);
	system("clear");
	print_maze();
	printf("\n Numero de linhas do labirinto: %d", num_rows);
	printf("\n Numero de colunas do labirinto: %d", num_cols); 
		
		if(pos.i+1 < num_rows && maze[pos.i+1][pos.j] == 's'){

			system("clear");
			print_maze();
			maze[pos.i][pos.j] = '-';
			system("clear");
			print_maze();
			return true;

		}
		
		/* Dado a posição atual, verifica quais sao as próximas posições válidas
			Checar se as posições abaixo são validas (i>0, i<num_rows, j>0, j <num_cols)
		 	e se são posições ainda não visitadas (ou seja, caracter 'x') e inserir
		 	cada uma delas no vetor valid_positions
		 		- pos.i, pos.j+1
		 		- pos.i, pos.j-1
		 		- pos.i+1, pos.j
		 		- pos.i-1, pos.j
		 	Caso alguma das posiçÕes validas seja igual a 's', retornar verdadeiro
	 	*/

		if(pos.i-1 >= 0 && pos.i-1 < num_rows && (maze[pos.i-1][pos.j] == 'x')){
			nova_posicao.i = pos.i-1;
			nova_posicao.j = pos.j;
			valid_positions.push(nova_posicao);
		}

		
	 	if(pos.j+1 >= 0 && pos.j+1 < num_cols && (maze[pos.i][pos.j+1] == 'x')){
			nova_posicao.i = pos.i;
			nova_posicao.j = pos.j+1;
			valid_positions.push(nova_posicao);
		}

		if(pos.j-1 >= 0 && pos.j-1 < num_cols && (maze[pos.i][pos.j-1] == 'x')){
			nova_posicao.i = pos.i;
			nova_posicao.j = pos.j-1;
			valid_positions.push(nova_posicao);
		}

		if(pos.i+1 >= 0 && pos.i+1 < num_rows && (maze[pos.i+1][pos.j] == 'x')){
			nova_posicao.i = pos.i+1;
			nova_posicao.j = pos.j;
			valid_positions.push(nova_posicao);
		}

		if(pos.j+1 >= 0 && pos.j+1 < num_cols && (maze[pos.i][pos.j+1] == 's')){
			nova_posicao.i = pos.i;
			nova_posicao.j = pos.j+1;
			valid_positions.push(nova_posicao);
		}

		
		if(pos.i-1 >= 0 && pos.i-1 < num_rows && (maze[pos.i-1][pos.j] == 's')){
			nova_posicao.i = pos.i-1;
			nova_posicao.j = pos.j;
			valid_positions.push(nova_posicao);
		}

		if(pos.j-1 >= 0 && pos.j-1 < num_cols && (maze[pos.i][pos.j-1] == 's')){
			nova_posicao.i = pos.i;
			nova_posicao.j = pos.j-1;
			valid_positions.push(nova_posicao);
		}

		if(pos.i+1 >= 0 && pos.i+1 < num_rows && (maze[pos.i+1][pos.j] == 's')){
			nova_posicao.i = pos.i+1;
			nova_posicao.j = pos.j;
			valid_positions.push(nova_posicao);
		}


		// Verifica se a pilha de posições nao esta vazia 
		//Caso não esteja, pegar o primeiro valor de  valid_positions, remove-lo e chamar a funçao walk com esse valor
		// Caso contrario, retornar falso

		if (!valid_positions.empty()) {

			pos_t proxima_position = valid_positions.top();
			valid_positions.pop();
			walk(proxima_position);
			while (!valid_positions.empty()){
				thread thrd(walk,valid_positions.top());
				valid_positions.pop();
				thrd.detach();
			}
			
		}
		
	return false;
}

int main(int argc, char* argv[]) {
	
	// carregar o labirinto com o nome do arquivo recebido como argumento
	pos_t initial_pos = load_maze("/workspaces/maze_runner/data/maze7.txt");
	// chamar a função de navegação
	bool exit_found = walk(initial_pos);
	
	// Tratar o retorno (imprimir mensagem)

	for(int i = 0; i < num_rows; i++){
		delete(maze[i]);
	}

	delete(maze);

	return 0;
}
