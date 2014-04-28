petulant-octo-dubstep
=====================

Best practice on learning Cocos2d-x with CocoStudio.

How to start a new game
-----------------------

1. Download the code from [cocos2d download site][4]
2. Run `setup.py`
3. Run the `cocos` script

Example:

    $ cd cocos2d-x
    $ ./setup.py
    $ source FILE_TO_SAVE_SYSTEM_VARIABLE
    $ cocos new MyCocos2dxGame -p com.godpaper.game.cocos2dx -l cpp -d C:/Users/yangboz/git/petulant-octo-dubstep
    $ cd C:/Users/yangboz/git/petulant-octo-dubstep/MyCocos2dxGame

### Build and run new project for android ###

    $ cocos run -p android -j 4

### Build and run new project for iOS ###

    $ cocos run -p ios
    
### Build and run new project for OSX ###

    $ cocos run -p mac

### Build and run new project for linux ###

if you never run cocos2d-x on linux, you need to install all dependences by the
script in **cocos2d/build/install-deps-linux.sh**

    $ cd cocos2d-x/build
    $ ./install-deps-linux.sh

Then

    $ cd NEW_PROJECTS_DIR/MyGame
    $ cocos run -p linux
    
Run

    $ bin/MyGame

### Build and run new project for win32 ###

    $ cocos run -p win32