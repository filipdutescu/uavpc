#include "uavpc/Pose/PoseService.hpp"

#include <iostream>
#include <stdexcept>

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
        m_WithRecognition(false)
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

                if (m_WithRecognition)
                {
                  auto processedFrame = DetectPoseFromFrame(resizedFrame);
                  DisplayFrameWithPose(processedFrame);
                }
                else
                {
                  cv::imshow("UAVPC", resizedFrame);
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
    m_OpenPoseWrapper.stop();
  }
}  // namespace uavpc::Pose
