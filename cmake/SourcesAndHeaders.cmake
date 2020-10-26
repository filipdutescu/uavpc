set(sources
  src/uavpc/Drone/ControllerFactory.cpp
  src/uavpc/Drone/DjiTelloController.cpp
  src/uavpc/Drone/DjiTelloControllerFactory.cpp
  src/uavpc/Exceptions/InvalidUriException.cpp
  src/uavpc/Exceptions/SocketClosedException.cpp
  src/uavpc/Exceptions/SocketConnectionException.cpp
  src/uavpc/Exceptions/SocketCreationException.cpp
  src/uavpc/Utils/UdpClient.cpp
)

set(exe_sources
  src/main.cpp
  ${sources}
)

set(headers
  include/uavpc/Drone/ControllerFactory.hpp
  include/uavpc/Drone/ControllerType.hpp
  include/uavpc/Drone/DjiTelloController.hpp
  include/uavpc/Drone/DjiTelloControllerFactory.hpp
  include/uavpc/Drone/IController.hpp
  include/uavpc/Exceptions/SocketClosedException.hpp
  include/uavpc/Exceptions/SocketConnectionException.hpp
  include/uavpc/Exceptions/SocketCreationException.hpp
  include/uavpc/Utils/CompatibilityMacros.hpp
  include/uavpc/Utils/UdpClient.hpp
)

set(test_sources
  src/uavpc/Drone/DjiTelloControllerTests.cpp
  src/uavpc/Drone/DjiTelloControllerFactoryTests.cpp
)
