TCP 20 byte min. - 3 way handshake and 4 way termination

  0                   1                   2                   3  
  0 1 2 3 4 5 6 7 8 9 A B C D E F 1 2 3 4 5 6 7 8 9 A B C D E F  
  --------------------------------------------------------------  
  |          Source Port          |       Destination Port       |  
  --------------------------------------------------------------  
  |                      Sequence Number                        |  
  --------------------------------------------------------------  
  |                  Acknowledgment Number                     |  
  --------------------------------------------------------------  
  |  Data  | Res. |C|E|U|A|P|R|S|F|         Window Size        |  
  | Offset |     |W|C|R|C|S|S|Y|I|                             |  
  --------------------------------------------------------------  
  |         Checksum          |      Urgent Pointer            |  
  --------------------------------------------------------------  
  |                    Options (if any)                        |  
  --------------------------------------------------------------  
  |                            Data                             |  
  --------------------------------------------------------------  

UPD 8 byte DataGram

  0                   1                   2                   3  
  0 1 2 3 4 5 6 7 8 9 A B C D E F 1 2 3 4 5 6 7 8 9 A B C D E F  
  --------------------------------------------------------------  
  |          Source Port          |       Destination Port       |  
  --------------------------------------------------------------  
  |            Length             |          Checksum            |  
  --------------------------------------------------------------  
  |                            Data                             |  
  --------------------------------------------------------------  
  --------------------------------------------------------------  


IP 20 byte min Segment. IP framgemtn is 1500 byte in ethernet


 0                   1                   2                   3  
  0 1 2 3 4 5 6 7 8 9 A B C D E F 1 2 3 4 5 6 7 8 9 A B C D E F  
  --------------------------------------------------------------  
  | Version |  IHL  |  Type of Service  |        Total Length       |  
  --------------------------------------------------------------  
  |         Identification        |Flags|      Fragment Offset      |  
  --------------------------------------------------------------  
  |  Time to Live  |   Protocol   |        Header Checksum         |  
  --------------------------------------------------------------  
  |                      Source IP Address                        |  
  --------------------------------------------------------------  
  |                   Destination IP Address                     |  
  --------------------------------------------------------------  
  |                    Options (if any, variable length)         |  
  --------------------------------------------------------------  
  |                            Data                              |  
  --------------------------------------------------------------  


-

  ┌──────────────┐  Layer 7 - Application   (e.g., HTTP, HTTPS, FTP, SMTP, gRPC)
  ├──────────────┤  Layer 6 - Presentation  (e.g., SSL/TLS, Protobuf, ASCII, JPEG)
  ├──────────────┤  Layer 5 - Session       (e.g., Sockets, RPC, NetBIOS)
  ├──────────────┤  Layer 4 - Transport     (e.g., TCP, UDP, QUIC)
  ├──────────────┤  Layer 3 - Network       (e.g., IP, ICMP, BGP, OSPF)
  ├──────────────┤  Layer 2 - Data Link     (e.g., Ethernet, Wi-Fi, PPP, MAC)
  ├──────────────┤  Layer 1 - Physical      (e.g., Fiber, Copper, Wireless, Cables)
  └──────────────┘  
