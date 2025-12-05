[![CI](https://github.com/cs100/final-project-ahami040-ejung047-alimt001-jmcla012/actions/workflows/main.yml/badge.svg)](https://github.com/cs100/final-project-ahami040-ejung047-alimt001-jmcla012/actions/workflows/main.yml)

# Crossy Road Clone

  Authors: [Jacob McLaughlin](https://github.com/BacoJaco), [Aaron Limtiaco](https://github.com/airvon), [Arman Hamidi Asl](https://github.com/armanmha), [Ethan Jung](https://github.com/ethanjung-commits)

## Project Description
This project is important to us because our group grew up with the dream of making video games and this is a great way to get experience doing so. This project also introduces the same methods of product development that software engineers in the industry utilize on a daily basis. Learning to work as a team similarly to how we would in a professional environment while doing something we are passionate about will help prepare us for industry work in the future.

We plan to use C++ for both the game logic and the graphics (which will be terminal-based). The input for our project will be key-presses for movement, pausing the game, and quitting the game. The output will be continuously-updating visuals that respond to the user's input. Visuals will include the character (a chicken), moving vehicles, a live-score, and a pause menu.

The features that the project provides include real-time character movement, a live-scoring system, and procedurally generated games. The objective of the game is to "cross the road" for as long as possible, without getting hit by a vehicle. The scoring system will show the user how well they did, and allow them to compete for the highest score. The score may be based on a timed system, where the longer the user lasts, the higher the score, or a point system, where each row of vehicles passed equates to one point. Each game will be procedurally generated (ie. every new game's vehicle placement is unique), so the user cannot memorize the pattern of the vehicles to "cheat the game" and easily get a high score.
 
## Diagrams
<b>Navigation:</b>

<img width="712" height="801" alt="Nav_Diagram" src="https://github.com/user-attachments/assets/0d7b38d3-9e97-47db-bcf7-ac93b2039e91" />

<h1></h1>
<b>Screen Layouts:</b>

<img width="1582" height="836" alt="Screen Layout" src="https://github.com/user-attachments/assets/0998028f-d350-4c0a-adb0-ecf69885a57b" />

<h1></h1>
<b>Screen Layout Description:</b>

* <b>Main Menu:</b>
The main menu screen presents the user with options to “Play”, “Change Difficulty”, “View Leaderboard”, and “Quit Game”. Navigating to the options with the arrow keys and pressing enter to select leads to the options’ respective screens. In the main menu, the user is also able to view the current high score and the game title.

 
* <b>Difficulty Menu:</b>
	The difficulty menu, which is accessed from the main menu, displays options to change the difficulty to either Easy, Medium, or Hard. The difficulty affects the speed and density of the obstacles moving within the gameplay screen. Users apply the change by selecting “Apply”, which saves the change and returns them to the main menu.

* <b>Leaderboard:</b>
	The leaderboard screen, also accessed from the main menu, displays the current top five high scores, along with the users that scored them. Users can navigate back to the main menu via the “Go Back” button.

* <b>Gameplay:</b>
	The main menu also leads to the gameplay screen, which presents the user with ASCII art of lanes, vehicles, rocks, and the user themself. A legend is provided to clear any confusion. The top right of the screen displays the controls, and the center shows the user’s current score.

* <b>Pause Screen:</b>
	The pause screen is accessed by pressing ESC during gameplay. It allows the player to rest, view their score, and either resume to gameplay or quit to the menu.

* <b>Game Over:</b>
	The game over screen occurs once the user has lost the game. It displays the score the user obtained, and the option to enter a name associated with the score in order to save the score. The bottom corners of the screen have buttons that allow the user to either “Retry”, which brings them back to the gameplay screen with a score of 0, or “Quit”, which brings them back to the main menu.

 
<h1></h1><b>Class Diagram:</b>
<br></br>

<img width="2241" height="1369" alt="CS100 Milestone 3 UMLpng" src="https://github.com/user-attachments/assets/e72d87ae-f039-4080-98ef-0bba29b7fd6b" />

<h1></h1>

<b>Class Diagram Description:</b>

* <b> Screen: </b>
	The screen class controls navigation for each of the menus and the gameplay. It stores the cursor’s current position and processes all input from the player.

* <b> Menu: </b>
	The menu class connects the user to the overall program. It holds the currentDifficulty int (enumerated: 1 = easy, 2 = medium, 3 = hard) and displays the current difficulty to the user. This class gives the user the ability to start the game, quit the program, change the current difficulty, and see the leaderboard. It also holds processInput() which processes user input by reading arrow keys and displays their current selection as a cursor which moves in real time.

* <b> LeaderboardScoreManagement: </b>
	The leaderboard score management class is aggregated to the Menu class and works by reading off scores stored in a predefined text file. It stores these scores in a vector of LeaderboardPlayer objects, which have an associated name, score, and difficulty level. The scores are sorted in descending order.

* <b> LeaderboardDisplay: </b>
	The leaderboard display class displays the organized scores from the score management class onto the screen for the user to see. When implemented, the user may choose how many scores to display (within the bounds of the vector).

* <b> LeaderboardPlayer: </b>
	The leaderboard player struct stores all data regarding the player (ie. name, score, and difficulty level). The '<' operator is overridden for sorting purposes.

* <b> Game: </b>
	The game class is called by the menu class and is in charge of tracking the user's score and the state of the game. The game may be started, paused, and ended from this class. Ending the game calls the class in charge of the game over screen.

* <b> PauseScreen: </b>
	The pause screen class is called during gameplay, and is used to freeze gameplay. The screen displays the current score, along with options to either resume or quit.

* <b> GameOverScreen: </b>
	The game over screen class displays a game over screen for the player if they lose the game. It includes their score, an option to save their score (along with their specified name), and options to retry or quit. Retrying calls the game class again, and the player restarts the game. Selecting quit causes the user to go back to the main menu, which is handled by the menu class.

* <b> Board: </b>
	The board class has a specified width and height, which represent the bounds of the game itself. The class can spawn in “lanes”, which is what the player and obstacles travel on during gameplay (these lanes are stored in a vector). A new board is generated each time a user plays through a game.

* <b> Gameplay Objects: </b>
	The gameplay objects class stores any objects that appear during gameplay, including lanes, obstacles (ie. vehicles) and the player. Each object has a specified length and shape (which is the visual representation of the object). The position of the object is stored so each object’s position can be manipulated and tracked. The safeToUser boolean specifies whether the player can safely interact with the object or if touching it will trigger the game to end.

* <b> VehicleLane and RockLane: </b>
	The lane classes store any vehicles or rocks that will travel across during gameplay, denoted by a specified shape, which comes from the gameplay objects class. The spawnVehicles() and spawnRocks() function causes the respective objects to appear on the lanes, with vehicle movement..

* <b> Vehicle: </b>
	The vehicle class is a gameplay object with a speed. The speed integer represents how quickly the vehicle will move across the screen during gameplay. The moveVehicle(int, int) function moves the vehicle to a position given in cartesian coordinates every refresh. 

* <b> Player: </b>
	The player class is a gameplay object whose movement dynamically changes. The movement is controlled by the movePlayer(char) function, which is called by the Game class and passes in the user’s input. This class holds a checkCollision() function which checks to see if the user's coordinates conflict with those from an unsafe gameplay object. This would mean that the player hit an object (vehicle in the context of the game) they weren’t supposed to and end the game.

<b>Class Diagram S.O.L.I.D. Updates:</b>

* <b> Leaderboard Class: </b>
	The Leaderboard class has now been split into two separate classes: one for data management, and one for displaying that data. This was done to comply with the single responsibility principle. This new setup allows us to make tweaks to how the scores are stored, managed, and sorted without affecting how they are displayed.

	A LeaderboardPlayer struct was also added to improve data management. It is now more efficient to change what data may be associated with a player.

* <b> GameOverScreen Class: </b>
	The game over display has now been separated from the overarching Game class. This was done to comply with both the single responsibility principle and the dependency inversion principle. Now, if the game over screen needs to be tweaked, or more options need to be added, it won’t affect the functionality of the Game class (ie. it follows the dependency principle).

* <b> Other S.O.L.I.D. Principles: </b>
	All classes inheriting from our GameplayObjects class already abide by the S.O.L.I.D. principles, namely the open-closed, Liskov’s substitution, and interface segregation principles. Each inherited class utilizes every function from the parent class, and any instance of GameplayObject could be substituted for one of the inherited classes.

## Screenshots
<b>Main Menu:</b>
<br>

<img width="761" height="694" alt="MainMenu" src="https://github.com/user-attachments/assets/7902002c-33e1-47d4-a375-a1b71a41af75" />

<br>
The main menu is navigated using the arrow/WASD keys, and the enter keys selects individual options. Pressing the enter key while "PLAY" is underlined leads to the gameplay, and pressing the enter key while "View Leaderboard" is underlined leads to the leaderboard.

<h1></h1>

<img width="764" height="676" alt="MainMenuDifficulty" src="https://github.com/user-attachments/assets/d87c47d0-b556-4eea-8c3b-5e0136a2fa6b" />

<br>
The left/right arrow keys change the difficulty. The options are "Easy", "Medium", and "Hard".

<h1></h1><b>Leaderboard:</b>
<br>

<img width="742" height="415" alt="Leaderboard" src="https://github.com/user-attachments/assets/c551fe24-c377-4f36-964e-4836e75bcb84" />

<br>
The leaderboard displays the top N scores, where N is a positive number chosen by the user. Pressing either the enter or q/Q keys anywhere on the leaderboard screen leads back to the main menu.

<h1></h1><b>Gameplay:</b>
<br>

<img width="861" height="617" alt="GameplayInitial" src="https://github.com/user-attachments/assets/f95e2bad-8c97-4c91-88ec-8063f76a7835" />

The gameplay can be navigated with the WASD/arrow keys. The cyan '@' symbol represents the character, and the yellow characters are coins. The '0' and '+' represent obstacles. The '0' is a moving vehicle and will end the game on player-collision. The '+' is a rock and will prevent the player from moving past it.

<h1></h1>

<img width="860" height="611" alt="GameplayUp" src="https://github.com/user-attachments/assets/354e1c92-5e6e-4ad0-a17f-61bce4fb7292" />

<br>
As the player progresses up through the level, the score is incremented. After some time, a red wall begins moving up to keep the player moving.

<h1></h1>
<img width="758" height="550" alt="GameplayDeath" src="https://github.com/user-attachments/assets/ac81eb4e-5bac-4a1e-ac81-a10fbc720828" />
<br>
When the player overlaps with a vehicle (denoted by '0'), the game ends, and the game over screen is triggered.



<h1></h1><b>Pause Screen:</b>
<br>

<img width="740" height="352" alt="Pause" src="https://github.com/user-attachments/assets/6d5d1d9c-646e-465d-8afe-8c7d399f7c39" />

<br>
The pause menu is accessed by pressing the ESC key, and pauses gameplay. The player can view their current score, and choose to either resume the game or quit back to the menu.

<h1></h1>
<img width="744" height="248" alt="image" src="https://github.com/user-attachments/assets/40c97b94-47ac-4f01-9640-2d7b69c9ac06" />
<br>
Selecting "Quit to Menu" (or pressing the Q/q key during gameplay) will lead to a confirmation screen, with navigation akin to the other menus.

<h1></h1><b>Game Over Screen:</b>
<br>


<img width="760" height="404" alt="GameOver" src="https://github.com/user-attachments/assets/798180fc-7ae3-497f-9a0c-a00f222475a9" />

<br>
Navigating to "Save Score" with the arrow keys allows the player to save their score for the leaderboard. Selecting "Retry" brings the player to a new level, and selecting "Quit to Menu" quits to the menu.

<h1></h1>

<img width="309" height="71" alt="GameOverSaveScore" src="https://github.com/user-attachments/assets/3d79186b-095e-4d67-aa06-14a137c96d15" />

<br>
Selecting "Save Score" leads to this screen, where the player may type up to three characters to represent their name. Pressing the enter key confirms and saves the score to a text file.

<h1></h1>



## Installation/Usage

<b> Dependencies: </b>
* Ensure CMake is installed on your system. For information on how to install CMake, refer to the [documentation](https://cmake.org/cmake/help/latest/index.html).
* For accurate testing, install Google Test in the ./tests directory by running the command: `git submodule add https://github.com/google/googletest.git`

<b> Running the Game: </b>
* While in the root directory, run `cmake .`, followed by `make`.
* Run `./bin/CS100FinalProject`, and enjoy the game!


## Testing/Validation
* <b>Unit Tests:</b> We utilized Google Test to cover all of our classes and their respective functions. Multiple tests were created for functions that deal with input, to ensure the program fails on invalid input.
* <b>CI Workflow:</b> We leveraged GitHub's workflow system to automatically run our test cases on pushes to the repository. This saved us from repeatably compiling and running each individual test file, and guaranteed all test cases pass before merging with the master branch.

