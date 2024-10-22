# Breakout

W Kavanagh. June Summer 2024

## controls

A/D to move the paddle right and left.
P to pause.

## Powerups

big/small paddle (blue)
fast/slow ball (fancy yellow)
fire ball (green)

# Tasklist

## Suggested fixes

* Fix the compiler issues in the code

## Suggested tasks

* Implement mouse input for pad
* Improved VFX (ball trail, paddle hit response, brick particle destruction)
* Better UI (progress bar rather than timer for countdown).
* GameLoop
* Better ball physics (Box2D)
* Leaderboards
* More ball types (e.g., multiball, sticky ball [where you shoot the ball from the paddle every time], tiny ball, big ball, brick-tracking ball)
* Sounds with increasing tone between bounces.
* Implement commentary with calls to an LLM such as LLama

# Time Details and Changelist
<Add information to this section about the time you've taken for this task along with a professional changelist.>

Task 1 - Fixed Compiler issue - removed circular dependency between fireball powerup class and powerup base class which was causing base class undefined error = 5 minutes
Task 2 - Implemented mouse input for paddle where the center of the paddle will move to the mouse's x position using the same speed variable as the keyboard input = 20 minutes
Task 3 - Moved and simplified pause functionality within its own function in game manager class = 5 minutes
Task 4 - Added screen shake effect after losing life = 12 minutes
Task 5 - Added progress bar for powerups, maintaining individual colours for each powerup = 22 minutes
Task 6 - Added sound manager class to play sounds for brick breaking, paddle collisions with the ball, losing a life and game over. Sound manager maintains scalability of the class. 	Sounds are stored using a map which can be added to using an Enum as the key = 1hr 40 minutes
Task 7 - Added replay ability after either losing or winning, space-bar can be pressed to restart the level = 10 minutes
Task 8 - Added big ball power up, ensured all UI display as it does with the other implemented powerups and adjusted the collision responses to account for greater circle radius. = 24 minutes
Task 9 - Added small ball power up consistent with implementation of big ball power up = 5 minutes
Task 10 - Added trail to ball, the trail is a vector of sf::CircleShapes that follow the ball, these shapes are updated with the speed and radius changes when the relevant powerups are activated = 25 minutes
Task 11 - Added explosive ball power up, finds the distance between hit brick and other bricks and assesses if it is within the explosion radius, if so the brick is removed along with the hit brick = 1 hr 40 minutes