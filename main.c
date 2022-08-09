// Microcontrollers Laboratory
// Practice 7
// Esteban Lavín Treviño

// Libraries and Headers
#include "Config_header.h" // Include the config header file

// Directives
#define _XTAL_FREQ 1000000

#define LCD_DATA_R      PORTD
#define LCD_DATA_W      LATD
#define LCD_DATA_DIR    TRISD
#define LCD_RS          LATCbits.LATC2
#define LCD_RS_DIR      TRISCbits.TRISC2
#define LCD_RW          LATCbits.LATC1
#define LCD_RW_DIR      TRISCbits.TRISC1
#define LCD_E           LATCbits.LATC0
#define LCD_E_DIR       TRISCbits.TRISC0

// Constants
        
// Global Variables - Function Prototypes
void Ports_configuration(void);                     // Ports configuration.
void release(void);                                 // Release function
void LCD_rdy(void);                                 // Function checks if LCD is ready
void LCD_init(void);                                // Function to initialize LCD
void LCD_cmd(char);                                 // Function that sends command to LCD
void send2LCD(char);                                // Function that sends data to LCD
void __interrupt (high_priority) high_isr(void);    // High priority Interrupt Service Request.
void __interrupt (low_priority) low_isr(void);      // Low priority Interrupt Service Request.

int key = 0;
int num1 = 0;
int num2 = 0;
int op = 0;
int res;

