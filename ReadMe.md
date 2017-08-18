Trouble Game Simulator
====================
A simple console-based simulator for Trouble Game, also known as Kindle. 

----
Developed by Aleksandr Semjonov.
The rules for the game can be found on an [official website][1].

Instructions:
------------------
After the simulator is started, a player presses number keys to select an action from the available set. A user is simulating actions of all four players.

For quick testing, hold down "1" until the desired game state is reached.

When the game is over, it provides a set of basic stats. The program is closed with an "Escape" key.

Compilation:
-----------------
**Windows:**

The project includes the full set of files for Visual Studio solution. The simulator has been compiled and tested with Visual Studio 2015 on Windows 10 machine.

------------
**Linux:**

Inside the TroubleGameSim folder, a **makefile** is present. Running this file will compile the simulator into executable file **sim**. Run the file with **./sim**. The project has been compiled and tested with gcc on Ubuntu 16.04 virtual machine.

[1]: http://www.hasbro.com/common/instruct/Trouble_%282002%29.pdf