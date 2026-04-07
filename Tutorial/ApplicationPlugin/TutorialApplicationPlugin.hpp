#pragma once
#include <score/plugins/application/GUIApplicationPlugin.hpp>

namespace Tutorial
{
/**
 * @brief The ApplicationPlugin class
 *
 * The ApplicationPlugin is a class that will be instantiated only once.
 * It is accessible in the whole application, by using an \ref
 * score::ApplicationContext instance.
 *
 * For instance:
 *
 * \code
 * auto& ctx = score::AppContext();
 * auto& my_plugin = ctx.applicationPlugin<Tutorial::ApplicationPlugin>();
 * \endcode
 *
 * Most of the time this is used to have ownership on some global data,
 * without enforcing the existence of a singleton at the type level.
 *
 * It is also used to add document plug-ins to a newly created or loaded
 * document.
 */
class ApplicationPlugin final : public score::GUIApplicationPlugin
{
public:
  ApplicationPlugin(const score::GUIApplicationContext& app);

protected:
  void on_newDocument(score::Document& doc) override;

  void on_documentChanged(score::Document* olddoc, score::Document* newdoc)
      override;

  score::GUIElements makeGUIElements() override;

  void on_initDocument(score::Document& doc) override;

  void on_loadedDocument(score::Document& doc) override;

  void on_createdDocument(score::Document& doc) override;

  void prepareNewDocument() override;

  void on_activeWindowChanged() override;
};
}
