# SO2
Code by Barto90(263851)

Eating and sleeping time is random in range 100ms - 999ms

## How to use

### 1.Build
  (Windows) g++ -std=c++11 -o Filozofowie Filozofowie.cpp -lpthread
  
  (Linux)   g++ -std=c++11 -o Filozofowie Filozofowie.cpp -pthread
## 2. Run the program providing parameters like so:
  (linux)
```
./Filozofowie <number of philosophers> 
```
  (windows) 
```
  Filozofowie.exe <number of philosophers> 
```
  for example:
```
./Filozofowie 5 
```
 or
Filozofowie.exe 6
    This will launch the program with 5 philosophers eating and sleeping till your PC gives up :D
    THE PROGRAM WILL NOT STOP ON ITS OWN - this is mostly for funsies as the main funcion waits for the philosophers to stop eating/sleeping(threads to finish working), but the philosophers found a philosopher's stone, so they will live on forever (or until you just close the programXD)
