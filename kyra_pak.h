/* Scumm Tools
 * Copyright (C) 2007 The ScummVM project
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

#ifndef KYRA_PAK_H
#define KYRA_PAK_H

#include "extract_kyra.h"
#include "util.h"

class PAKFile : public Extractor {
public:
	PAKFile() : _fileList(0), _isAmiga(false) {}
	~PAKFile() { delete _fileList; }

	bool loadFile(const char *file, const bool isAmiga);
	bool saveFile(const char *file);
	void clearFile() { delete _fileList; _fileList = 0; }

	const uint32 getFileSize() const { return _fileList->getTableSize()+5+4+_fileList->getFileSize(); }

	const uint8 *getFileData(const char *file, uint32 *size);

	bool addFile(const char *name, const char *file);
	bool addFile(const char *name, uint8 *data, uint32 size);

	bool removeFile(const char *name);

	cFileList *getFileList() const { return _fileList; }
private:
	FileList *_fileList;
	bool _isAmiga;
};

#endif