// Main Function
void main(void) {
    Ports_configuration();                          // Ports configuration
    LCD_init();                                     // LCD initialization
    while(1){                                       // Infinite Loop
        LATB = 0x70;                                // first row active
        switch(PORTB){                              // Switch with PORTB value (row and column)
            case 0x77:                              // Key 1
                if(key == 0){                       // if its the first key pressed
                    num1 = 1;                       // = 1
                    send2LCD(num1+'0');             // Send to LCD
                    __delay_ms(50);                 // delay
                    key = 1;                        
                } else if (key == 1 & op > 0){      // if its the second key pressed and there's an operand code available
                    num2 = 1;                       // = 1
                    send2LCD(num2+'0');             // Send to LCD
                    __delay_ms(50);                 // delay
                }
                release();                          // wait until key is released
            break;
            
            case 0x7B:                              // Key 2
                if(key == 0){                       // if its the first key pressed
                    num1 = 2;                       // = 2
                    send2LCD(num1+'0');             // Send to LCD
                    __delay_ms(50);                 // delay
                    key = 1;
                } else if(key == 1 & op > 0){       // if its the second key pressed and there's an operand code available
                    num2 = 2;                       // = 2
                    send2LCD(num2+'0');             // Send to LCD
                    __delay_ms(50);                 // delay
                }
                release();                          // wait until key is released
            break;
            
            case 0x7D:                              // Key 3
                if(key == 0){                       // if its the first key pressed
                    num1 = 3;                       // = 3
                    send2LCD(num1+'0');             // Send to LCD
                    __delay_ms(50);                 // delay
                    key = 1;
                } else if(key == 1 & op > 0){       // if its the second key pressed and there's an operand code available
                    num2 = 3;                       // = 3
                    send2LCD(num2+'0');             // Send to LCD
                    __delay_ms(50);                 // delay
                }
                release();                          // wait until key is released
            break;
            
            case 0x7E:                              // Key A (addition)
                if(key == 1){                       // if its the second key pressed
                    op = 1;                         // operation code = 1
                    send2LCD('+');                  // Send to LCD
                    __delay_ms(50);                 // delay
                }
                release();                          // wait until key is released
            break;
            
        }
        
        LATB = 0xB0;                                // Second row active
        switch(PORTB){                              // Switch with PORTB value (row and column)
            case 0xB7:                              // Key 4
                if(key == 0){                       // if its the first key pressed
                    num1 = 4;                       // = 4
                    send2LCD(num1+'0');             // Send to LCD
                    __delay_ms(50);                 // delay
                    key = 1;
                } else if(key == 1 & op > 0){       // if its the second key pressed and there's an operand code available
                    num2 = 4;                       // = 4
                    send2LCD(num2+'0');             // Send to LCD
                    __delay_ms(50);                 // delay
                }
                release();                          // wait until key is released
            break;
            
            case 0xBB:                              // Key 5
                if(key == 0){                       // if its the first key pressed
                    num1 = 5;                       // = 5
                    send2LCD(num1+'0');             // Send to LCD
                    __delay_ms(50);                 // delay
                    key = 1;
                } else if(key == 1 & op > 0){       // if its the second key pressed and there's an operand code available
                    num2 = 5;                       // = 5
                    send2LCD(num2+'0');             // Send to LCD
                    __delay_ms(50);                 // delay
                }
                release();                          // wait until key is released
            break;
            
            case 0xBD:                              // Key 6
                if(key == 0){                       // if its the first key pressed
                    num1 = 6;                       // = 6
                    send2LCD(num1+'0');             // Send to LCD
                    __delay_ms(50);                 // delay
                    key = 1;
                } else if(key == 1 & op > 0){        // if its the second key pressed and there's an operand code available
                    num2 = 6;                       // = 6
                    send2LCD(num2+'0');             // Send to LCD
                    __delay_ms(50);                 // delay
                }
                release();                          // wait until key is released
            break;
            
            case 0xBE:                              // Key B (subtraction)
                if(key == 1){                       // if its the second key pressed
                    op = 2;                         // = operation code = 2
                    send2LCD('-');                  // Send to LCD
                    __delay_ms(50);                 // delay
                }
                release();                          // wait until key is released
            break;
        }
        
        LATB = 0xD0;                                // Third row active
        switch(PORTB){                              // Switch with PORTB value (row and column)
            case 0xD7:                              // Key 7
                if(key == 0){                       // if its the first key pressed
                    num1 = 7;                       // = 7
                    send2LCD(num1+'0');             // Send to LCD
                    __delay_ms(50);                 // delay
                    key = 1;
                } else if(key == 1 & op > 0){       // if its the second key pressed and there's an operand code available
                    num2 = 7;                       // = 7
                    send2LCD(num2+'0');             // Send to LCD
                    __delay_ms(50);                 // delay
                }
                release();                          // wait until key is released
            break;
            
            case 0xDB:                              // Key 8
                if(key == 0){                       // if its the first key pressed
                    num1 = 8;                       // = 8
                    send2LCD(num1+'0');             // Send to LCD
                    __delay_ms(50);                 // delay
                    key = 1;
                } else if(key == 1 & op > 0){       // if its the second key pressed and there's an operand code available
                    num2 = 8;                       // = 8
                    send2LCD(num2+'0');             // Send to LCD
                    __delay_ms(50);                 // delay
                }
                release();                          // wait until key is released
            break;
            
            case 0xDD:                              // Key 9
                if(key == 0){                       // if its the first key pressed
                    num1 = 9;                       // = 9
                    send2LCD(num1+'0');             // Send to LCD
                    __delay_ms(50);                 // delay
                    key = 1;
                } else if(key == 1 & op > 0){       // if its the second key pressed and there's an operand code available
                    num2 = 9;                       // = 9
                    send2LCD(num2+'0');             // Send to LCD
                    __delay_ms(50);                 // delay
                }
                release();                          // wait until key is released
            break;
            
            case 0xDE:                              // Key C (multiplication)
                if(key == 1){                       // if its the second key pressed
                    op = 3;                         // = operation code = 3
                    send2LCD('*');                  // Send to LCD
                    __delay_ms(50);                 // delay
                }
                release();                          // wait until key is released
            break;
        }
        
        LATB = 0xE0;                                // fourth row active
        switch(PORTB){                              // Switch with PORTB value (row and column)
            case 0xE7:                              // Key * (Calculate)
                switch(op){                         // switch with operation code
                    case 1:                         // addition
                        res = num1 + num2;
                    break;
                    case 2:                         // subtraction
                        res = num1 - num2;
                    break;
                    case 3:                         // multiplication
                        res = num1 * num2;
                    break;
                    case 4:                         // division
                        res = num1 / num2;
                    break;
                }
                LCD_cmd(0xC1);                      // next line
                send2LCD(res+'0');                  // send to LCD
                release();                          // wait until key is released
            break;
            
            case 0xEB:                              // Key 0
                if(key == 0){                       // if its the first key pressed
                    num1 = 0;                       // = 0
                    send2LCD(num1+'0');             // Send to LCD
                    __delay_ms(50);                 // delay
                    key = 1;
                } else if(key == 1 & op > 0){         // if its the second key pressed and there's an operand code available
                    num2 = 0;                       // = 0
                    send2LCD(num2+'0');             // Send to LCD
                    __delay_ms(50);                 // delay
                }
                release();                          // wait until key is released
            break;
            
            case 0xED:                              // Key # (clear)
                num1 = 0;                           // reset num1
                num2 = 0;                           // reset num2
                res = 0;                            // reset result
                key = 0;                            // reset key
                op = 0;                             // reset operation
                LCD_cmd(0x01);                      // clear display
                release();                          // wait until key is released
            break;
            
            case 0xEE:                              // Key D (division)
                if(key == 1){                         // if its the second key pressed
                    op = 4;                         // operation code = 4
                    send2LCD('/');                  // Send to LCD
                    __delay_ms(50);                 // delay
                }
                release();                          // wait until key is released
            break;
        }
    }
    return;
}
 

