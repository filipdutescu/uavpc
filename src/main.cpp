#include "uavpc/Drone/DjiTelloController.hpp"
#include "uavpc/Drone/DjiTelloControllerFactory.hpp"
#include "uavpc/Utils/UdpClient.hpp"

#include <cstdlib>
#include <iostream>
#include <memory>
#include <sstream>

#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/videoio.hpp>

int main()
{
  std::shared_ptr<uavpc::Drone::ControllerFactory> controllerFac =
      std::make_shared<uavpc::Drone::DjiTelloControllerFactory>();
  auto controller = controllerFac->GetController();
  // auto* controllerCast = dynamic_cast<uavpc::Drone::DjiTelloController*>(controller.get());

  auto videoStream = controller->GetVideoStream();
  // auto videoStream = cv::VideoCapture();

  if (!videoStream.isOpened())
  {
    std::cout << "Fail.\n";

    std::stringstream ss;
    ss << "udp://@0.0.0.0:" << 11111;

    videoStream.open(ss.str());
  }
  else
  {
    std::cout << "Video stream open.\n";
  }

  cv::Mat frame;
  bool stop = false;
  while (!stop)
  {
    if (videoStream.read(frame))
    {
      if (!frame.empty())
      {
        cv::imshow("DJI Tello Drone Feed", frame);
      }
    }

    int key = cv::waitKey(15);
    if (key == 'q' || key == 'Q')
    {
      stop = true;
    }
  }

  return 0;
}
