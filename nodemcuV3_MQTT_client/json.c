//JSON API implementation, 2017 by phantomix
//License is LGPL (Version 3, 29 June 2007), see file "COPYING"

#include "json.h"

#ifdef __cplusplus
extern "C" {
#endif //__cplusplus
#include <string.h>

#if !defined(JSON_MAX_TOKEN_LENGTH)
	#warning please define JSON_MAX_TOKEN_LENGTH to at least the maximum used element name.
	#define JSON_MAX_TOKEN_LENGTH 64
#endif

#define CHAR_IF_SPACE2(C, D, SIZEPTR, RFAIL)    do { if(*(SIZEPTR) > 0) { *(D++) = (C); (*(SIZEPTR))--; } else return (RFAIL);  } while(0)

#define DIGITTOHEX(C) ( ((C) & 0x0F) >= 0x0A ? (((C) & 0x0F) - 0x0A + 'A') : (((C) & 0x0F) + '0') )
#define IS_HEX_DIGIT(C) ( (C >= '0' && C <= '9') || ( C >= 'A' && C <= 'F') || (C >= 'a' && c <= 'f') )
#define HEXTODIGIT(C) ((C >= '0' && c <= '9') ? (C - '0') : (((C) | 0x20) - 'a' + 0x0A) )

/** \brief  perform a stringcopy, while exchanging all critical characters
 *  \note this will terminate on \0 characters or buffer full
 *  \return json_error_out_of_memory if failed
 *  \return amount of characters, if there was enough space in the destination
 */
static json_error_e json_copy_escape(const char* source, char** destination, size_t* buffer_space)
{
    size_t fill = 0;
    char c;
    char* dest = *destination;
    while(c = *source++)
    {
        if(c < 0x20)  //escape to unicode notation
        {
            char digit;
            CHAR_IF_SPACE2('\\', dest, buffer_space, json_error_out_of_memory);
            CHAR_IF_SPACE2('u', dest, buffer_space, json_error_out_of_memory);
            CHAR_IF_SPACE2('0', dest, buffer_space, json_error_out_of_memory);
            CHAR_IF_SPACE2('0', dest, buffer_space, json_error_out_of_memory);
            digit = DIGITTOHEX(c >> 4);
            CHAR_IF_SPACE2(digit, dest, buffer_space, json_error_out_of_memory);
            digit = DIGITTOHEX(c);
            CHAR_IF_SPACE2(digit, dest, buffer_space, json_error_out_of_memory);
        } else if((c == '\\') || (c == '"'))
        {
            CHAR_IF_SPACE2('\\', dest, buffer_space, json_error_out_of_memory);
            CHAR_IF_SPACE2(c, dest, buffer_space, json_error_out_of_memory);
        } else
        {
            CHAR_IF_SPACE2(c, dest, buffer_space, json_error_out_of_memory);
        }
    }
    *destination = dest;
    return json_error_none;
}

json_error_e insert_contents(char destination[], size_t* buffer_space, const json_element_t descriptors[], const void* source, const uint8_t user_id)
{
    if(descriptors->element_count > 1) CHAR_IF_SPACE2('[', destination, buffer_space, json_error_out_of_memory);

    for(size_t i = 0; i < descriptors->element_count; i++)
    {
        const void* elementptr;

        json_typeclass_e typeclass = descriptors->element_typeclass;

        if(typeclass & json_typemask_pointer)
        {
            typeclass &= ~json_typemask_pointer;

            //JSON_SECURE_COPY(elementptr, source, sizeof(const void*));
            elementptr = *((const void**) source);
            source = ((char*) source) + sizeof(const void*);
        } else
        {
            elementptr = source;
            source = ((char*) source) + descriptors->element_size;
        }

        if(i) CHAR_IF_SPACE2(',', destination, buffer_space, json_error_out_of_memory);

        if(typeclass == json_typeclass_struct)
        {
            size_t new_space = *buffer_space;
            json_error_e err = struct_to_json(destination, &new_space, descriptors->element_structdesc, elementptr, user_id);
            if(err != json_error_none) return err;
            destination += (*buffer_space - new_space);
            *buffer_space = new_space;
        } else
        {
            CHAR_IF_SPACE2('"', destination, buffer_space, json_error_out_of_memory);
            switch(typeclass)
            {              
                case json_typeclass_char:
                {
                    CHAR_IF_SPACE2(*((char*) elementptr), destination, buffer_space, json_error_out_of_memory);
                } break;
                case json_typeclass_int:
                {
                    char itoabuffer[22];
                    switch(descriptors->element_size)
                    {
                        case 1: itoa(*(( int8_t*) elementptr), itoabuffer, 10); break;
                        case 2:
                                #if(ESP8266)
                                if((uint32_t)elementptr & 0x01) return json_error_model_struct_alignment;
                                #endif
                                itoa(*((int16_t*) elementptr), itoabuffer, 10); break;
                        case 4:
                                #if(ESP8266)
                                if((uint32_t)elementptr & 0x03) return json_error_model_struct_alignment;
                                #endif
                                itoa(*((int32_t*) elementptr), itoabuffer, 10); break;
                        case 8:
                                #if(ESP8266)
                                if((uint32_t)elementptr & 0x07) return json_error_model_struct_alignment;
                                #endif
                                ltoa(*((int64_t*) elementptr), itoabuffer, 10); break;
                        default: return json_error_model_element_size;  //error
                    }
                    {
                        //At this point, we don't need escaping but to save memory, we use the escape copy function
                        json_error_e err = json_copy_escape(itoabuffer, &destination, buffer_space);
                        if(err != json_error_none) return err;
                        //STRING_IF_SPACE2(itoabuffer, destination, buffer_space, json_error_out_of_memory);
                        //size_t content_fill = json_copy_escape(itoabuffer, &destination[fill], max_dest_size - fill);
                        //if(!content_fill) return 0;
                        //fill += content_fill;
                    }
                } break;
                case json_typeclass_uint:
                {
                    char utoabuffer[21];
                    switch(descriptors->element_size)
                    {
                        case 1: utoa( *(( uint8_t*) elementptr), utoabuffer, 10); break;
                        case 2:
                                #if(ESP8266)
                                if((uint32_t)elementptr & 0x01) return json_error_model_struct_alignment;
                                #endif
                                utoa( *((uint16_t*) elementptr), utoabuffer, 10); break;
                        case 4:
                                #if(ESP8266)
                                if((uint32_t)elementptr & 0x03) return json_error_model_struct_alignment;
                                #endif
                                utoa( *((uint32_t*) elementptr), utoabuffer, 10); break;
                        case 8:
                                #if(ESP8266)
                                if((uint32_t)elementptr & 0x07) return json_error_model_struct_alignment;
                                #endif
                                ultoa(*((uint64_t*) elementptr), utoabuffer, 10); break;
                        default: return json_error_model_element_size;  //error
                    }
                    {
                        //At this point, we don't need escaping but to save memory, we use the escape copy function
                        json_error_e err = json_copy_escape(utoabuffer, &destination, buffer_space);
                        if(err != json_error_none) return err;
                    }
                } break;
                case json_typeclass_flpoint:
                {
                    return json_error_model_element_typeclass;
                } break;
                case json_typeclass_cstring:
                {
                    json_error_e err = json_copy_escape((const char*) elementptr, &destination, buffer_space);
                    if(err != json_error_none) return err;
                } break;
                default: return json_error_model_element_typeclass;
            }
            CHAR_IF_SPACE2('"', destination, buffer_space, json_error_out_of_memory);
        }
    }
    if(descriptors->element_count > 1) CHAR_IF_SPACE2(']', destination, buffer_space, json_error_out_of_memory);
    return json_error_none;
}

json_error_e struct_to_json(char destination[], size_t* buffer_space, const json_element_t descriptors[], const void* source, const uint8_t user_id)
{  
    CHAR_IF_SPACE2('{', destination, buffer_space, json_error_out_of_memory);

    _Bool first = 1;
    for(;;) //no descriptors count available, so no iterator here.
    {
        _Bool output_this_element = 1;

        if(     (descriptors->element_typeclass == json_typeclass_eos)
            ||  (descriptors->element_size == 0)
            ||  (descriptors->element_count == 0)  )
            break;

        if(descriptors->permissions & json_permission_read_forbidden)
        {
            if(descriptors->permissions & json_permission_breach_throws_error)
                return json_error_permission_denied;
            else
                output_this_element = 0;
        } else
        if(descriptors->permissions & json_permission_read_respect_uid)
        {
            if(   (descriptors->read_user_id == user_id && !(descriptors->permissions & json_permission_read_allow_equal_uid ))
                ||(descriptors->read_user_id <  user_id && !(descriptors->permissions & json_permission_read_allow_lower_uid ))
                ||(descriptors->read_user_id <  user_id && !(descriptors->permissions & json_permission_read_allow_higher_uid)) )
            {
                if(descriptors->permissions & json_permission_breach_throws_error)
                    return json_error_permission_denied;
                else
                    output_this_element = 0;
            }
        }

        if(output_this_element)
        {
            if(!first)   CHAR_IF_SPACE2(',', destination, buffer_space, json_error_out_of_memory);
            first = 0;
    
            CHAR_IF_SPACE2('"', destination, buffer_space, json_error_out_of_memory);
            {
                //STRING_IF_SPACE2(descriptors->element_name, destination, buffer_space, json_error_out_of_memory);
                
                json_error_e err = json_copy_escape(descriptors->element_name, &destination, buffer_space);
                if(err != json_error_none) return err;
            }
            CHAR_IF_SPACE2('"', destination, buffer_space, json_error_out_of_memory);
            CHAR_IF_SPACE2(':', destination, buffer_space, json_error_out_of_memory);
    
            //next contents depend on if it's an array, a sub-struct or a single value. This is handled by insert_contents()
            size_t new_space = *buffer_space;
            json_error_e err = insert_contents(destination, &new_space, descriptors, source, user_id);
            if(err != json_error_none) return err;
    
            destination += (*buffer_space - new_space);
            *buffer_space = new_space;
        }

        if(descriptors->element_typeclass & json_typemask_pointer)
            source = ((char*) source) + (sizeof(const void*) * descriptors->element_count);
        else
            source = ((char*) source) + (descriptors->element_size * descriptors->element_count);

        descriptors++;
    }
    CHAR_IF_SPACE2('}', destination, buffer_space, json_error_out_of_memory);
    CHAR_IF_SPACE2('\0', destination, buffer_space, json_error_none);
    (*buffer_space)++;  //we need to revert the effect done by writing \0
    return json_error_none;
}

/** \brief  perform a stringcopy, while restoring all critical characters
 *  \note this will terminate on "\0" characters, on '"' characters, dest buffer full or src buffer empty
 */
static json_error_e json_copy_unescape(char* destination, size_t* buffer_space, const char** source, size_t* srclenptr)
{
  	for(;;)
  	{
    		char c;
        if(! (*srclenptr)) return json_error_out_of_input_data; //cannot read another char
    		c = **source;
        if(c == '"')
        {
            //if there's still space, add a \0 character to the current position, this doesn't count to the string length (strlen equivalent)
            if(*buffer_space)
            {
                *destination = '\0';
                return json_error_none;
            } else
                return json_error_out_of_memory;    //this enforces C-String to be null-terminated.
        } else if(c == '\0')
        {
            return json_error_malformatted_input;
        }
        //increasing the pointer has to occur after filtering out the above characters, as they need to be evaluated again outside this function
        (*source)++;
        (*srclenptr)--;
    		switch(c)
    		{
    			case '\\':
              if(! (*srclenptr)) return json_error_out_of_input_data; //cannot read another char
              c = **source;
              (*source)++;
              (*srclenptr)--;
          
      				if(c == 'u')
      				{
      					  uint16_t unicode;// = 0;
                  if((*srclenptr) < 4) return json_error_out_of_input_data; //cannot read another char
                  (*srclenptr) -= 4;
                  c = *(*source)++; if(IS_HEX_DIGIT(c)) unicode |= HEXTODIGIT(c) << 12; else return json_error_malformatted_input;
                  c = *(*source)++; if(IS_HEX_DIGIT(c)) unicode |= HEXTODIGIT(c) <<  8; else return json_error_malformatted_input;
                  c = *(*source)++; if(IS_HEX_DIGIT(c)) unicode |= HEXTODIGIT(c) <<  4; else return json_error_malformatted_input;
                  c = *(*source)++; if(IS_HEX_DIGIT(c)) unicode |= HEXTODIGIT(c) <<  0; else return json_error_malformatted_input;
                  if(unicode > 0xFF)
                  {
                      if(*buffer_space)
                      {
                          *destination++ = (unicode >> 8) & 0xFF;
                          (*buffer_space)--;
                      } else
                          return json_error_out_of_memory;
                  }
                  //the lower char will be written in "default" branch
                  c = (char) (unicode & 0xFF);
      				}
      				//fallthrough
    			default:
      				if(*buffer_space)
      				{
      					  *destination++ = c;
      					  (*buffer_space)--;
      				} else
      					  return json_error_out_of_memory;
      				break;
  		}
  	}
}

static json_error_e skip_arbitrary(const char** source, size_t* lenptr)
{
    for(;;)
    {
        if(! (*lenptr)) return json_error_out_of_input_data;
        switch(**source)
        {
            //these are the chars on which we want to react in the calling function
            case '"':
            case ':':  case ',':
            case '{':  case '}':
            case '[':  case ']':
                return json_error_none;

            //these are the chars we can safely ignore (skip)
			      case ' ':  case '\t':
            case '\n': case '\r':
                break;

            //and, last but not least, these are the evil chars we're not tolerating.
            case '\0':
            default:
                return json_error_malformatted_input;
        }
        (*source)++;
        (*lenptr)--;
    }
    return json_error_malformatted_input;
}

_Bool string_startswith(const char string[], const char startswith[])
{
    while(*startswith)
    {
        if(*startswith++ != *string++)
            return 0;
    }
    return 1;
}

//!\brief Skip boring chars(e.g. whitespace, newline, ...)
#define SKIP_OR_EXIT()      do { if((err = skip_arbitrary(&source, lenptr)) != json_error_none) return err; } while(0)

//!\brief perform a compare of next interesting location with an ascii character, return an error if this fails
#define COMPARE_OR_EXIT(C)  do { SKIP_OR_EXIT(); if(!(*lenptr)) return json_error_out_of_input_data; (*lenptr)--; if(*source++ != C) return json_error_malformatted_input; } while(0)

//!\brief Skip next interesting location, if it's a comma (used as delimiter between key:value pairs.) Uninteresting, as we are evaluating ']' and '}' separately.
#define SKIP_COMMA()        do { SKIP_OR_EXIT(); if(!(*lenptr)) return json_error_out_of_input_data; if(*source == ',') {(*lenptr)--; source++; } } while(0)

//!\brief read a complete token from the stream. Stop when out of memory or hitting an "interesting character". Un-Escape string input
#define TOKEN_OR_EXIT(DEST, BUFFER_SPACE) do { if((err = json_copy_unescape(DEST, BUFFER_SPACE, &source, lenptr)) != json_error_none) return err; } while(0)


//!\note and \todo this needs a null-terminated source input. Better would be a length-based approach (to be extended)
json_error_e json_to_struct(void* destination, const size_t destination_size, const json_element_t descriptors[], const char* source, size_t* lenptr, const uint8_t user_id)
{
    json_error_e err;
    COMPARE_OR_EXIT('{');
    for(;;)
    {
    		size_t token_space;
    		char current_token[JSON_MAX_TOKEN_LENGTH];

        COMPARE_OR_EXIT('"');
        token_space = JSON_MAX_TOKEN_LENGTH;
    		TOKEN_OR_EXIT(current_token, &token_space);
    		COMPARE_OR_EXIT('"');

        //Wonderful. Now let's find the specified descriptor from the descriptor list
        const json_element_t* descriptor = descriptors;
        void* elementptr = destination;
        
        json_typeclass_e typeclass;
        _Bool isPtr;
        while(1)
        {
            if(descriptor->element_typeclass == json_typeclass_eos) return json_error_element_not_found;

            typeclass = descriptor->element_typeclass;
            isPtr = (typeclass & json_typemask_pointer) != 0;
            typeclass &= ~json_typemask_pointer;
            if(string_startswith(current_token, descriptor->element_name))  //found it!
            {
                if((descriptor->permissions & json_permission_write_allowed))
                {
                    if(descriptor->permissions & json_permission_write_respect_uid)
                    {
                        if(   (descriptor->write_user_id == user_id && !(descriptor->permissions & json_permission_read_allow_equal_uid ))
                            ||(descriptor->write_user_id <  user_id && !(descriptor->permissions & json_permission_read_allow_lower_uid ))
                            ||(descriptor->write_user_id <  user_id && !(descriptor->permissions & json_permission_read_allow_higher_uid)) )
                        {
                            if(descriptor->permissions & json_permission_breach_throws_error)
                                return json_error_permission_denied;
                        } else
                            break;
                    } else
                        break;
                } else
                    if(descriptor->permissions & json_permission_breach_throws_error)
                        return json_error_permission_denied;                    
            }
            elementptr = (char*) elementptr + (isPtr
                                                  ? (typeclass == json_typeclass_cstring ? descriptor->element_count * sizeof(const char*) : sizeof(const void*))
                                                  : descriptor->element_count * descriptor->element_size);
            descriptor++;
        }

        if(isPtr)
            elementptr = *((void**) elementptr);

        COMPARE_OR_EXIT(':');
		    if(descriptor->element_count > 1)	COMPARE_OR_EXIT('[');

        for(int i = 0; i < descriptor->element_count; i++)
        {
            if(typeclass == json_typeclass_struct)
            {
                size_t len2 = *lenptr;
                err = json_to_struct(elementptr, descriptor->element_size, descriptor->element_structdesc, source, &len2, user_id);
                if(err != json_error_none) return err;
                size_t diff = *lenptr - len2;
                //as *lenptr holds the remaining source length, a negative (underflow) result means, json_to_struct has read over the end!
                if(diff > *lenptr) return json_error_out_of_input_data;
                source += diff;
                *lenptr = len2;
            } else
            {
                COMPARE_OR_EXIT('"');
                token_space = JSON_MAX_TOKEN_LENGTH;
                switch(typeclass)
                {
                    case json_typeclass_char:
                    {
                        *(( uint8_t*) elementptr) = *source++; break;
                        //TOKEN_OR_EXIT(current_token, &token_space);
                    } break;
                    case json_typeclass_int:
                    {
                        TOKEN_OR_EXIT(current_token, &token_space);
                    } break;
                    case json_typeclass_uint:
                    {
                        uint64_t val = atol(source);
                        //!\note and \todo this is ugly, as "source" cannot be expected to be a null-terminated c string and isn't input validated.
                        //strtoull()
                        switch(descriptor->element_size)
                        {
                            case 1:
                                *(( uint8_t*) elementptr) = (uint8_t) val; break;
                            case 2:
                                #if(ESP8266)
                                if((uint32_t)elementptr & 0x01) return json_error_model_struct_alignment;
                                #endif
                                *(( uint16_t*) elementptr) = (uint16_t) val; break;
                            case 4:
                                #if(ESP8266)
                                if((uint32_t)elementptr & 0x03) return json_error_model_struct_alignment;
                                #endif
                                *(( uint32_t*) elementptr) = (uint32_t) val; break;
                            case 8:
                                #if(ESP8266)
                                if((uint32_t)elementptr & 0x07) return json_error_model_struct_alignment;
                                #endif
                                *(( uint64_t*) elementptr) = (uint64_t) val; break;
                            default: return json_error_model_element_size;  //error
                        }
                        TOKEN_OR_EXIT(current_token, &token_space);
                    } break;
                    case json_typeclass_flpoint:
                    {
                        TOKEN_OR_EXIT(current_token, &token_space);
                    } break;
                    case json_typeclass_cstring:
                    {
                        token_space = descriptor->element_size;
                        TOKEN_OR_EXIT((char*) elementptr, &token_space);
                        //if(token_space) *((char*) elementptr) = '\0'; //buggy, and already happens in unescape function
                    } break;
                }
                COMPARE_OR_EXIT('"');
            }
            elementptr = ((char*) elementptr) + descriptor->element_size; //this is only relevant if we're dealing with an array.
            SKIP_COMMA(); //tolerate 0 to 1 commata
            SKIP_OR_EXIT();
        }

        if(descriptor->element_count > 1)	COMPARE_OR_EXIT(']');

        SKIP_COMMA(); //tolerate 0 to 1 commata
        SKIP_OR_EXIT();

        if(*source == '}')
        {
            if(!(*lenptr)) return json_error_out_of_input_data;
            (*lenptr)--;
            //source++; //we don't care anymore.
            return json_error_none;  //we're done with parsing stuff for this struct
        }
    }
    return json_error_none;
}

#ifdef __cplusplus
} //extern "C"
#endif //__cplusplus


