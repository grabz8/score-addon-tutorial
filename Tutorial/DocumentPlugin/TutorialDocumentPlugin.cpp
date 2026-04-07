#include "TutorialDocumentPlugin.hpp"

#include <wobjectimpl.h>

W_OBJECT_IMPL(Tutorial::DocumentPlugin)
namespace Tutorial
{

DocumentPlugin::DocumentPlugin(
    const score::DocumentContext& ctx,
    QObject* parent)
    : score::SerializableDocumentPlugin{ctx,
                                        "DocumentPlugin",
                                        parent}
{
}

}

template <>
void DataStreamReader::read(const Tutorial::DocumentPlugin& dev)
{
  insertDelimiter();
}

template <>
void DataStreamWriter::write(Tutorial::DocumentPlugin& plug)
{
  checkDelimiter();
}

template <>
void JSONReader::read(const Tutorial::DocumentPlugin& plug)
{
}

template <>
void JSONWriter::write(Tutorial::DocumentPlugin& plug)
{
}
