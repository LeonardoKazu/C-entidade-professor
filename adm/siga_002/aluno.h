#ifndef ALUNO_H
#define ALUNO_H
//garantem que o conte�do do arquivo de cabe�alho seja inclu�do apenas uma vez durante a compila��o para evitar problemas de redefini��o.

// Define a estrutura de dados para representar um aluno
struct _aluno {
    char nome[48];				// Nome do aluno
    long int cpf;				// CPF do aluno
    char senha;					// Senha do aluno (apenas um caractere?)
    int reg_a;					// Registro do aluno
    char materias[3][24];		// Mat�rias em que o aluno est� matriculado
    int priv;					 // Privil�gio do aluno
    //const int priv = 1; -> apagar se n�o for usar(?)
};

// Define um alias 'aluno' para 'struct _aluno'
typedef struct _aluno aluno;

// Fun��o para inicializar um aluno com valores padr�o
void init_aluno(aluno *a) {
    char vazio[24] = "...";				// String representando uma mat�ria vazia
    a->priv = 1;						 // Define o privil�gio padr�o
    a->reg_a = 100;						// Define o registro acad�mico padr�o
    
    // Inicializa todas as mat�rias do aluno como vazio
    for(int i = 0; i < 3; i++){
        strcpy(a->materias[i],vazio);
    }
    strcpy(a->materias[0],"ies100"); // Define uma mat�ria padr�o
}

#endif
