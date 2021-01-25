#include "uavpc/Utils/UdpClient.hpp"

#include <iostream>

#include "uavpc/Exceptions/InvalidUriException.hpp"
#include "uavpc/Exceptions/SocketClosedException.hpp"
#include "uavpc/Exceptions/SocketConnectionException.hpp"
#include "uavpc/Exceptions/SocketCreationException.hpp"
#include "uavpc/Utils/CompatibilityMacros.hpp"
#ifdef __linux__
#include <arpa/inet.h>
#include <sys/socket.h>
#include <unistd.h>
#endif

namespace uavpc
{
  namespace Utils
  {
#ifdef __linux__
    int UdpClient::OpenSocket(const std::string& address, std::uint16_t port)
    {
      int socketId = 0;
      sockaddr_in socketData{};

      if ((socketId = socket(AF_INET, SOCK_DGRAM, 0)) < 0)
      {
        std::cout << "Did not create socket.\n";
        throw Exceptions::SocketCreationException();
      }

      socketData.sin_family = AF_INET;
      socketData.sin_port   = htons(port);

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

    void UdpClient::CloseSocket(int socket)
    {
      shutdown(socket, SHUT_RDWR);
      if (close(socket) < 0)
      {
        throw Exceptions::SocketClosedException();
      }
    }

    void UdpClient::SendPacket(int socket, const std::string& message)
    {
      if (send(socket, message.c_str(), message.size(), 0) < 0)
      {
        throw Exceptions::SocketClosedException();
      }
    }

    std::string UdpClient::ReceivePacket(int socket, std::size_t length)
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
#endif
  }  // namespace Utils
}  // namespace uavpc
