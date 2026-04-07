project(score_addon_tutorial LANGUAGES CXX)

find_package(Qt6 COMPONENTS QuickWidgets)
# General initialization
score_common_setup()

# Source files
set(HDRS
    Tutorial/Process/Executor/TutorialProcessExecutor.hpp
    Tutorial/Process/Layer/TutorialProcessPresenter.hpp
    Tutorial/Process/Layer/TutorialProcessView.hpp
    Tutorial/Process/Layer/TutorialProcessLayerFactory.hpp
    Tutorial/Process/Layer/TutorialProcessLayer.hpp
    Tutorial/Process/LocalTree/TutorialProcessLocalTree.hpp
    Tutorial/Process/Inspector/TutorialProcessInspector.hpp
    Tutorial/Process/State/TutorialProcessState.hpp
    Tutorial/Process/TutorialProcessModel.hpp
    Tutorial/Process/TutorialProcessMetadata.hpp
    Tutorial/Process/TutorialProcessFactory.hpp
    Tutorial/ApplicationPlugin/TutorialApplicationPlugin.hpp
    Tutorial/Panel/TutorialPanelDelegate.hpp
    Tutorial/Panel/TutorialPanelDelegateFactory.hpp
    Tutorial/Settings/TutorialSettingsModel.hpp
    Tutorial/Settings/TutorialSettingsView.hpp
    Tutorial/Settings/TutorialSettingsPresenter.hpp
    Tutorial/Settings/TutorialSettingsFactory.hpp
    Tutorial/DocumentPlugin/TutorialDocumentPlugin.hpp
    Tutorial/Commands/AddBanana.hpp
    Tutorial/Commands/AddEntity.hpp
    Tutorial/Commands/TutorialCommandFactory.hpp
    Tutorial/SimpleElement/SimpleElement.hpp
    Tutorial/SimpleElement/SimpleEntity.hpp
    Tutorial/PolymorphicEntity/PolymorphicEntity.hpp
    Tutorial/PolymorphicEntity/PolymorphicEntityFactory.hpp
    Tutorial/PolymorphicEntity/Implementation/ConcretePolymorphicEntity.hpp

    score_addon_tutorial.hpp

)
set(SRCS
    Tutorial/SimpleElement/SimpleElement.cpp
    Tutorial/Process/Executor/TutorialProcessExecutor.cpp
    Tutorial/Process/Layer/TutorialProcessPresenter.cpp
    Tutorial/Process/Layer/TutorialProcessView.cpp
    Tutorial/Process/LocalTree/TutorialProcessLocalTree.cpp
    Tutorial/Process/Inspector/TutorialProcessInspector.cpp
    Tutorial/Process/State/TutorialProcessState.cpp
    Tutorial/Process/TutorialProcessModel.cpp
    Tutorial/ApplicationPlugin/TutorialApplicationPlugin.cpp
    Tutorial/Panel/TutorialPanelDelegate.cpp
    Tutorial/Settings/TutorialSettingsModel.cpp
    Tutorial/Settings/TutorialSettingsView.cpp
    Tutorial/Settings/TutorialSettingsPresenter.cpp
    Tutorial/DocumentPlugin/TutorialDocumentPlugin.cpp
    Tutorial/Commands/AddBanana.cpp
    Tutorial/Commands/AddEntity.cpp
    Tutorial/SimpleElement/SimpleEntity.cpp
    Tutorial/PolymorphicEntity/PolymorphicEntity.cpp
    Tutorial/PolymorphicEntity/PolymorphicEntityFactory.cpp
    Tutorial/PolymorphicEntity/Implementation/ConcretePolymorphicEntity.cpp

    score_addon_tutorial.cpp
)

qt6_add_resources(QRCS "${CMAKE_CURRENT_SOURCE_DIR}/resources/Tutorial.qrc")

# Creation of the library
add_library(${PROJECT_NAME} ${SRCS} ${HDRS} ${QRCS})

# Code generation
score_generate_command_list_file(${PROJECT_NAME} "${HDRS}")

# Link
target_link_libraries(${PROJECT_NAME} PUBLIC score_plugin_engine Qt6::QuickWidgets)

# Target-specific options
setup_score_plugin(${PROJECT_NAME})
