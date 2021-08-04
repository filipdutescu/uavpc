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
   * Used to detect poses from frames and display the video stream with/without the detected poses. Also saves the video
   * stream, if saving is enabled.
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

    /** @brief Detects poses of bodies from the given frame.
     *  @param[in] frame An cv::Mat instance containing the frame to be processed.
     *  @returns An std::shared_ptr<std::vector<std::shared_ptr<op::Datum>>> instance containing the result of processing the
     * frame.
     */
    virtual TDatumsSP DetectPoseFromFrame(const cv::Mat& frame) noexcept = 0;

    /** @brief Display the received frame using the OpenCV API.
     *  @param[in] frame An std::shared_ptr<std::vector<std::shared_ptr<op::Datum>>> instance containing the result of
     * processing the frame.
     */
    virtual void DisplayFrameWithPose(const TDatumsSP& frame) noexcept = 0;

    /** @brief Toggle recognition of poses on or off.
     *
     * If recognition is on, performance is significantly affected in the environment for which the program was developed. If
     * it is on, the frame with the estimated poses overlayed over it is shown, instead of the raw footage from the drone.
     */
    virtual void ToggleRecognition() noexcept = 0;

    /** @brief Toggle video stream saving of poses on or off.
     *
     * If saving is on, each frame (processed or not, based on whether recognition is turned on) is stored into a
     * cv::VideoWriter instance. The resulting video is writen in the directory the executable resides in. Writing of the
     * video is done either when saving is turned off or when the program stops.
     */
    virtual void ToggleSaveVideoStream() noexcept = 0;

    /** @brief Starts the loop responsible for processing and displaying frames on a separate thread.
     *  @param[in] videoStream A cv::VideoCapture instance which provides the raw footage from the drone.
     */
    virtual void StartDisplay(cv::VideoCapture& videoStream) = 0;

    /** @brief Stops processing and displaying frames.
     */
    virtual void StopDisplay() noexcept = 0;
  };
}  // namespace uavpc::Pose

#endif
