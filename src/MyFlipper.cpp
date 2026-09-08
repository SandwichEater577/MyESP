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

MenuItem subGHzMenuItems[] = {
    {"Read Signal", 1},
    {"Add Frequency", 2},
    {"Saved Signals", 3},
    {"Transmit Signal", 4},
    {"Exit", 5},
};

MenuItem nfcMenuItems[] = {
    {"Read Card", 1},
    {"Emulate Card", 2},
    {"Saved Cards", 3},
    {"Exit", 4},
};

MenuItem infraRedMenuItems[] = {
    {"Read Signal", 1},
    {"Saved Signals", 2},
    {"Transmit Signal", 3},
    {"Exit", 4},
};

MenuItem gpioMenuItems[] = {
    {"Read GPIO", 1},
    {"Set GPIO", 2},
    {"GPIO Tools", 3},
    {"Exit", 4},
};

MenuItem settingsMenuItems[] = {
    {"Display", 1},
    {"Buttons", 2},
    {"About", 3},
    {"Exit", 4},
};

int currentSelectedMenuItem = 1;
int menuCount = 5;
int menuLevel = 0;
int itemsCount = 0;

void drawMenu(int a)
{

    MenuItem *items = firstLevelMenuItems;

    switch (a)
    {
    case 0:
        menuLevel = 0;
        items = firstLevelMenuItems;
        itemsCount = sizeof(firstLevelMenuItems) / sizeof(firstLevelMenuItems[0]);
        break;
    case 1:
        menuLevel = 1;
        items = subGHzMenuItems;
        itemsCount = sizeof(subGHzMenuItems) / sizeof(subGHzMenuItems[0]);
        break;
    case 2:
        menuLevel = 2;
        items = nfcMenuItems;
        itemsCount = sizeof(nfcMenuItems) / sizeof(nfcMenuItems[0]);
        break;
    case 3:
        menuLevel = 3;
        items = infraRedMenuItems;
        itemsCount = sizeof(infraRedMenuItems) / sizeof(infraRedMenuItems[0]);
        break;
    case 4:
        menuLevel = 4;
        items = gpioMenuItems;
        itemsCount = sizeof(gpioMenuItems) / sizeof(gpioMenuItems[0]);
        break;
    case 5:
        menuLevel = 5;
        items = settingsMenuItems;
        itemsCount = sizeof(settingsMenuItems) / sizeof(settingsMenuItems[0]);
        break;
    }

    display.firstPage();

    do
    {
        display.setDrawColor(BLACK);

        // Border around the screen
        display.drawFrame(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);

        // Draw menu items
        for (int i = 0; i < itemsCount; i++)
        {
            switch (items[i].id == currentSelectedMenuItem)
            {
            case true:
                display.setDrawColor(BLACK);
                display.drawBox(5, 4 + (i * 12 - 1), SCREEN_WIDTH - 9, 11);
                display.setDrawColor(WHITE);
                break;
            case false:
                display.setDrawColor(BLACK);
                display.drawFrame(5, 4 + (i * 12 - 1), SCREEN_WIDTH - 9, 11);
                break;
            }

            display.setCursor(10, 12 + (i * 12));
            display.print(items[i].name);
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
    drawMenu(menuLevel);

    while (true)
    {

        int lastButtonUPState = digitalRead(BUTTON_UP);
        int lastButtonDOWNState = digitalRead(BUTTON_DOWN);
        int lastButtonLEFTState = digitalRead(BUTTON_LEFT);
        int lastButtonRIGHTState = digitalRead(BUTTON_RIGHT);
        int lastButtonOKState = digitalRead(BUTTON_OK);

        switch (lastButtonUPState)
        {
        case LOW:
            switch (menuLevel)
            {
            case 0:
            case 1:
            case 2:
            case 3:
            case 4:
            case 5:
                currentSelectedMenuItem = currentSelectedMenuItem > 1 ? currentSelectedMenuItem - 1 : menuCount;
                drawMenu(menuLevel);
                delay(200);
                break;
            }
            break;
        }
        switch (lastButtonDOWNState)
        {
        case LOW:
            switch (menuLevel)
            {
            case 0:
            case 1:
            case 2:
            case 3:
            case 4:
            case 5:
                currentSelectedMenuItem = currentSelectedMenuItem < menuCount ? currentSelectedMenuItem + 1 : 1;
                drawMenu(menuLevel);
                delay(200);
                break;
            }
            break;
        }
        switch (lastButtonLEFTState)
        {
        case LOW:
            return;
        }
        switch (lastButtonRIGHTState)
        {
        case LOW:
            return;
        }
        switch (lastButtonOKState)
        {
        case LOW:
            switch (menuLevel)
            {
            case 0:
                switch (currentSelectedMenuItem)
                {
                case 1:
                case 2:
                case 3:
                case 4:
                case 5:
                    drawMenu(currentSelectedMenuItem);
                    break;
                }
                break;
            }
        }
    }
}