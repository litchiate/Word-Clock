
/**
Original code by John Missikos and Damien Brombal (c) 2013 @ TinkerElectric.com

modified by litchiate
*/

#include "WordClock.h"

WordClock::WordClock() {
  
}

void WordClock::PixelClearAll() {
    for(int i=0; i<NUMPIXELS; i++) {
        pixels.setPixelColor(i, 0);
    }
}    
    
void WordClock::init() {
    pixels.begin(); // This initializes the NeoPixel library.
}
 
void WordClock::setColor( uint8_t colourR, uint8_t colourG, uint8_t colourB ) {
    colourOut = pixels.Color(colourR, colourG, colourB);
}

void WordClock::convertTime( int inputHour, int inputMinute ) {
    
  o_itis = 0;      //IT IS Output
  o_minutes = 0;   //MINTUTES Output
  o_oclock = 0;    //O'CLOCK Output
  o_to = 0;        //TO Output
  o_past = 0;      //PAST Output

  m_five = 0;      //FIVE Output
  m_ten = 0;       //TEN Output
  m_quarter = 0;   //QUARTER Output
  m_twenty = 0;    //TWENTY Output
  m_half = 0;      //HALF Output
  m_o     = 0;
  m_oo   = 0;
  m_ooo  = 0;
  m_oooo = 0;

  h_one = 0;       //ONE Output
  h_two = 0;       //TWO Output
  h_three = 0;     //THREE Output
  h_four = 0;      //FOUR Output
  h_five = 0;      //FIVE Output
  h_six = 0;       //SIX Output
  h_seven = 0;     //SEVEN Output
  h_eight = 0;     //EIGHT Output
  h_nine = 0;      //NINE Output
  h_ten = 0;       //TEN Output
  h_eleven = 0;    //ELEVEN Output
  h_twelve = 0;    //TWELVE Output
  
  o_itis = 1;      //IT IS is always on

  //Minute Serial Conversion
  if (inputMinute % 5 == 1) { m_o     = 1; }
  if (inputMinute % 5 == 2) { m_oo    = 1; }
  if (inputMinute % 5 == 3) { m_ooo   = 1; }
  if (inputMinute % 5 == 4) { m_oooo  = 1; }
  
  if (inputMinute < 5) {            //??:00 --> ??:04
    o_oclock = 1;
  } 
  else if (inputMinute < 35) {      //??:05 --> ??:34
    o_past = 1;
    if (inputMinute >= 30){         //??:30 --> ??:34
      m_half = 1;
    }
    else if (inputMinute >= 15 && inputMinute <20 ) { //??:15 --> ??:19
      m_quarter = 1;
    }
    else {
      o_minutes = 1;
      if (inputMinute >= 20){       //??:20 --> ??:29
        m_twenty = 1;
        if (inputMinute >= 25) {    //??:25 --> ??:29
          m_five = 1;
        }
      }
      else if (inputMinute >= 10){  //??:10 --> ??:14
        m_ten = 1;
      }
      else {                        //??:05 --> ??:09
        m_five = 1;
      }
    }  
  }
  else {                            //??:35 --> ??:59
    inputHour = inputHour + 1;
    o_to = 1;
    if (inputMinute >= 45 && inputMinute <50 ) { //??:45 --> ??:49
      m_quarter = 1;
    }
    else {
      o_minutes = 1;
      if (inputMinute < 45){        //??:35 --> ??:44
        m_twenty = 1;
        if (inputMinute < 40) {     //??:35 --> ??:39
          m_five = 1;
        }
      }
      else if (inputMinute < 55){   //??:50 --> ??:54
        m_ten = 1;
      }
      else {                        //??:55 --> ??:59
        m_five = 1;
      }
    }
  }

  if (inputHour >= 12) {            //Hour Conversion
    inputHour = inputHour - 12;
    if (inputHour == 12) {
      inputHour = inputHour - 12;
    }
  }

  switch(inputHour){
  case 0:
    h_twelve = 1;
    break;

  case 1:
    h_one = 1;
    break;

  case 2:
    h_two = 1;
    break;

  case 3:
    h_three = 1;
    break;

  case 4:
    h_four = 1;
    break;

  case 5:
    h_five = 1;
    break;

  case 6:
    h_six = 1;
    break;

  case 7:
    h_seven = 1;
    break;

  case 8:
    h_eight = 1;
    break;

  case 9:
    h_nine = 1;
    break;

  case 10:
    h_ten = 1;
    break;

  case 11:
    h_eleven = 1;
    break;
  }
    
}

