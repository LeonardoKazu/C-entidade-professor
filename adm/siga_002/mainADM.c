#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "aluno.h"
#include "professor.h"
#include "materia.h"

// Protótipos das funções
/*
int atualizar_aluno();                                        
int atualizar_professor();										
aluno cad_aluno();												
void* cadastrar_aluno();											
materia cad_materia();											
void* cadastrar_materia();										
professor cad_professor();										
void* cadastrar_professor();
void extende_mem_aluno(aluno **vet_cad, int *cont_cad);
void extende_mem_materia(materia **vet_cad, int *cont_cad);
void extende_mem_professor(professor **vet_cad, int *cont_cad);
int ler_alunos();
int ler_materia();
int ler_professor();
void limparBufferEntrada();
*/

atribuicao_mat(){//atribui mat�rias aos alunos

    int cont = 0;
    int index_prof;
    int index_mat;

    FILE *prof_data; //ponteiro para o arquivo dos professores
    FILE *mat_data;  //ponteiro para o arquivo de mat�rias

    professor *professor_vet; //ponteiro para array de estruturas dos professores, 'professor_vet'
    materia *materia_vet;     //ponteiro para aarray tabm�m, 'materia_vet'

    int prof_data_tamanho; //vari�veir para armazenar o tamanho dos arquivos
    int mat_data_tamanho;

    professor prof; // vari�vel prof do tipo professor
    int num_mat = sizeof(prof.materias) / sizeof(prof.materias[0]); //calcula o n�mero de mat�rias que um professor pode ter, dividindo o tamanho total do array materias pelo tamanho de um �nico elemento do array.

    
    prof_data = fopen("professor.bin", "rb+");
    if (prof_data == NULL) {
        perror("Erro ao abrir professor.bin");
        return 1;
    } //Abre o arquivo professor.bin no modo de leitura/escrita bin�ria (rb+). Se falhar, imprime uma mensagem de erro e retorna 1.

    mat_data = fopen("materia.bin", "rb+");
    if (mat_data == NULL) {
        perror("Erro ao abrir materia.bin");
        fclose(prof_data);
        return 1;
    } //Abre o arquivo materia.bin no modo de leitura/escrita bin�ria (rb+). Se falhar, imprime uma mensagem de erro, fecha o arquivo de professores e retorna 1.

    
    prof_data_tamanho = tamanho_arq(prof_data);
    mat_data_tamanho = tamanho_arq(mat_data);
    //Calcula o tamanho dos arquivos de professores e mat�rias usando a fun��o tamanho_arq

    int num_materias = mat_data_tamanho / sizeof(materia);
    int num_professores = prof_data_tamanho / sizeof(professor);
    //Calcula o n�mero de mat�rias e professores dividindo o tamanho do arquivo pelo tamanho de uma estrutura materia e professor, respectivamente.

    
    professor_vet = malloc(prof_data_tamanho);
    materia_vet = malloc(mat_data_tamanho);
	//Aloca mem�ria suficiente para armazenar todas as estruturas de professores e mat�rias lidas dos arquivos.
    
    fread(professor_vet, prof_data_tamanho, 1, prof_data);
    fread(materia_vet, mat_data_tamanho, 1, mat_data);
	//L� os dados dos arquivos professor.bin e materia.bin para os arrays professor_vet e materia_vet.
    
    for (int i = 0; i < num_materias; i++) {
        if (i == 0) {
            printf("       Mat�rias: %d - %s\n", (i + 1), materia_vet[i].nome);
        } else {
            printf("                 %d - %s\n", (i + 1), materia_vet[i].nome);
        }
    }//Exibe a lista de mat�rias dispon�veis para o usu�rio escolher.

    printf("Selecionar mat�ria da lista: ");
    scanf("%d", &index_mat);

    index_mat = index_mat - 1;

    clear_screen();//Limpa a tela.

    
    printf("Mat�ria selecionada: %s\n\n", materia_vet[index_mat].nome);
    for (int i = 0; i < num_professores; i++) {
        if (i == 0) {
            printf("        Professores: %d - %s\n", (i + 1), professor_vet[i].nome);
        } else {
            printf("                     %d - %s\n", (i + 1), professor_vet[i].nome);
        }
    }
    //Exibe a mat�ria selecionada e lista os professores dispon�veis.

    
    printf("\nDigite o numero do professor que ira� ministrar a aula: ");
    scanf("%d", &index_prof);

    index_prof = index_prof - 1;

    clear_screen();

    printf("\n Matéria  : %s\n", materia_vet[index_mat].nome);
    printf(" Professor: %s\n", professor_vet[index_prof].nome);
    printf(" \npressione ENTER para confirmar a atribuicao.");
    limparBufferEntrada(); //chama o limpador de buffer  
    getchar();

    
    strncpy(materia_vet[index_mat].professor, professor_vet[index_prof].nome, sizeof(materia_vet[index_mat].professor) - 1);
    materia_vet[index_mat].professor[sizeof(materia_vet[index_mat].professor) - 1] = '\0';
	//Copia o nome do professor para o campo professor da mat�ria selecionada, garantindo que a string esteja corretamente terminada com \0 (ou seja, sem \n)
    
    fseek(mat_data, 0, SEEK_SET);
    //Posiciona o ponteiro do arquivo de mat�rias no in�cio da mat�ria selecionada e grava os dados atualizados.
    fseek(mat_data, index_mat * sizeof(materia), SEEK_SET);
	 //Avan�a o ponteiro para a posi��o do struct da mat�ria selecionada.
    
    fwrite(&materia_vet[index_mat], sizeof(materia), 1, mat_data);
	//grava a o struct atualizado da mat�ria selecionada no arquivo.
    
    int found = 0;
    for (int j = 0; j < num_mat; j++) {
        if (strcmp(professor_vet[index_prof].materias[j], "...") == 0) {
            strncpy(professor_vet[index_prof].materias[j], materia_vet[index_mat].nome, sizeof(professor_vet[index_prof].materias[j]) - 1);
            professor_vet[index_prof].materias[j][sizeof(professor_vet[index_prof].materias[j]) - 1] = '\0';
            found = 1;
            break;
        }
    }//Atualiza o array de mat�rias do professor, encontrando o primeiro espa�o dispon�vel (representado por "...") e copiando o nome da mat�ria.

    if (!found) {
        printf("Nao ha espaco para adicionar mais materias ao professor.\n");
    }//Se n�o houver espa�o dispon�vel para adicionar mais mat�rias ao professor, exibe uma mensagem de erro.

    
    fseek(prof_data, 0, SEEK_SET);
    //Posiciona o ponteiro do arquivo de professores no in�cio do professor selecionado e grava os dados atualizados.
    fseek(prof_data, index_prof * sizeof(professor), SEEK_SET);
	//Avan�a o ponteiro para a posi��o do struct do professor selecionado. 
	
	   
    fwrite(&professor_vet[index_prof], sizeof(professor), 1, prof_data);
	// Grava o struct atualizado do professor selecionado no arquivo.
    
    fclose(prof_data);
    fclose(mat_data);
    free(professor_vet);
    free(materia_vet);
	//Fecha os arquivos de professores e mat�rias, e libera a mem�ria alocada para os arrays.
	
    return;

}


