#include "uavpc/Drone/DjiTelloController.hpp"

#include "uavpc/Trackers/Gesture.hpp"
#include "uavpc/Utils/UdpClient.hpp"

#include <iostream>
#include <sstream>

namespace uavpc::Drone
{
  DjiTelloController::DjiTelloController(bool connectOnInit)
      : m_CommandSocket(-1),
        m_StateSocket(-1),
        m_VideoStreamSocket(-1)
  {
    if (connectOnInit)
    {
      Connect();
    }
  }

  DjiTelloController::~DjiTelloController()
  {
    if (m_CommandSocket > -1)
    {
      SendCommand("streamoff");
    }
    if (m_VideoStreamSocket > -1)
    {
      Utils::UdpClient::CloseSocket(m_VideoStreamSocket);
    }

    if (m_StateSocket > -1)
    {
      Utils::UdpClient::CloseSocket(m_StateSocket);
    }

    if (m_CommandSocket > -1)
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

  void DjiTelloController::GetBattery()
  {
    SendCommand("battery?");
  }

  std::vector<std::string> DjiTelloController::GetCommands(const std::uint16_t &gestures)
  {
    std::vector<std::string> commands;

    if ((gestures & Trackers::Gesture::TILT_LEFT) != 0)
    {
      commands.emplace_back("left 20");
    }
    if ((gestures & Trackers::Gesture::TILT_RIGHT) != 0)
    {
      commands.emplace_back("right 20");
    }
    if ((gestures & Trackers::Gesture::TILT_UP) != 0)
    {
      commands.emplace_back("back 20");
    }
    if ((gestures & Trackers::Gesture::TILT_DOWN) != 0)
    {
      commands.emplace_back("forward 20");
    }

    return commands;
  }

  cv::VideoCapture DjiTelloController::GetVideoStream()
  {
    SendCommand("streamon");
    std::stringstream ss;

    ss << "udp://@" << m_VideoStreamUrl << ":" << m_VideoStreamPort << "?overrun_nonfatal=1&fifo_size=278877";

    auto uri = ss.str();
    auto videoStream = cv::VideoCapture(uri, cv::CAP_FFMPEG);

    // If GStreamer capture failed, try with the default backend.
    if (!videoStream.isOpened())
    {
      videoStream.open(ss.str());
    }

    return videoStream;
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
      m_CommandSocket = -1;
    }

    try
    {
      m_StateSocket = Utils::UdpClient::OpenSocket(m_StateUrl, m_StatePort);
    }
    catch (std::exception &)
    {
      m_StateSocket = -1;
    }

    try
    {
      m_VideoStreamSocket = Utils::UdpClient::OpenSocket(m_VideoStreamUrl, m_VideoStreamPort);
    }
    catch (std::exception &)
    {
      m_VideoStreamSocket = -1;
    }
  }
}  // namespace uavpc::Drone
