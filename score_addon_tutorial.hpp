#pragma once
#include <score/application/ApplicationContext.hpp>
#include <score/command/Command.hpp>
#include <score/command/CommandGeneratorMap.hpp>
#include <score/plugins/InterfaceList.hpp>
#include <score/plugins/qt_interfaces/CommandFactory_QtInterface.hpp>
#include <score/plugins/qt_interfaces/FactoryFamily_QtInterface.hpp>
#include <score/plugins/qt_interfaces/FactoryInterface_QtInterface.hpp>
#include <score/plugins/qt_interfaces/GUIApplicationPlugin_QtInterface.hpp>
#include <score/plugins/qt_interfaces/PluginRequirements_QtInterface.hpp>

#include <QObject>

#include <utility>
#include <vector>

/**
 * @brief The score_addon_tutorial class
 *
 * This class is the entry-point of the i-score plugin.
 *
 * \ref score::PluginLoader::loadPlugins contains the plug-in loading code.
 * \ref score::ApplicationInterface::loadPluginData contains plug-in setup
 * code.
 *
 * The loaded plug-in data can always be accessed through \ref
 * score::AppContext but it is better practice to have the objects depend on
 * their requirements through constructor injection, and provide these
 * requirements in the object factories which have access to the same context
 * without requiring a singleton function.
 *
 * When making a plug-in, not all the interfaces used here may be necessary;
 * this one aims to give an overview of all the possibilities.
 */
class score_addon_tutorial final : public score::Plugin_QtInterface,
                                   public score::FactoryInterface_QtInterface,
                                   public score::FactoryList_QtInterface,
                                   public score::ApplicationPlugin_QtInterface,
                                   public score::CommandFactory_QtInterface
{
  // Version, and unique identifier for the plug-in.
  // The uuid can be generated with "uuidgen" on linux or OS X.
  SCORE_PLUGIN_METADATA(1, "e8601d50-e29e-4437-8c65-fcee42655a0b")

public:
  score_addon_tutorial();
  ~score_addon_tutorial() override;

private:
  // Defined in Plugin_QtInterface
  std::vector<score::PluginKey> required() const override;

  void updateSaveFile(
      rapidjson::Value& obj,
      score::Version obj_version,
      score::Version current_version) override;

  // Defined in FactoryList_QtInterface
  std::vector<std::unique_ptr<score::InterfaceListBase>> factoryFamilies() override;
  //std::vector<score::InterfaceListBase*> factoryFamilies() override;

  // Defined in FactoryInterface_QtInterface
  //std::vector<std::unique_ptr<score::InterfaceBase>> factories(
  std::vector<score::InterfaceBase*> factories(
      const score::ApplicationContext& ctx,
      const score::InterfaceKey& key) const override;

  // Defined in ApplicationPlugin_QtInterface
  score::GUIApplicationPlugin*
  make_guiApplicationPlugin(const score::GUIApplicationContext& app) override;

  // Defined in CommandFactory_QtInterface
  std::pair<const CommandGroupKey, CommandGeneratorMap>
  make_commands() override;
};
