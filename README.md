# BIP39dice

**BIP39dice** is a simple ESP32-based tool to securely generate BIP39 mnemonic phrases using physical dice rolls.  
It is designed specifically for the [LilyGO® TTGO T-Display 1.14 Inch LCD ESP32 Control Board](https://lilygo.cc/products/lilygo%C2%AE-ttgo-t-display-1-14-inch-lcd-esp32-control-board) and is in an early experimental stage.

---

## What it does

- Allows you to enter entropy using one of the following two methods:  
  – An 8-sided die (**d8**) combined with **two hexadecimal dice** (0,1,..,9,A,B,C,D,E,F), of two **different colors**.  
  – An 8-sided die (**d8**) combined with **two 16-sided dice**, also of **two different colors**.  
  The two colored dice are read in a fixed order (e.g. white first, then black) to avoid human bias and maximize entropy.
- Supports **12-word** or **24-word** BIP39 mnemonic phrase generation.
- Calculates and appends the appropriate **checksum bit(s)** according to the [BIP39 standard](https://github.com/bitcoin/bips/blob/master/bip-0039.mediawiki), and derives the final 12th or 24th valid word.
- Displays the generated mnemonic directly on the screen.
- All processing is done **offline** on the ESP32 device.

Note: To avoid introducing human bias and reducing entropy, the order of the two dice (hexadecimal or 16-sided) must be predetermined. It is recommended to use two dice of different colors—for example, in the demo video, the white die is always read first, followed by the black one.

Quick demo (links to YouTube video):

<a href="https://youtu.be/SdviQpSpwHA">
  <img src="images/YTdemo010.jpg" alt="Watch the demo" width="640"/>
</a>


---

## Notes

- This project is currently tailored **only** for the **LilyGO TTGO T-Display** board.
- More boards and features may be supported in future versions.

---

## Requirements

This project was developed using the **Arduino IDE**.

### Arduino IDE setup:

1. Install ESP32 support:
   - **Tools → Board → Boards Manager**
   - Search for: `esp32` by **Espressif Systems**
   - Install the latest version.

2. Install required libraries:
   - **Library Manager → Search and install:**
     - `TFT_eSPI` by **Bodmer**
       - You must configure it for the LilyGO T-Display board (e.g. `Setup25_TTGO_T_Display.h`)
     - `Crypto` (any library that provides `SHA256` support, e.g., Arduino `Crypto` or `Arduino_Crypto`)

---

## Files

- `BIP39dice.ino` – the main sketch.

---

Stay tuned for the YouTube link and further development.
