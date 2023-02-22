# ErisSFML_GameEngine
#### Project status: abandoned (I decided to learn Godot instead)
I might return to this project when I'll decide to make a 2D videogame.



### \[TODO]    
- Fix the animation for north-east    
- ErisUtility Log - Add if constexpr to if statements into template to create copies of the function that' won't need to check if statements on runtime   
- Eris_Utility LOG_ERR requires body, make sure it has an overload that requires only one string   


### \[KNOWN BUGS]

- Setting 1280x720 as screen resolution doesn't cover the whole screen (matching resolution)

- Configuration:Release doesn't work even though Configuration:Dist does - Check macro EGE_RELEASE or dependencies' settings

### \[CHANGELOGS]
#### \[0.0.3]
- Fixed Premake5.lua (files)

#### \[0.0.2]
- Update loop is much better
- GameState and Menu State are loading
- Buttons are working
- ErisUtility Log - updated to use iomanip functionality
- ErisUtility Log - changed format and the format LOG_ERROR to LOG_ERR

#### \[0.0.1]
- Implemented basic sfml structures