int atualizar_aluno() {				//atualiza dados de um aluno no arquivo
    FILE *arquivo;					//ponteiro
    aluno aluno;					//armazena os dados de um aluno
    char nome_procurado[32];		//vetor/array para armazenar o nome do aluno a ser procurado
    int encontrado = 0;				//indica se o aluno foi encontrado

    printf("Nome do aluno: ");		//solicita o nome
    fgets(nome_procurado, sizeof(nome_procurado), stdin);
    //fgets l� uma linha de texto de um arquivo utilizando o nome_procurado, 
	//sizeof limita o tamanho m�ximo que pode ser lida 
	//stdin a entrada do teclado
    nome_procurado[strcspn(nome_procurado, "\n")] = 0; // Remove newline character
	// Remove o caractere (\n) de nova linha para n�o atrapalhar na compara��a
	
    arquivo = fopen("alunos.bin", "rb+");
    //abre o arquivo bin�rio para ler e escrever
    
    if (arquivo == NULL) {//verifica se houve erro na leitura
        printf("Erro ao abrir o arquivo.\n");
        return 1;
    }

    while (fread(&aluno, sizeof(aluno), 1, arquivo) == 1) {// Loop para ler cada registro de aluno no arquivo
        if (strcmp(aluno.nome, nome_procurado) == 0) { // Verifica se o nome do aluno corresponde ao procurado
            printf("Aluno encontrado:\nNome: %s\nCPF: %ld\n", aluno.nome, aluno.cpf); //imprime o nome do aluno encontrado, cpf e Id
            encontrado = 1;//marca como encontrado
            printf("Insira o nome da materia: ");
            fgets(aluno.materias[0], sizeof(aluno.materias[0]), stdin);// recebe a nova mat�ria
            aluno.materias[0][strcspn(aluno.materias[0], "\n")] = 0; // novamente ignora o "\n" 

            fseek(arquivo, -sizeof(aluno), SEEK_CUR);//move o ponteiro de volta a posi��o do ultimo registro (escrito ou lido), para sobrescrever com novos dados
            //fseek move o ponteiro
			//"arquivo" � onde a opera��o ser� realizada 
			//"-sizeof(aluno)" � o desloca o arquivo para atr�s do arquivo
            //"SEEK_CUR" indica que o deslocamento deve ser feito em rela��o a posi��o atual do arquivo
            fwrite(&aluno, sizeof(aluno), 1, arquivo);//escreve os novos dados do aluno no arquivo
            break;//saindo do loop
        }
    }

    if (!encontrado) {//caso n�o encontrado...
        printf("Item com o nome '%s' nao encontrado.\n", nome_procurado);
    }

    fclose(arquivo);//fecha o arquivo
    return 0;//retorna 0, indicando sucesso
}

