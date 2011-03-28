// $Id: Serializer.cpp 7099 2011-03-28 10:26:03Z FloSoft $
//
// Copyright (c) 2005 - 2010 Settlers Freaks (sf-team at siedler25.org)
//
// This file is part of Return To The Roots.
//
// Return To The Roots is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 2 of the License, or
// (at your option) any later version.
//
// Return To The Roots is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with Return To The Roots. If not, see <http://www.gnu.org/licenses/>.

///////////////////////////////////////////////////////////////////////////////
// Header
#include "main.h"
#include "Serializer.h"
#include "BinaryFile.h"

///////////////////////////////////////////////////////////////////////////////
// Makros / Defines
#if defined _WIN32 && defined _DEBUG && defined _MSC_VER
#define new new(_NORMAL_BLOCK, THIS_FILE, __LINE__)
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

void Serializer::WriteToFile(BinaryFile& file)
{
	file.WriteUnsignedInt(GetLength());
	file.WriteRawData(GetData(), GetLength());
}

void Serializer::ReadFromFile(BinaryFile& file)
{
	Clear();

	unsigned buffer_size;
	buffer_size = file.ReadUnsignedInt();
	Realloc(buffer_size);
	SetLength(buffer_size);
	file.ReadRawData(GetDataWritable(), buffer_size);
}

