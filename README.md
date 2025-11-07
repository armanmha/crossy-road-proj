[![Review Assignment Due Date](https://classroom.github.com/assets/deadline-readme-button-22041afd0340ce965d47ae6ef1cefeee28c7c493a6346c4f15d667ab976d596c.svg)](https://classroom.github.com/a/EvxoT0RF)
[![Open in Codespaces](https://classroom.github.com/assets/launch-codespace-2972f46106e565e64193e422d61a12cf1da4916b45550586e14ef0a7c637dd04.svg)](https://classroom.github.com/open-in-codespaces?assignment_repo_id=21130909)

# Crossy Road Clone

  Authors: [Jacob McLaughlin](https://github.com/BacoJaco), [Aaron Limtiaco](https://github.com/airvon), [Arman Hamidi Asl](https://github.com/armanmha), [Ethan Jung](https://github.com/ethanjung-commits)

## Project Description
This project is important to us because our group grew up with the dream of making video games and this is a great way to get experience doing so. This project also introduces the same methods of product development that software engineers in the industry utilize on a daily basis. Learning to work as a team similarly to how we would in a professional environment while doing something we are passionate about will help prepare us for industry work in the future.

We plan to use C++ for both the game logic and the graphics (which will be terminal-based). The input for our project will be key-presses for movement, pausing the game, and quitting the game. The output will be continuously-updating visuals that respond to the user's input. Visuals will include the character (a chicken), moving vehicles, a live-score, and a pause menu.

The features that the project provides include real-time character movement, a live-scoring system, and procedurally generated games. The objective of the game is to "cross the road" for as long as possible, without getting hit by a vehicle. The scoring system will show the user how well they did, and allow them to compete for the highest score. The score may be based on a timed system, where the longer the user lasts, the higher the score, or a point system, where each row of vehicles passed equates to one point. Each game will be procedurally generated (ie. every new game's vehicle placement is unique), so the user cannot memorize the pattern of the vehicles to "cheat the game" and easily get a high score.
 
## Diagrams
<b>Navigation:</b>

<img width="712" height="801" alt="Nav_Diagram" src="https://github.com/user-attachments/assets/d7e41e1d-a500-4884-af2e-f2a8ce638daf" /><h1></h1>

<b>Screen Layouts:</b>

<img width="1551" height="831" alt="Screen Layout" src="https://github.com/user-attachments/assets/8018eab8-f740-43ce-a03e-61c82ce49af6" /><h1></h1>

 
<b>Screen Layout Description:</b>

* <b>Main Menu:</b>
The main menu screen presents the user with options to “Play”, “Change Difficulty”, “View Leaderboard”, and “Quit Game”. Navigating to the options with the arrow keys and pressing enter to select leads to the options’ respective screens. In the main menu, the user is also able to view the current high score and the game title.

 
* <b>Difficulty Menu:</b>
	The difficulty menu, which is accessed from the main menu, displays options to change the difficulty to either Easy, Medium, or Hard. The difficulty affects the speed and density of the obstacles moving within the gameplay screen. Users apply the change by selecting “Apply”, which saves the change and returns them to the main menu.

* <b>Leaderboard:</b>
	The leaderboard screen, also accessed from the main menu, displays the current top five high scores, along with the users that scored them. Users can navigate back to the main menu via the “Go Back” button.

* <b>Gameplay:</b>
	The main menu also leads to the gameplay screen, which presents the user with ASCII art of lanes, vehicles, rocks, and the user themself. A legend is provided to clear any confusion. The top right of the screen displays the controls, and the center shows the user’s current score.

* <b>Game Over:</b>
	The game over screen occurs once the user has lost the game. It displays the score the user obtained, and the option to enter a name associated with the score in order to save the score. The bottom corners of the screen have buttons that allow the user to either “Retry”, which brings them back to the gameplay screen with a score of 0, or “Quit”, which brings them back to the main menu.

 
<h1></h1><b>Class Diagram:</b>
<br></br>


<img width="1086" height="802" alt="Class_Diagram" src="https://github.com/user-attachments/assets/ea793c7d-fafc-441f-9996-a3aea382d8db" />

<h1></h1>

<b>Class Diagram Description:</b>

* <b> Screen: </b>
	The screen class controls navigation for each of the menus and the gameplay. It stores the cursor’s current position and processes all input from the player.

* <b> Menu: </b>
	The menu class connects the user to the overall program. It holds the currentDifficulty int (enumerated: 1 = easy, 2 = medium, 3 = hard) and displays the current difficulty to the user. This class gives the user the ability to start the game, quit the program, change the current difficulty, and see the leaderboard. It also holds processInput() which processes user input by reading arrow keys and displays their current selection as a cursor which moves in real time.

* <b> Leaderboard: </b>
	The leaderboard class is aggregated to the Menu class and works by reading off scores stored in a predefined text file. It temporarily holds them in a sorted vector pair containing a user’s name and related score whenever the user navigates to the leaderboard screen. Using a vector pair allows the top 5 scores to be quickly displayed while giving the game class the ability to add scores and players to the leaderboard through the text file with less risk of erasing the score.

* <b> Game: </b>
The game class is called by the Menu class and controls the functions of the game. It is in charge of generating a Board object and holding the user’s score and name once a playthrough has ended. The savePlayerScore() function prompts the user for their name once they finish a playthrough and saves it, along with their score in the text file. When a player loses by hitting an obstacle, they are able to retry which resets the score to 0 and generates a brand new Board with different random obstacles, or they can select quit, which returns them to the main menu.

* <b> Board: </b>
	The board class has a specified width and height, which represent the bounds of the game itself. The class can spawn in “lanes”, which is what the player and obstacles travel on during gameplay (these lanes are stored in a vector). A new board is generated each time a user plays through a game.

* <b> Gameplay Objects: </b>
	The gameplay objects class stores any objects that appear during gameplay, including lanes, obstacles (ie. vehicles) and the player. Each object has a specified length and shape (which is the visual representation of the object). The position of the object is stored so each object’s position can be manipulated and tracked. The safeToUser boolean specifies whether the player can safely interact with the object or if touching it will trigger the game to end.

* <b> Lane: </b>
	The lane class stores any vehicles that will travel across it during gameplay, denoted by a specified shape, which comes from the gameplay objects class. The spawnVehicle() function causes the stored vehicles to move across the lane.

* <b> Vehicle: </b>
	The vehicle class is a gameplay object with a speed. The speed integer represents how quickly the vehicle will move across the screen during gameplay. The moveVehicle(int, int) function moves the vehicle to a position given in cartesian coordinates every refresh. 

* <b> Player: </b>
	The player class is a gameplay object whose movement dynamically changes. The movement is controlled by the movePlayer(char) function, which is called by the Game class and passes in the user’s input. This class holds a checkCollision() function which checks to see if the user's coordinates conflict with those from an unsafe gameplay object. This would mean that the player hit an object (vehicle in the context of the game) they weren’t supposed to and end the game.
