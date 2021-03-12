#include "uavpc/Utils/UdpClient.hpp"

#include "uavpc/Exceptions/InvalidUriException.hpp"
#include "uavpc/Exceptions/SocketClosedException.hpp"
#include "uavpc/Exceptions/SocketConnectionException.hpp"
#include "uavpc/Exceptions/SocketCreationException.hpp"

#include <iostream>
#ifndef _WIN32
#include <arpa/inet.h>
#include <sys/socket.h>

#include <unistd.h>
#endif

namespace uavpc::Utils
{
  UAVPC_SOCKET_TYPE UdpClient::OpenSocket(const std::string& address, std::uint16_t port)
  {
    UAVPC_SOCKET_TYPE socketId = 0;
    sockaddr_in socketData{};

    if ((socketId = socket(AF_INET, SOCK_DGRAM, 0)) < 0)
    {
      std::cout << "Did not create socket.\n";
      throw Exceptions::SocketCreationException();
    }

    socketData.sin_family = AF_INET;
    socketData.sin_port = htons(port);

    if (inet_pton(AF_INET, address.c_str(), &socketData.sin_addr) <= 0)
    {
      std::cout << "Did not convert ip address.\n";
      throw Exceptions::InvalidUriException();
    }

    if (connect(socketId, reinterpret_cast<sockaddr*>(&socketData), sizeof(sockaddr)) < 0)
    {
      std::cout << "Did not connect to socket.\n";
      throw Exceptions::SocketConnectionException();
    }

    return socketId;
  }

  void UdpClient::CloseSocket(UAVPC_SOCKET_TYPE socket)
  {
#if _WIN32 || _WIN64
    shutdown(socket, SD_BOTH);
    if (closesocket(socket) < 0)
#else
    shutdown(socket, SHUT_RDWR);
    if (close(socket) < 0)
#endif
    {
      throw Exceptions::SocketClosedException();
    }
  }

  void UdpClient::SendPacket(UAVPC_SOCKET_TYPE socket, const std::string& message)
  {
    if (send(socket, message.c_str(), message.size(), 0) < 0)
    {
      throw Exceptions::SocketClosedException();
    }
  }

  std::string UdpClient::ReceivePacket(UAVPC_SOCKET_TYPE socket, std::size_t length)
  {
    char* buffer = new char[length]{ 0 };

    if (read(socket, buffer, length) < 0)
    {
      throw Exceptions::SocketClosedException();
    }

    std::string result(buffer);
    delete[] buffer;

    return result;
  }
}  // namespace uavpc::Utils