int atualizar_professor() {//atualiza os dados de um professor no arquivo

	//		Declara��es e inicialiaza��es
    FILE *arquivo;				// Declara um ponteiro para o arquivo
    professor professor;		// Declara uma vari�vel do tipo 'professor'
    char nome_procurado[48];	// Declara um vetor de caracteres para armazenar o nome procurado
    int encontrado = 0;			// vari�vel para verificar se o professor foi encontrado

	//		Entrada do usu�rio
    printf("Nome do professor: ");
    fgets(nome_procurado, sizeof(nome_procurado), stdin);
    //"fgets" l� o nome digitado pelo usu�rio
    //"nome_procurado" � o vetor onde armazena esse dado
    //sizeof limita o tamanho para ser lido
    //"stdin" inclui o caractere de nova linha '\n' que � inserido ao pressionar Enter
    nome_procurado[strcspn(nome_procurado, "\n")] = 0; // remove nova linha gerado pelo '\n'

	//		Abertura do Arquivo
    arquivo = fopen("professor.bin", "rb+");
	//abre o arquivo professor.bin (bin de bin�rio)
	//"rb" � para ler e escrever sem apagar
    if (arquivo == NULL) {
    	//verifica se foi poss�vel abrir com sucesso
    	//se for NULL, significa que houve um erro
        printf("Erro ao abrir o arquivo.\n");//informa o erro
        return 1;  //retorna 1 para indicar que houve erro ao abrir o arquivo
    }

	//		Leitura e Atualiza��o do Arquivo
    while (fread(&professor, sizeof(professor), 1, arquivo) == 1) {
    	//Enquanto 'professor', onde os dados lidos do arquivo ser�o armmazenados, sizeof limitando o tamanho de dados a serem lidos
    	//"Fread" usado para ler arquivos em bin�rio
    	//1 � para o n�mero de �tens
    	//arquivo � o ponteiro para o arquivo bin�rio aberto, de onde os dados ser�o lidos
        if (strcmp(professor.nome, nome_procurado) == 0) {
        	//Compara os nomes no arquivo 'professor' com o nome procurado
            printf("Professor encontrado:\nNome: %s\nCPF: %ld\n", professor.nome, professor.cpf);
            encontrado = 1;//retorna sucesso ao encontrar
            printf("Insira o nome da materia: ");
            fgets(professor.materias[0], sizeof(professor.materias[0]), stdin);
            //l� o nome da mat�ria
            //"fgets" l� o nome digitado pelo usu�rio
    		//"professor.materias" � o vetor onde armazena esse dado
    		//sizeof limita o tamanho para ser lido
    		//"stdin" inclui o caractere de nova linha '\n' que � inserido ao pressionar Enter
            professor.materias[0][strcspn(professor.materias[0], "\n")] = 0; // Remove '\n'

            fseek(arquivo, -sizeof(professor), SEEK_CUR);//move o ponteiro para antes do registro de professor
            fwrite(&professor, sizeof(professor), 1, arquivo);//escreve os dados atualizados do professor no arquivo
            break;
        }
    }

    if (!encontrado) {//se n�o encontrado o professor...
        printf("Item com o nome '%s' nao encontrado.\n", nome_procurado);
    }

    fclose(arquivo);//fecha arquivo
    return 0;//retorna 0 para indicar sucesso
}

aluno cad_aluno() {		//fun��o para cadastrar um aluno novo
    aluno _aluno_;		//vari�vel aluno do tipo aluno
    init_aluno(&_aluno_);//inicializa a vari�vel aluno
    //define valores iniciais para os campos da estrutura para que tenham valores v�lidos
    printf("Nome: ");
    fgets(_aluno_.nome, sizeof(_aluno_.nome), stdin);//l� o nome do aluno a partir da entrada padr�o e armazena no campo at� o tamanho definido pelo 'sizeof'
    _aluno_.nome[strcspn(_aluno_.nome, "\n")] = 0; // Remove '\n' e substitui por \0 para terminar a string
    
	//leitura do cpf
	printf("CPF: ");
    scanf("%ld", &_aluno_.cpf);
    limparBufferEntrada();//chama essa fun��o que limpa o buffer
    //isso evita que entradas indesejadas interfiram com futuras leituras de entrada
    return _aluno_;//retorna a estrutura '_aluno_' preenchida
}

