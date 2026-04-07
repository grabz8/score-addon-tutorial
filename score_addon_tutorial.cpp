#include "score_addon_tutorial.hpp"

#include <score/plugins/FactorySetup.hpp>

#include <Tutorial/ApplicationPlugin/TutorialApplicationPlugin.hpp>
#include <Tutorial/DocumentPlugin/TutorialDocumentPlugin.hpp>
#include <Tutorial/Panel/TutorialPanelDelegate.hpp>
#include <Tutorial/PolymorphicEntity/Implementation/ConcretePolymorphicEntity.hpp>
#include <Tutorial/PolymorphicEntity/PolymorphicEntityFactory.hpp>
#include <Tutorial/Process/Executor/TutorialProcessExecutor.hpp>
#include <Tutorial/Process/Inspector/TutorialProcessInspector.hpp>
#include <Tutorial/Process/Layer/TutorialProcessLayerFactory.hpp>
#include <Tutorial/Process/LocalTree/TutorialProcessLocalTree.hpp>
#include <Tutorial/Process/TutorialProcessFactory.hpp>
#include <score/model/EntitySerialization.hpp>
#include <score_addon_tutorial_commands_files.hpp>

score_addon_tutorial::score_addon_tutorial() {}

score_addon_tutorial::~score_addon_tutorial() {}

/**
 * @brief score_addon_tutorial::required
 * @return Features that this plug-in requires.
 *
 * If a feature is listed here, i-score will load the
 * plug-in providing this feature (through \ref
 * score::Plugin_QtInterface::offered) before this one.
 */
auto score_addon_tutorial::required() const -> std::vector<score::PluginKey>
{
  return {};
}

/**
 * @brief score_addon_tutorial::updateSaveFile
 * This function is called if someone tries to load
 * a save file that was created with a previous version
 * of this plug-in.
 * This allows to update the JSON data in order to load
 * it in the current version.
 */
void score_addon_tutorial::updateSaveFile(
    rapidjson::Value& obj,
    score::Version obj_version,
    score::Version current_version)
{
}

/**
 * @brief score_addon_tutorial::factoryFamilies
 * This function allows the plug-in to provide new factory types.
 * All plug-ins will be scanned for factories of the provided type.
 *
 * For instance, a new interface to display some elements in a toolbar.
 *
 * Elements registered here can then be used through an \ref
 * score::ApplicationContext instance :
 *
 * \code
 * auto& ctx = score::AppContext();
 * auto& my_factories =
 * ctx.interfaces<Tutorial::PolymorphicElementFactoryList>(); \endcode
 */
std::vector<std::unique_ptr<score::InterfaceListBase>>
score_addon_tutorial::factoryFamilies()
{
  // Just use make_ptr_vector directly as suggested by the compiler
  return make_ptr_vector<
      score::InterfaceListBase,
      Tutorial::PolymorphicElementFactoryList>();
}



/**
 * @brief score_addon_tutorial::factories
 *
 * This function allows the plug-in to provide implementations for the
 * factory types provided earlier.
 *
 * For instance, factories for the elements that will go in the toolbar.
 *
 * An helper function is provided : \ref instantiate_factories .
 *
 * The factories registered here are then accessible like this :
 *
 * \code
 * // Get a context or use an existing one
 * auto& ctx = score::AppContext();
 *
 * // Get the list of factories that we are looking for
 * auto& my_factories = ctx.interfaces<Process::ProcessList>();
 *
 * // Get the key for the actual factory we want;
 * // Instead of doing this, it could already be saved somewhere for instance.
 * auto process_key = Metadata<ConcreteKey_k, Tutorial::ProcessFactory>::get();
 *
 * // Get the actual factory
 * auto my_process_factory = my_factories.get(process_key);
 * \endcode
 *
 * However, it should rarely be necessary to access a particular factory.
 * The general case should be getting a factory according to an user input.
 */
std::vector<score::InterfaceBase*>
score_addon_tutorial::factories(
    const score::ApplicationContext& ctx,
    const score::InterfaceKey& key) const
{
  return instantiate_factories<
      score::ApplicationContext,
      FW<Process::ProcessModelFactory, Tutorial::ProcessFactory>,
      FW<Process::LayerFactory, Tutorial::LayerFactory>,
      FW<Process::InspectorWidgetDelegateFactory, Tutorial::InspectorFactory>,
      FW<Execution::ProcessComponentFactory, Tutorial::ProcessExecutorComponentFactory>,
      FW<LocalTree::ProcessComponentFactory, Tutorial::LocalTreeProcessComponentFactory>,
      FW<score::DocumentPluginFactory, Tutorial::DocumentPluginFactory>,
      FW<score::PanelDelegateFactory, Tutorial::PanelDelegateFactory>,
      FW<Tutorial::PolymorphicElementFactory, Tutorial::ConcretePolymorphicElementFactory>
      >(ctx, key);
}


/**
 * @brief score_addon_tutorial::make_applicationPlugin
 *
 * This function allows to instantiate an application-wide object.
 * These objects are instantiated before any factory.
 */
score::GUIApplicationPlugin* score_addon_tutorial::make_guiApplicationPlugin(
    const score::GUIApplicationContext& app)
{
  return new Tutorial::ApplicationPlugin{app};
}

/**
 * @brief score_addon_tutorial::make_commands
 * This function provides the list of commands available with this
 * plug-in.
 */
std::pair<const CommandGroupKey, CommandGeneratorMap>
score_addon_tutorial::make_commands()
{
  using namespace Tutorial;
  std::pair<const CommandGroupKey, CommandGeneratorMap> cmds{
      CommandFactoryName(), CommandGeneratorMap{}};

  // CMake generates the "addon_commands.hpp" and "addon_commands_file.hpp"
  // by scanning the source files for \ref SCORE_COMMAND_DECL or \ref
  // SCORE_COMMAND_DECL_T.

  ossia::for_each_type<
#include <score_addon_tutorial_commands.hpp>
      >(score::commands::FactoryInserter{cmds.second});

  return cmds;
}

#include <score/plugins/PluginInstances.hpp>
SCORE_EXPORT_PLUGIN(score_addon_tutorial)
