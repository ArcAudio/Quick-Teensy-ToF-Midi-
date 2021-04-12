long previousMillis = 0;        // will store last time LED was updated

// the follow variables is a long because the time, measured in miliseconds,
// will quickly become a bigger number than can be stored in an int.
long interval = 500;   

float basePitch = 440.0;
int root = 76;
float midiFreq = 220.0;
int lastMid;

unsigned long delayVal;
int scalePusher = 0; // variable to push up the scale
const int amountOfScales = 4; // If you make more scales change this number to the amt in the array

const int amountOfArps = 5; // If you make more scales change this number to the amt in the array

const int amountOfMetrii = 4; // If you make more scales change this number to the amt in the array

int noteArray[amountOfScales] [8] = {   {0,2,4,6,7,9,11,12}, // Majpr 
                                        {0,2,4,5,7,9,11,12}, // Lydian
                                        {0,2,3,5,7,8,10,12},
                                        {0,2,3,5,7,8,11,12}
                                     // {0,3,6,9,12,15,18,21},
                                     // {0,2,4,6,8,10,12,14},
                                     // {0,4,7,11,14,17,19,21}
                        };

int chordArray[amountOfArps] [5] = {   {0,4,7,11,14},
                                        {0,4,7,10,14},
                                        {0,3,7,10,14},
                                        {0,2,7,11,14},
                                         {0,3,6,9,12}
                                     // {0,2,4,6,8,10,12,14},
                                     // {0,4,7,11,14,17,19,21}
                        };
