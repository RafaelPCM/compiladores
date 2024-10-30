# Compiladores

FONTE: MATERIAL DE LABORATORIO DE COMPILADORES DO PROFESSOR JUDSON SANTOS SANTIAGO

O LINK DO GITHUB DO CODIGO FONTE DO ANALISADOR LEXICO PODE ACESSADO:

https://github.com/JudsonSS/Compiladores/tree/2e1b81ba859e18e938ea149d1cef2edea04dde36/Labs/Lab06



## Para rodar o projeto:

### [Como Instalar GCC/G++ MinGW no Windows:](https://terminalroot.com.br/2022/12/como-instalar-gcc-gpp-mingw-no-windows.html)


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

3. **Instalar e usar o nmake ou make**:
   O erro que menciona que nmake ou make não foram encontrados indica que essas ferramentas não estão instaladas ou configuradas no seu PATH.

   Instalar o NMake: O nmake é parte da instalação do Visual Studio. Certifique-se de que você tenha o Developer Command Prompt for Visual Studio disponível, que inclui o nmake automaticamente. Execute o comando nmake de dentro do Developer Command Prompt em vez do PowerShell.

   Instalar o make: Se você quiser usar o make, pode instalar o MSYS2 ou o MinGW no Windows. Isso fornecerá as ferramentas de desenvolvimento UNIX, como o make.

   Instale o MSYS2: MSYS2 Download (https://www.msys2.org/)
   Após a instalação, abra o terminal MSYS2 e instale o make com o comando:
   ```bash
   pacman -S make
   ```

4. Alternativa com Ninja:
   Se preferir usar outra ferramenta de build, pode instalar o Ninja, que também funciona com o CMake.

   Baixe o Ninja: Ninja Download (https://ninja-build.org/)
   Após baixar e adicionar o Ninja ao seu PATH, você pode usar o comando:

   ```bash
   cmake -G Ninja ..
   ninja
   ```

5. **Verificar o caminho do MinGW**:
   Certifique-se de que o MinGW (incluindo gcc, g++ e make) está instalado corretamente.
   O caminho para o MinGW deve estar incluído na variável de ambiente PATH do Windows.
   Se o MinGW não estiver instalado, você pode instalá-lo seguindo os passos abaixo:

   Instalar MinGW: Baixe o MinGW.
   Após a instalação, adicione o diretório bin do MinGW (onde gcc, g++, e make estão localizados) ao PATH do Windows.
   Para verificar se o MinGW está instalado e configurado corretamente, execute os seguintes comandos no terminal:

      ```bash
      gcc --version
      g++ --version
      make --version
      ```



### Possiveis Erros:

O erro indica que o CMake está tentando compilar um programa de teste simples, mas não conseguiu, provavelmente porque o caminho para o compilador MinGW ou para o make está incorreto ou não foi configurado corretamente. Além disso, o CMake tenta usar C:/mingw64/bin/gcc.exe, o que pode não estar no local certo.

Solução: Verificar a instalação e o caminho do MinGW
Aqui estão os passos para corrigir:

1. **Verifique o caminho do MinGW**
Certifique-se de que o MinGW esteja instalado corretamente e que o caminho para o binário do MinGW esteja correto. O caminho padrão do MinGW é geralmente C:/MinGW/bin, e não C:/mingw64/bin.

Verifique se o caminho do compilador gcc está correto. No terminal, rode:

```bash
where gcc
```
Isso deve mostrar o caminho para o gcc.

Se o gcc estiver em outro diretório (por exemplo, C:/MinGW/bin/gcc.exe), você precisará configurar o CMake para apontar para o local correto.

2. **Corrija o comando CMake com o caminho correto**
Com base na localização do gcc e do make, ajuste o comando para garantir que o CMake use o caminho correto. Aqui está um exemplo, assumindo que o MinGW está instalado em C:/MinGW:

```bash
cmake -G "MinGW Makefiles" -DCMAKE_C_COMPILER=C:/MinGW/bin/gcc.exe -DCMAKE_CXX_COMPILER=C:/MinGW/bin/g++.exe -DCMAKE_MAKE_PROGRAM=C:/MinGW/bin/make.exe
```
Esse comando garante que o CMake esteja usando os compiladores e o programa de build correto.

3. **Teste o CMake**
Depois de corrigir o caminho, tente novamente:

```bash
make
```


Resumo:
Verifique onde está instalado o gcc com o comando where gcc.
Ajuste o comando CMake para usar os caminhos corretos do gcc e make:
```bash
cmake -G "MinGW Makefiles" -DCMAKE_C_COMPILER=C:/MinGW/bin/gcc.exe -DCMAKE_CXX_COMPILER=C:/MinGW/bin/g++.exe -DCMAKE_MAKE_PROGRAM=C:/MinGW/bin/make.exe
```
Compile o projeto com make.


O problema está relacionado ao fato de o CMake não conseguir localizar o compilador GCC corretamente. Você mencionou que o caminho do GCC no seu sistema é C:\mingw64\bin\gcc.exe, mas no comando você estava especificando C:/MinGW/bin/gcc.exe, que não corresponde ao caminho correto.

Vamos corrigir isso configurando o caminho correto para o GCC e o G++.

Passos para corrigir:
Corrigir o comando CMake: Use o caminho correto para os compiladores gcc e g++, que no seu caso são encontrados em C:\mingw64\bin.

O comando atualizado será:

```bash
cmake -G "MinGW Makefiles" -DCMAKE_C_COMPILER=C:/mingw64/bin/gcc.exe -DCMAKE_CXX_COMPILER=C:/mingw64/bin/g++.exe -DCMAKE_MAKE_PROGRAM=C:/mingw64/bin/make.exe
```

Isso informará ao CMake onde encontrar o compilador correto e o make no caminho correto.

Verificar a instalação do MinGW: Como o caminho é C:\mingw64\bin\gcc.exe, verifique se você instalou o MinGW-w64 corretamente e se ele está configurado no PATH.

Execute o make novamente: Se o CMake for configurado corretamente, você pode compilar o projeto com:

```bash
make
```
