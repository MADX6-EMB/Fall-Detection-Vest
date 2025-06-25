#🦺 Fall Detection & Airbag Deployment Vest
An IoT-based wearable safety system that detects sudden falls in elderly or mobility-impaired individuals and immediately deploys an airbag using a chemical reaction, while also sending a real-time alert via Telegram.

📌 Features:
✅ Real-time fall detection using MPU6050 accelerometer + gyroscope
🧠 ESP32 processes motion data & determines fall
💥 Airbag inflates instantly via H₂O₂ + KI chemical reaction
🛜 Sends a Telegram alert to caregivers
🔋 Fully portable with vest integration

📊 System Flow :
📥 User wears the vest
🔄 MPU6050 continuously tracks motion
📉 Sudden fall detected →
⚙️ ESP32 activates servo motor →
🧪 Servo mixes H₂O₂ + KI →
🫧 Oxygen gas rapidly generated →
🎈 Airbag inflates within seconds
📨 Telegram message sent:

⚠️ “Fall Detected! Immediate attention required.”

🧠 Software Architecture

ESP32 Microcontroller:
Reads motion data from MPU6050
Applies thresholds to detect falls
Triggers the actuator and sends Telegram alert

Telegram Bot:
Connected via Wi-Fi
Sends fall alerts to caregivers in real time

⚗️ The Chemistry Behind It
🧪 2H₂O₂ → 2H₂O + O₂ (gas)
Using potassium iodide (KI) as a catalyst, hydrogen peroxide (H₂O₂) decomposes into water and oxygen gas — inflating the airbag in seconds.

