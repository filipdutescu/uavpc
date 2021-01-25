#include "uavpc/Drone/DjiTelloControllerFactory.hpp"

namespace uavpc
{
  namespace Drone
  {
    std::shared_ptr<IController> DjiTelloControllerFactory::createController()
    {
      return std::make_shared<DjiTelloController>(m_ConnectOnInit);
    }

    DjiTelloControllerFactory::DjiTelloControllerFactory(bool connectOnInit) : m_ConnectOnInit(connectOnInit)
    {
    }

    bool DjiTelloControllerFactory::ConnectOnInit() const noexcept
    {
      return m_ConnectOnInit;
    }

    void DjiTelloControllerFactory::SetConnectOnInit(bool connectOnInit)
    {
      m_ConnectOnInit = connectOnInit;
    }
  }  // namespace Drone
}  // namespace uavpc
