#ifndef SPIFFS_H
#define SPIFFS_H 1
#include "FS.h"
#include "json.h"

extern FSInfo spiffs_info;

bool spiffs_initialize();
bool read_json(const char* filename, void* target, const size_t target_size, const json_element_t desc[]);

#endif //SPIFFS_H

