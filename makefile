cspace: color.o core_functions.o debug.o interface_functions.o main.o menù.o OnlyPrintfSystem.o OPSo.o Parser.o pmotor.o SDL_core.o shell.o string_functions.o type.o
		gcc -o cspace color.o core_functions.o debug.o interface_functions.o main.o menù.o OnlyPrintfSystem.o OPSo.o Parser.o pmotor.o SDL_core.o shell.o string_functions.o type.o CS_header.h -lm
main.o: main.c CS_header.h
	cc -c main.c -lm
color.o: color.c CS_header.h
	cc -c color.c -lm
core_functions.o: core_functions.c CS_header.h
	cc -c core_functions.c -lm
debug.o: debug.c CS_header.h
	cc -c debug.c -lm
interface_functions.o: interface_functions.c CS_header.h
	cc -c interface_functions.c -lm
menù.o: menù.c CS_header.h
	cc -c menù.c -lm
OnlyPrintfSystem.o: OnlyPrintfSystem.c CS_header.h
	cc -c OnlyPrintfSystem.c -lm
OPSo.o: OPSo.c CS_header.h
	cc -c OPSo.c -lm
Parser.o: Parser.c CS_header.h
	cc -c Parser.c -lm
pmotor.o: pmotor.c CS_header.h
	cc -c pmotor.c -lm
SDL_core.o: SDL_core.c CS_header.h
	cc -c SDL_core.c -lm
shell.o: shell.c CS_header.h
	cc -c shell.c -lm
string_functions.o: string_functions.c CS_header.h
	cc -c string_functions.c -lm
type.o: type.c CS_header.h
	cc -c type.c -lm
clean:
	rm color.o core_functions.o debug.o interface_functions.o main.o menù.o OnlyPrintfSystem.o OPSo.o Parser.o pmotor.o SDL_core.o shell.o string_functions.o type.o
