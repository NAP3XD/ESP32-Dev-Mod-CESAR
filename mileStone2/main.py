from fastapi import FastAPI
import requests

# ESP32 IP Address (Replace with your actual IP:PORT)
ESP32_IP = "1.1.1.1:8082"

app = FastAPI()

def get_esp32_data():
    try:
        response = requests.get(f"http://{ESP32_IP}/temperature", timeout=5)
        if response.status_code == 200:
            return response.json()
        else:
            return {"error": "Failed to fetch data from ESP32"}
    except Exception as e:
        return {"error": str(e)}

@app.get("/")
def home():
    return {"message": "ESP32 Temperature API via WiFi"}

@app.get("/temperature")
def temperature():
    return get_esp32_data()

# Run with: uvicorn main:app --host 0.0.0.0 --port 8003
# Save as main.py
