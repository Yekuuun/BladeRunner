```C
                       ____  _           _      ____                              
                      | __ )| | __ _  __| | ___|  _ \ _   _ _ __  _ __   ___ _ __ 
                      |  _ \| |/ _` |/ _` |/ _ \ |_) | | | | '_ \| '_ \ / _ \ '__|
                      | |_) | | (_| | (_| |  __/  _ <| |_| | | | | | | |  __/ |   
                      |____/|_|\__,_|\__,_|\___|_| \_\\__,_|_| |_|_| |_|\___|_|                          

                              Simple keylogger fully written in C++
                                                         
``` 
**Simple keylogger developped by my hand sending data through sockets to dedicated server keeping logs of clients. This project was fully developped in C++**

---

### Disclaimer 🚨
This project was made only for learning purpose. I'm not responsible if you decide to use this code for malicious purpose. I developped it to learn by a practical case sockets & low level functions under WinAPI

---

### Compile client ?

`g++ -o client bladerunner.cpp -lws2_32`

### Warning 

For server side code, you have to chose a path to a valid folder who will keep the logs of the program in `server/src/server.cpp`

---

### What i've implemented ?

🟢 TCP connection between client - host

🟢 Sending Keylogger data to server

🟢 Keeping logs of received data


---

Thanks to <a href="https://github.com/ajayrandhawa">ajayrandhawa</a> for key tracing.
