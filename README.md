# Drop
Drop is a game developed for Arduino platform and is comprised of a falling ball and some random pads going in the opposite directions. The objective of the game is to fall as long as possible, avoiding the pads that can push the ball upward ouside the display area.

This project was developed as a homework for the *Introduction to robotics with Arduino* course at the University of Bucharest.

[Video demo](https://photos.app.goo.gl/e3Ct6j8UyayXbnqi8)

## Gameplay
Initially the game is in the `INTRO` state. The player can move the ball horizontally and nothing happens. By pressing the joystick the game starts. For every unit the ball balls, the score grows by one point. For every 40 points the speed of the pads grows by 10 ms, up to the limmit of 200 ms. For every 120 points, the player gets a new life. Every time the ball is pushed outside the display area, the player looses a life. When the player runs out of lives, it's GAME OVER. Here the user sees his score and the can start over again.

## Hardware Requirements
For assembling the game, the following are required:
* 8x8 LED matrix controlled by a MAX 7219 driver
* LCD display and a Hitachi HD44780 driver
* Joystick

## Librarii externe
The following external libraries are used:
* LedControl for controlling the LED matrix
* EventManager for handling "button pressed" and "game over" events in an asynchronous fashion
* LiquidCrystal for controlling the LCD display

The first two libraries are distibuted alongside the game, in this repository. The last one is distributed with the Arduino IDE.

## Code Description
The core of the game is implemented in the `ball_fall` class. It maintains the current state of the game and dispatches the following commands:
* `move_ball(direction)`
* `drop_ball()` - returns the current score
* `pads_up()` - returns `true` if the game continues, `false` otherwise
* `reset()`
* `add_life()`

The state of the game can be queried using the following methods:
* `get_lifes()`
* `get_score()`
* `print_matrix(char[8][8])` - loads the argument with what the game displays
* `print(char screen[8])` - loads the argument with what the game displays, represented as a byte array. Specially designed for the LED matrix.

The game logic on the hardware implementation is coded in the file `ball_fall.ino`, where the commands are called, the quries on the state are run, the hardware resources are managed (displays, joystick). Here is also managed the difficulty by setting the rate at whitch the commands on the game are run and the state of the game (`INTRO`, `PLAYING`, `OVER`).

For scheduling the events to happen at certain points in time, the class `lifecycle_manager` is implemented. It keeps a priority queue with pointers to functions. The priority is given by the point in time at which the action (function) should be executed. This priority queue is implemented as a min-heap with the default capacity of 20. This capacity can be set by modifying the `EVENT_COUNT` value.
