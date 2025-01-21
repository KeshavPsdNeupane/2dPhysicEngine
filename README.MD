# Bounce Ball Game Physics Engine

This repository houses a physics engine and supporting framework for a bounce ball game. The engine is built with modularity and extensibility in mind, allowing for seamless integration of new features, levels, and mechanics. The primary focus is on creating an efficient physics system combined with gameplay mechanics that enhance player experience.

## Classes and Their Purpose

## Core Physics Components

**` Rigidbody: `**

The foundational class responsible for implementing core physics properties and behaviors, including velocity, acceleration, friction, and collision responses.

Serves as the base class for all objects requiring physics interactions.

**` GameShape:`** 

An abstract class inheriting from Rigidbody.

Acts as a blueprint for all game objects that need to be drawable and interactable (e.g., handling collisions or updates).

**` Game Objects`**

These classes inherit from GameShape and define specific gameplay elements:

**` Rect:`**

Represents the player.

Implements unique behaviors like user-controlled movement and interactions with the environment.

**` Path:`**

Functions as the ground.

Provides a static surface for the player to move on, with no special physics alterations.

**` BouncePad:`**

Derived from Path but introduces a high coefficient of restitution.

Causes objects to rebound with significant force upon contact, adding dynamic gameplay elements.

**`Inflator:`**

Expands the player’s size when interacted with.

Alters gameplay by affecting the player’s collision box and movement dynamics.

**`Deflator:`**

Opposite of the Inflator.

Shrinks the player, reducing their size and altering interactions with the environment.

**`Collectable:`**

Represents items like coins or tokens for the player to collect.

Enhances level objectives and progression mechanics.

**`Checkpoint:`**

Acts as a save point.

Allows the player to respawn from the checkpoint location after being damaged by enemies or falling out of bounds.

**`LevelEndMarker:`**

Marks the end of a level.

Enforces progression conditions: the player must collect at least 85% + 1 of the total coins in the level to activate.

**`StaticEnemy:`**

A stationary enemy that deals damage on its left and right sides.

**`StaticEnemySidewise:`**

A variation of StaticEnemy rotated by 90 degrees.

Deals damage on its top and bottom sides instead of the left and right.

**`DynamicEnemy:`**

A moving enemy that oscillates vertically (up and down) within a defined range from its spawn point.

Adds a dynamic challenge for players to avoid.

**`InvisibleEnemy:`**

An undetectable enemy.

Damages the player when they leave the world bounds, effectively punishing unintended behavior.

## Managers

**`StateManager:`**

Manages different game states, such as menus, gameplay, and pause screens.

Facilitates transitions between states and ensures the game logic adheres to the active state.

**`ResourceManager:`**

Handles the loading, caching, and distribution of game assets like textures, fonts, and sounds.

Reduces redundancy and improves resource management efficiency.

**`CollisionManager:`**

Centralized system for managing collision detection and resolution.

Uses a CollisionID enum to map specific collision handling logic between different object types (e.g., player vs. enemy).

## Grid System

**`GridClass:`**

Manages the game’s grid-based layout for organizing objects.

Tracks objects that are drawable, updatable, and collidable, improving performance by focusing on nearby entities relative to the player.

Optimizes collision checks by grouping objects into grid cells.

## Level Creation

**`TileResource:`**

Parses .txt files located in the Assets folder to create game levels.

Converts raw text data into game objects, defining their type, position, and properties.

**`WorldSuperClass:`**

Abstract base class for implementing unique world behavior.

Defines common functionalities that all levels inherit.

**`Level:`**

A concrete implementation of a playable level.

(TODO: Update to accept .txt file paths as a constructor argument for greater flexibility.)

## Features

# Physics Engine:

Fully implemented physics with properties like gravity, restitution, and collision response.

## Supports dynamic and static objects.

**`Grid-Based Optimization:`**

Efficiently tracks and updates game objects based on proximity to the player.

Reduces computational overhead by limiting updates to relevant objects.

**`Collision System:`**

Unique CollisionID system for managing and resolving specific interactions.

Supports multiple object types with custom behaviors.

**`Level Design:`**

Text-based level creation allows rapid prototyping and editing.

Modular world system enables the addition of new levels with minimal effort.

**`Modularity:`**

Object-oriented architecture ensures easy extension of classes and features.

Resource and state managers provide a centralized structure for managing game logic and assets.


# To-Do

Update Level class to accept .txt file paths as a constructor argument.

Implement more advanced enemy behaviors, such as AI-driven movement.

Optimize the collision detection algorithm for complex scenes.

Enhance visual effects and animations for a better player experience.

Add support for multiplayer or cooperative gameplay.
