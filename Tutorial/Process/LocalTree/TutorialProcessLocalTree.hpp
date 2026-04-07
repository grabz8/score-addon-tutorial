#pragma once
#include <LocalTree/LocalTreeComponent.hpp>
#include <LocalTree/ProcessComponent.hpp>

namespace Tutorial
{
class ProcessModel;

//! This component displays informations about an object in the Device
//! Explorer, in the left panel.
class LocalTreeProcessComponent
    : public LocalTree::ProcessComponent_T<ProcessModel>
{
  COMPONENT_METADATA("b387ed01-831a-487d-8686-42094813f2a7")

public:
  LocalTreeProcessComponent(
      ossia::net::node_base& parent,
      Tutorial::ProcessModel& scenario,
      const score::DocumentContext& doc,
      QObject* parent_obj);

  ~LocalTreeProcessComponent() override;

private:
  std::unique_ptr<LocalTree::BaseProperty> m_bananaProperty;
};

using LocalTreeProcessComponentFactory
    = LocalTree::ProcessComponentFactory_T<LocalTreeProcessComponent>;
}
