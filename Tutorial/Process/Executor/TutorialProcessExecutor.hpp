#pragma once
#include <Process/Execution/ProcessComponent.hpp>

#include <ossia/dataflow/graph_node.hpp>
#include <ossia/dataflow/node_process.hpp>

namespace Device
{
class DeviceList;
}
/**
 * These classes provide execution components to a process.
 * I.E. what happens once the score plays.
 *
 * Please refer to the Execution documentation.
 */
namespace Tutorial
{
class ProcessModel;

//! Component and bridge between the GUI / Edition thread and the execution
//! thread.
class ProcessExecutorComponent final
    : public Execution::
          ProcessComponent_T<Tutorial::ProcessModel, ossia::node_process>
{
  COMPONENT_METADATA("4797971b-54cd-43e5-8514-e2e941303d1a")
public:
  ProcessExecutorComponent(
      ProcessModel& element,
      const Execution::Context& ctx,
      QObject* parent);
};

using ProcessExecutorComponentFactory
    = Execution::ProcessComponentFactory_T<ProcessExecutorComponent>;

}
