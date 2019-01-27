all:
	@$(MAKE) basic > /dev/null 1> /dev/null 2> /dev/null

basic:
	mkdir -p bin
	$(MAKE) bison
	$(MAKE) flex
	g++ -std=c++14 bin/lex.yy.c bin/parser.tab.c -o compiler

bison:
	bison -d src/parser.y
	mv parser.tab.* bin

flex:
	flex src/scanner.l bin/parser.tab.h
	mv lex.yy.* bin

test_file:
	@$(MAKE) basic > /dev/null 1> /dev/null 2> /dev/null
	@./compiler < tests/jftt2018-testy/program0.imp > result
	@mr/maszyna-rejestrowa-cln result

clear:
	rm -f compiler
	rm -f bin/parser.tab.*
	rm -f bin/lex.yy.*
	clear
