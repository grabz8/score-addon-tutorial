#include "TutorialApplicationPlugin.hpp"

namespace Tutorial
{

ApplicationPlugin::ApplicationPlugin(const score::GUIApplicationContext& app)
    : GUIApplicationPlugin{app}
{
}

void ApplicationPlugin::on_newDocument(score::Document& doc) {}

void ApplicationPlugin::on_documentChanged(
    score::Document* olddoc,
    score::Document* newdoc)
{
}

score::GUIElements ApplicationPlugin::makeGUIElements()
{
  return {};
}

void ApplicationPlugin::on_initDocument(score::Document& doc) {}

void ApplicationPlugin::on_loadedDocument(score::Document& doc) {}

void ApplicationPlugin::on_createdDocument(score::Document& doc) {}

void ApplicationPlugin::prepareNewDocument() {}

void ApplicationPlugin::on_activeWindowChanged() {}

}
