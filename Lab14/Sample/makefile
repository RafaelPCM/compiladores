# Para importar o FlexLexer.h no meu computador
# Compiladores
CC=g++
LEX=flex++
LEX=/msys64/usr/bin/flex++ # Apenas pro meu PC
CXXFLAGS += -I/usr/include -I/usr/include/flex/src -I"C:/msys64/usr/include"  # Apenas pro meu PC

# Dependências
all: sample

sample: sample.o parser.o lex.yy.o
	$(CC) $(CXXFLAGS) sample.o parser.o lex.yy.o -o sample

sample.o: sample.cpp parser.h
	$(CC) $(CXXFLAGS) -c -std=c++17 sample.cpp

parser.o: parser.cpp parser.h tokens.h
	$(CC) $(CXXFLAGS) -c -std=c++17 parser.cpp

lex.yy.o: lex.yy.cc tokens.h
	$(CC) $(CXXFLAGS) -c -std=c++17 lex.yy.cc

lex.yy.cc: lexer.l tokens.h
	$(LEX) lexer.l

clean:
	rm sample lex.yy.cc lex.yy.o parser.o sample.o



# # Arquivo antigo 
# # Compiladores
# CC=g++
# LEX=flex++

# # Dependências
# all: sample

# sample: sample.o parser.o lex.yy.o
# 	$(CC) sample.o parser.o lex.yy.o -o sample

# sample.o: sample.cpp parser.h
# 	$(CC) -c -std=c++17 sample.cpp

# parser.o: parser.cpp parser.h tokens.h
# 	$(CC) -c -std=c++17 parser.cpp

# lex.yy.o: lex.yy.cc tokens.h
# 	$(CC) -c -std=c++17 lex.yy.cc

# lex.yy.cc: lexer.l tokens.h
# 	$(LEX) lexer.l

# clean:
# 	rm sample lex.yy.cc lex.yy.o parser.o sample.o
