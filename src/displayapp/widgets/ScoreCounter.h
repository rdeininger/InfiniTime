#pragma once
#include <lvgl/lvgl.h>

namespace Pinetime {
  namespace Applications {
    namespace Widgets {
      class ScoreCounter {
      public:
        ScoreCounter(lv_font_t& font);

        void Create();
        void UpBtnPressed();
        void DownBtnPressed();
        void HideControls();
        void ShowControls();
        void EnablePointMode();
        void SetValueChangedEventCallback(void* userData, void (*handler)(void* userData));

        int GetValue() const {
          return value;
        }

        lv_obj_t* GetObject() const {
          return counterContainer;
        };

      private:
        void UpdateLabel();
        void (*ValueChangedHandler)(void* userData) = nullptr;

        lv_obj_t* counterContainer;
        lv_obj_t* myUpBtn;
        lv_obj_t* myDownBtn;
        lv_obj_t* opUpBtn;
        lv_obj_t* opDownBtn;
        lv_obj_t* myScore;
        lv_obj_t* opScore;
        lv_obj_t* myUpperLine;
        lv_obj_t* myLowerLine;
        lv_obj_t* opUpperLine;
        lv_obj_t* opLowerLine;
        lv_point_t linePoints[2];
        int myValue;
        int opValue;
        bool pointMode = false;
        lv_font_t& font;

        void* userData = nullptr;
      };
    }
  }
}
