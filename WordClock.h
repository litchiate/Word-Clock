/**
Original code by John Missikos and Damien Brombal (c) 2013 @ TinkerElectric.com

modified by litchiate
*/

#include <Arduino.h>
#include <Adafruit_NeoPixel.h>

#define PIN            2    // ws2812 PIN  GPIO2
#define NUMPIXELS      121  // 11*11

class WordClock {

private:
    
    Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);
    //----------word configuration--------------------------------------------------------------
    uint8_t o_itis   = 0;    //IT IS Output
    uint8_t o_minutes= 0;    //MINTUTES Output
    uint8_t o_oclock = 0;    //O'CLOCK Output
    uint8_t o_to     = 0;    //TO Output
    uint8_t o_past   = 0;    //PAST Output

    uint8_t m_five   = 0;    //FIVE Output
    uint8_t m_ten    = 0;    //TEN Output
    uint8_t m_quarter= 0;    //QUARTER Output
    uint8_t m_twenty = 0;    //TWENTY Output
    uint8_t m_half   = 0;    //HALF Output
    uint8_t m_o      = 0;
    uint8_t m_oo     = 0;
    uint8_t m_ooo    = 0;
    uint8_t m_oooo   = 0;

    uint8_t h_one    = 0;    //ONE Output
    uint8_t h_two    = 0;    //TWO Output
    uint8_t h_three  = 0;    //THREE Output
    uint8_t h_four   = 0;    //FOUR Output
    uint8_t h_five   = 0;    //FIVE Output
    uint8_t h_six    = 0;    //SIX Output
    uint8_t h_seven  = 0;    //SEVEN Output
    uint8_t h_eight  = 0;    //EIGHT Output
    uint8_t h_nine   = 0;    //NINE Output
    uint8_t h_ten    = 0;    //TEN Output
    uint8_t h_eleven = 0;    //ELEVEN Output
    uint8_t h_twelve = 0;    //TWELVE Output
    //------------------------------------------------------------------------------------------
    uint32_t colourOut;
   
    void PixelClearAll();
   
public:

    WordClock();
    void init();
    void setColor(uint8_t colourR, uint8_t colourG, uint8_t colourB);
    void convertTime(int inputHour, int inputMinute);
    void displayEL();
    void displayAll();
    void displayTime();
   
};
