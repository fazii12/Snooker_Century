# Snooker_Century
C++ console based desktop application for recording and managing live game score for the variant of Snooker known as Century
README!
Snooker Century Score Management (Console Based Desktop Application)

Introduction
Snooker Century is variant of game Snooker played by atleast 2 players and max 10 players. 
The players play on their turn which is decided randomly at the start of the game. There are total 8 balls used in which white is also included, the score of each ball is given below.
Yellow	2
Green	3
Brown	4
Blue	5
Pink	6
Black	7
Red 	8

The score of each player is initialized with 0 and as the balls are potted their corresponding score is added to the player’s score. In same way if a ball aimed is not potted and any other ball is potted instead then foul is made and the score of that ball is subtracted from score of the player. Time is allotted e.g. 1 hour , 2 hours. The players who score hundred points within given time are winners.
My project actually manages the score and updates the position of every player in the game 

Working
At first it asks you to select an option either to start a game or just simply save (not implemented in the code).
Afterwards it asks for number of players (2-10),
Asks for Winning threshold (after how many players scoring 100 the game will end?)
Asks for Winning score (usually its 100 but for ease of time sometimes less than 100 is also considered)

For the number of players entered you are asked to input names and ages of all the players.
Initial board can be seen with 0 score assigned to every player.
Score is entered turn wise for every player and it goes on until winning threshold is not achieved.

Compilation Instructions
1.	Use IDE such as Visual Studio C++ with g++ compiler
OR 
2.	Place files in a folder, Open command prompt, change directory to containing folder and use commands 

For compiling :
 g++ -c *.cpp -o compiledprogram

Run:
./compiledprogram






















