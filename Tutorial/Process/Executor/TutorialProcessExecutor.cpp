#include "TutorialProcessExecutor.hpp"
#include "ossia/network/base/parameter.hpp"
#include <ossia/network/value/value.hpp>
#include <Process/ExecutionContext.hpp>

#include <ossia/dataflow/port.hpp>
#include <ossia/network/base/node.hpp>

#include <Tutorial/Process/TutorialProcessModel.hpp>
#include <score/tools/Bind.hpp>

namespace Tutorial
{

//! The class that does the actual execution, in the execution thread
class tutorial_node final : public ossia::graph_node
{
public:
  double last_val{};
  tutorial_node()
  {
    m_inlets.push_back(new ossia::value_inlet());
    m_outlets.push_back(new ossia::audio_outlet());
  }

  void
  run(const ossia::token_request& tk, ossia::exec_state_facade f) noexcept override
  {
    using namespace std;

    // Direct write in the environment.
    if (auto n = f.find_node("my_device:/a/banana"))
    {
      if (auto p = n->get_parameter())
      {
		//f.insert(*p, ossia::typed_value{1.234f});
// 1. Get the port reference (p is likely your parameter/port pointer)
// If p is a pointer to ossia::net::parameter_base
// Explicit conversion to ossia::value
p->push_value(ossia::value{1.234f}); 

      }
    }

    // tk.prev_date : logical current date of the node
    // tk.date : logical new date of the node at the end of this tick

    auto samples = (tk.date - tk.prev_date).impl;
    if (tk.forward()) // time is going forward
    {
      // Fetch received input messages
      auto& input = *m_inlets[0]->target<ossia::value_port>();
      auto& messages = input.get_data();

      if (!messages.empty())
      {
        // always relative to the current tick, e.g. between 0 and buffer_size:
        // messages.back().timestamp;
        last_val = ossia::convert<double>(messages.back().value);
      }

      // Write some audio
      auto& output = *m_outlets[0]->target<ossia::audio_port>();
      output.set_channels(1); // number of channels

      auto& chan = output.channel(0);

      if (chan.size() < tk.offset.impl + samples)
        chan.resize((tk.offset + samples).impl);

      const auto sr = f.sampleRate();
      for (int i = 0; i < samples; i++)
      {
        chan[tk.offset.impl + i] = sin(2. * 3.141597 * last_val * i / sr);
      }
    }
  }

  std::string label() const noexcept override { return "tutorial"; }
};

ProcessExecutorComponent::ProcessExecutorComponent(
    Tutorial::ProcessModel& element,
    const Execution::Context& ctx,
    QObject* parent)
    : ProcessComponent_T{element, ctx, "TutorialExecutorComponent", parent}
{
  auto n = std::make_shared<tutorial_node>();

  ::bind(
      element,
      Tutorial::ProcessModel::p_bananas{},
      this,
      [this, n](int bananas) {
        // this lambda happens in the GUI thread whenever "banans" change

        assert(n);
        in_exec([n, bananas] {
          // This one happens in an execution thread.
          // No need for mutexes, non-concurrent access to the nodes is
          // guaranteed. However remember to pass data either by copy or stored
          // in a shared_ptr
          assert(n);
          n->last_val = 60. * bananas;
        });
      });

  node = n;
  m_ossia_process = std::make_shared<ossia::node_process>(node);
}

}
