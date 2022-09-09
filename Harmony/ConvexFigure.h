#pragma once
#include "Figure.h"
#include "AngleUtilities.h"

namespace Harmony
{

class ConvexFigure :
  public Figure
{
 public:
  
  ConvexFigure() = default;

  ConvexFigure(const Triangle& tri);

  void
  operator=(const Triangle& tri);

  uint 
  getSide(const Dimencion& point) const override;
  
  bool
  isPointInside(const Dimencion& point, uint& side) const override;

  inline void
  deletePoint(const Dimencion& point)
  {
    m_points.erase(find(m_points.begin(),m_points.end(),point));
    calcCenter();
    orderPoints();
  }

  inline void
  addPoint(const Dimencion& point)
  {
    m_points.push_back(point);
    calcCenter();
    orderPoints();
  }

  inline void
  addPoints(const vector<Dimencion>& newPoints)
  {
    m_points.insert(m_points.end(),newPoints.begin(),newPoints.end());
    calcCenter();
    orderPoints();
  }

  vector<Dimencion>
  getPoints() override
  {
    return m_points;
  }
 protected:
  
  /**
   * @brief calculates the actual center of the figure
  */
  inline void
  calcCenter()
  {
    m_center = {0.f,0.f};
    for(auto& point : m_points){
      m_center += point;
    }
    m_center /= m_points.size();
  }

  /**
   * @brief orders the points clockwise
  */
  inline void
  orderPoints()
  {
    map<float,Dimencion> angles;
    for(auto& point : m_points){
      angles.insert({VectorToAngle(point-m_center),point});
    }
    m_points.clear();
    for(auto& point : angles){
      m_points.push_back(point.second);
    }
  }

  /**
   * @brief all the points of this figure
  */
  vector<Dimencion> m_points;
};

}


