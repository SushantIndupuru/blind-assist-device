Ultrasonic Obstacle Detection Device

A low-cost wearable that helps visually impaired individuals detect nearby obstacles through haptic feedback. Two ultrasonic sensors drive left/right vibration feedback independently so users can tell which side a hazard is on.

Built and tested at the Calcutta Blind School. Full details in our paper (see below).

---

Hardware

| Component | Qty |
|---|---|
| Arduino Nano | 1 |
| HC-SR04 Ultrasonic Sensor | 2 |
| Coin Vibration Motor | 2 |
| Custom PCB | 1 |
| Li-Po Battery 3.7V 1000mAh | 1 |
| Buck-Boost Converter | 1 |
| 3D-Printed Case (`hardware/cad/blindsonnarcase.step`) | 1 |
| Wrist strap | 1 |

[Full Bill of Materials](hardware/BOM.xlsx) - ~$18.70 per unit total.

---

Wiring

Pin mapping is defined in `src/config.h`:

| Arduino Pin | Component |
|---|---|
| D8 | Left HC-SR04 TRIG |
| D9 | Left HC-SR04 ECHO |
| D6 | Right HC-SR04 TRIG |
| D7 | Right HC-SR04 ECHO |
| D3 (PWM) | Left motor channel 1 |
| D2 (PWM) | Left motor channel 2 |
| D5 (PWM) | Right motor channel 1 |
| D4 (PWM) | Right motor channel 2 |
| D13 | Status LED |
| VIN | Buck-boost output |
| GND | Common ground |

---

Firmware Build and Upload (PlatformIO)

This repository uses PlatformIO (not an Arduino `.ino` sketch).

1. Build (release): `pio run -e release`
2. Upload (release): `pio run -e release -t upload`
3. Serial monitor (9600 baud): `pio device monitor -b 9600`

Available environments in `platformio.ini`:

- `debug` (`-Og -g2 -DDEBUG`)
- `release` (`-Os -DNDEBUG`)

Board/framework defaults:

- Board: `nanoatmega328new`
- Framework: `arduino`
- Upload speed: `115200`

No external libraries are required.

---

Repo Structure

```
blind-assist-device/
├── hardware/
│   ├── BOM.xlsx
│   ├── stl/                        # 3D-printable case
│   └── pcb/                        # Gerber and drill/manufacturing outputs
├── src/                            # Firmware source files
```

---

Paper

For full system design, experimental results, and discussion:

> Ray, R. & Indupuru, S. (2025). *Ultrasonic Obstacle Detection Device.* [link]

---

Acknowledgments

Thank you to the participants at the Calcutta Blind School who volunteered to test this prototype.