# 🔥 IgnitOMatic

**IgnitOMatic** is an all-in-one Arduino-based ignition system that lets you fine-tune engine timing on the fly.  
Adjust ignition parameters live over a Serial connection — no need to reflash your code every time you make a change.

---

## 🚀 Features

- Real-time tuning via Serial
- Adjustable ignition angle map
- Threshold configuration
- Command-based interface
- Easy integration with small engines or DIY ECUs

---

## 🧪 Updating values

The tables are a fixed lenght of 20 stored in EEPROM. To update them use serial command:
```text
SET_VARIABLES:<1 value for impulse>,<20 values for RPM>,<20 valuses for angle>
```

---

## Roadmap

- [x] use the EEPROM to store the map (https://docs.arduino.cc/learn/built-in-libraries/eeprom/)
- [] add linear interpolation between the map points
- [] make cmd app to upload csv data
- [] use wireless module to update the map values
- [] make a UI app to wirelessly update the maps