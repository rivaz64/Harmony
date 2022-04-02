#include "Transition.h"

void
Harmony::Transition::execute()
{
  (*this)(m_newState);
}
