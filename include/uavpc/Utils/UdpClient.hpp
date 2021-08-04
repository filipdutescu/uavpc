#ifndef UAVPC_UTILS_UDP_CLIENT_HPP_
#define UAVPC_UTILS_UDP_CLIENT_HPP_

#include <string>

namespace uavpc::Utils
{
  /** @class UdpClient
   *  @brief A helper class used to handle a UDP socket.
   */
  class UdpClient
  {
   public:
    UdpClient() = delete;
    UdpClient(const UdpClient&) = delete;
    UdpClient(UdpClient&&) = delete;
    ~UdpClient() = delete;

    UdpClient& operator=(const UdpClient&) = delete;
    UdpClient& operator=(UdpClient&&) = delete;

    /** @brief Given an address and a port, create and bind a socket.
     *  @param[in] address An std::string containing the IP address (without the protocol) of the UDP server to connect to.
     *  @param[in] port An std::uint16_t containing the port of the UDP server to connect to.
     *  @throw uavpc::Exceptions::InvalidUriException
     *  @throw uavpc::Exceptions::SocketConnectionException
     *  @throw uavpc::Exceptions::SocketCreationException
     *  @returns An integer representing the socket file descriptor.
     */
    static int OpenSocket(const std::string& address, std::uint16_t port);

    /** @brief Closes the socket received as a parameter.
     *  @param[in] socket An integer representing a socket file descriptor.
     *  @throw uavpc::Exceptions::SocketClosedException
     */
    static void CloseSocket(int socket);

    /** @brief Send a UDP packet to a given server socket.
     *  @param[in] socket An integer representing socket file descriptor.
     *  @param[in] message An std::string containing the packet contents.
     *  @throw uavpc::Exceptions::SocketClosedException
     */
    static void SendPacket(int socket, const std::string& message);

    /** @brief Try to receive and get the contents of a packet.
     *  @param[in] socket An integer representing the socket file descriptor.
     *  @param[in] length An std::size_t representing the expected length of the package to be received.
     *  @throws uavpc::Exceptions::SocketClosedException
     *  @returns An std::string containing the package contents.
     */
    static std::string ReceivePacket(int socket, std::size_t length);
  };
}  // namespace uavpc::Utils

#endif