void* cadastrar_aluno() {//fun��o para o processo de cadastro de alunos
    //cadastra v�rios alunos e aramzena em bin�rio
   
    FILE *alunos_cad;//ponteiro para o arquivo
    int cont_cad = 0;//contador para a quantidade de alunos acadastrados
    char novo_cad;//para armazenar se o usu�rio deseja cadastrar um novo aluno ou n�o 
    int tamanho_alunos_cad;
    int reg_a_ult_cad;
    int arquivo_iniciado = 0;
    
    printf("Deseja cadastrar um aluno?\nDigite 's' para continuar ou 'n' para sair.\n");
    scanf("%c", &novo_cad);
    limparBufferEntrada();
    
    aluno *vet_aluno = NULL;//ponteiro para o vetor aluno que inicialmente � NULL

    
    
    while(novo_cad != 'n'){//fazer at�... o usu�rio digitar 'n'
        
        extende_mem_aluno(&vet_aluno, &cont_cad);
        //extende_mem_aluno expande o array vet_aluno para acomodar um novo aluno.
        vet_aluno[cont_cad - 1] = cad_aluno(); //Chama cad_aluno para cadastrar um novo aluno e armazena os dados no final do array vet_aluno.
        vet_aluno[cont_cad - 1].reg_a += cont_cad - 1; //Atualiza o campo reg_a do novo aluno.
        printf("Deseja cadastrar outro aluno?\nDigite 's' para continuar ou 'n' para sair.\n");
        scanf("%c", &novo_cad);
        limparBufferEntrada();

        while(novo_cad != 's' && novo_cad != 'n'){ //Se a entrada for inv�lida, pede repetidamente at� que o usu�rio digite uma entrada v�lida ('s' ou 'n').
            printf("Entrada invalida.\nDigite 's' para continuar ou 'n' para sair.\n");
            scanf("%c", &novo_cad);
            limparBufferEntrada();
        }

    }//Se o usu�rio digitar 's', o loop recome�a. Se digitar 'n', o loop termina.



    alunos_cad = fopen("alunos.bin", "rb");
    
    if(alunos_cad == NULL){ //caso tenha erro ao abrir o arquivo
    
        // printf("Erro ao abrir arquivo"); -> apagar se n�o usar mais(?)
        // exit(1);-> apagar se n�o usar mais(?)
        
        alunos_cad = fopen("alunos.bin", "wb");//abre ou cria o arquivo de alunos cadastrados no arquivo 'alunos.bin' e l�/escreve em bin�rio 'rb'
    }else{ //caso tenha aberto com sucesso
        alunos_cad = fopen("alunos.bin", "ab"); //abre o arquivo e adiciona os dados ao final do arquivo sem sobrescrever o que j� tinha 
        tamanho_alunos_cad = tamanho_arq(alunos_cad)/sizeof(aluno); //Calcula o n�mero de registros do tipo aluno j� presentes no arquivo. A fun��o tamanho_arq(alunos_cad) retorna o tamanho do arquivo em bytes. Dividindo pelo tamanho de um �nico registro aluno (sizeof(aluno)), obtemos o n�mero de registros.
        arquivo_iniciado = 1; //Define a vari�vel arquivo_iniciado como 1, indicando que o arquivo foi inicializado e cont�m registros.
        
    }

    if(arquivo_iniciado == 1){ //Verifica se arquivo_iniciado � 1, confirmando que o arquivo j� cont�m registros.
        for(int i = 0; i < cont_cad; i++ ){ //Um la�o for que percorre todos os novos registros de alunos armazenados no vetor vet_aluno.
            vet_aluno[i].reg_a += tamanho_alunos_cad;//Atualiza o valor do campo reg_a de cada novo aluno. Este campo � incrementado pelo n�mero de registros j� presentes no arquivo (tamanho_alunos_cad). Isso assegura que os registros dos novos alunos continuem a numera��o dos registros j� presentes no arquivo.
        }
    }

    
    fwrite(vet_aluno, sizeof(aluno), cont_cad, alunos_cad);//escreve o vetor 'vet_aluno' no arquivo 'alunos.bin'
    //'fwrite' escreve 'cont_cad' elementos, cada um com tamanho de 'sizeof(aluno)'
	printf("%d", cont_cad);


    fclose(alunos_cad);//fecha o arquivo
    free(vet_aluno);//libera mem�ria alocada para o vetor 'vet_aluno'

    return 0;//retorna 0 demonstrando que a fun��o foi conclu�da com sucesso
}

materia cad_materia() { 						//cadastra uma mat�rio
    materia _materia_;  						//Declara uma vari�vel local _materia_ do tipo materia. Esta vari�vel armazenar� os dados da mat�ria que ser� cadastrada.
    init_materia(&_materia_);					//Chama a fun��o init_materia
    printf("Nome da materia: ");
    fgets(_materia_.nome, sizeof(_materia_.nome), stdin); //Usa a fun��o fgets para ler uma linha de texto do stdin
    //sizeof(_materia_.nome) especifica o tamanho do buffer nome, garantindo que n�o se ultrapasse o tamanho alocado para o nome da mat�ria.
    _materia_.nome[strcspn(_materia_.nome, "\n")] = 0; // Remove '\n' e substitui por \0
    printf("Sigla: ");
    fgets(_materia_.sigla, sizeof(_materia_.sigla), stdin);//Usa a fun��o fgets para ler uma linha de texto do stdin e armazena esse texto no campo sigla da estrutura _materia_.
	//sizeof(_materia_.sigla) especifica o tamanho do buffer sigla, garantindo que n�o se ultrapasse o tamanho alocado para a sigla da mat�ria.
    _materia_.sigla[strcspn(_materia_.sigla, "\n")] = 0; // Remove '\n' e substitui por \0
    return _materia_;
}

