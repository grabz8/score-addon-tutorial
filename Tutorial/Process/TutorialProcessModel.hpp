#pragma once
#include <Process/Process.hpp>

#include <score/model/EntityMap.hpp>

#include <Tutorial/PolymorphicEntity/PolymorphicEntity.hpp>
#include <Tutorial/Process/TutorialProcessMetadata.hpp>
#include <Tutorial/SimpleElement/SimpleElement.hpp>

namespace Tutorial
{
class ProcessModel final : public Process::ProcessModel
{
  SCORE_SERIALIZE_FRIENDS
  PROCESS_METADATA_IMPL(Tutorial::ProcessModel)

  W_OBJECT(ProcessModel)

public:
  ProcessModel(
      const TimeVal& duration,
      const Id<Process::ProcessModel>& id,
      QObject* parent);

  template <typename Impl>
  ProcessModel(Impl& vis, QObject* parent) : Process::ProcessModel{vis, parent}
  {
    vis.writeTo(*this);
  }

  score::EntityMap<SimpleElement> simpleElements;
  score::EntityMap<PolymorphicEntity> polymorphicEntities;

  int bananas() const;
  void setBananas(int bananas);
  void bananasChanged(int bananas) W_SIGNAL(bananasChanged, bananas);

  PROPERTY(int, bananas READ bananas WRITE setBananas NOTIFY bananasChanged)
private:
  QString prettyName() const noexcept override;
  //void startExecution() override;
  //void stopExecution() override;
  //void reset() override;
  ProcessStateDataInterface* startStateData() const noexcept override;
  ProcessStateDataInterface* endStateData() const noexcept override;
  Selection selectableChildren() const noexcept override;
  Selection selectedChildren() const noexcept override;
  void setSelection(const Selection& s) const noexcept override;

  void setDurationAndScale(const TimeVal& newDuration) noexcept override;
  void setDurationAndGrow(const TimeVal& newDuration) noexcept override;
  void setDurationAndShrink(const TimeVal& newDuration) noexcept override;

  int m_bananas{};
};
}
