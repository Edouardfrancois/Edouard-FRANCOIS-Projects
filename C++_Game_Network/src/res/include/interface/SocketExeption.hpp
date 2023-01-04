/*
** EPITECH PROJECT, 2022
** LibSocket
** File description:
** Exeption
*/

#ifndef EXEPTION_HPP_
#define EXEPTION_HPP_

#include <exception>
#include <cstring>
#include <errno.h>
#include <string>

namespace SocketExeption
{
    class Exeption : public std::exception
    {
    public:
        Exeption() {}
        Exeption(std::string const &msg) : _Msg(msg) {}
        Exeption(int DataInt) : _DataInt(DataInt) {}
        Exeption(__attribute__((unused)) bool take_errno) : _ErrnoCode(errno), _Msg(strerror(errno)) { errno = 0; }
        ~Exeption() = default;
        char const *what() const noexcept override
        {
            return this->_Msg.c_str();
        }
        int GetErrno() const noexcept
        {
            return this->_ErrnoCode;
        }
        int GetDataInt() const noexcept
        {
            return this->_DataInt;
        }

    private:
        const int _ErrnoCode = 0;
        const int _DataInt = 0;
        const std::string _Msg;
    };

    class ISocketError : public Exeption
    {
    public:
        ISocketError() : Exeption(true) {}
    };
    class ISocketSetNoBlockingError : public Exeption
    {
    public:
        ISocketSetNoBlockingError() : Exeption(true) {}
    };
    class PortChange : public Exeption
    {
    public:
        PortChange(int DataInt) : Exeption(DataInt) {}
    };
    class BindError : public Exeption
    {
    public:
        BindError() : Exeption(true) {}
    };
    class PortProtected : public BindError
    {
    };
    class ImpossibleToBind : public Exeption
    {
    public:
        ImpossibleToBind() : Exeption(true) {}
    };
    class PollError : public Exeption
    {
    public:
        PollError() : Exeption(true) {}
    };
    class SelectError : public Exeption
    {
    public:
        SelectError() : Exeption(true) {}
    };
    class ReadSocketError : public Exeption
    {
    public:
        ReadSocketError() : Exeption(true) {}
    };
    class ImpossibleToConnect : public Exeption
    {
    public:
        ImpossibleToConnect() : Exeption(true) {}
    };
    class SocketCloseConnection : public Exeption
    {
    public:
        SocketCloseConnection() : Exeption() {}
    };
    class SendError : public Exeption
    {
    public:
        SendError() : Exeption(true) {}
    };
};

#endif /* !EXEPTION_HPP_ */
