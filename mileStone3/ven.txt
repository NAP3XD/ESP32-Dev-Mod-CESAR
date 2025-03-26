# ven_dante.py
import asyncio
import random
from datetime import timedelta
from openleadr import OpenADRClient, enable_default_logging

enable_default_logging()

async def collect_temperature():
    return round(random.uniform(20.0, 30.0), 2)

async def collect_humidity():
    return round(random.uniform(40.0, 60.0), 2)

async def handle_event(event):
    decision = random.choice(['optIn', 'optOut'])
    print(f"Received event {event['event_descriptor']['event_id']}, responding with {decision}")
    return decision

client = OpenADRClient(
    ven_name='Dante-007',
    vtn_url='https://localhost:8080/OpenADR2/Simple/2.0b',
    cert='certs/dante.crt',
    key='certs/dante.key',
    ca_file='certs/dante.crt'  # Trust self-signed cert
)

client.add_report(
    callback=collect_temperature,
    resource_id='sensor001',
    measurement='temperature',
    sampling_rate=timedelta(seconds=5)
)

client.add_report(
    callback=collect_humidity,
    resource_id='sensor001',
    measurement='humidity',
    sampling_rate=timedelta(seconds=5)
)

client.add_handler('on_event', handle_event)

loop = asyncio.get_event_loop()
loop.create_task(client.run())
loop.run_forever()
