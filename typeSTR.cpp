/*
#############################################################################################
#    Tux in Space - space exploration game													#
#    Copyright (C) 2016-2017  emanuele.sorce@hotmail.com									#
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
 * the big type class 
 */
 
#include "typeSTR.h"

using namespace std;

/***
 * Build the type structure reading it from a file
 */
typeSTR::typeSTR (signal& result) {
	
	string buf;
	int num_types = 0;
	ifstream stream(TYPE_DATABASE_FILE);
	if(!stream) {
		result = signal::file_err;
		return;
	}
	
	// count how many types there are in the file

	while(1) {
		// read the line (jumping blank ones)
		in_hfs (buf, stream);
		if(!buf.length())
			continue;
		// if is a new object memorize that there is a new object
		if (!buf.compare(0, 6, "NAME: "))
			num_types++;
		// if the file is finished exit
		else if (!buf.compare(0, 3, "EOF"))
			break;
	}
		
	// alloc enought spaces for all the ttype structures
	t.resize(num_types);
	
	// NAME. scan all the names
	
	stream.close();
	stream.open(TYPE_DATABASE_FILE);
	
	if(!stream) {
		result = signal::file_err;
		return;
	}
	
		
	for(unsigned int i=0; i!=t.size(); i++) {
		do
			in_hfs(buf, stream);
		while
			(buf.compare(0, 6, "NAME: "));
		t[i].name = buf.substr(6, buf.length());
	}
	
	
	// PARENT. Set all the parent
	
	stream.close();
	stream.open(TYPE_DATABASE_FILE);
	
	if(!stream) {
		result = signal::file_err;
		return;
	}
		
	for(unsigned int i=0; i!=t.size(); i++) {
		do
			in_hfs(buf, stream);
		while
			(buf.compare(0, 8, "PARENT: "));
		string parent = buf.substr(8, buf.length());
		t[i].parent = Search(parent);
	}
	
	// OTHER STUFF
	
	stream.close();
	stream.open(TYPE_DATABASE_FILE);
	
	if(!stream) {
		result = signal::file_err;
		return;
	}
		
	// loop to scan every feature
	for(unsigned int i=0; i!=t.size(); i++) {
		
		// start assigning parent's values
		t[i].color_max = t[i].parent->color_max;
		t[i].color_min = t[i].parent->color_min;
		t[i].hunted = t[i].parent->hunted;
		t[i].hunter = t[i].parent->hunter;
		t[i].mass_max = t[i].parent->mass_max;
		t[i].mass_min = t[i].parent->mass_min;
		t[i].product = t[i].parent->product;
		t[i].merge = t[i].parent->merge;
		t[i].description.clear();
		// then scan own values over his parent ones
		
		// name, jump it
		in_hfs(buf, stream);
		
		
		while(1){
			
			in_hfs(buf, stream);
		  
			if(!buf.compare(0, 13, "DESCRIPTION: ")) {
				t[i].description = buf.substr(13, buf.length());
				continue;
			}
			// mass max:
			if(!buf.compare(0, 10, "MASS MAX: ")) {
				string temp = buf.substr(9, buf.length());
				t[i].mass_max = atof(temp.c_str());
				continue;
			}
			// mass min:
			if(!buf.compare(0, 10, "MASS MIN: ")) {
				string temp = buf.substr(9, buf.length());
				t[i].mass_min = atof(temp.c_str());
				continue;
			}
			// blue max:
			if(!buf.compare(0, 10, "BLUE MAX: ")) {
				string temp = buf.substr(10, buf.length());
				t[i].color_max.blue = atoi(temp.c_str());
				continue;
			}
			// blue min:
			if(!buf.compare(0, 10, "BLUE MIN: ")) {
				string temp = buf.substr(10, buf.length());
				t[i].color_min.blue = atoi(temp.c_str());
				continue;
			}
			// red max:
			if(!buf.compare(0, 9, "RED MAX: ")) {
				string temp = buf.substr(9, buf.length());
				t[i].color_max.red = atoi(temp.c_str());
				continue;
			}
			// red min:
			if(!buf.compare(0, 9, "RED MIN: ")) {
				string temp = buf.substr(9, buf.length());
				t[i].color_min.red = atoi(temp.c_str());
				continue;
			}
			// green max:
			if(!buf.compare(0, 11, "GREEN MAX: ")) {
				string temp = buf.substr(11, buf.length());
				t[i].color_max.green = atoi(temp.c_str());
				continue;
			}
			// green min:
			if(!buf.compare(0, 11, "GREEN MIN: ")) {
				string temp = buf.substr(11,buf.length());
				t[i].color_min.green = atoi(temp.c_str());
				continue;
			}
			// HUNTED:
			if(!buf.compare(0, 8,"HUNTED: ")) {
				if(buf[8] == 'N')
					t[i].hunted = false;
				else if (buf[8] == 'Y')
					t[i].hunted = true;
				else{
					debug_Printf(IRREGULARITY "Unvalid argurment at line:");
					debug_Printf(buf);
					debug_Printf("inside the object: " + t[i].name);
				}
				continue;
			}
			// HUNTER:
			if(!buf.compare(0, 8,"HUNTER: ")) {
				if(buf[8] == 'N')
					t[i].hunter = false;
				else if (buf[8] == 'Y')
					t[i].hunter = true;
				else{
					debug_Printf(IRREGULARITY "Unvalid argurment at line:");
					debug_Printf(buf);
					debug_Printf("inside the object: " + t[i].name);
				}
				continue;
			}
			// PRODUCT:
			if(!buf.compare(0, 9, "PRODUCT: ")) {
				string temp = buf.substr(9, buf.length());
				t[i].product = Search(temp);
				continue;
			}
			// MERGE:
			if(!buf.compare(0, 7, "MERGE: ")) {
				if(buf[7] == 'N')
					t[i].merge = false;
				else if (buf[7] == 'Y')
					t[i].merge = true;
				else{
					debug_Printf(IRREGULARITY "Unvalid argurment at line:");
					debug_Printf(buf);
					debug_Printf("inside the object: " + t[i].name);
				}
				continue;
			}
		
			// NOT PARSABLE LINE
			if(buf.compare(0, 8, "PARENT: ")) {
				debug_Printf(IRREGULARITY "typeSTR::typeSTR! Unparsable line");
				debug_Printf(buf);
				debug_Printf("inside object " + t[i].name);
				continue;
			}
			break;
		}
		// assign the description if none has been set
		if(!t[i].description.length())
			t[i].description =  "No description is available for this type yet";
	}
	
	debug_Stype(*this);
}



