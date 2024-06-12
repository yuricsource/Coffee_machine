idf_component_register(
    SRC_DIRS  "." "../Esp32/Source/Hal/" "../Esp32/Source/App/" "../Esp32/Source/Utils/" "../Esp32/Libraries/freertos-addons/Source"
    INCLUDE_DIRS "." "../Esp32/Include/Hal/" "../Esp32/Include/App/" "../Esp32/Include/Utils/" "../Esp32/Libraries/freertos-addons/Source/include"
)

target_compile_definitions(${COMPONENT_LIB} PUBLIC CPP_FREERTOS_NO_EXCEPTIONS)