// Function Definitions
void Ports_configuration(void){         // Ports configuration.
    // PORTB
    ANSELB = 0x00;                      // Digital
    TRISB = 0x0F;                       // Input
    WPUB = 0x0F;                        // Pull up resistors available
    INTCON2 = INTCON2 & 0x7F;           // Activate the pull up resistors
}

void release(void){                     // Release function
    __delay_ms(50);                     // delay
    while(1){                           // infinite loop until returned
        if((PORTB & 0x0F) == 0x0F) {    // if button is released
            __delay_ms(100);            // delay
            return;                     // break loop
        }
    }
    __delay_ms(50);                     // delay
}

void LCD_rdy(void){ // waits until the LCD is not busy
    char test;
    // configure LCD data bus for input
    LCD_DATA_DIR = 0b11111111;
    test = 0x80;
    while(test){
        LCD_RS = 0; // select IR register
        LCD_RW = 1; // set read mode
        LCD_E = 1; // setup to clock data
        test = LCD_DATA_R;
        Nop();
        LCD_E = 0; // complete a read cycle
        test &= 0x80; // check flag busy bit
    }
    LCD_DATA_DIR = 0b00000000;
}

void LCD_init(void){ //initializes LCD
    LATC = 0; // make sure LCD control port is low
    LCD_E_DIR = 0; // config LCD enable pin for output
    LCD_RS_DIR = 0; // config LCD RS pin for output
    LCD_RW_DIR = 0; // config LCD R/W pin for output
    LCD_cmd(0x38); // configure display to 2x40
    LCD_cmd(0x0F); // turn on displau, cursor and blinking
    LCD_cmd(0x01); // clear display and move cursor to home
}

void LCD_cmd(char cx){ // sends command to LCD
    LCD_rdy(); // wait until LCD is ready
    LCD_RS = 0; // select IR register
    LCD_RW = 0; // set write mode
    LCD_E = 1; // setup clock data
    Nop();
    LCD_DATA_W = cx; // send out command
    Nop(); // small delay
    LCD_E = 0; // complete an external write cycle
}

void send2LCD(char xy){ // outputs to LCD
    LCD_RS = 1;
    LCD_RW = 0;
    LCD_E = 1;
    LCD_DATA_W = xy;
    Nop();
    Nop();
    LCD_E = 0;
}

void __interrupt (high_priority) high_isr(void){//  High priority Interrupt Service Request.
    Nop();
}
void __interrupt (low_priority)  low_isr(void){//   Low priority Interrupt Service Request.
    Nop();
}
