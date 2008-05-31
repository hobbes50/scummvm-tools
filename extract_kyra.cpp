/* extract_kyra - Extractor for Kyrandia .pak archives
 * Copyright (C) 2004  Johannes Schickel
 * Copyright (C) 2004-2008  The ScummVM Team
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.

 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.

 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301, USA.
 *
 * $URL$
 * $Id$
 *
 */

#include "kyra_pak.h"
#include "kyra_ins.h"

void showhelp(char *exename) {
	printf("\nUsage: %s [params] <file>\n", exename);

	printf("\nParams:\n");
	printf( "-o <filename>     Extract only <filename>\n"
			"-x                Extract all files\n"
			"-a                Extract files from the Amiga .PAK files\n"
			"-2                Extract files from HoF installer files\n");

	exit(2);
}

int main(int argc, char **argv) {
	char inputPath[768];

	if (argc < 2)
		showhelp(argv[0]);

	bool extractAll = false, extractOne = false, isAmiga = false, isHoFInstaller = false;
	char singleFilename[256] = "";
	int param;

	for (param = 1; param < argc; param++) {
		if (strcmp(argv[param], "-o") == 0) {
			extractOne = true;
			param++;

			if (param >= (argc - 1)) {
				printf("You must supply a filename with -o\n");
				printf("Example: %s -o ALGAE.CPS A_E.PAK\n", argv[0]);

				exit(-1);
			} else {
				strcpy(singleFilename, argv[param]);
			}
		} else if (strcmp(argv[param], "-x") == 0) {
			extractAll = true;
		} else if (strcmp(argv[param], "-a") == 0) {
			isAmiga = true;
		} else if (strcmp(argv[param], "-2") == 0) {
			isHoFInstaller = true;
		}
	}

	if (param > argc)
		showhelp(argv[0]);

	Extractor *extract = 0;
	if (isHoFInstaller) {
		extract = new HoFInstaller(argv[argc - 1]);
	} else {
		PAKFile *myfile = new PAKFile;
		if (!myfile->loadFile(argv[argc - 1], isAmiga)) {
			delete myfile;
			error("Couldn't load file '%s'", argv[argc - 1]);
		}

		extract = myfile;
	}

	getPath(argc[argv - 1], inputPath);

	if (extractAll) {
		extract->outputAllFiles(inputPath);
	} else if (extractOne) {
		char outputFilename[1024];
		snprintf(outputFilename, 1024, "%s/%s", inputPath, singleFilename);
		extract->outputFileAs(singleFilename, outputFilename);
	} else {
		extract->drawFileList();
	}

	return 0;
}