void* cadastrar_materia() {
    FILE *materias_cad; //ponteiro do arquivo
    int cont_cad = 0;   //contador de quantas mat�rias foram cadastradas
    char novo_cad;		//usado para armazenar a resposta se deseja ou n�o continuar cadastrando as respostas

    materia *vet_materia = NULL;//Declara um ponteiro vet_materia para uma estrutura do tipo materia e o inicializa como NULL. Este ponteiro ser� usado para armazenar dinamicamente as mat�rias cadastradas.

	//		Loop de Cadastro
    do { //continua executando at� que novo_cad seja 'n'
        printf("Deseja cadastrar uma materia? Digite 's' para continuar ou 'n' para sair: ");
        scanf(" %c", &novo_cad);
        limparBufferEntrada();

        if (novo_cad == 's') {//Se o usu�rio digitar 's', a fun��o extende_mem_materia � chamada para aumentar a mem�ria alocada para o vetor vet_materia, permitindo armazenar mais mat�rias
            extende_mem_materia(&vet_materia, &cont_cad); //
            vet_materia[cont_cad - 1] = cad_materia(); //Chama a fun��o cad_materia para cadastrar uma nova mat�ria e armazena a mat�ria no vetor vet_materia na posi��o cont_cad - 1
            //Incrementa cont_cad para contabilizar a nova mat�ria cadastrada.
        }
    } while (novo_cad != 'n');

	//		Manipula��o de arquivo
    materias_cad = fopen("materia.bin", "wb");
    if (materias_cad == NULL) {
        printf("Erro ao abrir arquivo.\n");
        exit(1);
    }	//Abre (ou cria) o arquivo materia.bin no modo de escrita bin�ria (wb). O conte�do existente do arquivo ser� sobrescrito.
		//Verifica se o arquivo foi aberto com sucesso. Se n�o foi, imprime uma mensagem de erro e encerra o programa com exit(1).

    fwrite(vet_materia, sizeof(materia), cont_cad, materias_cad);
    printf("Total de matérias cadastradas: %d\n", cont_cad);
    //Escreve o conte�do do vetor vet_materia no arquivo materia.bin. O fwrite escreve cont_cad elementos, cada um com o tamanho sizeof(materia).
	//Imprime o n�mero total de mat�rias cadastradas.

    fclose(materias_cad);
    free(vet_materia);
    //Fecha o arquivo materia.bin.
	//Libera a mem�ria alocada dinamicamente para o vetor vet_materia.
    
    return 0;
    //Retorna 0, indicando que a fun��o foi executada com sucesso. Apesar da fun��o ter sido declarada como void*, ela retorna um inteiro
}

professor cad_professor() {
    professor _professor_;
    init_professor(&_professor_);
    //A fun��o cad_professor cria uma vari�vel _professor_ do tipo professor e a inicializa usando a fun��o init_professor.
    printf("Nome: ");
    fgets(_professor_.nome, sizeof(_professor_.nome), stdin);
    //A fun��o solicita ao usu�rio que insira o nome do professor e armazena essa informa��o na vari�vel _professor_.nome. Qualquer caractere de nova linha ('\n') no final � removido para garantir que a string seja bem formatada.
    _professor_.nome[strcspn(_professor_.nome, "\n")] = 0; // Remove newline character
    printf("CPF: ");
    scanf("%ld", &_professor_.cpf);
    //A fun��o solicita ao usu�rio que insira o CPF do professor e armazena essa informa��o na vari�vel _professor_.cpf. Ap�s a entrada, o buffer do teclado � limpo para evitar interfer�ncias em futuras leituras.
    limparBufferEntrada();
    return _professor_;//A fun��o retorna a estrutura _professor_ contendo os dados do professor rec�m-cadastrado.
}

void* cadastrar_professor() {
	//A fun��o cadastrar_professor manipula o arquivo de professores e usa vari�veis para contar e armazenar temporariamente os professores cadastrados
    FILE *professores_cad;
    int cont_cad = 0; //conta quantos professores foram cadastrados
    char novo_cad;//aramzena a resposta se vai querer ou n�o continuar cadastrando o novo professor

    professor *vet_professor = NULL;
    //Declara um ponteiro vet_professor do tipo professor, inicializado com NULL. Este ponteiro ser� usado para armazenar dinamicamente uma lista de professores.

	//		Loop de Cadastro
    do {
        printf("Deseja cadastrar um professor? Digite 's' para continuar ou 'n' para sair: ");
        scanf(" %c", &novo_cad);
        limparBufferEntrada();
        //Exibe uma mensagem perguntando ao usu�rio se deseja cadastrar um novo professor. L� a resposta do usu�rio e limpa o buffer de entrada para evitar problemas com entradas subsequentes.

        if (novo_cad == 's') {
            extende_mem_professor(&vet_professor, &cont_cad);
            vet_professor[cont_cad - 1] = cad_professor();
        }//Se a resposta for 's', a fun��o extende_mem_professor � chamada para ajustar o tamanho do vetor vet_professor e incrementar cont_cad
    } while (novo_cad != 'n');
    //Em seguida, chama a fun��o cad_professor para cadastrar um novo professor e armazena esse professor no vetor. O loop continua at� que o usu�rio digite 'n'.

	//		Manipula��o de Arquivo
    professores_cad = fopen("professor.bin", "wb");
    if (professores_cad == NULL) {
        printf("Erro ao abrir arquivo.\n");
        exit(1);
    }//Abre o arquivo professor.bin no modo "wb" (escrita bin�ria). Se o arquivo n�o puder ser aberto, exibe uma mensagem de erro e termina o programa.

    fwrite(vet_professor, sizeof(professor), cont_cad, professores_cad);
    printf("Total de professores cadastrados: %d\n", cont_cad);
    //Escreve o conte�do do vetor vet_professor no arquivo professor.bin, gravando cont_cad elementos de tamanho sizeof(professor). Em seguida, exibe o total de professores cadastrados.

    fclose(professores_cad);
    free(vet_professor);
    return 0;
    //Fecha o arquivo professores_cad para garantir que os dados sejam salvos corretamente. Libera a mem�ria alocada para vet_professor para evitar vazamento de mem�ria. A fun��o retorna 0, indicando que a opera��o foi conclu�da com sucesso.
}

