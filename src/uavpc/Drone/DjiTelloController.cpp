#include "uavpc/Drone/DjiTelloController.hpp"

#include "uavpc/Utils/UdpClient.hpp"

#include <iostream>
#include <sstream>

namespace uavpc
{
  namespace Drone
  {
    DjiTelloController::DjiTelloController(bool connectOnInit)
        : m_CommandSocket(UAVPC_SOCKET_DEFAULT),
          m_StateSocket(UAVPC_SOCKET_DEFAULT),
          m_VideoStreamSocket(UAVPC_SOCKET_DEFAULT)
    {
      if (connectOnInit)
      {
        Connect();
      }
    }

    DjiTelloController::~DjiTelloController()
    {
      if (m_CommandSocket > UAVPC_SOCKET_DEFAULT)
      {
        SendCommand("streamoff");
      }
      if (m_VideoStreamSocket > UAVPC_SOCKET_DEFAULT)
      {
        Utils::UdpClient::CloseSocket(m_VideoStreamSocket);
      }

      if (m_StateSocket > UAVPC_SOCKET_DEFAULT)
      {
        Utils::UdpClient::CloseSocket(m_StateSocket);
      }

      if (m_CommandSocket > UAVPC_SOCKET_DEFAULT)
      {
        Utils::UdpClient::CloseSocket(m_CommandSocket);
      }
    }

    void DjiTelloController::SendCommand(const std::string &command)
    {
      std::cout << "[Command] Sending \"" << command << "\"...\n";
      Utils::UdpClient::SendPacket(m_CommandSocket, command);
      std::cout << "[Command] Drone responded: \"" << Utils::UdpClient::ReceivePacket(m_CommandSocket, s_DefaultPacketSize)
                << "\".\n";
    }

    cv::VideoCapture DjiTelloController::GetVideoStream()
    {
      SendCommand("streamon");
      std::stringstream ss;

      ss << "udp://@" << m_VideoStreamUrl << ":" << m_VideoStreamPort;

      return cv::VideoCapture(ss.str(), cv::CAP_GSTREAMER);
    }

    std::string DjiTelloController::GetCommandUrl() const noexcept
    {
      return m_CommandUrl;
    }

    std::uint16_t DjiTelloController::GetCommandPort() const noexcept
    {
      return m_CommandPort;
    }

    std::string DjiTelloController::GetStateUrl() const noexcept
    {
      return m_StateUrl;
    }

    std::uint16_t DjiTelloController::GetStatePort() const noexcept
    {
      return m_StatePort;
    }

    std::string DjiTelloController::GetVideoStreamUrl() const noexcept
    {
      return m_VideoStreamUrl;
    }

    std::uint16_t DjiTelloController::GetVideoStreamPort() const noexcept
    {
      return m_VideoStreamPort;
    }

    void DjiTelloController::Connect()
    {
      try
      {
        m_CommandSocket = Utils::UdpClient::OpenSocket(m_CommandUrl, m_CommandPort);
        std::cout << "[Drone] Starting SDK mode...\n";
        std::cout << "[Command] Sending \"command\"...\n";
        Utils::UdpClient::SendPacket(m_CommandSocket, "command");
        std::cout << "[Command] Drone responded: \"" << Utils::UdpClient::ReceivePacket(m_CommandSocket, s_DefaultPacketSize)
                  << "\".\n";
      }
      catch (std::exception &)
      {
        m_CommandSocket = UAVPC_SOCKET_DEFAULT;
      }

      try
      {
        m_StateSocket = Utils::UdpClient::OpenSocket(m_StateUrl, m_StatePort);
      }
      catch (std::exception &)
      {
        m_StateSocket = UAVPC_SOCKET_DEFAULT;
      }

      try
      {
        m_VideoStreamSocket = Utils::UdpClient::OpenSocket(m_VideoStreamUrl, m_VideoStreamPort);
      }
      catch (std::exception &)
      {
        m_VideoStreamSocket = UAVPC_SOCKET_DEFAULT;
      }
    }
  }  // namespace Drone
}  // namespace uavpc