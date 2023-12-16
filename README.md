# 3D Maze

Simple pseudo 3D renderer that displays a maze in first person using BSP Trees. This was made for an University project long ago.
You can see a showcase of the app [here](https://www.youtube.com/watch?v=NNnu6VDo9EQ).

## How it works

The main requeriment of the subject was to make a game that made use of some sort of data structure, so I decided to use BSP trees to resolve visibility problem in a pseudo 3D scene as Doom did back in the 90s.

### Scene construction

The scene is stored as a collecion of sectors defined by two points, representing the walls of the labiryint, each sector is then stored inside a binary tree that satisfyes that any sector which is to in front of the sector of a node will lay on the left subtree of the node, otherwise it will do on the right.

### Rendering

The main idea is to traverse all the sectors ordered from the nearest to the camera to the farthest, drawing them in screen in that order and keeping a vector which the vertical lines that have already be drawn so there are not walls ocluded by others that lay be behind them.
To achieve that is for what the BSP tree was constructed, we iterate depth first the tree checking whether the camera is in front or behind certain vector and iterating first the left subtree if is behind or the right tree if is in front. We also keep how many vertical lines are to be drawn so when it reaches 0 we stop iterating the tree as all the visible scene has already be drawn.

## Build

A premake5 file is provided to build the project, however take in mind that is has only been tested in windows with visual studio.

It will also require to have SDL2 runtime and dev libraries installed globally in your system. In Visual Studio we strongly reccomend you to use vcpkg.
