#pragma once

#include "displayapp/screens/Screen.h"
#include <lvgl/lvgl.h>

namespace Pinetime {
  namespace Applications {
    namespace Screens {
      class TennisScore : public Screen
      {
      public:
          TennisScore(DisplayApp* app);
          ~TennisScore() override;
      };
    }
  }
}
