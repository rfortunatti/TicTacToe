#include <stdio.h>
#include <stdlib.h>
#include <time.h>
//Minha conven��o valor-s�mbolo:
// 0 = Linha, valor nulo; 1 = X, s�mbolo do jogador; 2 = O, s�mbolo do comp.

void Imprime_Tabuleiro (int vL1[], int vL2[], int vL3[]);
void Constroi_Tabuleiro (int vL1[], int vL2[], int vL3[]);
void Computa_Jogada (int vL1[], int vL2[], int vL3[], int opcLinha, int opcCol,
	int identificador);
void Rodada_PC (int vL1[], int vL2[], int vL3[]);
int Verifica_Ganho (int vL1[], int vL2[], int vL3[]);

int main ()
{
	int vL1[3], vL2[3], vL3[3], opcLinha, opcCol;

	printf ("Bem vindo ao jogo da velha\n--------------------------------\n");
	Constroi_Tabuleiro (vL1, vL2, vL3);
	do
	{
		printf ("\n");
		Imprime_Tabuleiro (vL1, vL2, vL3);
		do
		{
            printf ("\nEntre com sua jogada: ");
			scanf ("%d %d", &opcLinha, &opcCol);
			if (opcLinha > 3 || opcLinha < 1)
			{
				printf ("\nValor de linha invalido");
			}
			if (opcCol > 3 || opcCol < 1)
			{
				printf ("\nValor de coluna invalido");
			}
		}while (opcLinha > 3 || opcLinha < 1 || opcCol > 3 || opcCol < 1);
		Computa_Jogada (vL1, vL2, vL3, opcLinha, opcCol, 0);
		if (Verifica_Ganho (vL1, vL2, vL3) == 0)
		{
			printf ("\n\nO PC GANHOU!");
			system ("PAUSE");
			break;
		}
		if (Verifica_Ganho (vL1, vL2, vL3) == 1)
		{
			printf ("\n\nO USUARIO GANHOU!\n");
			system ("PAUSE");
			break;
		}
		Rodada_PC (vL1, vL2, vL3);
	}while (opcLinha > 0);
}

void Constroi_Tabuleiro (int vL1[], int vL2[], int vL3[])
{
	for (int i = 0; i < 3; i++) {
		vL1[i] = 0;
		vL2[i] = 0;
		vL3[i] = 0;
	}
}

void Imprime_Tabuleiro (int vL1[], int vL2[], int vL3[])
{
	//Um ponteiro para modificar o vetor-alvo. Assim n�o preciso
	//criar tr�s la�os -- apenas repito e altero o valor do ponteiro.
	int *vetor;
	vetor = vL1;

	for (int j = 1; j <= 3; j++) {
		for (int i = 0; i < 3; i++) {
			switch (vetor[i]) {
			case 0:
				printf ("- ");
				break;
			case 1:
				printf ("X ");
				break;
			case 2:
				printf ("O ");
				break;
			}
			if (vetor == vL1 && i == 2) {
			printf ("\n");
			vetor = vL2;
			break;
			}
			if (vetor == vL2 && i == 2) {
			printf ("\n");
			vetor = vL3;
			break;
			}

		}
	}

}

void Computa_Jogada (int vL1[], int vL2[], int vL3[], int opcLinha, int opcCol,
int identificador)
{
	//A vari�vel identificador diz para esta fun��o se quem mandou os valores
	//foi o usu�rio ou o PC. 0 para usu�rio e 1 para PC.
	//Usu�rio:
	if (identificador == 0) {
		if (opcLinha == 1) {
		vL1[opcCol - 1] = 1;
		return;
		}

		if (opcLinha == 2) {
		vL2[opcCol - 1] = 1;
		return;
		}

		if (opcLinha == 3) {
		vL3[opcCol - 1] = 1;
		return;
		}
	}
	//PC:
	if (identificador == 1) {
		if (opcLinha == 1) {
		vL1[opcCol - 1] = 2;
		return;
		}

		if (opcLinha == 2) {
		vL2[opcCol - 1] = 2;
		return;
		}

		if (opcLinha == 3) {
		vL3[opcCol - 1] = 2;
		return;
		}
	}
}

void Rodada_PC (int vL1[], int vL2[], int vL3[])
{
	//A id�ia � o computador gerar dois valores rand�micos. Estes ser�o os par�-
	//-metro que o usu�rio tamb�m passa, mas aqui haver� verifica��o se a op��o
	//j� foi utilizada. Caso positivo, os valores s�o gerados novamente at�
	//obter uma posi��o n�o utilizada. Assim que valores v�lidos s�o gerados,
	//a fun��o Computa_Jogada � chamada com identificador 1;

	int opcLinhaPC, opcColPC, *pont;

	do
	{
		srand (time(NULL) + 35) ;
		opcLinhaPC = (rand () % 3) + 1;

		srand (time(NULL) + 1245) ;
		opcColPC = (rand () % 3) + 1;

		switch (opcLinhaPC) {
			case 1:
			pont = vL1;
			break;

			case 2:
			pont = vL2;
			break;

			case 3:
			pont = vL3;
			break;
		}
		if (pont[opcColPC - 1] == 1 || pont[opcColPC - 1] == 2) {
			continue;
		}else
		{
			break;
		}
	}while (4);

	Computa_Jogada (vL1, vL2, vL3, opcLinhaPC, opcColPC, 1);
}

int Verifica_Ganho (int vL1[], int vL2[], int vL3[])
{
	//A fun��o retorna 1 caso o jogador ganhe e 0 se o PC ganhar.
	//Verificando as possibilidades de ganho para o usu�rio.
	if (vL1[0] == 1 && vL2[1] == 1 && vL3[2] == 1) {
		return 1;
	}
	if (vL1[2] == 1 && vL2[1] == 1 && vL3[0] == 1) {
		return 1;
	}
	if (vL1[0] == 1 && vL1[1] == 1 && vL1[2] == 1) {
		return 1;
	}
	if (vL2[0] == 1 && vL2[1] == 1 && vL2[2] == 1) {
		return 1;
	}
	if (vL3[0] == 1 && vL3[1] == 1 && vL3[2] == 1) {
		return 1;
	}
	if (vL1[0]  == 1 && vL3[0] == 1 && vL3[0] == 1) {
		return 1;
	}
	if (vL1[1]  == 1 && vL3[1] == 1 && vL3[1] == 1) {
		return 1;
	}
	if (vL1[2]  == 1 && vL3[2] == 1 && vL3[2] == 1) {
		return 1;
	}
	//Verificando as possibilidades de ganho para o PC.
	if (vL1[0] == 2 && vL2[1] == 2 && vL3[2] == 2) {
		return 0;
	}
	if (vL1[2] == 2 && vL2[1] == 2 && vL3[0] == 2) {
		return 0;
	}
	if (vL1[0] == 2 && vL1[1] == 2 && vL1[2] == 2) {
		return 0;
	}
	if (vL2[0] == 2 && vL2[1] == 2 && vL2[2] == 2) {
		return 0;
	}
	if (vL3[0] == 2 && vL3[1] == 2 && vL3[2] == 2) {
		return 0;
	}
	if (vL1[0]  == 2 && vL3[0] == 2 && vL3[0] == 2) {
		return 0;
	}
	if (vL1[1]  == 2 && vL3[1] == 2 && vL3[1] == 2) {
		return 0;
	}
	if (vL1[2]  == 2 && vL3[2] == 2 && vL3[2] == 2) {
		return 0;
	}
	return 3;
}
