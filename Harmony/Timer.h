#pragma once
#include "Delegate.h"

namespace Harmony{

/**
 * @brief check certain time and executes something when the time finish
*/
class Timer
{
 public:

  /**
   * @brief initialize the timer and waits for the first time to happen
   * @param time 
  */
  Timer(float time) :
    m_time(time), m_totalTime(time){}

  /**
   * @brief initialize the time with a certaim time to wait for the first time
   * @param time 
   * @param totalTime 
  */
  Timer(float time, float totalTime) :
    m_time(time), m_totalTime(totalTime){}


 private:

  inline void
  update(float delta)
  {
    m_time-=delta;
    if(m_time<0){
      m_time+=m_totalTime;
      m_event();
    }
  }

  /**
   * @brief the actualTime
  */
  float m_time;

  /**
   * @brief the time to wait
  */
  float m_totalTime;

  /**
   * @brief the event to execute when the time is over
  */
  Delegate<> m_event;
};

}



