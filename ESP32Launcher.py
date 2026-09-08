import time
import sys
import os
import msvcrt
import subprocess
import platform


def frameAnimation(message, frames=4, speed=0.05):
    for frame in ["|", "/", "-", "\\"] * frames:
        subprocess.call('cls' if platform.system() == "Windows" else 'clear', shell=True)
        print(f"{message}: {frame}")
        time.sleep(speed)
    subprocess.call('cls' if platform.system() == "Windows" else 'clear', shell=True)

myFlipperInstructions = [
    {
        "text": "Connect the ESP32-S3 to the breadboard.",
    },
    {
        "text": "Connect the rotary encoder to the breadboard.",
    },
    {
        "text": "Connect the LCD display to the breadboard.",
    },
    {
        "text": "Arrange the components so they do not interfere with one another.",
    },
    {
        "text": "Connect the LCD CS pin to ESP32-S3 GPIO 10.",
    },
    {
        "text": "Connect the LCD RSE pin to ESP32-S3 GPIO 11.",
    },
    {
        "text": "Connect the LCD RS pin to ESP32-S3 GPIO 12.",
    },
    {
        "text": "Connect the LCD SCL pin to ESP32-S3 GPIO 13.",
    },
    {
        "text": "Connect the LCD SI pin to ESP32-S3 GPIO 14.",
    },
    {
        "text": "Connect the LCD VDD pin to the breadboard's positive power rail.",
    },
    {
        "text": "Connect the LCD VSS pin to the breadboard's negative power rail.",
    },
    {
        "text": "Connect the LCD A pin to the breadboard's positive power rail.",
    },
    {
        "text": "Connect the LCD K pin to the breadboard's negative power rail.",
    },
    {
        "text": "Connect the ESP32-S3 3V3 pin to the breadboard's positive power rail.",
    },
    {
        "text": "Connect the ESP32-S3 GND pin to the breadboard's negative power rail.",
    },
    {
        "text": "Connect the rotary encoder 5V pin to the breadboard's positive power rail.",
    },
    {
        "text": "Connect the rotary encoder GND pin to the breadboard's negative power rail.",
    },
    {
        "text": "Connect the rotary encoder S1 pin to ESP32-S3 GPIO 4.",
    },
    {
        "text": "Connect the rotary encoder S2 pin to ESP32-S3 GPIO 5.",
    },
    {
        "text": "Connect the rotary encoder KEY pin to ESP32-S3 GPIO 6.",
    },
    {
        "text": "Verify every connection before powering on the ESP32-S3.",
    },
    {
        "text": "Connect the ESP32-S3 to your computer with a USB cable.",
    }
] 


options = [
    {
        "name": "MyFlipper",
    },
    {
        "name": "Nothing",    
    }
]

def myFlipperFunc(a):
    if a == 1:
        print("MyFlipper instructions:")
        for x, instruction in enumerate(myFlipperInstructions, start=1):
            print(f"{x}. {instruction['text']}")
        input("Press Enter to continue...")

    project_dir = os.path.dirname(os.path.abspath(__file__))
    my_flipper_file = os.path.join(project_dir, "src", "MyFlipper.cpp")
    if not os.path.isfile(my_flipper_file):
        print(f"MyFlipper.cpp was not found at: {my_flipper_file}")
        return

    frameAnimation("Compiling MyFlipper.cpp", 10, 0.05)
    result = subprocess.run(
        [sys.executable, "-m", "platformio", "run", "--target", "upload"],
        cwd=project_dir,
        check=False,
    )
    if result.returncode != 0:
        print(f"ESP32-S3 upload failed with exit code {result.returncode}.")
    else:
        print("ESP32-S3 upload completed successfully.")

def handle_continuation():
        frameAnimation("Continuing", 4, 0.05)
        selected = 0

        while True:
            os.system("cls")
            print("Select a program to run (Up/Down, Enter to select):")
            for index, option in enumerate(options):
                marker = "✓ " if index == selected else "  "
                print(f"{marker}{option['name']}")

            key = msvcrt.getch()
            if key in (b"\x00", b"\xe0"):
                key = msvcrt.getch()
                if key == b"H":  # Up arrow
                    selected = (selected - 1) % len(options)
                elif key == b"P":  # Down arrow
                    selected = (selected + 1) % len(options)
            elif key in (b"\r", b"\n"):
                break

        subprocess.call('cls' if sys.platform == "win32" else 'clear', shell=True)
        frameAnimation(f"Loading {options[selected]['name']}", 4, 0.05)

        print(f"Preparing {options[selected]['name']}...")
        print("Instructions are available.")
        userInput = input("Would you like to view them? (Y/n): ")
        match userInput:
            case "Y" | "y" | "":
                if options[selected]['name'] == "MyFlipper":
                    myFlipperFunc(1)
                elif options[selected]['name'] == "Nothing":
                    print("No instructions are available for this option.")
            case "n" | "N":
                myFlipperFunc(0)
            case _:
                print("Invalid input. Please enter Y or n.")
        

def main():
    print("ESP32-S3 C++ program launcher")
    userInput = input("Would you like to continue? (Y/n): ")
    match userInput:
        case "Y" | "y" | "":
            handle_continuation()
        case "n" | "N":
            frameAnimation("Stopping", 3, 0.05)
        case _:
            print("Invalid input. Please enter Y or n.")

if __name__ == "__main__":
    main()