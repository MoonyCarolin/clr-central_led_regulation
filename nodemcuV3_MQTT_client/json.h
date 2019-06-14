//JSON API implementation, 2017 by phantomix
//License is LGPL (Version 3, 29 June 2007), see file "COPYING"

//Read about json here: http://www.ietf.org/rfc/rfc4627.txt (this implementation doesn't stricly follow the rfc yet.)
//For using this over an HTTP server, json should be delivered as "application/json"

#ifndef JSON_H
#define JSON_H

#ifdef __cplusplus
extern "C" {
#endif //__cplusplus

#include <stddef.h>
#include <stdint.h>

//usage
// (1) define a reflection description of your data
// (2) to convert a struct to json, call struct_to_json(), together with the description
// (3) to convert json to a struct, call json_to_struct(), together with the description

typedef enum
{
    json_error_none                 = 0x00,
    json_error_out_of_memory        = 0x01,
    json_error_out_of_input_data    = 0x02,
    json_error_unknown_escaped_data = 0x03,
    json_error_malformatted_input   = 0x04,
    json_error_model_element_size   = 0x05,
    json_error_model_element_typeclass= 0x06,
    json_error_model_struct_alignment= 0x07,
    json_error_element_not_found    = 0x08,
    json_error_permission_denied    = 0x09,
} json_error_e;


/*
data arrangement types:
supported	type														setup
yes			direct single element (struct entity)						typeclass = 1...5, count = 1
yes			direct array of elements (within the struct)				typeclass = 1...5, count >= 2
yes			pointer to single element (struct holds the pointer)		typeclass = (1..5) | pointer, count = 1
yes			pointer to array of elements (one pointer in struct)		typeclass = (1..5) | pointer, count >= 2
yes			direct c-string within struct								typeclass = 6, count = 1
yes			direct array of c-strings									typeclass = 6, count >= 2
yes			pointer to c-string											typeclass = 6 | pointer, count = 1
yes			pointer to array of c-strings								typeclass = 6 | pointer, count >= 2
no			pointer array to elements									-
*/
//typeclasses specify the type of data we're handling. they are used in conjunction with a byte width to distinguish e.g. uint8_t from uint32_t, float from double etc.
typedef enum
{
    json_typeclass_invalid = 0x00,
    json_typeclass_eos     = 0x00,  //!< End-of-Struct
    json_typeclass_char    = 0x01,
    json_typeclass_int     = 0x02,
    json_typeclass_uint    = 0x03,
    json_typeclass_flpoint = 0x04,
    json_typeclass_struct  = 0x05,
    json_typeclass_cstring = 0x06,

    json_typemask_pointer  = 0x40,  //!< Every typeclass can be masked with this value to signal a "pointer to the object[s]. This is useful for  describing if e.g. an array is directly embedded to a struct, or if it is exists separately.
} json_typeclass_e;

typedef enum
{
    json_permission_read_respect_uid        = 0x0001, //!< main switch for json_permission_read_allow_*_uid
    json_permission_read_allow_lower_uid    = 0x0002,
    json_permission_read_allow_equal_uid    = 0x0004,
    json_permission_read_allow_higher_uid   = 0x0008,

    json_permission_write_respect_uid       = 0x0010, //!< main switch for json_permission_write_allow_*_uid
    json_permission_write_allow_lower_uid   = 0x0020,
    json_permission_write_allow_equal_uid   = 0x0040,
    json_permission_write_allow_higher_uid  = 0x0080,

    json_permission_breach_throws_error     = 0x2000, //!< Unpermitted actions will break parsing / outputting (restrictive). Otherwise, the specific field is just ignored
    json_permission_read_forbidden          = 0x4000, //!< Main switch for read access (default: on)
    json_permission_write_allowed           = 0x8000, //!< Main switch for write access (default: off)
} json_permission_mask_e;

struct json_element_t;

typedef struct json_element_t
{
    const char*                   element_name;         //!< C-String
    const json_typeclass_e        element_typeclass;
    const size_t                  element_size;         //!< byte width of a single element
    const size_t                  element_count;        //!< in case, the specific element is an array, this defines the length (or in case of a cstring, the max-length)
    const struct json_element_t*  element_structdesc;   //!< If the typeclass of this element is "struct", the structdesc entry links to the description array of this substruct.
    json_permission_mask_e        permissions;
    uint8_t                       read_user_id;
    uint8_t                       write_user_id;
} json_element_t;


json_error_e struct_to_json(char destination[], size_t* buffer_space, const json_element_t descriptors[], const void* source, const uint8_t user_id);

//!\note with json_to_struct, you should work on a copy of your struct as partially-parsed input can also alter the destination content.
//!\note lenptr will be decreased during the process and remains at "unprocessed bytes after processing the whole struct description"
json_error_e json_to_struct(void* destination, const size_t destination_size, const json_element_t descriptors[], const char* source, size_t* lenptr, const uint8_t user_id);


_Bool string_startswith(const char string[], const char startswith[]);

#ifdef __cplusplus
} //extern "C"
#endif //__cplusplus
#endif //JSON_H

