set(drone_headers
  include/uavpc/Drone/ControllerFactory.hpp
  include/uavpc/Drone/ControllerType.hpp
  include/uavpc/Drone/DjiTelloController.hpp
  include/uavpc/Drone/DjiTelloControllerFactory.hpp
  include/uavpc/Drone/IController.hpp
)

set(drone_sources
  src/uavpc/Drone/ControllerFactory.cpp
  src/uavpc/Drone/DjiTelloController.cpp
  src/uavpc/Drone/DjiTelloControllerFactory.cpp
)

set(exceptions_headers
  include/uavpc/Exceptions/I2CUnsupportedException.hpp
  include/uavpc/Exceptions/InvalidAddressException.hpp
  include/uavpc/Exceptions/InvalidUriException.hpp
  include/uavpc/Exceptions/SocketClosedException.hpp
  include/uavpc/Exceptions/SocketConnectionException.hpp
  include/uavpc/Exceptions/SocketCreationException.hpp
)

set(exceptions_sources
  src/uavpc/Exceptions/I2CUnsupportedException.cpp
  src/uavpc/Exceptions/InvalidAddressException.cpp
  src/uavpc/Exceptions/InvalidUriException.cpp
  src/uavpc/Exceptions/SocketClosedException.cpp
  src/uavpc/Exceptions/SocketConnectionException.cpp
  src/uavpc/Exceptions/SocketCreationException.cpp
)

set(hardware_headers
  include/uavpc/Hardware/AccelerometerRange.hpp
  include/uavpc/Hardware/GyroscopeRange.hpp
  include/uavpc/Hardware/II2CService.hpp
  include/uavpc/Hardware/I2CService.hpp
  include/uavpc/Hardware/Mpu6050.hpp
  include/uavpc/Hardware/Mpu6050Options.hpp
  include/uavpc/Hardware/SensorData.hpp
)

set(hardware_sources
  src/uavpc/Hardware/I2CService.cpp
  src/uavpc/Hardware/Mpu6050.cpp
)

set(pose_headers
  include/uavpc/Pose/IPoseService.hpp
  include/uavpc/Pose/PoseService.hpp
)

set(pose_sources
  src/uavpc/Pose/PoseService.cpp
)

set(trackers_headers
  include/uavpc/Trackers/Gesture.hpp
  include/uavpc/Trackers/GestureService.hpp
  include/uavpc/Trackers/HandTracker.hpp
  include/uavpc/Trackers/IGestureService.hpp
  include/uavpc/Trackers/KalmanFilter.hpp
)

set(trackers_sources
  src/uavpc/Trackers/GestureService.cpp
  src/uavpc/Trackers/HandTracker.cpp
  src/uavpc/Trackers/KalmanFilter.cpp
)

set(utils_headers
  include/uavpc/Utils/MathsHelper.hpp
  include/uavpc/Utils/UdpClient.hpp
)

set(utils_sources
  src/uavpc/Utils/MathsHelper.cpp
  src/uavpc/Utils/UdpClient.cpp
)

set(headers
  include/uavpc/Joystick.hpp
  ${drone_headers}
  ${exceptions_headers}
  ${hardware_headers}
  ${pose_headers}
  ${trackers_headers}
  ${utils_headers}
)

set(sources
  src/uavpc/Joystick.cpp
  ${drone_sources}
  ${exceptions_sources}
  ${hardware_sources}
  ${pose_sources}
  ${trackers_sources}
  ${utils_sources}
)

set(exe_sources
  src/main.cpp
  ${sources}
)

set(test_sources
  src/uavpc/Drone/DjiTelloControllerTests.cpp
  src/uavpc/Drone/DjiTelloControllerFactoryTests.cpp
  src/uavpc/Hardware/AccelerometerRangeTests.cpp
  src/uavpc/Hardware/GyroscopeRangeTests.cpp
  src/uavpc/Hardware/Mpu6050Tests.cpp
  src/uavpc/Hardware/SensorDataTests.cpp
  src/uavpc/Trackers/GestureServiceTests.cpp
  src/uavpc/Trackers/HandTrackerTests.cpp
  src/uavpc/Trackers/KalmanFilterTests.cpp
  src/uavpc/Utils/MathsHelperTests.cpp
)
