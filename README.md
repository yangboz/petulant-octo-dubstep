petulant-octo-dubstep
=====================

##Cocos2d-X

Best practice on learning Cocos2d-x with CocoStudio.

How to start a new project
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
    
### VS2013 configurations ###

http://blog.csdn.net/fansongy/article/details/18366275

http://blog.csdn.net/marpools/article/details/18895129

### Backlog

1.Cocos2d-X UIComponents lack of mouse_over effect,less of customize skin support;

2.Cocos2d-X/OpenCV using wstring,UTF8 character based file path will crash;

3.Cocos2d-X loss of native desktop file drag and drop funnction support;

...


## MXML

1.SDK:4.13.0 with TileList border width issue fix;

2.AIR with desktop support extending to ImageMagick(convert.exe);

## ImageMagick

http://www.imagemagick.org/

### CMD example ###

convert C:\image.jpg -resize 333x500 -rotate 0 +repage 333x333+0+30 -crop 333x333+0+0 -background white -flatten C:\image_output.jpg
