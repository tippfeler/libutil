// Copyright (c) 2005 - 2015 Settlers Freaks (sf-team at siedler25.org)
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
#ifndef MESSAGEQUEUE_H_INCLUDED
#define MESSAGEQUEUE_H_INCLUDED

#include <queue>
#include <stddef.h>

class Message;
class Socket;

template<typename T, typename Container=std::deque<T> >
class iterable_queue : public std::queue<T,Container>
{
public:
    typedef typename Container::iterator iterator;
    typedef typename Container::const_iterator const_iterator;

    iterator begin() { return this->c.begin(); }
    iterator end() { return this->c.end(); }
    const_iterator begin() const { return this->c.begin(); }
    const_iterator end() const { return this->c.end(); }
};

//class Socket;
class MessageQueue
{
    public:
        MessageQueue(Message * (*createfunction)(unsigned short)) : createfunction(createfunction) {}
        MessageQueue(const MessageQueue& mq);
        ~MessageQueue(void);

        MessageQueue& operator=(const MessageQueue& mq);

    private:
        typedef iterable_queue<Message*> Queue;
        typedef iterable_queue<Message*>::iterator QueueIt;
        Queue messages;
        Message* (*createfunction)(unsigned short);

    public:
        void clear(void);

        /// flusht die Queue, verschickt alle Elemente.
        bool flush(Socket& sock) { return send(sock, messages.size(), 0xFFFFFFFF); }

        /// liefert die Größe der Queue
        unsigned int count() { return messages.size(); }

        /// verschickt Pakete der Queue, maximal @p max, mit einem maximal @p sizelimit groß (aber beliebig viele kleine)
        bool send(Socket& sock, int max, unsigned int sizelimit = 512);
        bool recv(Socket& sock, bool wait = false);

    public:
        /// hängt ein Element hinten an.
        void push(Message* message) { messages.push(message); }
        /// liefert das vorderste Element der Queue.
        Message* front() { return (!messages.empty() ? messages.front() : NULL); }
        /// entfernt das vorderste Element aus der Queue.
        void pop(void);
        /// Returns the first element and removes it from the queue. Returns NULL if there is none
        /// Caller is responsible for deleting it!
        Message* popFront(){
            if(messages.empty())
                return NULL;
            Message* msg = messages.front();
            messages.pop();
            return msg;
        }

};

#endif // LOBBYMESSAGEQUEUE_H_INCLUDED
