#ifndef UAVPC_POSE_POSE_SERVICE_HPP_
#define UAVPC_POSE_POSE_SERVICE_HPP_

#include "uavpc/Pose/IPoseService.hpp"

#include <chrono>
#include <mutex>
#include <thread>

#include <opencv2/videoio.hpp>

namespace uavpc::Pose
{
  using namespace std::chrono_literals;

  class PoseService : public IPoseService
  {
    cv::VideoCapture m_VideoStream;

    std::thread m_RecognitionThread;
    std::mutex m_RecognitionMutex;
    bool m_ShouldRun;

    static constexpr std::chrono::milliseconds s_MutexTryLockWaitTime = 5ms;

   public:
    PoseService() noexcept;
    PoseService(const PoseService&) = delete;
    PoseService(PoseService&&) = delete;
    PoseService& operator=(const PoseService&) = delete;
    PoseService& operator=(PoseService&&) = delete;
    ~PoseService() override;

    TDatumsSP DetectPoseFromFrame(const cv::Mat& frame) noexcept override;

    void DisplayFrameWithPose(const TDatumsSP& frame) noexcept override;

    void SetVideoStream(const cv::VideoCapture& videoStream) noexcept override;

    void StartRecognition(cv::VideoCapture& videoStream) override;

    void StopRecognition() noexcept override;
  };
}  // namespace uavpc::Pose

#endif