void WordClock::displayTime() {  // display "IT IS XXXX"

  PixelClearAll();

  //list the time, then in it, list the pixels that are with i 
  if (o_itis == 1){       //IT IS Output
    pixels.setPixelColor(6, colourOut);//DONE
    pixels.setPixelColor(7, colourOut);
    pixels.setPixelColor(9, colourOut);
    pixels.setPixelColor(10, colourOut);

  }
  if (o_minutes == 1){    //MINTUTES Output
      //nothing, no minutes on small version
  }
  if (o_oclock == 1){     //O'CLOCK Output
      pixels.setPixelColor(104, colourOut);//done
      pixels.setPixelColor(105, colourOut);
      pixels.setPixelColor(106, colourOut);
      pixels.setPixelColor(107, colourOut);
      pixels.setPixelColor(108, colourOut);
      pixels.setPixelColor(109, colourOut);
  }
  if (o_to == 1){         //TO Output
      pixels.setPixelColor(42, colourOut);//DONE
      pixels.setPixelColor(43, colourOut);
  }
  if (o_past == 1){       //PAST Output
      pixels.setPixelColor(51, colourOut);//DONE
      pixels.setPixelColor(52, colourOut);
      pixels.setPixelColor(53, colourOut);
      pixels.setPixelColor(54, colourOut);
  }
  if (m_five == 1){       //FIVE Output
      pixels.setPixelColor(22, colourOut);//done
      pixels.setPixelColor(23, colourOut);
      pixels.setPixelColor(24, colourOut);
      pixels.setPixelColor(25, colourOut);
  }
  if (m_ten == 1){        //TEN Output 
      pixels.setPixelColor(38, colourOut);//done
      pixels.setPixelColor(39, colourOut);
      pixels.setPixelColor(40, colourOut);
  }
  if (m_quarter == 1){    //QUARTER Output
      pixels.setPixelColor(13, colourOut);//DONE
      pixels.setPixelColor(14, colourOut);
      pixels.setPixelColor(15, colourOut);
      pixels.setPixelColor(16, colourOut);
      pixels.setPixelColor(17, colourOut);
      pixels.setPixelColor(18, colourOut);
      pixels.setPixelColor(19, colourOut);
  }  
  if (m_twenty == 1){     //TWENTY Output
      pixels.setPixelColor(27, colourOut);//done
      pixels.setPixelColor(28, colourOut);
      pixels.setPixelColor(29, colourOut);
      pixels.setPixelColor(30, colourOut);
      pixels.setPixelColor(31, colourOut);
      pixels.setPixelColor(32, colourOut);
  }
  if (m_half == 1){       //HALF Output 
      pixels.setPixelColor(33, colourOut);//done
      pixels.setPixelColor(34, colourOut);
      pixels.setPixelColor(35, colourOut);
      pixels.setPixelColor(36, colourOut);
  }
  if (h_one == 1){        //ONE Output
      pixels.setPixelColor(77, colourOut);//done
      pixels.setPixelColor(78, colourOut);
      pixels.setPixelColor(79, colourOut);
  }  
  if (h_two == 1){        //TWO Output
      pixels.setPixelColor(80, colourOut);//done
      pixels.setPixelColor(81, colourOut);
      pixels.setPixelColor(82, colourOut);
  }  
  if (h_three == 1){      //THREE Output
      pixels.setPixelColor(83, colourOut);//done
      pixels.setPixelColor(84, colourOut);
      pixels.setPixelColor(85, colourOut);
      pixels.setPixelColor(86, colourOut);
      pixels.setPixelColor(87, colourOut);
  }  
  if (h_four == 1){       //FOUR Output
      pixels.setPixelColor(73, colourOut);//done
      pixels.setPixelColor(74, colourOut);
      pixels.setPixelColor(75, colourOut);
      pixels.setPixelColor(76, colourOut);
  }  
  if (h_five == 1){       //FIVE Output
      pixels.setPixelColor(69, colourOut);//done
      pixels.setPixelColor(70, colourOut);
      pixels.setPixelColor(71, colourOut);
      pixels.setPixelColor(72, colourOut);
  }  
  if (h_six == 1){        //SIX Output
      pixels.setPixelColor(66, colourOut);//done
      pixels.setPixelColor(67, colourOut);
      pixels.setPixelColor(68, colourOut);
  }  
  if (h_seven == 1){      //SEVEN Output
      pixels.setPixelColor(45, colourOut);//done
      pixels.setPixelColor(46, colourOut);
      pixels.setPixelColor(47, colourOut);
      pixels.setPixelColor(48, colourOut);
      pixels.setPixelColor(49, colourOut);
  }  
  if (h_eight == 1){      //EIGHT Output
      pixels.setPixelColor(94, colourOut);//done
      pixels.setPixelColor(95, colourOut);
      pixels.setPixelColor(96, colourOut);
      pixels.setPixelColor(97, colourOut);
      pixels.setPixelColor(98, colourOut);
  }  
  if (h_nine == 1){       //NINE Output
      pixels.setPixelColor(55, colourOut);//done
      pixels.setPixelColor(56, colourOut);
      pixels.setPixelColor(57, colourOut);
      pixels.setPixelColor(58, colourOut);
  }  
  if (h_ten == 1){        //TEN Output
      pixels.setPixelColor(99, colourOut);//done
      pixels.setPixelColor(100, colourOut);
      pixels.setPixelColor(101, colourOut);
  }  
  if (h_eleven == 1){     //ELEVEN Output
      pixels.setPixelColor(88, colourOut);//done
      pixels.setPixelColor(89, colourOut);
      pixels.setPixelColor(90, colourOut);
      pixels.setPixelColor(91, colourOut);
      pixels.setPixelColor(92, colourOut);
      pixels.setPixelColor(93, colourOut);
  }  
  if (h_twelve == 1){     //TWELVE Output
      pixels.setPixelColor(60, colourOut);//DONE
      pixels.setPixelColor(61, colourOut);
      pixels.setPixelColor(62, colourOut);
      pixels.setPixelColor(63, colourOut);
      pixels.setPixelColor(64, colourOut);
      pixels.setPixelColor(65, colourOut);
  } 
  if (m_o == 1){          //O
      pixels.setPixelColor(115, colourOut);
    }
  if (m_oo == 1){         //OO
      pixels.setPixelColor(115, colourOut);
      pixels.setPixelColor(114, colourOut);
    }
  if (m_ooo == 1){        //OOO
      pixels.setPixelColor(115, colourOut);
      pixels.setPixelColor(114, colourOut);
      pixels.setPixelColor(113, colourOut);
    }
  if (m_oooo == 1){       //OOOO
      pixels.setPixelColor(115, colourOut);
      pixels.setPixelColor(114, colourOut);
      pixels.setPixelColor(113, colourOut);
      pixels.setPixelColor(112, colourOut);
    }
  pixels.show(); // This sends the updated pixel color to the hardware.       
    
}

void WordClock::displayEL() {    // display "El Psy Congroo"
    PixelClearAll();

    pixels.setPixelColor(5, colourOut); // E
    pixels.setPixelColor(4, colourOut); // L
    pixels.show();
    delay(500);
    
    pixels.setPixelColor(37, colourOut); // P
    pixels.setPixelColor(50, colourOut); // S
    pixels.setPixelColor(59, colourOut); // Y
    pixels.show();
    delay(500);
    
    pixels.setPixelColor(120, colourOut); // congroo
    pixels.setPixelColor(119, colourOut);
    pixels.setPixelColor(118, colourOut);
    pixels.setPixelColor(117, colourOut);
    pixels.setPixelColor(116, colourOut);
    pixels.setPixelColor(115, colourOut);
    pixels.setPixelColor(114, colourOut);
    pixels.show();
    delay(2000); 
}    

void WordClock::displayAll() {
    for(int i=0; i<NUMPIXELS; i++) {
        pixels.setPixelColor(i, colourOut);
    }
    pixels.show();
}
   
