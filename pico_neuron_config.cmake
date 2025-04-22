
if(NOT DEFINED MODEL_NAME)
    set(MODEL_NAME "hindmarsh_rose")
endif()
set(CONFIG_FILE "${CMAKE_SOURCE_DIR}/config/${MODEL_NAME}.cfg")
file(READ "${CONFIG_FILE}" CONFIG_CONTENTS)

function(parse_define_from_config VAR_NAME CONFIG_STR)
    string(REGEX MATCH "${VAR_NAME}=.*" LINE "${CONFIG_STR}")
    string(REPLACE "${VAR_NAME}=" "" VALUE "${LINE}")
    # Strip quotes, if needed
    string(STRIP "${VALUE}" VALUE)
    set(${VAR_NAME}_VALUE "${VALUE}" PARENT_SCOPE)
endfunction()

parse_define_from_config(DECIMAL_PRECISION "${CONFIG_CONTENTS}")
parse_define_from_config(MODEL_NAME "${CONFIG_CONTENTS}")
parse_define_from_config(SYNAPTICAL "${CONFIG_CONTENTS}")
parse_define_from_config(RESPONSE "${CONFIG_CONTENTS}")
parse_define_from_config(THRESHOLD "${CONFIG_CONTENTS}")
parse_define_from_config(ORDERED_PARAMS "${CONFIG_CONTENTS}")


