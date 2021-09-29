from socket import * 
import struct
import numpy as np
import cv2

IP = "192.168.137.218"
PORT = 5000
ADDR = (IP,PORT)

tcpCliSock = socket(AF_INET,SOCK_STREAM)
tcpCliSock.connect(ADDR)

while(True):
  tcpCliSock.send(bytes("OK","utf-8"))
  info_raw = tcpCliSock.recv(4*6)
  # print(len(info_raw))
  info = struct.unpack("6f",info_raw)
  print(info)
  file_length_raw = tcpCliSock.recv(4)

  if file_length_raw:
    file_length = struct.unpack("I",file_length_raw)
    # print(file_length[0])

    file_raw = b''
    while(True):
      tmp = tcpCliSock.recv(1024)
      file_raw = file_raw + tmp
      if(len(file_raw) >= file_length[0]):
        break
    
    try:
      # i = np.frombuffer(file_raw, dtype=np.float32)
      
      # i= i*255.0
      # i = i.astype(np.uint8)
      # i = i.reshape(160,160)
      
      info = info
      cx = info[0]*160
      cy = info[1]*160
      w = info[2]*160
      h = info[3]*160

      x1 = int(cx - w/2)
      x2 = int(cx + w/2)
      y1 = int(cy - h/2)
      y2 = int(cy + h/2)

      # cv2.rectangle(i,(x1,y1),(x2,y2),(255,0,0), 2)
      # cv2.imshow("img",i)

      if(cv2.waitKey(1) & 0xFF == ord('q')):
        tcpCliSock.send(bytes("KO","utf-8"))
        break
      # with open("test.jpg","wb") as f:
      #   f.write(file_raw)
    except Exception as e:
      print(e)
      continue

tcpCliSock.close()
