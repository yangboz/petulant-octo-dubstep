fbxconverter alpha

Convert .fbx to .c3t used by cocos2d-x. Thanks to libgdx fbx-conv. We use their code and do some change.

It is the first version and has many bugs for sure. Feel free to contact us. Source code is here,
https://github.com/Trace0429/fbx-conv 

USAGE:

Command line
MAC:
cd [path of fbx-conv]
./fbx-conv FBXFile

Windows:
cd [path of fbx-conv]
fbx-conv FBXFile

It will generate a .c3t file at directory of FBXFile

Note: the bones in the FBX file should not be more than 50. 
