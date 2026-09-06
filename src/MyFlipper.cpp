#include <Arduino.h>
#include <U8g2lib.h>

// Our screen resolution
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64

// U8g2 drawing values, matching your LCD
#define BLACK 1
#define WHITE 0

// Our display pins
#define LCD_CS 10
#define LCD_RST 11
#define LCD_DC 12
#define LCD_SCL 13
#define LCD_SI 14
#define BUTTON_UP 5
#define BUTTON_LEFT 4
#define BUTTON_DOWN 7
#define BUTTON_RIGHT 6
#define BUTTON_OK 8

// Create an object called "display"
U8G2_ST7565_EA_DOGM128_1_4W_SW_SPI display(
    U8G2_R0,
    LCD_SCL,
    LCD_SI,
    LCD_CS,
    LCD_DC,
    LCD_RST);

struct MenuItem
{
    const char *name;
    int id;
};

MenuItem firstLevelMenuItems[] = {
    {"Sub-GHz", 1},
    {"NFC", 2},
    {"Infra-Red", 3},
    {"GPIO", 4},
    {"Settings", 5},
};

void drawMenu()
{
    display.firstPage();

    do
    {
        display.setDrawColor(BLACK);

        // Border around the screen
        display.drawFrame(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);

        // Solid strip at the right edge
        display.drawBox(124, 4, 0, SCREEN_HEIGHT);

        // Draw menu items
        for (int i = 0; i < sizeof(firstLevelMenuItems) / sizeof(MenuItem); i++)
        {
            display.setCursor(10, 15 + (i * 12));
            display.print(firstLevelMenuItems[i].name);
        }
    } while (display.nextPage());
}

void setup()
{
    Serial.begin(115200);

    pinMode(BUTTON_UP, INPUT_PULLUP);
    pinMode(BUTTON_LEFT, INPUT_PULLUP);
    pinMode(BUTTON_DOWN, INPUT_PULLUP);
    pinMode(BUTTON_RIGHT, INPUT_PULLUP);
    pinMode(BUTTON_OK, INPUT_PULLUP);

    // Start the LCD
    display.begin();
    display.getU8x8()->x_offset = 4;
    display.setContrast(60);
    display.setFont(u8g2_font_6x10_tf);
    display.setFontMode(1);
}

void loop()
{
    display.firstPage();

    do
    {
        display.setDrawColor(BLACK);

        // Border around the screen
        display.drawFrame(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);

        // Solid strip at the right edge
        display.drawBox(124, 4, 0, SCREEN_HEIGHT);

    } while (display.nextPage());
}