void clear_screen() {
    #ifdef _WIN32 //#ifdef _WIN32 verifica se o c�digo est� sendo compilado em um ambiente Windows.
        system("cls");//Se estiver no Windows (_WIN32 � definido para sistemas Windows), ele executa o comando system("cls"), que limpa a tela no prompt de comando do Windows usando o comando cls.
    #else
        system("clear");//Se n�o estiver no Windows, ou seja, em sistemas Unix-like, ele executa o comando system("clear"), que limpa a tela usando o comando clear.
    #endif
}

void extende_mem_aluno(aluno **vet_cad, int *cont_cad) {//estende a mem�ria alocada dinamicamente para armazenar informa��es sobre os alunos
    //Ela recebe um ponteiro para ponteiro de aluno (aluno **vet_cad) e um ponteiro para inteiro (int *cont_cad).
	//O ponteiro para ponteiro de aluno (aluno **vet_cad) � usado para que as altera��es feitas na aloca��o de mem�ria dentro da fun��o sejam refletidas fora dela. Isso permite que o vetor de alunos seja modificado mesmo ap�s o retorno da fun��o.
	*cont_cad += 1; //incrementa o contador de alunos
    aluno *temp = realloc(*vet_cad, (*cont_cad) * sizeof(aluno)); //realloc � usado para alterar o tamanho da mem�ria previamente alocada.
    //(*cont_cad) * sizeof(aluno) calcula o novo tamanho em bytes com base no n�mero atual de alunos.
    if (temp == NULL) {
        printf("Erro ao alocar memória\n");
        exit(1);
    }
	//Se for bem-sucedida, atualiza o ponteiro vet_cad para apontar para a nova mem�ria alocada (*vet_cad = temp;).
	//Se n�o for bem-sucedida, exibe uma mensagem de erro e encerra o programa.
    *vet_cad = temp;//atualiza o ponteiro original para que ele aponte para a nova �rea de mem�ria, garantindo que o vetor de alunos seja estendido corretamente e que as altera��es persistam fora da fun��o.
}

void extende_mem_materia(materia **vet_cad, int *cont_cad) {
	//Esta fun��o recebe dois argumentos:
	//vet_cad: Um ponteiro para um ponteiro de materia. Isso significa que vet_cad cont�m o endere�o de mem�ria de um vetor de materiais.
	//cont_cad: Um ponteiro para um inteiro que mant�m o n�mero atual de elementos no vetor.
    *cont_cad += 1; //aciona +1 ao contador de materias ao vetor
    materia *temp = realloc(*vet_cad, (*cont_cad) * sizeof(materia));
    //materia *temp: Declara��o de um ponteiro tempor�rio para materiais.
    //realloc(*vet_cad, (*cont_cad) * sizeof(materia)): Esta fun��o tenta realocar mem�ria para o vetor de materiais. Se bem-sucedida, ela aumentar� o tamanho do vetor para acomodar mais um material. *vet_cad cont�m o endere�o do vetor de materiais, e (*cont_cad) * sizeof(materia) calcula o tamanho necess�rio para o vetor.
    if (temp == NULL) {
        printf("Erro ao alocar memoria\n");
        exit(1);
        //Verifica se a realoca��o de mem�ria foi bem-sucedida. Se temp for NULL, significa que a realoca��o falhou, ent�o exibimos uma mensagem de erro e encerramos o programa.
    }
    *vet_cad = temp;
    //Atualiza o ponteiro vet_cad para apontar para a nova �rea de mem�ria alocada. Se a realoca��o de mem�ria for bem-sucedida, o endere�o de temp � atribu�do a *vet_cad, garantindo que o vetor original agora aponte para a nova �rea de mem�ria.
}

