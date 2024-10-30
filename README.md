# Compiladores

FONTE: MATERIAL DE LABORATORIO DE COMPILADORES DO PROFESSOR JUDSON SANTOS SANTIAGO

O LINK DO GITHUB DO CODIGO FONTE DO ANALISADOR LEXICO PODE ACESSADO:

https://github.com/JudsonSS/Compiladores/tree/2e1b81ba859e18e938ea149d1cef2edea04dde36/Labs/Lab06



## Para rodar o projeto:

### [Como Instalar GCC/G++ MinGW no Windows:](https://terminalroot.com.br/2022/12/como-instalar-gcc-gpp-mingw-no-windows.html)

### Comandos uteis para rodar o projeto:

#### Para rodar o Lab06
cd Lab06

g++ -o lexer lexer.cpp expressions.cpp

Get-Content input.txt | ./lexer.exe



#### Para rodar o Lab10:
cd Lab10


<!-- Para o teste 1 -->

g++ -o Lab10/Ast/Testes/teste1.exe `
Lab10/Ast/main.cpp `
Lab10/Ast/ast.cpp `
Lab10/Ast/lexer.cpp `
Lab10/Ast/parser.cpp `
Lab10/Ast/error.cpp `
Lab10/Ast/symtable.cpp `
Lab10/Ast/checker.cpp `
-std=c++17

.\Lab10\Ast\Testes\teste1.exe Lab10/Ast/Testes/teste1.cpp


<!-- Para o teste 2 -->
g++ -o Lab10/Ast/Testes/teste2.exe `
Lab10/Ast/main.cpp `
Lab10/Ast/ast.cpp `
Lab10/Ast/lexer.cpp `
Lab10/Ast/parser.cpp `
Lab10/Ast/error.cpp `
Lab10/Ast/symtable.cpp `
Lab10/Ast/checker.cpp `
-std=c++17

.\Lab10\Ast\Testes\teste2.exe Lab10/Ast/Testes/teste2.cpp




#### Para rodar o Lab11: 

Para rodar e testar o código com as modificações que fizemos, você precisará seguir alguns passos. Vou detalhar o processo abaixo:

### Requisitos
1. **Compilador C++**: Certifique-se de que você tem um compilador C++ instalado (como `g++`).
2. **CMake**: O projeto parece usar CMake para configuração, então você precisará do CMake instalado para compilar o projeto.

### Passos para compilar e rodar

1. **Baixe o projeto**:
   - Extraia o arquivo zip atualizado (`Lab11.zip`) em um diretório local.

2. **Abra um terminal** (ou um prompt de comando se estiver no Windows).

3. **Navegue até o diretório do projeto**:
   ```bash
   cd caminho/para/Lab11
   ```

4. **Crie um diretório build** (para não misturar os arquivos de compilação com os arquivos de origem):
   ```bash
   mkdir build
   cd build
   ```

5. **Execute o CMake** para configurar o projeto:
   ```bash
   cmake ..
   ```

6. **Compile o projeto**:
   ```bash
   make
   ```

7. **Rode o projeto**:
   Após a compilação, o executável estará disponível no diretório `build`. Para rodar o código usando o teste fornecido no arquivo `teste4.cpp`, execute:
   ```bash
   ./nome_do_executavel Testes/teste4.cpp
   ```

   Substitua `nome_do_executavel` pelo nome gerado após a compilação (pode ser algo como `tradutor`, dependendo de como foi configurado).

### Verificar o código intermediário gerado
Ao rodar o código com `teste4.cpp`, você verá o código intermediário gerado no terminal, que deve ser semelhante ao exemplo fornecido na questão.

Se você tiver dúvidas adicionais sobre o processo, estarei à disposição!



O erro que você está recebendo indica que o comando `cmake` não está disponível no seu sistema, o que significa que o CMake não está instalado ou não foi configurado corretamente no seu ambiente. Vamos resolver isso instalando o CMake e configurando o ambiente de compilação.

### Passos para instalar o CMake no Windows:

1. **Instale o CMake**:
   - Baixe o CMake no site oficial: [https://cmake.org/download/](https://cmake.org/download/)
   - Escolha a versão para Windows e baixe o instalador.
   - Durante a instalação, marque a opção **"Add CMake to the system PATH"** para garantir que você possa executar o `cmake` diretamente do terminal.

2. **Verifique se o CMake foi instalado corretamente**:
   Após a instalação, abra um **novo terminal** ou **Prompt de Comando** e digite:
   ```bash
   cmake --version
   ```
   Isso deve exibir a versão do CMake instalada, confirmando que a instalação foi bem-sucedida.

### Compilando o projeto:

Após instalar o CMake:

1. **Navegue até o diretório do projeto** no terminal:
   ```bash
   cd C:\Users\rafae\vscodeworkbench\compiladores\Lab11
   ```

2. **Crie o diretório `build` e configure o CMake**:
   ```bash
   mkdir build
   cd build
   cmake ..
   ```

3. **Compile o projeto**:
   ```bash
   make
   ```

4. **Execute o projeto**:
   Após a compilação, execute o projeto com o teste fornecido:
   ```bash
   ./nome_do_executavel ..\Testes\teste4.cpp
   ```

Se o CMake estiver corretamente instalado e o caminho estiver configurado no sistema, esses passos permitirão que você compile e execute o projeto corretamente. Se houver mais algum problema, estou à disposição para ajudar!





cmake -G "MinGW Makefiles" -DCMAKE_C_COMPILER=C:/mingw64/bin/gcc.exe -DCMAKE_CXX_COMPILER=C:/mingw64/bin/g++.exe -DCMAKE_MAKE_PROGRAM=C:/mingw64/bin/make.exe

make


g++ teste1.cpp -o teste1
g++ teste2.cpp -o teste2
g++ teste3.cpp -o teste3
g++ teste4.cpp -o teste4



.\teste1.exe
.\teste2.exe
.\teste3.exe
.\teste4.exe
