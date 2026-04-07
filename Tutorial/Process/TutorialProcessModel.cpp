#include "TutorialProcessModel.hpp"
#include <score/application/ApplicationComponents.hpp>
#include <score/plugins/SerializableHelpers.hpp>
#include <score/model/EntitySerialization.hpp>
#include <score/model/EntityMapSerialization.hpp>
#include <Tutorial/PolymorphicEntity/PolymorphicEntityFactory.hpp>
#include <wobjectimpl.h>

W_OBJECT_IMPL(Tutorial::ProcessModel)
namespace Tutorial
{

ProcessModel::ProcessModel(
    const TimeVal& duration,
    const Id<Process::ProcessModel>& id,
    QObject* parent)
    : Process::ProcessModel{duration, id, "TutorialProcess", parent}
{
  metadata().setInstanceName(*this);
}

int ProcessModel::bananas() const
{
  return m_bananas;
}

void ProcessModel::setBananas(int bananas)
{
  if (m_bananas == bananas)
    return;

  m_bananas = bananas;
  bananasChanged(bananas);
}

QString ProcessModel::prettyName() const noexcept
{
  return tr("Tutorial Process");
}

//void ProcessModel::startExecution() {}

//void ProcessModel::stopExecution() {}

//void ProcessModel::reset() {}

ProcessStateDataInterface* ProcessModel::startStateData() const noexcept
{
  return nullptr;
}

ProcessStateDataInterface* ProcessModel::endStateData() const noexcept
{
  return nullptr;
}

Selection ProcessModel::selectableChildren() const noexcept
{
  return {};
}

Selection ProcessModel::selectedChildren() const noexcept
{
  return {};
}

void ProcessModel::setSelection(const Selection& s) const noexcept {}

void ProcessModel::setDurationAndScale(const TimeVal& newDuration) noexcept {}

void ProcessModel::setDurationAndGrow(const TimeVal& newDuration) noexcept {}

void ProcessModel::setDurationAndShrink(const TimeVal& newDuration) noexcept {}

}

/**
 * Here lies the serialization code for the ProcessModel.
 * There is :
 * - a read method (read the program memory into a save file)
 * - a write method (write the save file to program memory).
 *
 * These methods must be implemented for two save formats :
 * - QDataStream : lean and fast (binary), but the order in which
 *   the data is saved must be the same than when reloading and
 *   there cannot be "missing" data.
 *
 * - JSON : slower, but human-readable, and keys can be missing.
 */
template <>
void DataStreamReader::read(const Tutorial::ProcessModel& proc)
{
  /** Save the SimpleElements **/
  m_stream << (int32_t)proc.simpleElements.size();
  for (const auto& e : proc.simpleElements)
  {
    readFrom(e);
  }

  /** Save the PolymorphicElements **/
  m_stream << (int32_t)proc.polymorphicEntities.size();
  for (const auto& e : proc.polymorphicEntities)
  {
    readFrom(e);
  }

  // Save a simple data member
  m_stream << proc.m_bananas;

  // Add an element in the stream that will be checked on loading.
  // This is not necessary, but very useful for debugging.
  insertDelimiter();
}

template <>
void DataStreamWriter::write(Tutorial::ProcessModel& proc)
{
  int32_t simple_count;
  m_stream >> simple_count;

  /** Load the SimpleElements
   * We can just instantiate them like this since there is
   * no inheritance / subclass
   */
  for (; simple_count-- > 0;)
  {
    proc.simpleElements.add(new Tutorial::SimpleElement{*this, &proc});
  }

  /** Load the PolymorphicElements
   * This is a bit more involved :
   * since we do not know the actual type of the PolymorphicElement,
   * we have to instantiate it from a factory.
   */
  int32_t poly_count;
  m_stream >> poly_count;

  auto& pl = components.interfaces<Tutorial::PolymorphicElementFactoryList>();
  for (; poly_count-- > 0;)
  {
    auto e = deserialize_interface(pl, *this, &proc);
    if (e)
    {
      proc.polymorphicEntities.add(e);
    }
    else
    {
      // The save cannot be reloaded correctly, here we throw
      // but other options should be possible.
      throw std::runtime_error("Unable to load.");
    }
  }

  // Load a simple data member
  m_stream >> proc.m_bananas;

  // Check that the stream has not been corrupted.
  checkDelimiter();
}

/**
 * We now do the same thing, but in JSON.
 * Some things are shorter to write, others are sometimes longer.
 */
template <>
void JSONReader::read(const Tutorial::ProcessModel& proc)
{
  obj["SimpleElements"] = proc.simpleElements;
  obj["PolyElements"] = proc.polymorphicEntities;
  obj["Bananas"] = proc.m_bananas;
}

template <>
void JSONWriter::write(Tutorial::ProcessModel& proc)
{
  for (const auto& json_vref : obj["SimpleElements"].toArray())
  {
    JSONObject::Deserializer deserializer{json_vref};
    proc.simpleElements.add(new Tutorial::SimpleElement{deserializer, &proc});
  }

  auto& pl = components.interfaces<Tutorial::PolymorphicElementFactoryList>();
  for (const auto& json_vref : obj["PolyElements"].toArray())
  {
    JSONObject::Deserializer deserializer{json_vref};
    auto e = deserialize_interface(pl, deserializer, &proc);
    if (e)
    {
      proc.polymorphicEntities.add(e);
    }
    else
    {
      // The save cannot be reloaded correctly, here we throw
      // but other options should be possible.
      throw std::runtime_error("Unable to load.");
    }
  }

  proc.m_bananas = obj["Bananas"].toInt();
}
