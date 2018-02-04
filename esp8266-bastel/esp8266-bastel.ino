#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <Adafruit_NeoPixel.h>

#define WS2812_PIXELS_PER_STRIPE 150
#define EFFECT_REDIAL_INTERVAL 30000
#define LOGO_ENABLED 1


#define LOGO_INDEX_UPPER  127
#define LOGO_INDEX_LOWER  99

typedef enum
{
    effect_lbound = 0,

    effect_color_fader = 0,

    effect_moving_color_wheel,
    effect_sparkle,

    effect_dezentrale_bright,
    effect_dezentrale_walking_dot,
    effect_dezentrale_knightrider,

    effect_count
} effects;


static const uint8_t effect_propability[effect_count] = {128,  128, 48, (LOGO_ENABLED ? 192 : 0), (LOGO_ENABLED ? 144 : 0), (LOGO_ENABLED ? 80 : 0) };
static const uint8_t effect_brightness[effect_count]  = { 20, 20, 255, 255, 255, 255};

#define R 0
#define G 1
#define B 2

uint8_t stripe_data[WS2812_PIXELS_PER_STRIPE][3];

//#define WS2812_PIN0 4   //D2
#define WS2812_PIN0 12   //D6
//#define WS2812_PIN1 0   //D3
//#define WS2812_PIN2 2   //D4
//#define WS2812_PIN3 15  //D8
//#define WS2812_PIN4 13  //D7
//#define WS2812_PIN5 12  //D6
//not in use, but available: Arduino pin 5 (D1)
//not in use, doesn't output anything: Arduino pin 3
//not in use, crashes: 6, 7, 8

static Adafruit_NeoPixel stripe = Adafruit_NeoPixel(WS2812_PIXELS_PER_STRIPE, WS2812_PIN0, NEO_GRB + NEO_KHZ800);

static _Bool mixpixels = 0;

static void stripe_prepare_flush()
{
    for(int led_index = 0; led_index < WS2812_PIXELS_PER_STRIPE; led_index++)
    {
        uint8_t r = stripe_data[led_index][R];
        uint8_t g = stripe_data[led_index][G];
        uint8_t b = stripe_data[led_index][B];
        stripe.setPixelColor(led_index, stripe.Color(r,g,b));
    }
}

static void stripe_color(uint8_t r, uint8_t g, uint8_t b, uint8_t brightness)
{
    if(brightness < 255)
    {
        //dim
        r = ((uint16_t) brightness * (uint16_t) r) >> 8;
        g = ((uint16_t) brightness * (uint16_t) g) >> 8;
        b = ((uint16_t) brightness * (uint16_t) b) >> 8;
    }
    for(int led_index = 0; led_index < WS2812_PIXELS_PER_STRIPE; led_index++)
    {
        stripe_data[led_index][R] = r;
        stripe_data[led_index][G] = g;
        stripe_data[led_index][B] = b;
    }
}
static void stripe_setpixel(uint8_t led_index, uint8_t r, uint8_t g, uint8_t b, uint8_t brightness)
{
    if(led_index < WS2812_PIXELS_PER_STRIPE)
    {
        if(brightness < 255)
        {
            //dim
            r = ((uint16_t) brightness * (uint16_t) r) >> 8;
            g = ((uint16_t) brightness * (uint16_t) g) >> 8;
            b = ((uint16_t) brightness * (uint16_t) b) >> 8;
        }

        //mix r,g,b to stripe data
        stripe_data[led_index][R] = r;
        stripe_data[led_index][G] = g;
        stripe_data[led_index][B] = b;
    }
}
static void stripe_mixpixel(uint8_t led_index, uint8_t r, uint8_t g, uint8_t b, uint8_t brightness)
{
    if(led_index < WS2812_PIXELS_PER_STRIPE)
    {
        if(brightness < 255)
        {
            //dim
            r = ((uint16_t) brightness * (uint16_t) r) >> 8;
            g = ((uint16_t) brightness * (uint16_t) g) >> 8;
            b = ((uint16_t) brightness * (uint16_t) b) >> 8;
        }

        if(mixpixels)
        {
            //mix r,g,b to stripe data
            stripe_data[led_index][R] = ((uint16_t) stripe_data[led_index][R] + (uint16_t) r) / 2;
            stripe_data[led_index][G] = ((uint16_t) stripe_data[led_index][R] + (uint16_t) g) / 2;
            stripe_data[led_index][B] = ((uint16_t) stripe_data[led_index][R] + (uint16_t) b) / 2;
        } else
        {
            stripe_data[led_index][R] = r;
            stripe_data[led_index][G] = g;
            stripe_data[led_index][B] = b;
        }
    }
}

