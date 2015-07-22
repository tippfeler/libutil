// $Id: SocketSet.h 9359 2014-04-25 15:37:22Z FloSoft $
//
// Copyright (c) 2005 - 2011 Settlers Freaks (sf-team at siedler25.org)
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
#ifndef SOCKETSET_H_INCLUDED
#define SOCKETSET_H_INCLUDED

#pragma once

#ifdef _WIN32
    #include <winsock2.h>
#else
    #include <sys/select.h>
    #define SOCKET int
#endif // _WIN32

class Socket;

/// FD_Set-Wrapper-Klasse f�r portable TCP/IP-Verbindungen
class SocketSet
{
    public:
        /// Standardkonstruktor von @p SocketSet.
        SocketSet();

        /// r�umt das @p SocketSet auf.
        void Clear(void);

        /// f�gt ein @p Socket zum @p SocketSet hinzu.
        void Add(Socket& sock);

        /// f�hrt einen Select auf dem @p SocketSet aus.
        int Select(int timeout, int which = 2);

        /// ist ein @p Socket im @p SocketSet?
        bool InSet(Socket& sock);

    private:
        fd_set set;     ///< Das fd_set
        SOCKET highest; ///< H�chste Socket des Sets
};

#endif // SOCKETSET_H_INCLUDED
