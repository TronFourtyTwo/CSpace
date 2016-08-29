/*
#############################################################################
#    CSpace - space simulator												#
#    Copyright (C) 2016  emanuele.sorce@hotmail.com							#
#																			#
#    This program is free software; you can redistribute it and/or modify	#
#    it under the terms of the GNU General Public License as published by	#
#    the Free Software Foundation, version 3 or compatibles.				#
#																			#
#    This program is distributed in the hope that it will be useful,		#
#    but WITHOUT ANY WARRANTY; without even the implied warranty of			#
#    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the			#
#    GNU General Public License for more details.							#
#																			#
#    You should have received a copy of the GNU General Public License		#
#    along with this program; if not, write to the Free Software			#
#    Foundation, Inc.														#
#############################################################################

 * The function OnlyPrintfSystem: print words in a simple behavior that adapts on the value of width and height
 * 
 * The advantages on use OnlyPrintfSystem is:
 * 		- A simply but nice automatic impagination that all function could use whit a simple call 
 * 		- make the program nice
 * 		- A very more simple algoritm (faster and lighter) respect more complex mode (like the AIB), but equally can adapts the width and height numbers
 * 		- Use only of the Standard C library for now
 *
 * 	NOTE:
 * 	OnlyPrintfSystem is often called OPS
 * 
 */

 /**Only Printf System */
	void OPS(char *phrase, void **var) {
	DebugPrint("ops");
	
	//loop counter
	int i;
	// counter for lines
	WORD linedone;
	// counter for columns
	WORD columndone;
	// the number of character of phrase elaborated
	QWORD chardone;
	// the number of space to leave blank at the start of every line (max one digit)
	BYTE theet = 0;
	// one if the buf is finished
	BYTE bufend = 0;
	// the position in the var array
	QWORD pos = 0;
	// the buffer to print, his size and position
	DWORD size = (inf.width-TWOFRAMELUN) * (inf.height-5) +1;
	char *buf = (char *) malloc (sizeof(char[size]));
	while (buf == NULL) {
		OPSML("OPS");
		buf = (char *) malloc (sizeof(char[size]));
	}
	DWORD bufpos = 0;
	
	
	//OPS PART ONE: writing the buffer. Elaborate the input and write it in buf
	for(chardone=0; bufpos!=size-1;) {
		
		// dinamic printing! (character that mean other character, here translated)
		if(phrase[chardone] == '%') {
			// advance to the next character
			chardone++;
			// an int value to print
			if(phrase[chardone] == 'i') {
				bufpos += sprintf(&buf[bufpos], "%d", *((int *)var[pos]) );
				pos++;
			}
			// an unsigned int value to print
			if(phrase[chardone] == 'u') {
				bufpos += sprintf(&buf[bufpos], "%u", *((unsigned int *)var[pos]) );
				pos++;
			}
			// a long double value to print
			else if(phrase[chardone] == 'l') {
				bufpos += sprintf(&buf[bufpos], "%.*Lf", inf.numprecision, *((long double *)var[pos]) );
				pos++;
			}
			// a string to print
			else if(phrase[chardone] == 's') {
				bufpos += sprintf(&buf[bufpos], "%s", (char *) var[pos]);
				pos++;
			}
			// a line to print , f mean '(f)inish line' | example: %f. => a line of '.' NOTE: whitout '\n'
			else if(phrase[chardone] == 'f') {
				chardone++;
				for(i=0; i!=inf.width-TWOFRAMELUN; i++) {
					buf[bufpos] = phrase[chardone];
					bufpos++;
				}
			}
			// the '%' character (%%)
			else if(phrase[chardone] == '%' ){
				buf[bufpos] = '%';
				bufpos++;
			}
			// advance to the next character
			chardone++;
		}
		// the bip character
		else if(phrase[chardone] == '\a') {
			printf("\a");	//bip the bip but don't transfer it to the second part
			chardone++;
		}
		// a normal character
		else if(phrase[chardone] != 0) {
			buf[bufpos] = phrase[chardone];
			chardone++;
			bufpos++;
		}
		//end of string
		else {
			//put in the buffer the END directive (&e) and exit
			buf[bufpos] = '&';
			bufpos++;
			buf[bufpos] = 'e';
			break;
		}
	}
	
	//OPS PART TWO: print the buf
	bufpos=0;
	printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n");
	//the first two line of the frame
	PrintLine(FRAMESTART, 0);
	printf("\n%s", FRAME);
	PrintLine(FRAMEEND, TWOFRAMELUN);
	printf("%s\n", FRAMER);
	//printf the buf
	for(linedone=0; linedone < inf.height-5; linedone++) {
		//the frame
		printf("%s", FRAME);
		//print the buf
		for(columndone=0; columndone < inf.width-TWOFRAMELUN; columndone++) {
			
			// PART ONE: check for directives. a directive started whit '&'
			if (buf[bufpos] == '&') {
				bufpos++;
				//if is the '&' character
				if(buf[bufpos] == '&') {
					printf("&");
					bufpos++;
				}
				//if is the (e)nd directive
				else if(buf[bufpos] == 'e') {
					bufend = 1;
				} 
				//if is a (t)heet directive
				else if(buf[bufpos] == 't') {
					bufpos++;
					// scan the new number
					if (buf[bufpos] == '0') theet=0;
					else if (buf[bufpos] == '1') theet=1;
					else if (buf[bufpos] == '2') theet=2;
					else if (buf[bufpos] == '3') theet=3;
					else if (buf[bufpos] == '4') theet=4;
					else if (buf[bufpos] == '5') theet=5;
					else if (buf[bufpos] == '6') theet=6;
					else if (buf[bufpos] == '7') theet=7;
					else if (buf[bufpos] == '8') theet=8;
					else if (buf[bufpos] == '9') theet=9;
					// or scan a letter whit a meaning 
					else if (buf[bufpos] == 'd') theet = THEETDESCR;	// for a description
					else if (buf[bufpos] == 'i') {						// for two digit theet
						bufpos++;
						if (buf[bufpos] == '0') theet=10;
						else if (buf[bufpos] == '1') theet=11;
						else if (buf[bufpos] == '2') theet=12;
						else if (buf[bufpos] == '3') theet=13;
						else if (buf[bufpos] == '4') theet=14;
						else if (buf[bufpos] == '5') theet=15;
						else if (buf[bufpos] == '6') theet=16;
						else if (buf[bufpos] == '7') theet=17;
						else if (buf[bufpos] == '8') theet=18;
						else if (buf[bufpos] == '9') theet=19;
					}	
				}
				bufpos++;
			}
			
			// PART TWO: print the buffer
			// if the buffer is finished print only spaces
			if (bufend == 1)
				printf(" ");
			// print a space if we are behind the theet
			else if (columndone < theet)
				printf(" ");
			// a space in the first column is ignored
			else if ((columndone == theet) && (buf[bufpos] == ' ')) {
				bufpos++;
				columndone--;
			}
			// a normal character
			else if (buf[bufpos] != '\n') {
				printf("%c", buf[bufpos]);
				bufpos++;
			}
			// a '\n' character
			else {
				// print the remaining space whit spaces
				PrintLine(" ", columndone+TWOFRAMELUN);
				bufpos++;
				// if there is space for more line print the new line
				if(linedone < inf.height-5) {
					printf("%s\n%s", FRAMER, FRAME);
					linedone++;
					columndone = -1;
				}
			}
		}
		//the frame
		printf("%s\n", FRAMER);
	}
	//last lines
	printf("%s", FRAME);
	PrintLine(FRAMEEND, TWOFRAMELUN);
	printf("%s\n", FRAMER);
	PrintLine(FRAMESTART, 0);
	printf("\n%s: ", FRAME);
	
	// finish the function
	free(buf);
	return;
	}
	
/***
 * OPSE (OnlyPrintfSystemError) printf an error message whit the OPS
 */
	void OPSE(char *message, void **var){
		DebugPrint("opse");
		
		//size of message
		WORD size;
		size = strlen(message);
		//the message to print
		char *buffer = (char *) malloc (sizeof(char[8+size]));
		while(buffer == NULL){
			OPSML("OPSE");
			buffer = (char *) malloc (sizeof(char[8+size]));
		}
		//a nice bip
		printf("\a");
		//set the buffer
		strcpy(buffer, "ERROR!\n\n");
		strcat(buffer, message);
		//printf the buffer
		OPS(buffer, var);
		//exit the function
		free(buffer);
		return;
	}

/***
 * OPSML (OnlyPrintfSystemMemorylack) is called when the memory lack to signal the problem
 */	
	void OPSML(char *data) {
		
		printf ("\n\n\n\n\aThe program has a problem whit memory allocation while: '%s'. Probably the RAM is overload. Press something to retry\n\t", data);
		DebugPrint("opsml: the program has problem whit memory allocation while:");
		DebugPrint(data);
		getchar();
		
		return;
	}