static void stripe_mix(uint8_t r, uint8_t g, uint8_t b, uint8_t brightness)
{
        if(brightness < 255)
        {
            //dim
            r = ((uint16_t) brightness * (uint16_t) r) >> 8;
            g = ((uint16_t) brightness * (uint16_t) g) >> 8;
            b = ((uint16_t) brightness * (uint16_t) b) >> 8;
        }
        if(mixpixels)
        for(int led_index = 0; led_index < WS2812_PIXELS_PER_STRIPE; led_index++)
        {
            //mix r,g,b to stripe data
            stripe_data[led_index][R] = ((uint16_t) stripe_data[led_index][R] + (uint16_t) r) / 2;
            stripe_data[led_index][G] = ((uint16_t) stripe_data[led_index][R] + (uint16_t) g) / 2;
            stripe_data[led_index][B] = ((uint16_t) stripe_data[led_index][R] + (uint16_t) b) / 2;
        }
        else
        for(int led_index = 0; led_index < WS2812_PIXELS_PER_STRIPE; led_index++)
        {
            stripe_data[led_index][R] = r;
            stripe_data[led_index][G] = g;
            stripe_data[led_index][B] = b;
        }
}



static void init_effect(int time, effects effect, uint8_t brightness, _Bool old_act);
static void run_effect(int time, effects effect, uint8_t brightness);


void setup()
{

    Serial.begin(115200);
    Serial.println();
    Serial.println("Startup");
    stripe.begin();
    stripe_color(0, 0, 0, 255);
    stripe_prepare_flush();
    stripe.show();
}



_Bool effect_active[effect_count] = {0};

static int effect_last_redial = 0;
static int effect_next_redial = 0;

void loop()
{
    //first, let's set up an 1ms timebase for further led motion handling
    static int time_old = 0;
    static _Bool flush_prepare_required = 0;
    static _Bool flush_required = 0;
    int time = millis();

    if(time > time_old + 20)
    {
        time_old = time;
        if(time >= effect_next_redial)
        {
            Serial.print("redial=");
            effect_last_redial = time;
            effect_next_redial = time + EFFECT_REDIAL_INTERVAL;
            for(int i = 0; i < effect_count; i++)
            {
                _Bool old_act = effect_active[i];
                _Bool act = ((rand() & 0xFF) <= effect_propability[i]);
                effect_active[i] = act;
                if(act)
                {
                    Serial.print(i);
                    init_effect(time, (effects) i, effect_brightness[i], old_act);
                }
                
            }
            //Serial.print(" (");Serial.print((int) effect_count);Serial.print(')');
            Serial.println();
            return;
        }
        else
        {
            stripe_color(0, 0, 0, 255);
            for(int i = 0; i < effect_count; i++)
            {
                if(effect_active[i])
                {
                    yield();
                    run_effect(time, (effects) i, effect_brightness[i]);
                    mixpixels = 1;
                }
            }
            flush_prepare_required = 1;
            flush_required = 1;
        }
    }
    else if(flush_prepare_required)
    {
        flush_prepare_required = 0;
        stripe_prepare_flush();
        mixpixels = 0;
    }
    else if(flush_required)
    {
        flush_required = 0;
        stripe.show();
    }
}
#define DIRECTION_LEFT 1
#define DIRECTION_RIGHT 0
#define DIRECTION_UP 1
#define DIRECTION_DOWN 0

static uint8_t color_fader_start_r, color_fader_start_g, color_fader_start_b;
static uint8_t color_fader_end_r=0, color_fader_end_g=0, color_fader_end_b=0;
static int16_t color_fader_steps_r, color_fader_steps_g, color_fader_steps_b;

static uint16_t dezentrale_walking_dot_index;
static uint8_t dezentrale_walking_dot_r, dezentrale_walking_dot_g, dezentrale_walking_dot_b;
static uint8_t dezentrale_walking_dot_bg_r, dezentrale_walking_dot_bg_g, dezentrale_walking_dot_bg_b;

static uint8_t dezentrale_bright_r, dezentrale_bright_g, dezentrale_bright_b;

