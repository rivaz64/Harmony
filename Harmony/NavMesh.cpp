#include "NavMesh.h"
#include "VectorUtilities.h"

namespace Harmony{

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

      if(tris[i].tri.hasEdge(tris[o].tri.point1,tris[o].tri.point2)){
        tris[i].adjacents.insert({0,o});
      }
      if(tris[i].tri.hasEdge(tris[o].tri.point2,tris[o].tri.point3)){
        tris[i].adjacents.insert({1,o});
      }
      if(tris[i].tri.hasEdge(tris[o].tri.point3,tris[o].tri.point1)){
        tris[i].adjacents.insert({2,o});
      }
      //if(tris[i].tri.areAdjacent(tris[o].tri)){
      //  tris[i].adjacents.push_back(o);
      //}
    }
  }
}

vector<uint> NavMesh::findPath(Vector2f start, Vector2f end){
  uint nodeStart = 0, nodeEnd = 0;
  auto numOfNodes = tris.size();
  for(uint i=0; i<numOfNodes; ++i){
    if(tris[i].tri.isPointInside(start)){
      nodeStart = i;
    }
    if(tris[i].tri.isPointInside(end)){
      nodeEnd = i;
    }
  }
  return findPath(nodeStart, nodeEnd);
}

vector<uint>
NavMesh::findPath(uint start, uint end)
{
  //vector<uint> searched;
  list<uint> forsearch;
  //node, parent
  map<uint,uint> paths;
  forsearch.push_back(end);
  paths.insert({end,-1});
  while(forsearch.size()>0){
    auto searchAtID =*forsearch.begin();
    if(searchAtID == start){
      vector<uint> ans;
      uint actualNode = start;
      while(actualNode != end){
        ans.push_back(actualNode);
        actualNode = paths[actualNode];
      }
      return ans;
    }
    auto searchAt = tris[searchAtID];
    forsearch.pop_front();
    for(auto& node : searchAt.adjacents){
      if(paths.find(node.second)==paths.end()){
        forsearch.push_back(node.second);
        paths.insert({node.second,searchAtID});
      }
    }
  }
}

}

