# **Pac-Man game (kinda)**
by: Tkachenko Nikita

---

### Description

A 2D game in some way similar to famous Pac-Man, written in C++, with use of SFML library. 
The project was made in order to practise OOP style programming and Patters.

![image](https://github.com/tka4nik/Pac-Man/assets/39916647/1847cf4d-7ae7-47bb-adfd-92498f9f53c9)

![image](https://github.com/tka4nik/Pac-Man/assets/39916647/fb4f0749-3b96-4619-b34b-ffd2dfb25bd8)

![image](https://github.com/tka4nik/Pac-Man/assets/39916647/2a50e017-26df-49c4-8410-dd8b91b3bd10)


### Features
* Main menu with 3 levels of difficulty
* - Easy: Small available area, no enemies
  - Medium: Medium available area, some enemies
  - Hard: Obstacles, more enemies
* Interactable enemies and food
* WASD controls, `Ctrl+Z` keybind to revert time


 ### Patterns used:
 * `StateMachine` for managing gamestates
 * `Composite` and `Command` for handling buttons
 * `Prototype` and `Memento` for handing game saves
 * `Builder` for making of levels (including walls and such)
 * `Visitor` for interactions with enemies and food
 * 

### Installation

You should have `git` and a compiler for C++/17 installed

```
git clone https://github.com/tka4nik/Pac-Man.git

cd Pac-Man
mkdir build && cd build
cmake ..
cmake --build .
cd ../workdir
./../build/Pacman
```
