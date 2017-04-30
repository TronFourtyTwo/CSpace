/*
#############################################################################################
#    CSpace - space simulator																#
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
 * The purpose of this is to Create a friendly UI using only OPS() (OnlyPrintfSystem).
 * 
 * print an intestation whit the current time and other stuff, then reserve some space for settingrmation about the objects
 * 
 */

#include "OPSo.h"

using namespace std;

void OPSo (const setting& set, system_c& sys) {
	
	string buffer;
		
	// the line whit the time and two lines of '-'
	buffer += "TIME: ";
	buffer += sys.stime.String();
	// two lines of '-'
	buffer += "\n%r-%r-";
	
	// if there isn't any object
	if (sys.o.size()) {
		// A loop that tell to every object something
		for (unsigned int i=0; i!=sys.o.size(); i++) {
			
			object &t = sys.o[i];
			
			// Tell the name, type and mass, the x, the y and the z. conclude whit a line of '-'
			buffer += t.name;
			buffer += " | ";
			buffer += t.typ->name;
			buffer += "\nX axis: ";
			buffer += to_string(t.pos.x);
			buffer += " Km with a velocity of ";
			buffer += to_string(t.vel.x);
			buffer +=" Km/s\nY axis: ";
			buffer += to_string(t.pos.y);
			buffer += " Km with a velocity of ";
			buffer += to_string(t.vel.y);
			buffer += " Km/s\nZ axis: ";
			buffer += to_string(t.pos.z);
			buffer += " Km with a velocity of ";
			buffer += to_string(t.vel.z);
			buffer += " Km/s\n%r-";
		}
	}
	else
		buffer += "\n&t1The system is empty.&t2\nUse the 'create' command to create a new object\nUse the 'help' command for help";
	
	// Print all
	OPS(set, buffer);
}
