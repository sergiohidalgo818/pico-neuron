

if(NOT DEFINED MODEL_NAME)
    set(MODEL_NAME "hindmarsh_rose")
endif()
set(CONFIG_FILE "${CMAKE_SOURCE_DIR}/config/${PICO_BOARD}/${MODEL_NAME}.cfg")
# Function to parse config values
function(parse_config)
    # Read the entire config file
    file(READ "${CONFIG_FILE}" CONFIG_CONTENTS)
    
    # Convert to LF line endings
    string(REPLACE "\r" "" CONFIG_CONTENTS "${CONFIG_CONTENTS}")
    
    # Split into lines
    string(REGEX MATCHALL "[^\n]+" LINES "${CONFIG_CONTENTS}")
    
    foreach(LINE IN LISTS LINES)
        # Skip comments and empty lines
        if(NOT LINE MATCHES "^[ \t]*#" AND LINE MATCHES "=")
            # Split at first = sign
            string(REGEX REPLACE "^([^=]*)=(.*)" "\\1;\\2" PARTS "${LINE}")
            list(GET PARTS 0 VAR_NAME)
            list(GET PARTS 1 VAR_VALUE)
            
            # Clean up the values
            string(STRIP "${VAR_NAME}" VAR_NAME)
            string(STRIP "${VAR_VALUE}" VAR_VALUE)
            
            # Remove trailing comments
            string(REGEX REPLACE "[ \t]*#.*$" "" VAR_VALUE "${VAR_VALUE}")
            string(STRIP "${VAR_VALUE}" VAR_VALUE)
            
            # Remove surrounding quotes if present
            string(REGEX REPLACE "^\"(.*)\"$" "\\1" VAR_VALUE "${VAR_VALUE}")
            
            # Set as CMake variable
            set(${VAR_NAME} "${VAR_VALUE}" PARENT_SCOPE)
            message(STATUS "${VAR_NAME} = ${VAR_VALUE}")
        endif()
    endforeach()
endfunction()

parse_config()

string(REGEX REPLACE "f" "" THRESHOLD "${THRESHOLD}")
string(REGEX REPLACE "f" "" TIME_INCREMENT "${TIME_INCREMENT}")
string(REGEX REPLACE "f" "" FREQUENCY "${FREQUENCY}")

if(DEFINED ORDERED_PARAMS)

    string(REGEX REPLACE "f" "" RAW_VALUES "${ORDERED_PARAMS}")

    string(REGEX REPLACE ",[ \t]*" "," RAW_VALUES "${RAW_VALUES}")

    set(${ORDERED_PARAMS} "${ORDERED_PARAMS}" )
endif()
