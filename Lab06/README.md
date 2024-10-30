# Para rodar o Lab06
cd Lab06

g++ -o lexer lexer.cpp expressions.cpp

Get-Content input.txt | ./lexer.exe