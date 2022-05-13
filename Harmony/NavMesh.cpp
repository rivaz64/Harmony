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
  vector<Triangle> temp;
  auto center = average(points);
  auto far = farest(points,center);
  auto farestDir = (far-center).normalized();
  auto farestSize = (far-center).magnitud();
  auto other = Harmony::Vector2f(-farestDir.y,farestDir.x)*(farestSize*sqrt(3));
  
  Harmony::Triangle originalTri(far*2-center,center*2-far+other,center*2-far-other);

  tris.push_back(originalTri);
  
  auto ref = &originalTri.point1;
  for(int i = 0; i<3; ++i){
    temp.push_back(Triangle(*(ref+i),*(ref+(i+1)%3),points[0]));
  }

  tris = temp;
  auto numOfPoints = points.size();
  for(int i=1; i<numOfPoints; ++i){
    addPoint(points[i],tris);
  }

  Harmony::vector<int> badTris;
  
  ref = &originalTri.point1;
  int nu; 
  int nume;
  for(int i = 0; i<3; ++i){
    badTris.clear();
    nu = 0;
    for(auto& tri : tris){
      if(tri.hasPoint(*(ref+i))){
        badTris.push_back(nu);
      }
      ++nu;
    }
    nume = 0;
    Harmony::vector<Harmony::Triangle> temp;
    for(auto& n : badTris){
      for(nume; nume<n; ++nume){
        temp.push_back(tris[nume]);
      }
      ++nume;
    }
    for(nume;nume<tris.size();++nume){
      temp.push_back(tris[nume]);
    }
    tris = temp;
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
NavMesh::generateFromPoints(const Dimencion& minPoint, 
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
  
  points.push_back(minPoint);
  points.push_back(maxPoint);
  points.push_back(Dimencion(minPoint.x,maxPoint.y));
  points.push_back(Dimencion(maxPoint.x,minPoint.y));

  delauniTriangulation(points,triangulation);

  for(auto& tri : triangulation){
    if(!isTriInFigs(tri,obstacles)){
      tris.push_back(tri);
    }
  }
}

}

