/*
#############################################################################################
#    CSpace - space simulator																#
#    Copyright (C) 2016  emanuele.sorce@hotmail.com											#
#																							#
#    This program is free software; you can redistribute it and/or modify					#
#    it under the terms of the GNU General Public License as published by					#
#    the Free Software Foundation, version 3 or compatibles.								#
#																							#
#    This program is distributed in the hope that it will be useful,						#
#    but WITHOUT ANY WARRANTY; without even the implied warranty of							#
#    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the							#
#    GNU General Public License for more details.											#
#																							#
#    You should have received a copy of the GNU General Public License						#
#    along with this program; if not, write to the Free Software							#
#    Foundation, Inc.																		#
#############################################################################################
 *
 * In this file there are functions that manage type
 * 
 *
 *
 * Prototipes:
 */
	/***
	 * The function InitObject set the type structure reading it from a file and return his address
	 */
	tStype *Inittype (FILE *stream, tinf *inf) {
		
		// The type mean structure (static because must be passed to others functions)
		static tStype types_struct;
		//counter
		int i;
	
		// read how many types there are in the file
		fscanf(stream, "%i\n\n", &types_struct.number);
		
		//alloc enought spaces for all the ttype structure
		types_struct.type = (ttype *) malloc (types_struct.number * sizeof(ttype));
		for(; types_struct.type == NULL;) {
			OPSML(inf);
			types_struct.type = (ttype *) malloc (types_struct.number * sizeof(ttype));
		}
		
		for (i=0; i!=types_struct.number; i++) {
			//scan name, description and parent
			ScanFString (types_struct.type[i].name, stream);
			ScanFString (types_struct.type[i].description, stream);
			ScanFString (types_struct.type[i].parent, stream);
			fscanf(stream, "\n");
		}
	
		return &types_struct;
	}
	
	/***
	 * Given a name, this function return the pointer to that type. If there isn't any type whit that name return NULL
	 */
	ttype *typeSearchName(tStype *type, char *name) {
		//counter
		int i;
		//the loop that search the type whit the true name
		for(i=0; i!=type->number; i++) {
			//if the two name are equal
			if (0 == strcmp(type->type[i].name, name))
				 return &type->type[i];
		};
		
		return NULL;
	}
	
	
	
	/***
	 * This function return the descripiton of the type name
	 */ 
	char *typeDescriptionFromName (tStype *type, char *name) {

		// pointer to the requested type
		ttype *type_point;
		//Search the type whit that name
		type_point = typeSearchName (type, name);
		if(type_point!=NULL)
			return type_point->description;
		else
			return "This object type doesn't exist";
	}
	
	/***
	 * This function return the parent of the type name
	 */ 
	char *typeParentFromName (tStype *type, char *name) {
	
		// pointer to the requested type
		ttype *type_point;
		//Search the type whit that name
		type_point = typeSearchName (type, name);
		if(type_point!=NULL)
			return type_point->parent;
		else
			return "This object type doesn't exist";
	}
	 
	/***
	 * In the kind browser you can browse types in the type.typ file, see descriptions and choose one type to return to the calling function
	 * 
	 * file is the source struct
	 * title is an intestation to write as title
	 * if v is 0 we woudn't	return a type (so the UI changes respect 1)
	 * if v isn't 0			return a type
	 */ 
	ttype *TypeBrowser(tinf *inf, tStype *Stype, char *title) {
		 
		//in the gerarchic tree of type, is the common parent that the types shown have
		char commonparent[NAMELUN] = "NULL";
		// static buffer and dinamic buffer
		char sbuf[BUFFERSIZE];
		char dbuf[BUFFERSIZE];
		//temp pointer
		ttype *temp;
		//temp string
		char number[4];
		//counters
		int i;
		int maxnum;
		//pointer to the first member of an array where are stored the pointer to the right types, whit order from the number printed
		ttype **npoint = (ttype **) malloc (sizeof(ttype *) * Stype->number);
		//inputs
		int input;
		int input2;
		
		//initialize the buffers
		strcpy (sbuf, title);
		strcat (sbuf, "\n");
		
		//the main loop
		do {
			//reset the dinamic buffer
			strcpy(dbuf, sbuf);
			//write in the dbuf the parent if one else a generic word
			if (strcmp(commonparent, "NULL") != 0)
				strcat(dbuf, commonparent);
			else
				strcat(dbuf, "Object");
			strcat(dbuf, ":\n\n");
			//search for types that have have as parent commonparent and add them to the buffer
			i=0;
			maxnum=0;
			do{
				//if the type has commonparent as parent
				if(strcmp(Stype->type[i].parent, commonparent) == 0) {
					snprintf(number, 3, "%d", maxnum+1);
					strcat(dbuf, number);
					strcat(dbuf, ") ");
					strcat(dbuf, Stype->type[i].name);
					strcat(dbuf, "\n");
					npoint[maxnum] = &Stype->type[i];
					maxnum++;
				}
				//go to the next type
				i++;
			}
			while(i!=Stype->number);
		
			//add the description button
			maxnum++;
			snprintf(number, 4, "%d", maxnum);
			strcat(dbuf, "\n");
			strcat(dbuf, number);
			strcat(dbuf, ") description of an object\n");
			//add the back button
			maxnum++;
			snprintf(number, 3, "%d", maxnum);
			strcat(dbuf, number);
			strcat(dbuf, ") back to the top of the tree");
			
			//print
			OPS(inf, dbuf, NULL, NULL);
			
			// scan input
			SafeIScan(inf, &input);
			
			// make the numbers start from zero and go to the higher number-1
			input--;
			maxnum--;
			
			// control that the value given is valid, if not, restart.
			if (input < 0) {
				continue;
			}
			if (input > maxnum) {
				continue;
			}
			
			//if the value point to a type set this type as pointer and continue if the type is parent of some type, else exit the loop
			if (input < maxnum-1) {
				printf("\ninput:%i\n", input);
				printf("maxnum:%i\n", maxnum);
				printf("common:%s\n", commonparent);
				printf("point:%p\n", npoint[maxnum]);
				printf("delta:%s\n", npoint[maxnum]->name);
				strcpy(commonparent, npoint[maxnum]->name);
				input2 = 0;
				for(i=0; i!=Stype->number; i++) {
					if(strcmp(commonparent, Stype->type[i].parent) == 0)
						input2++;
				}
				if(input2 > 0) {
					free(*npoint);
					return &Stype->type[input-1];
				}
				continue;
			}
			//if is the description button
			if (input == maxnum-1){
				OPS(inf, "Of which type of object do you want an explaination? [type its maxnumber]", 0, 0);
				SafeIScan(inf, &input2);
				temp = typeSearchName(Stype, npoint[input-1]->name);
				strcpy(dbuf, temp->name);
				strcat(dbuf, ":");
				strcat(dbuf, "\n\nDescription:   ");
				strcat(dbuf, temp->description);
				if(strcmp(temp->parent, "NULL") != 0) {  
					strcat(dbuf, "\n\nThis type of object is under the category:   ");
					strcat(dbuf, temp->parent);
				}
				else
					strcat(dbuf, "\n\nThis type of object isn't under any category");
				strcat(dbuf, "\n\nPress a maxnumber to continue");
				OPS(inf, dbuf, 0, 0);
				SafeIScan(inf, &input2);
				continue;
			}
			//if is the back button return to the start
			if (input == maxnum){
				strcpy (commonparent, "NULL");
				continue;
			}
			
		}
		while(1);
		 
		return NULL;
	}
	 
	 
	 
