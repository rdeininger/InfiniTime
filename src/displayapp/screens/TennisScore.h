#pragma once

#include "displayapp/screens/Screen.h"
#include "displayapp/widgets/ScoreCounter.h"
#include "displayapp/widgets/ScoreBoard.h"
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
        int padding = 5;
        int btnHeight = 45;

        Widgets::ScoreBoard gameBoard = Widgets::ScoreBoard();
        Widgets::ScoreBoard set1Board = Widgets::ScoreBoard();
        Widgets::ScoreBoard set2Board = Widgets::ScoreBoard();
        Widgets::ScoreBoard set3Board = Widgets::ScoreBoard();


      };
    }
  }
}