static uint16_t dezentrale_knightrider_index;
#define DEZENTRALE_KNIGHTRIDER_LEN  15
static _Bool dezentrale_knightrider_direction;

static _Bool moving_color_wheel_dir_r, moving_color_wheel_dir_g, moving_color_wheel_dir_b;
static uint8_t moving_color_wheel_color_r, moving_color_wheel_color_g, moving_color_wheel_color_b;
#define MOVING_COLOR_WHEEL_STEPS 8

static void init_effect(int time, effects effect, uint8_t brightness, _Bool old_act)
{
    switch(effect)
    {
        case effect_color_fader:
            color_fader_start_r = color_fader_end_r;
            color_fader_start_g = color_fader_end_g;
            color_fader_start_b = color_fader_end_b;
            color_fader_end_r = color_fader_start_r + 64 + rand() & 0x7F - (rand() & 0x01) * 127;
            color_fader_end_g = color_fader_start_g + 64 + rand() & 0x7F - (rand() & 0x01) * 127;
            color_fader_end_b = color_fader_start_b + 64 + rand() & 0x7F - (rand() & 0x01) * 127;
            color_fader_steps_r = color_fader_end_r - color_fader_start_r;
            color_fader_steps_g = color_fader_end_g - color_fader_start_g;
            color_fader_steps_b = color_fader_end_b - color_fader_start_b;
            break;
        case effect_moving_color_wheel:
            if(!old_act)
            {
                uint8_t rnd = rand();
                moving_color_wheel_dir_r = DIRECTION_UP;
                moving_color_wheel_dir_g = DIRECTION_UP;
                moving_color_wheel_dir_b = DIRECTION_UP;
                moving_color_wheel_color_r = 1;
                moving_color_wheel_color_g = 255;
                moving_color_wheel_color_b = 1;
            }
            break;
        case effect_sparkle:
            effect_active[effect_color_fader] = 0;
            effect_active[effect_moving_color_wheel] = 0;
            
            break;
        case effect_dezentrale_bright:
            //run_effect(time, effect);
            dezentrale_bright_r = 191 + rand() & 0x3F;
            dezentrale_bright_g = 191 + rand() & 0x3F;
            dezentrale_bright_b = 191 + rand() & 0x3F;
            break;
        case effect_dezentrale_walking_dot:
        
            effect_active[effect_dezentrale_bright] = 0;
            dezentrale_walking_dot_index = 128;
            dezentrale_walking_dot_r = 127 + rand() & 0x7F;
            dezentrale_walking_dot_g = 127 + rand() & 0x7F;
            dezentrale_walking_dot_b = 127 + rand() & 0x7F;
            break;
        case effect_dezentrale_knightrider:
        
            effect_active[effect_dezentrale_bright] = 0;
            effect_active[effect_dezentrale_walking_dot] = 0;
            if(!old_act)
            {
                dezentrale_knightrider_direction = DIRECTION_RIGHT;
                dezentrale_knightrider_index = LOGO_INDEX_UPPER;
            }
            break;
    }
}

