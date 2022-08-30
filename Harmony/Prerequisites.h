#pragma once
#include <vector>
#include <list>
#include <map>
#include <tuple>
#include <string>
#include <iostream>
#include <memory>
#include <algorithm>
#include <functional>
#include <memory>
#include <set>
#include "Vector2f.h"
#ifdef UNREAL_HARMONY
#include "CoreMinimal.h"
#endif


namespace Harmony{

class Vector2f;
class Object;
class Pawn;
class Controler;
class State;
class Message;
class BlackBoard;
class Transition;
class Detector;
class Grid;
class Figure;
class Quad;
class Hexagon;
class Graph;
class Maze;
class HexGrid;
class QuadGrid;
class Timer;
class Action;
class NavLink;
class MultiGrid;
struct SearchNode;
class Path;
class Triangle;
class ConvexFigure;

using std::vector;
using std::list;
using std::map;
using std::pair;
using std::tuple;
using std::set;
using std::move;
using std::string;
using std::find;
using std::advance;
using std::swap;
using std::function;
using std::_Mem_fn;
using std::_Binder;
using std::mem_fn;
using std::bind;
using std::shared_ptr;
using std::weak_ptr;
using std::make_shared;
using uint = unsigned int;

#ifdef UNREAL_HARMONY
using Dimencion = FVector;
#else
using Dimencion = Vector2f;
#endif

inline float
size(const Dimencion& vector){

#ifdef UNREAL_HARMONY
return vector.Size();
#else
return vector.magnitud();
#endif

}

}