#include "TutorialProcessLocalTree.hpp"

#include <LocalTree/Property.hpp>
#include <Tutorial/Process/TutorialProcessModel.hpp>

namespace Tutorial
{

LocalTreeProcessComponent::LocalTreeProcessComponent(
    ossia::net::node_base& parent,
    Tutorial::ProcessModel& scenario,
    const score::DocumentContext& doc,
    QObject* parent_obj)
    : LocalTree::ProcessComponent_T<Tutorial::ProcessModel>{
          parent,             // 1
          scenario,           // 2
          doc,                // 3
          "TutorialComponent", // 4 - The missing string name!
          parent_obj}         // 5
{
  add<ProcessModel::p_bananas>(scenario);
}





LocalTreeProcessComponent::~LocalTreeProcessComponent() {}

}