void extende_mem_professor(professor **vet_cad, int *cont_cad) { //Essa fun��o basicamente estende dinamicamente o vetor de professores para acomodar mais um professor, garantindo que n�o percamos os dados j� existentes e que possamos adicionar novos professores ao vetor.
	//Esta fun��o recebe dois argumentos:
	//vet_cad: Um ponteiro para um ponteiro de professor. Isso significa que vet_cad cont�m o endere�o de mem�ria de um vetor de professores.
	//cont_cad: Um ponteiro para um inteiro que mant�m o n�mero atual de elementos no vetor.
    *cont_cad += 1;
    //*cont_cad += 1;: Isso aumenta o valor do contador de professores em 1. Ou seja, estamos dizendo que queremos adicionar mais um professor ao vetor.
    professor *temp = realloc(*vet_cad, (*cont_cad) * sizeof(professor));
    //professor *temp: Declara��o de um ponteiro tempor�rio para professores.
    //realloc(*vet_cad, (*cont_cad) * sizeof(professor)): Esta fun��o tenta realocar mem�ria para o vetor de professores. Se bem-sucedida, ela aumentar� o tamanho do vetor para acomodar mais um professor. *vet_cad cont�m o endere�o do vetor de professores, e (*cont_cad) * sizeof(professor) calcula o tamanho necess�rio para o vetor.
    if (temp == NULL) {
        printf("Erro ao alocar memoria\n");
        exit(1);
    }//Verifica se a realoca��o de mem�ria foi bem-sucedida. Se temp for NULL, significa que a realoca��o falhou, ent�o exibimos uma mensagem de erro e encerramos o programa.
    *vet_cad = temp;
    //Atualiza o ponteiro vet_cad para apontar para a nova �rea de mem�ria alocada. Se a realoca��o de mem�ria for bem-sucedida, o endere�o de temp � atribu�do a *vet_cad, garantindo que o vetor original agora aponte para a nova �rea de mem�ria.
}

int ler_alunos() {
    
    int num_alunos; //armazena n�mero total de alunos

    aluno *alunos_cad; // Ponteiro para armazenar os alunos lidos do arquiv

    FILE *arquivo_alunos_cad; // Ponteiro para o arquivo de alunos

    arquivo_alunos_cad = fopen("alunos.bin", "rb"); // Abre o arquivo de alunos para leitura bin�ria

    if(arquivo_alunos_cad == NULL){// Verifica se houve erro na abertura do arquivo
        printf("Erro ao abrir o arquivo");
        return 1;// Retorna 1 para indicar erro
    }

    fseek(arquivo_alunos_cad,0,SEEK_END); // Move o cursor para o final do arquivo
    int tamanho_arq = ftell(arquivo_alunos_cad);// Obt�m o tamanho do arquivo em bytes
    fseek(arquivo_alunos_cad,0,SEEK_SET);// Move o cursor de volta para o in�cio do arquivo

    num_alunos = tamanho_arq / sizeof(aluno);// Calcula o n�mero de alunos no arquivo

    alunos_cad = malloc(sizeof(aluno) * num_alunos);// Aloca mem�ria para armazenar os alunos

    fread(alunos_cad, sizeof(aluno), num_alunos, arquivo_alunos_cad);// L� os alunos do arquivo para a mem�ria

    for(int i = 0; i < num_alunos; i++){// Loop para imprimir os dados de cada aluno
        printf("\n");
        printf(" nome: %s\n Reg.Acad.: %d\n CPF:%ld\n Privilegio: %d\n", alunos_cad[i].nome,alunos_cad[i].reg_a, alunos_cad[i].cpf,alunos_cad[i].priv);
        printf(" Matérias: ");
        for(int j = 0; j < 3; j++ ){// Loop para imprimir as mat�rias do aluno
            if(j == 0){
                printf("%s",alunos_cad[i].materias[j]);
            }else{
                printf("\n           %s",alunos_cad[i].materias[j]);
            }
            
        }
        printf("\n\n"); 
    }
}

int ler_materia() {
    
    int num_materias;// Vari�vel para armazenar o n�mero total de mat�rias

    materia *materias_cad;// Ponteiro para armazenar as mat�rias lidas do arquivo

    FILE *arquivo_materias_cad;// Ponteiro para o arquivo de mat�rias

    arquivo_materias_cad = fopen("materia.bin", "rb");// Abre o arquivo de mat�rias para leitura bin�ria


    if(arquivo_materias_cad == NULL){ //// Verifica se houve erro na abertura do arquivo
        printf("Erro ao abrir o arquivo");
        return 1; // Retorna 1 para indicar erro
    }


    fseek(arquivo_materias_cad,0,SEEK_END);// Move o cursor para o final do arquivo
    int tamanho_arq = ftell(arquivo_materias_cad);// Obt�m o tamanho do arquivo em bytes
    fseek(arquivo_materias_cad,0,SEEK_SET);// Move o cursor de volta para o in�cio do arquivo


    num_materias = tamanho_arq / sizeof(materia);// Calcula o n�mero de mat�rias no arquivo

    materias_cad = malloc(sizeof(materia) * num_materias);// Aloca mem�ria para armazenar as mat�rias

    fread(materias_cad, sizeof(materia), num_materias, arquivo_materias_cad);// L� as mat�rias do arquivo para a mem�ria


    for(int i = 0; i < num_materias; i++){// Loop para imprimir os dados de cada mat�ria
        printf("\n");
        printf(" nome: %s\n Sigla: %s\n Professor: %s\n\n", materias_cad[i].nome, materias_cad[i].sigla, materias_cad[i].professor);
    }
}

