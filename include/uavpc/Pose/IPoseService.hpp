#ifndef UAVPC_POSE_IPOSE_SERVICE_HPP_
#define UAVPC_POSE_IPOSE_SERVICE_HPP_

#include <memory>
#include <vector>

#include <opencv2/core/mat.hpp>
#include <opencv2/videoio.hpp>

#include <openpose/headers.hpp>

namespace uavpc::Pose
{
  using TDatumsSP = std::shared_ptr<std::vector<std::shared_ptr<op::Datum>>>;

  /** @interface IPoseService
   *  @brief Defines operations regarding pose detection.
   *
   * Used to detect poses from frames and
   */
  class IPoseService
  {
   public:
    IPoseService() = default;
    IPoseService(const IPoseService&) = default;
    IPoseService(IPoseService&&) = default;
    IPoseService& operator=(const IPoseService&) = default;
    IPoseService& operator=(IPoseService&&) = default;
    virtual ~IPoseService() = default;

    virtual TDatumsSP DetectPoseFromFrame(const cv::Mat& frame) noexcept = 0;

    virtual void DisplayFrameWithPose(const TDatumsSP& frame) noexcept = 0;

    virtual void SetVideoStream(const cv::VideoCapture& videoStream) noexcept = 0;

    virtual void StartRecognition(cv::VideoCapture& videoStream) = 0;

    virtual void StopRecognition() noexcept = 0;
  };
}  // namespace uavpc::Pose

#endif
