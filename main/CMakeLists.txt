idf_component_register(
    SRC_DIRS  "." "../Esp32/Source/Hal/" "../Esp32/Source/App/" "../Esp32/Source/Utils/" "../Esp32/Libraries/freertos-addons/Source" "../Esp32/Source/Protocol/Mqtt"
    INCLUDE_DIRS "." "../Esp32/Include/" "../Esp32/Include/Hal/" "../Esp32/Include/App/" "../Esp32/Include/Common/" "../Esp32/Include/Utils/" "../Esp32/Libraries/freertos-addons/Source/include" "../Esp32/Include/Protocol" "../Esp32/Include/Protocol/Mqtt"
)

target_compile_definitions(${COMPONENT_LIB} PUBLIC CPP_FREERTOS_NO_EXCEPTIONS)