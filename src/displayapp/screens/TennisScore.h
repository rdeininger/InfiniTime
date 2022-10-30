#pragma once

#include "displayapp/screens/Screen.h"
#include "displayapp/widgets/ScoreCounter.h"
#include <lvgl/lvgl.h>

namespace Pinetime {
  namespace Applications {
    namespace Screens {
      class TennisScore : public Screen
      {
      public:
          TennisScore(DisplayApp* app);
          ~TennisScore() override;

      private:
        Widgets::ScoreCounter scoreCounter = Widgets::ScoreCounter(jetbrains_mono_76);
      };
    }
  }
}
