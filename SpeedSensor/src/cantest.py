#!/usr/bin/env python
# -*- coding: utf-8 -*-

# import MCP2515
# import time
# from datetime import datetime
# print("--------------------------------------------------------")
# # try:
# # This setup is referred to CAN SPI click mounted on flip n click device slot A 
# can = MCP2515.MCP2515()
# print("init...")
# can.Init()
# print("send data...")
# id = 0x0 #max 7ff
# data = [1, 2, 3, 4, 5, 6, 7, 8]
# dlc = 8
# can.Send(id, data, dlc)

# readbuf = []
# # while(1):
# while(1):
# 	readbuf = can.Receive()
# 	print(readbuf)
# 	time.sleep(0.5)

# print("--------------------------------------------------------")
# # except Exception as e:
#     # print(e)



# #!/usr/bin/env python
# # -*- coding: utf-8 -*-

# import MCP2515
# import time
# import csv
# from datetime import datetime

# # Nome do arquivo CSV
# csv_filename = "can_data_log.csv"

# # Cria o arquivo CSV e escreve o cabeçalho
# with open(csv_filename, mode='w', newline='', encoding='utf-8') as file:
#     writer = csv.writer(file)
#     writer.writerow(["Timestamp", "ID", "Data", "DLC"])  # Cabeçalho do CSV

# print("--------------------------------------------------------")


import MCP2515
import time
import csv
from datetime import datetime

# Nome do arquivo CSV
csv_filename = "speedsensor_data_log.csv"

# Cria o arquivo CSV e escreve o cabeçalho
with open(csv_filename, mode='w', newline='', encoding='utf-8') as file:
    writer = csv.writer(file)
    writer.writerow(["Timestamp", "Data"])  # Cabeçalho do CSV

print("--------------------------------------------------------")

can = MCP2515.MCP2515()
print("init...")
can.Init()

readbuf = []

while True:
    readbuf = can.Receive()
    if readbuf:
        timestamp = datetime.now().strftime('%Y-%m-%d %H:%M:%S')

        print(f"{timestamp}: {readbuf}")

        with open(csv_filename, mode='a', newline='', encoding='utf-8') as file:
            writer = csv.writer(file)
            writer.writerow([timestamp, readbuf[0]])
    
    time.sleep(0.5)

print("--------------------------------------------------------")