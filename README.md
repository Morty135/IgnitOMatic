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

## 🧑‍💻 Command Structure

You can send commands to the Arduino while it's running using the following formats:

### ➤ Set a Single Value
SET <variable_name> <value>
### ➤ Set a Value in a Map (up to index 9)
SET <variable_name> <index> <value>

---

## 🧪 Examples

```text
SET threshold 300          // Set the threshold value to 300
SET angleMap 3 15          // Set angleMap[3] to 15