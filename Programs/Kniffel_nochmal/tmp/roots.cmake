# roots.cmake
set(CMSIS_PACK_ROOT "C:/Users/smdan/AppData/Local/Arm/Packs" CACHE PATH "CMSIS pack root")
cmake_path(ABSOLUTE_PATH CMSIS_PACK_ROOT NORMALIZE OUTPUT_VARIABLE CMSIS_PACK_ROOT)
set(CMSIS_COMPILER_ROOT "C:/Users/smdan/.vscode/extensions/arm.cmsis-csolution-1.64.2-win32-x64/tools/cmsis-toolbox/etc" CACHE PATH "CMSIS compiler root")
cmake_path(ABSOLUTE_PATH CMSIS_COMPILER_ROOT NORMALIZE OUTPUT_VARIABLE CMSIS_COMPILER_ROOT)
set(SOLUTION_ROOT "C:/TI_Labor/gitProjekte/ITS-BRD-VSC/Programs/Kniffel_nochmal" CACHE PATH "CMSIS solution root")
cmake_path(ABSOLUTE_PATH SOLUTION_ROOT NORMALIZE OUTPUT_VARIABLE SOLUTION_ROOT)
