#include "spiffs.h"

//http://esp8266.github.io/Arduino/versions/2.3.0/doc/filesystem.html

FSInfo spiffs_info;

bool spiffs_initialize()
{
  
    SPIFFS.begin();
    return SPIFFS.info(spiffs_info) != 0;
}


bool read_json(const char* filename, void* target, const size_t target_size, const json_element_t desc[])
{
    File f = SPIFFS.open(filename, "r");
    if (!f) return 0;

    size_t fsize = f.size();

    char* fbuffer = (char*) malloc(fsize + 1);
    
    if (!fbuffer)
    {
        f.close();
        return 0;
    }

    f.read((uint8_t*) fbuffer, fsize);
    f.close();
    fbuffer[fsize] = '\0';

//    Serial.println(fbuffer);
    json_error_e err = json_to_struct(target, target_size, desc, fbuffer, &fsize, 0);
    free(fbuffer);
    if(err)
    {
      Serial.print("; JSON parsing error ");
      char tmp[20];
      utoa(err, tmp, 10);
      Serial.println(tmp);
      return 0;
    } else
      return 1;
}

