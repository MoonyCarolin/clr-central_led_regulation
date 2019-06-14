#include "json_model.h"

#ifdef __cplusplus
extern "C" {
#endif //__cplusplus



const json_element_t wifi_config_json_desc[] =
{
    { .element_name = "mode",       .element_typeclass = json_typeclass_cstring,  .element_size = 4, .element_count = 1, .permissions = json_permission_write_allowed},
    { .element_name = "ssid",       .element_typeclass = json_typeclass_cstring,  .element_size = 32, .element_count = 1, .permissions = json_permission_write_allowed},
    { .element_name = "pass",       .element_typeclass = json_typeclass_cstring,  .element_size = 32, .element_count = 1, .permissions = json_permission_write_allowed},
    { .element_name = "",           .element_typeclass = json_typeclass_eos,      .element_size =  0,  .element_count = 0 },
};


const json_element_t mqtt_config_json_desc[] =
{
    { .element_name = "server",     .element_typeclass = json_typeclass_cstring,  .element_size = 32, .element_count = 1, .permissions = json_permission_write_allowed},
    { .element_name = "port",       .element_typeclass = json_typeclass_uint,     .element_size = 2, .element_count = 1, .permissions = json_permission_write_allowed},
    { .element_name = "user",       .element_typeclass = json_typeclass_cstring,  .element_size = 32, .element_count = 1, .permissions = json_permission_write_allowed},
    { .element_name = "pass",       .element_typeclass = json_typeclass_cstring,  .element_size = 32, .element_count = 1, .permissions = json_permission_write_allowed},
    { .element_name = "",           .element_typeclass = json_typeclass_eos,      .element_size =  0,  .element_count = 0 },
};


const json_element_t position_config_json_desc[] =
{
    { .element_name = "position1",       .element_typeclass = json_typeclass_cstring,  .element_size = 32, .element_count = 1, .permissions = json_permission_write_allowed},
    { .element_name = "position2",       .element_typeclass = json_typeclass_cstring,  .element_size = 32, .element_count = 1, .permissions = json_permission_write_allowed},
    { .element_name = "position3",       .element_typeclass = json_typeclass_cstring,  .element_size = 32, .element_count = 1, .permissions = json_permission_write_allowed},
    { .element_name = "position4",       .element_typeclass = json_typeclass_cstring,  .element_size = 32, .element_count = 1, .permissions = json_permission_write_allowed},
    { .element_name = "position5",       .element_typeclass = json_typeclass_cstring,  .element_size = 32, .element_count = 1, .permissions = json_permission_write_allowed},
    { .element_name = "",                .element_typeclass = json_typeclass_eos,      .element_size =  0,  .element_count = 0 },
};



#ifdef __cplusplus
} //extern "C"
#endif //__cplusplus
