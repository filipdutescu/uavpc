#include "uavpc/Pose/PoseService.hpp"

#include <iostream>
#include <stdexcept>

#include <opencv2/core/types.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/videoio.hpp>

#include <openpose/core/matrix.hpp>
#include <openpose/thread/enumClasses.hpp>
#include <openpose/wrapper/wrapper.hpp>

namespace uavpc::Pose
{
  PoseService::PoseService() noexcept : m_ShouldRun(false)
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
    }
  }

  TDatumsSP PoseService::DetectPoseFromFrame(const cv::Mat &frame) noexcept
  {
    op::Wrapper opWrapper{ op::ThreadManagerMode::Asynchronous };
    opWrapper.start();

    const auto rawImage = OP_CV2OPCONSTMAT(frame);

    return opWrapper.emplaceAndPop(rawImage);
  }

  void PoseService::DisplayFrameWithPose(const TDatumsSP &frame) noexcept
  {
    try
    {
      std::cout << "here" << std::endl;
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

  void PoseService::SetVideoStream(const cv::VideoCapture &videoStream) noexcept
  {
    m_VideoStream = videoStream;
  }

  void PoseService::StartRecognition(cv::VideoCapture &videoStream)
  {
    m_ShouldRun = true;

    if (!videoStream.isOpened())
    {
      // TODO: add custom exception
      throw std::runtime_error("Video stream closed.");
    }

    m_RecognitionThread = std::thread(
        [&]
        {
          cv::Mat frame;
          auto width = static_cast<int>(videoStream.get(cv::CAP_PROP_FRAME_WIDTH) / 2);
          auto height = static_cast<int>(videoStream.get(cv::CAP_PROP_FRAME_HEIGHT) / 2);

          while (m_ShouldRun)
          {
            if (videoStream.read(frame))
            {
              if (!frame.empty())
              {
                cv::Mat resizedFrame;
                cv::resize(frame, resizedFrame, cv::Size(width, height));

                auto processedFrame = DetectPoseFromFrame(resizedFrame);
                DisplayFrameWithPose(processedFrame);
              }
            }
            else
            {
              std::cout << "could not read frame" << std::endl;
            }

            int key = cv::waitKey(15);
            if (key == 'q' || key == 'Q')
            {
              break;
            }
          }

          while (!m_RecognitionMutex.try_lock())
          {
            std::this_thread::sleep_for(s_MutexTryLockWaitTime);
          }

          m_ShouldRun = false;

          m_RecognitionMutex.unlock();
        });
  }

  void PoseService::StopRecognition() noexcept
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
  }
}  // namespace uavpc::Pose
