#include "uavpc/Pose/PoseService.hpp"

#include <ctime>
#include <iostream>
#include <stdexcept>
#include <string>

#include <opencv2/core/types.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/videoio.hpp>

#include <openpose/core/matrix.hpp>
#include <openpose/core/point.hpp>
#include <openpose/thread/enumClasses.hpp>

namespace uavpc::Pose
{
  PoseService::PoseService() noexcept
      : m_OpenPoseWrapper(op::ThreadManagerMode::Asynchronous),
        m_ShouldRun(false),
        m_WithRecognition(false),
        m_SaveVideoStream(false)
  {
  }

  PoseService::~PoseService()
  {
    if (m_ShouldRun)
    {
      while (!m_RecognitionMutex.try_lock())
      {
        std::this_thread::sleep_for(s_MutexTryLockWaitTime);
      }

      m_ShouldRun = false;

      m_RecognitionMutex.unlock();

      while (!m_RecognitionThread.joinable())
      {
        std::this_thread::sleep_for(s_MutexTryLockWaitTime);
      }

      if (m_RecognitionThread.joinable())
      {
        m_RecognitionThread.join();
      }
      m_RecognitionMutex.unlock();

      if (m_SaveVideoStream)
      {
        ToggleSaveVideoStream();
      }
    }
  }

  TDatumsSP PoseService::DetectPoseFromFrame(const cv::Mat &frame) noexcept
  {
    const auto rawImage = OP_CV2OPCONSTMAT(frame);

    return m_OpenPoseWrapper.emplaceAndPop(rawImage);
  }

  void PoseService::DisplayFrameWithPose(const TDatumsSP &frame) noexcept
  {
    try
    {
      if (frame != nullptr && !frame->empty())
      {
        const auto image = OP_OP2CVCONSTMAT(frame->at(0U)->cvOutputData);
        if (!image.empty())
        {
          cv::imshow("UAVPC", image);
        }
      }
    }
    catch (const std::exception &e)
    {
      std::cerr << "Could not display frame with pose: " << e.what();
    }
  }

  void PoseService::ToggleRecognition() noexcept
  {
    m_WithRecognition = !m_WithRecognition;
  }

  void PoseService::ToggleSaveVideoStream() noexcept
  {
    m_SaveVideoStream = !m_SaveVideoStream;

    if (m_ShouldRun)
    {
      if (m_SaveVideoStream)
      {
        while (m_RecognitionMutex.try_lock())
        {
          std::this_thread::sleep_for(s_MutexTryLockWaitTime);
        }
        constexpr auto format = "uavpc_%Y%m%d_%H%M%S.mp4";
        constexpr auto bufferSize = 30U;
        char buffer[bufferSize]{ '\0' };

        std::strftime(buffer, bufferSize, format, std::localtime(nullptr));
        m_PersistentVideoStream.open(
            std::string(buffer), cv::VideoWriter::fourcc('M', 'P', '4', 'V'), -1, m_VideoStreamSize);
        m_RecognitionMutex.unlock();
      }
      else
      {
        while (m_RecognitionMutex.try_lock())
        {
          std::this_thread::sleep_for(s_MutexTryLockWaitTime);
        }
        m_PersistentVideoStream.release();
        m_RecognitionMutex.unlock();
      }
    }
  }

  void PoseService::StartDisplay(cv::VideoCapture &videoStream)
  {
    m_ShouldRun = true;

    if (!videoStream.isOpened())
    {
      throw std::runtime_error("Video stream closed.");
    }

    m_RecognitionThread = std::thread(
        [&]
        {
          auto width = static_cast<int>(videoStream.get(cv::CAP_PROP_FRAME_WIDTH) / 2);
          auto height = static_cast<int>(videoStream.get(cv::CAP_PROP_FRAME_HEIGHT) / 2);
          auto opWidth = (width / (16 * 3) + 1) * 16;
          auto opHeight = (width / (16 * 3) + 1) * 16;
          cv::Mat frame;
          op::WrapperStructPose poseConfig{};

          poseConfig.netInputSize = op::Point<int>(opWidth, opHeight);
          poseConfig.poseModel = op::PoseModel::MPI_15_4;
          m_OpenPoseWrapper.configure(poseConfig);
          m_OpenPoseWrapper.start();

          while (m_ShouldRun)
          {
            if (videoStream.read(frame))
            {
              if (!frame.empty())
              {
                cv::Mat resizedFrame;
                cv::resize(frame, resizedFrame, cv::Size(width, height));
                cv::Mat persistentFrame = resizedFrame;

                if (m_WithRecognition)
                {
                  auto processedFrame = DetectPoseFromFrame(resizedFrame);
                  DisplayFrameWithPose(processedFrame);
                  persistentFrame = OP_OP2CVCONSTMAT(processedFrame->at(0U)->cvOutputData);
                }
                else
                {
                  cv::imshow("UAVPC", resizedFrame);
                }

                if (m_SaveVideoStream)
                {
                  while (m_RecognitionMutex.try_lock())
                  {
                    std::this_thread::sleep_for(s_MutexTryLockWaitTime);
                  }
                  m_PersistentVideoStream.write(persistentFrame);
                  m_RecognitionMutex.unlock();
                }
              }
            }
            else
            {
              std::cout << "could not read frame" << std::endl;
            }

            cv::waitKey(1);
          }
        });
  }

  void PoseService::StopDisplay() noexcept
  {
    while (!m_RecognitionMutex.try_lock())
    {
      std::this_thread::sleep_for(s_MutexTryLockWaitTime);
    }

    m_ShouldRun = false;

    m_RecognitionMutex.unlock();

    while (!m_RecognitionThread.joinable())
    {
      std::this_thread::sleep_for(s_MutexTryLockWaitTime);
    }

    if (m_RecognitionThread.joinable())
    {
      m_RecognitionThread.join();
    }
    m_RecognitionMutex.unlock();
    m_OpenPoseWrapper.stop();
  }
}  // namespace uavpc::Pose