/***
 * Given a name, this function return the pointer to that type. If there isn't any type whit that name return nullptr
 */
type *typeSTR::Search (const string& tofind) {
	
	// the loop that search the type whit the right name
	for(unsigned int i=0; i!=t.size(); ++i)
		if (!t[i].name.compare(tofind))
			 return &t[i];
	
	debug_Printf("(!) typeSTR::Search: No type with this name has been found!");
	debug_Printf(tofind);
	
	return nullptr;
}



/***
 * In the kind browser you can browse types read from type.typ file and stored in Stype, see descriptions and choose one type to return to the calling function
 * 
 * file is the source struct
 * title is an intestation to write as title
 */ 
type& typeSTR::Browse(const setting& set, const string& title) {
		
	// in the gerarchic tree of types, is the common parent that the types listed have
	type *commonparent = Search("Object");
	type& genobj = *Search("Object");
	// the output buffer
	stringstream buf;
	// The pointers to the types listed
	vector<type *> types_listed;
	// input
	unsigned int input;

	// the main loop
	while(1) {
		types_listed.clear();
		buf.clear();
		buf.str("");
		// the title
		buf << title << "\n";
		// write in the dbuf the parent
		buf << commonparent->name << ":\n";
		// search for types that have as parent commonparent
		for (unsigned int i=0; i!=t.size(); i++) {
			// if the type has commonparent as parent
			if(t[i].parent == commonparent) {
				// if the type and his parent are the same, go ahead, because
				// it will be printed in the generic
				if(&t[i] == t[i].parent)
					continue;
				types_listed.push_back(&t[i]);
				buf << "\n" << types_listed.size() << ") " << t[i].name;
			}
		}
		// add the generic button
		buf << "\n";
		buf << types_listed.size() + 1;
		buf << ") Generic ";
		buf << commonparent->name;
		// add the description button
		buf << "\n\n";
		buf << types_listed.size() + 2;
		buf << ") description of an object";
		// add the back button
		buf << "\n";
		buf << types_listed.size() + 3;
		buf << ") back to the top";
		// print
		OPS(set, buf.str());
		
		// scan the input as long as a valid number is given
		do
			input = in_i();
		while ((input < 1) || (input > types_listed.size() + 3));
		
		// if the value point to a type, set this type as pointer and continue if the type is parent of some type, else exit the loop
		if (input <= types_listed.size()) {
			bool child = false;
			commonparent = types_listed[input-1];
			for(unsigned int i=0; i!=t.size(); i++) {
				if(commonparent == t[i].parent)
					child = true;
			}
			if(child == false) 
				return *commonparent;
		}
		// if is the generic xxx button
		else if (input == types_listed.size() + 1)
			return *commonparent;
		// if is the description button
		else if (input == types_listed.size() + 2) {
			
			// output
			buf.clear();
			buf.str("");
			buf << "Of which type of object do you want an explaination?\n";
			for(unsigned int i=0; i < types_listed.size(); i++)
				buf << "\n" << i+1 << ") " << types_listed[i]->name;
			// generic
			buf << "\n" << types_listed.size() +1 << ") Generic " << commonparent->name;
			
			OPS(set, buf.str());
			// input
			unsigned int n = in_i();
			
			// check that is a valid value
			if ((n < 1) || (n > types_listed.size() + 1)) {
				OPS(set, "There is no type with that number!\n\nPress something to continue...");
				in_s();
				continue;
			}
			
			// set the type
			type* type_descr;
			if(n == types_listed.size()+1)
				type_descr = commonparent;
			else
				type_descr = types_listed[n-1];
			buf.clear();
			buf.str("");
			buf << "Info about:  " << type_descr->name;
			buf << "\n\nDescription: &ti3" << type_descr->description << "&t0";
			buf << "\nUnder the category:&t9 " << type_descr->parent->name << "&t0";
			// the mass range
			buf << "\nMinimum mass: " << type_descr->mass_min;
			buf << "\nMaximum mass: " << type_descr->mass_max;
			// the color range
			buf << "\nColor range:\n&t9red: " << type_descr->color_min.red << " - " << type_descr->color_max.red;
			buf << "\ngreen: " << type_descr->color_min.green << " - " << type_descr->color_max.green;
			buf << "\nblue: " << type_descr->color_min.blue << " - " << type_descr->color_max.blue << "&t0";

			// finalizing the description page
			buf << "\n\nPress something to continue...";
			OPS(set, buf.str());
			in_s();
		}
		// if is the back button return to the start
		else if (input == types_listed.size() + 3)
			commonparent = &genobj;
	}
}
