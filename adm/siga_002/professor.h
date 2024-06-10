#ifndef professor_H
#define professor_H
// evita inclus�es m�ltiplas do mesmo arquivo de cabe�alho.

struct _professor {
	// Aqui � definida a estrutura de dados _professor, que possui cinco membros: nome, cpf, senha, materias e priv. Esses membros representam os dados de um professor.
    char nome[48];
    long int cpf;
    char senha;
    char materias[3][32];
    int priv;
};

typedef struct _professor professor;
//Define um novo tipo de dado professor como um apelido para struct _professor.

void init_professor(professor *prof) {
	//Esta fun��o inicializa uma estrutura de professor. Ela recebe um ponteiro para uma estrutura de professor como argumento e configura o membro priv como 2 e preenche o membro materias com strings vazias. Essa fun��o � �til para configurar valores padr�o ou iniciais para um professor.
    char vazio[24] = "...";
    prof->priv = 2;
    for(int i = 0; i < 3; i++){
        strcpy(prof->materias[i],vazio);
    }
    //strncpy(prof->materias[0],vazio,sizeof(prof->materias[0]));
}


#endif
//Indica o fim do bloco condicional #ifndef. Se o identificador professor_H n�o estiver definido, todo o conte�do entre #ifndef e #endif ser� processado.
