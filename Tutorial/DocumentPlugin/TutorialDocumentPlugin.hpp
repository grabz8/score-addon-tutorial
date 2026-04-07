#pragma once
#include <score/plugins/documentdelegate/plugin/DocumentPlugin.hpp>
#include <score/plugins/documentdelegate/plugin/DocumentPluginCreator.hpp>

namespace Tutorial
{
class DocumentPlugin;
}

UUID_METADATA(
    ,
    score::DocumentPluginFactory,
    Tutorial::DocumentPlugin,
    "164843db-345f-4e31-b614-f8de5ca7e94f")

namespace Tutorial
{
/**
 * @brief The DocumentPlugin class
 *
 * The DocumentPlugin is a class that will be instantiated once per document.
 * It is accessible through a \ref score::DocumentContext.
 *
 * For instance:
 *
 * \code
 * score::DocumentContext& ctx = ...;
 * auto& my_plugin = ctx.plugin<Tutorial::DocumentPlugin>();
 * \endcode
 *
 * If (and only if) there is no easy access to a \ref score::DocumentContext
 * instance, one can get it from an object that is part of the i-score object
 * tree :
 *
 * \code
 * score::DocumentContext& ctx =
 * score::IDocument::documentContext(some_object); \endcode
 *
 * But this should seldom be used, and especially not in resource-intensive
 * parts of the application. If it is going to be reused, the context should be
 * cached somewhere.
 *
 */
class DocumentPlugin final : public score::SerializableDocumentPlugin
{
  W_OBJECT(DocumentPlugin)
  SCORE_SERIALIZE_FRIENDS

  MODEL_METADATA_IMPL(DocumentPlugin)

public:
  explicit DocumentPlugin(
      const score::DocumentContext& ctx,
      QObject* parent);

  template <typename Impl>
  DocumentPlugin(const score::DocumentContext& ctx, Impl& vis, QObject* parent)
      // Old: {ctx, vis, "DocumentPlugin", parent}
      // New: {ctx, "DocumentPlugin", vis, parent}
      : score::SerializableDocumentPlugin{ctx, vis, parent}
  {
    vis.writeTo(*this);
  }

};

using DocumentPluginFactory = score::DocumentPluginFactory_T<DocumentPlugin>;
}
