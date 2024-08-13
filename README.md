# JUCEissueExample

reproduction steps:
- in CMakeLists.txt set your own paths:

  add_subdirectory("pathToJuce" JUCE)
  
  set(NUGET_EXE "path/nuget.exe")
  
  nuget.exe is included
- refresh CMake
- select AuxioPluginExample_Standalone and run, preferably debug mode, build takes a while
- in plugin window "options" and click "Reset to default state" until it crashes
- if it errors on *repeated* runs, changing generator to NMake Makefiles and clearing build files works for me
