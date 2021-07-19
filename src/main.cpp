#include "uavpc/Drone/DjiTelloController.hpp"
#include "uavpc/Drone/DjiTelloControllerFactory.hpp"
#include "uavpc/Hardware/AccelerometerRange.hpp"
#include "uavpc/Hardware/I2CService.hpp"
#include "uavpc/Hardware/Mpu6050.hpp"
#include "uavpc/Joystick.hpp"
#include "uavpc/Pose/IPoseService.hpp"
#include "uavpc/Pose/PoseService.hpp"
#include "uavpc/Trackers/Gesture.hpp"
#include "uavpc/Trackers/GestureService.hpp"
#include "uavpc/Trackers/HandTracker.hpp"
#include "uavpc/Trackers/IGestureService.hpp"
#include "uavpc/Utils/UdpClient.hpp"

#include <chrono>
#include <cstdlib>
#include <iostream>
#include <memory>
#include <ostream>
#include <sstream>
#include <thread>

#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/videoio.hpp>

#include <openpose/core/datum.hpp>

void showStream()
{
  auto controllerFac = std::make_shared<uavpc::Drone::DjiTelloControllerFactory>();
  auto controller = controllerFac->GetController();
  auto videoStream = controller->GetVideoStream();

  if (!videoStream.isOpened())
  {
    std::cout << "Fail.\n";

    std::stringstream ss;
    ss << "udp://@0.0.0.0:" << 11111U;

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
}

void mpu6050Testing()
{
  namespace HW = uavpc::Hardware;
  using namespace std::chrono_literals;
  constexpr std::uint8_t busAddress = 0x68;

  std::unique_ptr<HW::II2CService> i2cService = std::make_unique<HW::I2CService>('1', busAddress);
  std::this_thread::sleep_for(1s);
  auto options = HW::Mpu6050Options(HW::AccelerometerRange::G4, HW::GyroscopeRange::DEGS500);
  auto mpu6050 = HW::Mpu6050(std::move(i2cService), options);

  std::size_t prevOutputSize = 0U;
  constexpr auto waitTime = 0.5s;
  while (true)
  {
    const auto accelData = mpu6050.GetAccelerometerData();
    const auto gyroData = mpu6050.GetGyroscopeData();

    std::stringstream ss;
    ss << "\tAccelerometer Data:\n"
       << accelData.X << "\t" << accelData.Y << "\t" << accelData.Z << "\n\n"
       << "\tGyroscope Data:\n"
       << gyroData.X << "\t" << gyroData.Y << "\t" << gyroData.Z;
    auto output = ss.str();

    if (prevOutputSize > 0U)
    {
      std::cout << "\033[1A\033[K"
                << "\033[1A\033[K"
                << "\033[1A\033[K"
                << "\033[1A\033[K"
                << "\033[1A\033[K" << std::flush;
    }

    std::cout << output << std::endl;
    prevOutputSize = output.length();

    std::this_thread::sleep_for(waitTime);
  }
}

void handTrackerTesting()
{
  namespace HW = uavpc::Hardware;
  namespace TK = uavpc::Trackers;
  using namespace std::chrono_literals;
  constexpr std::uint8_t busAddress = 0x68;

  auto i2cService = std::make_shared<HW::I2CService>('1', busAddress);
  std::this_thread::sleep_for(1s);
  auto options = HW::Mpu6050Options(HW::AccelerometerRange::G8, HW::GyroscopeRange::DEGS1000);
  auto mpu6050 = HW::Mpu6050(i2cService, options);
  std::shared_ptr<TK::IGestureService> gestureService = std::make_shared<TK::GestureService>();
  auto handTracker = TK::HandTracker(std::move(mpu6050), gestureService);

  // constexpr auto waitTime = 0.5s;
  while (true)
  {
    auto gestures = handTracker.GetGestures();
    // auto distances = handTracker.GetDistances();

    std::stringstream ss("Current gestures(s):");
    if ((gestures & TK::Gesture::LEFT) != 0)
    {
      ss << " left;";
    }
    if ((gestures & TK::Gesture::RIGHT) != 0)
    {
      ss << " right;";
    }
    if ((gestures & TK::Gesture::FORWARD) != 0)
    {
      ss << " forward;";
    }
    if ((gestures & TK::Gesture::BACKWARD) != 0)
    {
      ss << " backward;";
    }
    if ((gestures & TK::Gesture::UP) != 0)
    {
      ss << " up;";
    }
    if ((gestures & TK::Gesture::DOWN) != 0)
    {
      ss << " down;";
    }
    if ((gestures & TK::Gesture::TILT_LEFT) != 0)
    {
      ss << " tilt left;";
    }
    if ((gestures & TK::Gesture::TILT_RIGHT) != 0)
    {
      ss << " tilt right;";
    }
    if ((gestures & TK::Gesture::TILT_UP) != 0)
    {
      ss << " tilt up;";
    }
    if ((gestures & TK::Gesture::TILT_DOWN) != 0)
    {
      ss << " tilt down;";
    }

    if ((gestures | TK::Gesture::NONE) != 0)
    {
      // std::cout << ss.str() << std::endl;
    }
    // std::cout << distances << std::endl;
    // std::this_thread::sleep_for(waitTime);
  }
}

class DjiTelloDroneController : public uavpc::Drone::DjiTelloController
{
 public:
  DjiTelloDroneController() : uavpc::Drone::DjiTelloController(false)
  {
  }

  void SendCommand(const std::string& command) override
  {
    std::cout << command << std::endl;
  }

  cv::VideoCapture GetVideoStream() override
  {
    return cv::VideoCapture(0);
  }
};

class I2CService : public uavpc::Hardware::II2CService
{
  [[nodiscard]] std::int32_t ReadByteData(std::uint8_t registerAddress) const noexcept override
  {
    return static_cast<std::uint32_t>(0b1) & registerAddress;
  }

  void WriteByteData(std::uint8_t registerAddress, std::uint8_t value) const noexcept override
  {
    std::stringstream ss;
    ss << registerAddress;
    ss << value;
  }

  [[nodiscard]] std::int32_t ReadWordData(std::uint8_t registerAddress) const noexcept override
  {
    return static_cast<std::uint32_t>(0b1) & registerAddress;
  }
};

class PoseService : public uavpc::Pose::IPoseService
{
  using TDatumsSP = std::shared_ptr<std::vector<std::shared_ptr<op::Datum>>>;

 public:
  TDatumsSP DetectPoseFromFrame(const cv::Mat& frame) noexcept override
  {
    if (frame.empty())
    {
      return nullptr;
    }
    else
    {
      return nullptr;
    }
  }

  void DisplayFrameWithPose(const TDatumsSP& frame) noexcept override
  {
    if (frame->empty())
    {
    }
  }

  void ToggleRecognition() noexcept override
  {
  }

  void StartRecognition(cv::VideoCapture& videoStream) noexcept override
  {
    videoStream.isOpened();
  }

  void StopRecognition() noexcept override
  {
  }
};

int main()
{
  // showStream();

  // mpu6050Testing();

  // handTrackerTesting();

  // constexpr std::uint8_t busAddress = 0x68;
  //auto controller = uavpc::Drone::DjiTelloControllerFactory().GetController();

  //// auto i2cService = std::make_unique<uavpc::Hardware::I2CService>('1', busAddress);
  auto mpu6050 = uavpc::Hardware::Mpu6050(
      // std::move(i2cService),
      std::make_shared<I2CService>(),
      uavpc::Hardware::Mpu6050Options(uavpc::Hardware::AccelerometerRange::G8, uavpc::Hardware::GyroscopeRange::DEGS250));

  auto gestureService = std::make_shared<uavpc::Trackers::GestureService>();
  auto handTracker = uavpc::Trackers::HandTracker(mpu6050, gestureService);
  auto controller = std::make_shared<DjiTelloDroneController>();
  // auto poseService = std::make_shared<PoseService>();

  auto poseService = std::make_shared<uavpc::Pose::PoseService>();

  uavpc::Joystick(controller, handTracker, poseService).Run();

  return 0;
}
