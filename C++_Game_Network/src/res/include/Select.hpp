/*
** EPITECH PROJECT, 2022
** LibSocket
** File description:
** Select
*/

#ifndef SELECT_HPP_
#define SELECT_HPP_

#include <sys/types.h>
#include <sys/select.h>

#include <algorithm>

#include <vector>

namespace Networks
{
  class Select
  {
  public:
    Select(int Socket)
    {
      FD_ZERO(&this->_ForInitRead);
      FD_ZERO(&this->_CurrentWrite);
      FD_SET(Socket, &this->_ForInitRead);
      this->_NbFds = Socket;
    }
    ~Select() = default;

  public:
    enum _SelectEvent
    {
      S_EVENT_NEW_CONNECTION,
      S_EVENT_READ,
      S_EVENT_CLOSE,
      S_EVENT_WRITE,
      S_EVENT_ERROR,
    };

    typedef struct _SocketEvent_s
    {
      _SelectEvent Event;
      int Socket;
      struct sockaddr_in addrclient;
    } _SocketEvent_t;

  protected:
    void _ResetSelectData()
    {
      _CurrentRead = _ForInitRead;
    }

    void _SetSocket(const int Socket)
    {
      FD_SET(Socket, &this->_ForInitRead);
      this->_AllSocket.push_back(Socket);
      if (Socket > this->_NbFds)
        this->_NbFds = Socket;
    }

    void _RemoveSocket(const int ToRemove, const int SocketServer)
    {
      FD_CLR(ToRemove, &this->_ForInitRead);
      this->_NbFds = SocketServer;
      std::remove(this->_AllSocket.begin(), this->_AllSocket.end(), ToRemove);
      for (const auto &i : this->_AllSocket)
        if (i > SocketServer)
          this->_NbFds = i;
    }

    _SocketEvent_t
    _GetSocketEvent(const int SocketServer) const
    {
      if (FD_ISSET(SocketServer, &this->_CurrentRead))
        return {S_EVENT_NEW_CONNECTION, SocketServer, {0, 0, 0, 0}};
      for (const auto &i : this->_AllSocket)
        if (FD_ISSET(i, &this->_CurrentRead))
          return {S_EVENT_READ, i, {0, 0, 0, 0}};
        else if (FD_ISSET(i, &this->_CurrentWrite))
          return {S_EVENT_WRITE, i, {0, 0, 0, 0}};
      return {S_EVENT_ERROR, -1, {0, 0, 0, 0}};
    };

    fd_set *_GetSelectRead()
    {
      return &this->_CurrentRead;
    }

    fd_set *_GetSelectWrite()
    {
      return &this->_CurrentWrite;
    }

    int _GetNbFds() const
    {
      return this->_NbFds;
    }

    const std::vector<int> &
    _GetAllSocket() const
    {
      return this->_AllSocket;
    }

  private:
    std::vector<int> _AllSocket;
    fd_set _ForInitRead;
    fd_set _CurrentRead;
    fd_set _CurrentWrite;
    struct timeval _TimeOut;
    int _NbFds;
  };
  using SocketEvent_u = Networks::Select::_SocketEvent_t;
};

#endif /* !SELECT_HPP_ */
