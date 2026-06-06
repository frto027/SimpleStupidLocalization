# example:
# add the following things to your cmake file

# include(${EXTERN_DIR}/include/sslocalization/utils/csv2hpp.cmake)
# ssl10n_csv_2_hpp(${COMPILE_ID} "${CMAKE_CURRENT_BINARY_DIR}/sslocalization_generated" "SSL10nGen.hpp" "${CMAKE_CURRENT_SOURCE_DIR}/localize.csv")

set(SSL10N_CSV2CPP_PYTHON_FILE ${CMAKE_CURRENT_LIST_DIR}/csv2cpp.py)
function(ssl10n_csv_2_hpp ProjectName GenerateTargetPath GeneratedHeaderName)
        file(MAKE_DIRECTORY ${GenerateTargetPath}/)
        set(EMBBED_DATA_HPP   ${GenerateTargetPath}/${GeneratedHeaderName})
        set(EMBBED_DATA_CPP   ${GenerateTargetPath}.cpp)

        find_package(Python3 REQUIRED COMPONENTS Interpreter)
        add_custom_command(
                OUTPUT ${EMBBED_DATA_HPP} ${EMBBED_DATA_CPP}
                COMMAND ${Python3_EXECUTABLE} ${SSL10N_CSV2CPP_PYTHON_FILE} ${EMBBED_DATA_HPP} ${EMBBED_DATA_CPP} ${ARGN}
                DEPENDS ${ARGN}
                COMMENT "Generate hpp from csv file..."
                VERBATIM
        )
        add_custom_target(SSL10nCsv2Hpp DEPENDS ${EMBBED_DATA_CPP})
        add_dependencies(${ProjectName} SSL10nCsv2Hpp)
        target_sources(${ProjectName} PRIVATE ${EMBBED_DATA_CPP})
        target_include_directories(${ProjectName} PRIVATE ${GenerateTargetPath}/)
endfunction()

