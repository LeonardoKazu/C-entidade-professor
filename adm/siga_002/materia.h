#ifndef materia_H
//Verifica se o identificador materia_H n�o est� definido. Se n�o estiver definido, significa que este arquivo de cabe�alho ainda n�o foi inclu�do neste arquivo de c�digo-fonte, evitando inclus�es m�ltiplas.

#define materia_H
//Define o identificador materia_H, indicando que este arquivo de cabe�alho est� sendo inclu�do neste ponto do c�digo-fonte.

struct _materia {
	//Define uma estrutura de dados _materia, que cont�m informa��es sobre uma disciplina ou mat�ria, como nome, professor e sigla.
    char nome[48];
    char professor[48];
    char sigla[7];
    
};

typedef struct _materia materia;
//struct _materia: � como uma caixa que pode conter informa��es sobre uma mat�ria, como nome, professor e sigla.
//typedef: � uma palavra-chave que usamos em C para criar apelidos para tipos de dados existentes.
//materia: � o novo nome que estamos dando para struct _materia.


void init_materia(materia *materia) { //init_materia: � uma fun��o que inicializa uma estrutura materia. Neste caso, define o nome do professor como "sem atribui��o".
    //char vazio[24] = "..."; --> apagar se n�o utilizar?
    strcpy(materia->professor, "sem atribuicao");
    //strncpy(prof->materias[0],vazio,sizeof(prof->materias[0]));--> apagar se n�o utilizar?
}


#endif
//#endif: Indica o fim do bloco condicional #ifndef. Se o identificador materia_H j� estiver definido, todo o conte�do entre #ifndef e #endif ser� ignorado durante inclus�es subsequentes.
