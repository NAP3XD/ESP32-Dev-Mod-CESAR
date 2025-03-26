# vtn_dante.py
import asyncio
from datetime import datetime, timedelta, timezone
from openleadr import OpenADRServer, enable_default_logging
import random

enable_default_logging()

async def on_create_party_registration(registration_info):
    if registration_info['ven_name'] == 'Dante-007':
        return 'dante_ven_id', 'dante_reg_id'
    return False

async def on_register_report(ven_id, resource_id, measurement, unit, scale,
                             min_sampling_interval, max_sampling_interval):
    async def on_update(data):
        for ts, val in data:
            print(f"{ven_id} reported {measurement} = {val} at {ts}")
    return on_update, min_sampling_interval

async def on_event_response(ven_id, event_id, opt_type):
    print(f"{ven_id} responded to {event_id} with: {opt_type}")

""""
server = OpenADRServer(
    vtn_id='Dante-007',
    cert='/home/nico/IoTProj/ESP32-Dev-Mod-CESAR/mileStone3/certs/cert.pem',
    key='/home/nico/IoTProj/ESP32-Dev-Mod-CESAR/mileStone3/certs/key.pem',
    passphrase='dante'

)
"""

server = OpenADRServer(vtn_id='Dante-007')

server.add_handler('on_create_party_registration', on_create_party_registration)
server.add_handler('on_register_report', on_register_report)

now = datetime.now(timezone.utc) + timedelta(seconds=10)

server.add_event(
    ven_id='dante_ven_id',
    signal_name='simple',
    signal_type='level',
    event_id='power_event',
    intervals=[{
        'dtstart': now,
        'duration': timedelta(minutes=5),
        'signal_payload': 1
    }],
    callback=on_event_response
)

loop = asyncio.get_event_loop()
loop.create_task(server.run())
loop.run_forever()
