all:
	$(MAKE) basic

basic:
	mkdir -p bin
	$(MAKE) bison
	$(MAKE) flex
	g++ -std=c++14 bin/lex.yy.c bin/parser.tab.c -o compiler

bison:
	bison -d src/parser.y --verbose
	mv parser.tab.* bin

flex:
	flex src/scanner.l bin/parser.tab.h
	mv lex.yy.* bin

test_file:
	$(MAKE) basic
	#./compiler < tests/programs/programMy.imp > result
	./compiler < tests/jftt2018-testy/8-for.imp > result
	mr/maszyna-rejestrowa result

clear:
	rm -f compiler
	rm -f bin/parser.tab.*
	rm -f bin/lex.yy.*
	clear