int ler_professor() {
    
    int num_professores;// Vari�vel para armazenar o n�mero total de professores

    professor *professores_cad;// Ponteiro para armazenar os professores lidos do arquivo

    FILE *arquivo_professores_cad;// Ponteiro para o arquivo de professores

    arquivo_professores_cad = fopen("professor.bin", "rb");// Abre o arquivo de professores para leitura bin�ria

    if(arquivo_professores_cad == NULL){ //// Verifica se houve erro na abertura do arquivo
        printf("Erro ao abrir o arquivo");
        return 1;// Retorna 1 para indicar erro
    }

    fseek(arquivo_professores_cad,0,SEEK_END);// Move o cursor para o final do arquivo
    int tamanho_arq = ftell(arquivo_professores_cad);// Obt�m o tamanho do arquivo em bytes
    fseek(arquivo_professores_cad,0,SEEK_SET);// Move o cursor de volta para o in�cio do arquivo

    num_professores = tamanho_arq / sizeof(professor);// Calcula o n�mero de professores no arquivo

    professores_cad = malloc(sizeof(professor) * num_professores);// Aloca mem�ria para armazenar os professores

    fread(professores_cad, sizeof(professor), num_professores, arquivo_professores_cad);// L� os professores do arquivo para a mem�ria

    for(int i = 0; i < num_professores; i++){// Loop para imprimir os dados de cada professor
        printf("\n");
        printf(" nome: %s\n CPF:%ld\n Privilégio: %d\n", professores_cad[i].nome, professores_cad[i].cpf,professores_cad[i].priv);
        printf(" Materias: ");
        for(int j = 0; j < 3; j++ ){
            if(j == 0){
                printf("%s",professores_cad[i].materias[j]);
            }else{
                printf("\n           %s",professores_cad[i].materias[j]);
            }
            
        }
        printf("\n\n");
    }
}

void limparBufferEntrada() {
    int c; //// Vari�vel para armazenar cada caractere lido do buffer
    while ((c = getchar()) != '\n' && c != EOF){};// Loop para ler e descartar caracteres do buffer at� encontrar '\n' (quebra de linha) ou EOF (final do arquivo)
	// Este loop continua enquanto o caractere atual n�o for uma quebra de linha '\n' e n�o for o final do arquivo EOF
	// Isso garante que o buffer seja totalmente limpo at� o pr�ximo '\n' ou EOF
}

int tamanho_arq(FILE *data_set) {

    fseek(data_set, 0, SEEK_END);
    // Move o indicador de posi��o do arquivo para o final do arquivo
    //Isso � feito para determinar o tamanho total do arquivo.
    
    int tamanho_arq = ftell(data_set);
    // Obtem a posi��o atual do indicador de posi��o, que � o tamanho do arquivo
    //int tamanho_arq = ftell(data_set): ftell() retorna a posi��o atual do indicador de posi��o do arquivo, que no caso de ter sido movido para o final do arquivo, � o tamanho do arquivo.
    
	fseek(data_set, 0, SEEK_SET);
    // Move o indicador de posi��o do arquivo de volta para o in�cio do arquivo
    //Move o indicador de posi��o do arquivo de volta para o in�cio do arquivo, para deixar o arquivo pronto para leitura ou escrita.
    
	return tamanho_arq;
    // Retorna o tamanho do arquivo em bytes
}

int main() { //main contendo os cases para chamar as fun��es
    int opcao;

    do {
        printf("\nSelecione uma opcao:\n");
        printf("1.Atribuir Materia\n");
        printf("2. Atualizar Aluno\n");
        printf("3. Atualizar Professor\n");
        printf("4. Cadastrar Aluno\n");
        printf("5. Cadastrar Materia\n");
        printf("6. Cadastrar Professor\n");
        printf("7. Ler Alunos\n");
        printf("8. Ler Materia\n");
        printf("9. Ler Professor\n");
        printf("10. Sair\n");
        printf("Digite a opcao desejada: ");
        scanf("%d", &opcao);
        limparBufferEntrada();

        switch (opcao) {
            case 1:
                atribuicao_mat();
                break;
            case 2:
                atualizar_aluno();
                break;
            case 3:
                atualizar_professor();
                break;
            case 4:
                cadastrar_aluno();
                break;
            case 5:
                cadastrar_materia();
                break;
            case 6:
                cadastrar_professor();
                break;
            case 7:
                ler_alunos();
                break;
            case 8:
                ler_materia();
                break;
            case 9:
                ler_professor();
                break;
            case 10:
                printf("Saindo...\n");
                break;
            default:
                printf("Opcao invalida. Tente novamente.\n");
                break;
        }
    } while (opcao != 10);

    return 0;
}