static void run_effect(int time, effects effect, uint8_t brightness)
{
    switch(effect)
    {
        case effect_color_fader:
            //if(!(time & 0xFF))
            //calculate new r,g,b
            {
                int timediff = time - effect_last_redial;
                int timediff_total = effect_next_redial - effect_last_redial;
                uint16_t r = color_fader_start_r + color_fader_steps_r * timediff / timediff_total;
                uint16_t g = color_fader_start_g + color_fader_steps_g * timediff / timediff_total;
                uint16_t b = color_fader_start_b + color_fader_steps_b * timediff / timediff_total;
                yield();
                stripe_mix(r,g,b, brightness);
            }
            break;
            
        case effect_moving_color_wheel:
            {
                _Bool dir_r = moving_color_wheel_dir_r;
                _Bool dir_g = moving_color_wheel_dir_g;
                _Bool dir_b = moving_color_wheel_dir_b;
                uint8_t col_r = moving_color_wheel_color_r;
                uint8_t col_g = moving_color_wheel_color_g;
                uint8_t col_b = moving_color_wheel_color_b;

                if((moving_color_wheel_color_r == 255) || (moving_color_wheel_color_r == 0))
                    moving_color_wheel_dir_r = !moving_color_wheel_dir_r;
                if((moving_color_wheel_color_g == 255) || (moving_color_wheel_color_g == 0))
                    moving_color_wheel_dir_g = !moving_color_wheel_dir_g;
                if((moving_color_wheel_color_b == 255) || (moving_color_wheel_color_b == 0))
                    moving_color_wheel_dir_b = !moving_color_wheel_dir_b;
                moving_color_wheel_color_r += moving_color_wheel_dir_r ? 1 : -1;
                moving_color_wheel_color_g += moving_color_wheel_dir_g ? 1 : -1;
                moving_color_wheel_color_b += moving_color_wheel_dir_b ? 1 : -1;

                for(int i = 0; i < WS2812_PIXELS_PER_STRIPE; i++)
                {
                    for(int s = 0; s < MOVING_COLOR_WHEEL_STEPS; s++)
                    {
                        if((col_r == 255) || (col_r == 0)) dir_r = !dir_r;
                        if((col_g == 255) || (col_g == 0)) dir_g = !dir_g;
                        if((col_b == 255) || (col_b == 0)) dir_b = !dir_b;
                        col_r += dir_r ? 1 : -1;
                        col_g += dir_g ? 1 : -1;
                        col_b += dir_b ? 1 : -1;
                    }
                    stripe_mixpixel(i,col_r,col_g,col_b, brightness);
                }
            }
            break;
        case effect_sparkle:
            {
                //for(int i = 0; i < 3; i++)
                {
                    uint16_t index = rand() % WS2812_PIXELS_PER_STRIPE;
                    uint8_t color = 128 + rand() & 0x7F;
                    stripe_setpixel(index, color, color, color, brightness); 
                }
            }
            break;
        case effect_dezentrale_bright:
            for(int i = LOGO_INDEX_LOWER; i < LOGO_INDEX_UPPER; i++)
                stripe_setpixel(i,dezentrale_bright_r,dezentrale_bright_g,dezentrale_bright_b, brightness);
            break;
            
        case effect_dezentrale_walking_dot:
            {
                uint16_t old_index =dezentrale_walking_dot_index + 1;
                if(old_index == LOGO_INDEX_UPPER + 1) old_index = LOGO_INDEX_LOWER;
                stripe_data[old_index][R] = dezentrale_walking_dot_bg_r;
                stripe_data[old_index][G] = dezentrale_walking_dot_bg_g;
                stripe_data[old_index][B] = dezentrale_walking_dot_bg_b;
                stripe_setpixel(dezentrale_walking_dot_index,dezentrale_walking_dot_r,dezentrale_walking_dot_g,dezentrale_walking_dot_b, brightness);
                dezentrale_walking_dot_index--;
                if(dezentrale_walking_dot_index == LOGO_INDEX_LOWER - 1) dezentrale_walking_dot_index = LOGO_INDEX_UPPER;
                dezentrale_walking_dot_bg_r = stripe_data[dezentrale_walking_dot_index][R];
                dezentrale_walking_dot_bg_g = stripe_data[dezentrale_walking_dot_index][G];
                dezentrale_walking_dot_bg_b = stripe_data[dezentrale_walking_dot_index][B];
            }
            break;
        case effect_dezentrale_knightrider:
            {
                for(int i = LOGO_INDEX_LOWER; i <= LOGO_INDEX_UPPER; i++)
                    stripe_setpixel(i, 0, 0, 0, 255);
                    
                uint16_t current_index = dezentrale_knightrider_index;
                _Bool current_direction = dezentrale_knightrider_direction;
                for(int i = 0; i < DEZENTRALE_KNIGHTRIDER_LEN; i++)
                {
                    stripe_setpixel(current_index, (DEZENTRALE_KNIGHTRIDER_LEN - i) * 8, 0, 0, brightness);
                    if((current_index == LOGO_INDEX_UPPER) || (current_index == LOGO_INDEX_LOWER))
                        current_direction = !current_direction;
                    if(current_direction == DIRECTION_RIGHT)
                        current_index++;
                    else
                        current_index--;
                }
                if(dezentrale_knightrider_direction == DIRECTION_RIGHT) dezentrale_knightrider_index--; else dezentrale_knightrider_index++;
                if((dezentrale_knightrider_index == LOGO_INDEX_UPPER) || (dezentrale_knightrider_index == LOGO_INDEX_LOWER))
                    dezentrale_knightrider_direction = !dezentrale_knightrider_direction;
            }
            break;
    }
}

