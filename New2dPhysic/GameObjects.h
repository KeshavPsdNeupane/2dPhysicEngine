#pragma once
#include"PhysicLoop.h"
#include"Body/RigidBody.h"
#include"PhysicUtility/Utility.h"
#include"Objects/Rect.h"
#include"Body/ContactMechanic.h"
#include"Path/Path.h"
#include"Resources/Resources.h"
#include"GameGrid/GameGrid.h"
#include"Objects/Inflator.h"
#include"Objects/Deflator.h"
#include"Path/BouncyPath.h"
#include"Objects/Collectable.h"
#include<vector>
struct GameObject {
public:
    GameGrid grid;
    Resources resource;
    std::shared_ptr<Rect> rectangle;
    std::vector<std::shared_ptr<Path>> path;
	std::shared_ptr<Inflator> inflator;
	std::shared_ptr<Deflator> deflator;
	std::shared_ptr<BouncyPath> bouncyPath;
    std::vector<std::shared_ptr<Collectable>> collectable;
    PhysicLoop loop;
};
extern GameObject gameObject;
