﻿# Sistema de Gerenciamento Acadêmico

## Descrição

Este projeto implementa um sistema de gerenciamento acadêmico utilizando arquivos binários para armazenar dados de estudantes e membros acadêmicos. As principais funcionalidades incluem leitura, escrita e atualização de registros de estudantes e membros acadêmicos, bem como a verificação de autenticação baseada em CPF e senha.

## Funcionalidades

### Estruturas de Dados
1. **membroAcademico**: Estrutura para armazenar informações de membros acadêmicos (professores e alunos), incluindo CPF, senha, nome, privilégio e matéria.
2. **Estudante**: Estrutura para armazenar informações de estudantes, incluindo nome, notas, média, faltas e situação (aprovado ou reprovado).

### Funções Principais
- **LerArquivo**: Lê um registro de estudante de um arquivo binário.
- **EscreverNoArquivo**: Escreve um registro de estudante em um arquivo binário.
- **EncontrarDadoPorNome**: Busca um registro de estudante no arquivo binário baseado no nome e retorna seus dados.
- **MostrarNotas**: Exibe as notas de um estudante específico.
- **MostrarFaltas**: Exibe as faltas e a situação de um estudante específico.
- **EscreverUsuario**: Escreve um registro de membro acadêmico em um arquivo binário.
- **VerificarCpfSenha**: Verifica se o CPF e a senha fornecidos correspondem a um registro de membro acadêmico no arquivo binário.
- **FormatarArquivo**: Formata o arquivo binário com registros de estudantes ou membros acadêmicos para testes.
- **AtribuirNotas**: Atualiza as notas de um estudante específico no arquivo binário.
- **RealizarChamada**: Atualiza as faltas de estudantes após realizar a chamada.

## Uso

### Compilação e Execução
Para compilar o programa, utilize um compilador C como `gcc`:
```sh
gcc -o sistema_academico sistema_academico.c
```

Para executar o programa, utilize:
```sh
./sistema_academico
```

### Formatação Inicial dos Arquivos
Antes de usar o sistema, formate os arquivos binários com registros de teste:
```c
FormatarArquivo("Estudantes.bin");
FormatarArquivoLogin("Usuarios.bin");
```

### Autenticação
Para acessar o sistema, os usuários devem autenticar-se fornecendo CPF e senha. O sistema verifica os dados e permite o acesso conforme o privilégio do usuário (professor ou aluno).

### Menu do Sistema
Após a autenticação, o usuário pode escolher entre as opções disponíveis:
- **Aviso**: Exibe mensagens para o usuário.
- **Notas**: Mostra as notas do estudante.
- **Faltas**: Mostra as faltas e a situação do estudante.
- **Sair**: Sai do sistema.

### Menu do Professor
Os professores têm opções adicionais:
- **Atribuir notas**: Permite atualizar as notas dos estudantes.
- **Realizar chamada**: Permite atualizar as faltas dos estudantes.
- **Fechamento da matéria**: Finaliza o período da matéria, calculando médias e situações finais.

## Estrutura do Código
O código está estruturado em funções que realizam operações específicas, facilitando a manutenção e a expansão do sistema. As funções são chamadas conforme a opção selecionada pelo usuário nos menus.

## Exemplo de Uso
```c
int main() {
    // Exemplo de inicialização do sistema e login de um usuário
    FormatarArquivo("Estudantes.bin");
    FormatarArquivoLogin("Usuarios.bin");

    membroAcademico usuario;
    if (VerificarCpfSenha("Usuarios.bin", "47735823109", "senha1", &usuario)) {
        Aluno(usuario);
    } else {
        printf("Autenticação falhou.\n");
    }

    return 0;
}
```

## Contribuições
Contribuições são bem-vindas! Sinta-se à vontade para abrir issues e pull requests.

## Licença
Este projeto está licenciado sob a MIT License.
