set(sources
  src/uavpc/Joystick.cpp
  src/uavpc/Drone/ControllerFactory.cpp
  src/uavpc/Drone/DjiTelloController.cpp
  src/uavpc/Drone/DjiTelloControllerFactory.cpp
  src/uavpc/Exceptions/I2CUnsupportedException.cpp
  src/uavpc/Exceptions/InvalidAddressException.cpp
  src/uavpc/Exceptions/InvalidUriException.cpp
  src/uavpc/Exceptions/SocketClosedException.cpp
  src/uavpc/Exceptions/SocketConnectionException.cpp
  src/uavpc/Exceptions/SocketCreationException.cpp
  src/uavpc/Hardware/I2CService.cpp
  src/uavpc/Hardware/Mpu6050.cpp
  src/uavpc/Pose/PoseService.cpp
  src/uavpc/Trackers/GestureService.cpp
  src/uavpc/Trackers/HandTracker.cpp
  src/uavpc/Trackers/KalmanFilter.cpp
  src/uavpc/Utils/MathsHelper.cpp
  src/uavpc/Utils/UdpClient.cpp
)

set(exe_sources
  src/main.cpp
  ${sources}
)

set(headers
  include/uavpc/Joystick.hpp
  include/uavpc/Drone/ControllerFactory.hpp
  include/uavpc/Drone/ControllerType.hpp
  include/uavpc/Drone/DjiTelloController.hpp
  include/uavpc/Drone/DjiTelloControllerFactory.hpp
  include/uavpc/Drone/IController.hpp
  include/uavpc/Exceptions/I2CUnsupportedException.hpp
  include/uavpc/Exceptions/InvalidAddressException.hpp
  include/uavpc/Exceptions/InvalidUriException.hpp
  include/uavpc/Exceptions/SocketClosedException.hpp
  include/uavpc/Exceptions/SocketConnectionException.hpp
  include/uavpc/Exceptions/SocketCreationException.hpp
  include/uavpc/Hardware/AccelerometerRange.hpp
  include/uavpc/Hardware/GyroscopeRange.hpp
  include/uavpc/Hardware/II2CService.hpp
  include/uavpc/Hardware/I2CService.hpp
  include/uavpc/Hardware/Mpu6050.hpp
  include/uavpc/Hardware/Mpu6050Options.hpp
  include/uavpc/Hardware/SensorData.hpp
  include/uavpc/Pose/IPoseService.hpp
  include/uavpc/Pose/PoseService.hpp
  include/uavpc/Trackers/Gesture.hpp
  include/uavpc/Trackers/GestureService.hpp
  include/uavpc/Trackers/HandTracker.hpp
  include/uavpc/Trackers/IGestureService.hpp
  include/uavpc/Trackers/KalmanFilter.hpp
  include/uavpc/Utils/CompatibilityMacros.hpp
  include/uavpc/Utils/MathsHelper.hpp
  include/uavpc/Utils/UdpClient.hpp
)

set(test_sources
  src/uavpc/Drone/DjiTelloControllerTests.cpp
  src/uavpc/Drone/DjiTelloControllerFactoryTests.cpp
)
