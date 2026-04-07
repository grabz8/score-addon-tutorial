#pragma once
#include <Process/ProcessMetadata.hpp>

namespace Tutorial
{
class ProcessModel;
}

PROCESS_METADATA(
    ,                                       // Potentially an EXPORT macro
    Tutorial::ProcessModel,                 // The class
    "8337475a-9a3c-4195-9d60-b25c8bb94756", // Unique identifier
    "Tutorial", // Internal name // Name that will be stored in the save file
    "Tutorial", // Pretty name   // Name that will be shown to the user
    Process::ProcessCategory::Other, // Category    // A broad category
    "Tutorial",                      // Category    // Precise name for the category
    "A tutorial process",            // Description // Textual description
    "ossia score",                   // Author
    {},                              // Tags
    {std::vector<Process::PortType>{}}, // Inputs
    {std::vector<Process::PortType>{}}, // Outpus
    QUrl(""),   // Doc url
    Process::ProcessFlags::SupportsAll | Process::ProcessFlags::PutInNewSlot)   // Flags
