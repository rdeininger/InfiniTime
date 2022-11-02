#pragma once

#include "displayapp/screens/Screen.h"
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

          void IncTop();
          void DecTop();
          void IncBottom();
          void DecBottom();

      private:
        int padding = 5;
        int btnHeight = 45;

        char game[6] = "Game";
        char set1[2] = "1";
        char set2[2] = "2";
        char set3[2] = "3";
        char plus[2] = "+";
        char minus[2] = "-";
        char advantage[3] = "Ad";
        char win[3] = "Wi";
        char end[4] = "End";
        uint8_t scores[8] = {0,0,0,0,0,0,0,0};
        uint8_t currentSet = 1;

        bool pointMode = false;
        bool isWin = false;

        void addToSet();
        void updateGameText();
        void updateSetText();

        Widgets::ScoreBoard gameBoard = Widgets::ScoreBoard();
        Widgets::ScoreBoard set1Board = Widgets::ScoreBoard();
        Widgets::ScoreBoard set2Board = Widgets::ScoreBoard();
        Widgets::ScoreBoard set3Board = Widgets::ScoreBoard();
      };
    }
  }
}
