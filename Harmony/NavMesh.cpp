#include "NavMesh.h"
#include "Pawn.h"
#include "VectorUtilities.h"
#include "Controller.h"

namespace Harmony{

#define CENTER(n) tris[n].tri.getCenter()
#define DISTANCE(n) (CENTER(n)-centerStart).magnitud()
#define DISTANCE2(n,m) (CENTER(n)-CENTER(m)).magnitud()
#define INSERT_TO_FIND(n) insertToFind({n,DISTANCE(n)},forsearch)

void
addPoint(const Harmony::Vector2f& point, vector<Triangle>& triangulation){
  Harmony::vector<Harmony::Triangle> badTris;
  Harmony::vector<int> badTrisId;
  int num = 0;
  for(auto& tri : triangulation){
    auto center = tri.circumcenter();
    auto radius = (tri.point1-center).magnitud();
    if((point-center).magnitud()<radius){
      badTris.push_back(tri);
      badTrisId.push_back(num);
    }
    ++num;
  }
  auto badTrisNum = badTris.size();
  
  vector<Vector2f> polygon;
  for(int i = 0; i<badTrisNum; ++i){
    auto ref = &badTris[i].point1;
    for(int u = 0; u<3; ++u){
      bool conect = false;
      for(int o = 0; o<badTrisNum; ++o){
        if(i==o) continue;
        if(badTris[o].hasEdge(*(ref+u),*(ref+(u+1)%3))){
          conect = true;
          break;
        }
      }
      if(!conect){
        polygon.push_back(*(ref+u));
        polygon.push_back(*(ref+(u+1)%3));
      }
    }
  }
  num = 0;
  vector<Triangle> temp;
  for(auto& n : badTrisId){
    for(num; num<n; ++num){
      temp.push_back(triangulation[num]);
    }
    ++num;
  }
  for(num;num<triangulation.size();++num){
    temp.push_back(triangulation[num]);
  }
  triangulation = temp;

  auto edges = polygon.size()/2;

  for(int i = 0; i<edges; ++i){
    triangulation.push_back(Harmony::Triangle(polygon[i*2],polygon[i*2+1],point));
  }
}

void 
delauniTriangulation(const vector<Dimencion>& points, vector<Triangle>& tris)
{ 
  auto numOfPoints = points.size();
  for(int i=0; i<numOfPoints; ++i){
    addPoint(points[i],tris);
  }
}


bool
isPointInFig(const Dimencion& tri,const vector<Dimencion>& fig){
  return find(fig.begin(),fig.end(),tri) != fig.end();
}

bool
isTriInFig(const Triangle& tri,const vector<Dimencion>& fig){
  return isPointInFig(tri.point1,fig) &&
         isPointInFig(tri.point2,fig) &&
         isPointInFig(tri.point3,fig);
}

bool
isTriInFigs(const Triangle& tri,const vector<vector<Dimencion>>& figs){
  for(auto& fig : figs){
    if(isTriInFig(tri,fig)){
      return true;
    }
  }
  return false;
}

void 
NavMesh::generate(const Dimencion& minPoint, 
                            const Dimencion& maxPoint, 
                            const vector<vector<Dimencion>>& obstacles)
{
  vector<Dimencion> points;
  vector<Triangle> triangulation;
  uint numOfPoints = 0;
  for(auto& obstacle : obstacles){
    numOfPoints += obstacle.size();
  }
  uint actualPoints = 0;
  points.resize(numOfPoints);
  for(auto& obstacle : obstacles){
    uint numOfPointsInObstacle = obstacle.size();
    memcpy(points.data()+actualPoints,obstacle.data(),sizeof(Dimencion)*numOfPointsInObstacle);
    actualPoints += numOfPointsInObstacle;
  }
  triangulation.push_back(Triangle(minPoint,maxPoint,Dimencion(minPoint.x,maxPoint.y)));
  triangulation.push_back(Triangle(minPoint,maxPoint,Dimencion(maxPoint.x,minPoint.y)));

  delauniTriangulation(points,triangulation);

  for(auto& tri : triangulation){
    if(!isTriInFigs(tri,obstacles)){
      tris.push_back({tri,{}});
    }
  }

  uint numOfTris = tris.size();
  
  for(uint i = 0; i<numOfTris; ++i){
    for(uint o = 0; o<numOfTris; ++o){
      if(i==o) continue;
      auto& actualTri = tris[i];
      auto& comparingTri = tris[o];
      if(comparingTri.tri.hasEdge(actualTri.tri.point1,actualTri.tri.point2)){
        tris[i].adjacents.insert({0,o});
      }
      if(comparingTri.tri.hasEdge(actualTri.tri.point2,actualTri.tri.point3)){
        tris[i].adjacents.insert({1,o});
      }
      if(comparingTri.tri.hasEdge(actualTri.tri.point3,actualTri.tri.point1)){
        tris[i].adjacents.insert({2,o});
      }
    }
  }
}

bool
NavMesh::getCellAt(const Dimencion& point, uint& nodeId)
{
  auto numOfNodes = tris.size();
  uint side;
  for(uint i=0; i<numOfNodes; ++i){
    if(tris[i].tri.isPointInside(point,side)){
      nodeId = i;
      return true;
    }
  }
  return false;
}

const 
Figure* NavMesh::getFigure(const uint id)
{
  return &tris[id].tri;
}

map<uint,uint>
NavMesh::getAdjacentCells(const uint id)
{
  return tris[id].adjacents;
}

//void
//NavMesh::addPawn(Pawn* pawn)
//{
//  uint node = 0;
//  getCellAt(pawn->getPosition(),node);
//  pawns.insert({pawn,node});
//}
//
//list<Dimencion> 
//NavMesh::findPath(Dimencion start, Dimencion end){
//  uint nodeStart = 0, nodeEnd = 0;
//  getCellAt(start,nodeStart);
//  getCellAt(end,nodeEnd);
//  list<Dimencion> ans;
//  auto path = findPath(nodeStart, nodeEnd);
//  for(auto& node : path){
//    ans.push_back(tris[node].tri.getCenter());
//  }
//  return ans;
//}
//
//void 
//insertToFind(PathFindNode newNode, list<PathFindNode>& forsearch){
//  for(auto node = forsearch.begin(); node != forsearch.end(); ++node){
//    if(node->distanceToGoal+node->distanceOfPath > newNode.distanceToGoal+newNode.distanceOfPath){
//      forsearch.insert(node,newNode);
//      return;
//    }
//  }
//  forsearch.push_back(newNode);
//}
//
//
//vector<uint>
//NavMesh::findPath(uint start, uint end)
//{
//  list<PathFindNode> forsearch;
//  //node, parent
//  map<uint,uint> paths;
//  auto centerStart = CENTER(start);
//  insertToFind({end,DISTANCE(end),0},forsearch);
//  paths.insert({end,-1});
//  while(forsearch.size()>0){
//    auto actualAtNode = *forsearch.begin();
//    auto searchAtID = actualAtNode.id;
//    if(searchAtID == start){
//      vector<uint> ans;
//      uint actualNode = start;
//      while(actualNode != end){
//        ans.push_back(actualNode);
//        actualNode = paths[actualNode];
//      }
//      ans.push_back(actualNode);
//      return ans;
//    }
//    auto searchAt = tris[searchAtID];
//    forsearch.pop_front();
//    for(auto& node : searchAt.adjacents){
//      if(paths.find(node.second)==paths.end()){
//        insertToFind({node.second,DISTANCE(node.second),DISTANCE2(node.second,searchAtID)+actualAtNode.distanceOfPath},forsearch);//forsearch.push_back(node.second);
//        paths.insert({node.second,searchAtID});
//      }
//    }
//  }
//}


uint 
NavMesh::goToNewNode(const Dimencion& originalPos,
                     const Dimencion& destiny, 
                     uint actualNodeId, 
                     Dimencion& obstacle, 
                     Dimencion& normal)
{
  auto prevNodeId = actualNodeId;
  auto actualNode = tris[actualNodeId];
  uint side;
  while(!actualNode.tri.isPointInside(destiny,side)){  
    auto ref = &actualNode.tri.point1;
    bool advancing = false;;
    for(uint i = 0; i<3; ++i){
      if(Vector2f::intersect(*(ref+i),*(ref+(1+i)%3),originalPos,destiny,obstacle)){
        advancing = true;
        if(actualNode.adjacents.find(i) == actualNode.adjacents.end()){
          normal = actualNode.tri.normalOfEdgeToInside(i);
          return -1;
        }
        if(prevNodeId == actualNode.adjacents[i]){
          continue;
        }
        prevNodeId = actualNodeId;
        actualNodeId = actualNode.adjacents[i];
        actualNode = tris[actualNodeId];
        break;
      }
    }
    if(!advancing){
      uint ans;
      getCellAt(destiny,ans);
      return ans;
    }
  }
  return actualNodeId;
}

float sign (Dimencion p1, Dimencion p2, Dimencion p3)
{
  return (p1.x - p3.x) * (p2.y - p3.y) - (p2.x - p3.x) * (p1.y - p3.y);
}


void 
NavMesh::update(float deltaTime)
{
  for(auto& data : pawns){
    auto pawn = data.first;
    auto position = pawn->getPosition();
    auto prevPosition = pawn->getPrevPosition();
    auto velocity = pawn->getVelocity();
    Dimencion newPos;
    Dimencion collicion;
    Dimencion normal;

    //sets the pawn to its node in the navmesh
    data.second = goToNewNode(prevPosition,position,data.second,collicion,normal);

    //todo: multiplicar velocity por variable
    newPos = position+velocity;

    if(goToNewNode(position,newPos,data.second,collicion,normal) == -1){
      pawn->getController()->m_variables.setVariableAs<Dimencion>("pointToGo",collicion+normal*216.f);
      pawn->getController()->message(MESSAGES::OnObstacle);
    }

  }
}

}

