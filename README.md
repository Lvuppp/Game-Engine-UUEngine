# OOP Curswork 
Student: Bagrovets Egor Sergeevich \
Group number: 153504 

This repository develops a software tool for creating 3D computer games, based on its own game engine. 

# Software tool
The software tool for creating computer games will implement basic tools for creating games.

# Game Engine
The game engine will allow to perform various basic operations on objects (moving, rotating, resizing). The same game engine will provide basic objects such as cube, ball and so on. There will be implemented basic physics for various ideal objects, for example for inelastic solid body will be implemented gravitation force, impulse, but elastic force will not be implemented for it. There will also be created various physical quantities that can be turned off, such as kinetic energy or potential energy. Basic classes for working with the scene, camera, lighting will be implemented.

# Functional Requirments
*Application* give opportunities to create scenes(with camera and lighting), change scenes settings; give posabilities to add, edit settings (coordinates, scale, rotation, diffuse/normal texture), lock\unlock and remove game objects, also create physics 3d object, edit its setting(additional parameters like weight, speed, impulse kinetic/potential energy) and remove them. Gives various basic 3d game objects. You can attach scripts to game objects, like camera, 3d objects and etc.. After you set up the scene you can start it in real time. In the starting scene all your uploaded objects and scripts will be handled by the game engine. 

*Game Engine* should implement functions of processing graphics and physics parts of game objects.  Engine should have ways to work with created scenes and set up default basic scene objects like lighting, camera, base3d objects and base3d physics objects. Engine working with physics and graphics parts by Physics Engine and Graphics Engine.

Physics Engine should process the behavior of every physics 3d object at all play time. Physics in the game will be implemented by processing of various forces like gravity,normal etc., and also by kinetic, potential energy and impulse. Physics engine should process basic collisions of objects.

*Graphics Engine* should process the 3d models and textures of game objects, also process lights and camera behavior.

*Camera* should draw objects in the draw area. Also use basic game object functions.

*Lighting* should create rays on the scene. Also use basic game object functions

Base functions that each *game object* should implement:


* moving the game object on scene
* rotating the game object on scene
* scale - scale the model of the game object
* setCoordinate - set coordinate of the game object on scene
* setRotation - set rotation 
* lock/unlock -lock/unlock game object on scene
* update - update own statement of the object on scene.

# Data models:
* .cpp files implement scripts of game objects
* .obj, .fbx files consist implementation of 3d objects
* .jpeg, .jpg, .png file implement texture of game objects
