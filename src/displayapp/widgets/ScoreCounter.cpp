#include "displayapp/widgets/ScoreCounter.h"
#include "components/datetime/DateTimeController.h"
#include "displayapp/InfiniTimeTheme.h"

using namespace Pinetime::Applications:Widgets;

namespace {
  void MyUpBtnEventHandler(lv_obj_t* obj, lv_event_t event) {
    auto* widget = static_cast<ScoreCounter*>(obj->user_data);
    if (event == LV_EVENT_SHORT_CLICKED || event == LV_EVENT_LONG_PRESSED_REPEAT) {
      widget->MyUpBtnPressed();
    }
  }

  void MyDownBtnEventHandler(lv_obj_t* obj, lv_event_t event) {
    auto* widget = static_cast<ScoreCounter*>(obj->user_data);
    if (event == LV_EVENT_SHORT_CLICKED || event == LV_EVENT_LONG_PRESSED_REPEAT) {
      widget->MyDownBtnPressed();
    }
  }

  void OpUpBtnEventHandler(lv_obj_t* obj, lv_event_t event) {
    auto* widget = static_cast<ScoreCounter*>(obj->user_data);
    if (event == LV_EVENT_SHORT_CLICKED || event == LV_EVENT_LONG_PRESSED_REPEAT) {
      widget->OpUpBtnPressed();
    }
  }

  void OpDownBtnEventHandler(lv_obj_t* obj, lv_event_t event) {
    auto* widget = static_cast<ScoreCounter*>(obj->user_data);
    if (event == LV_EVENT_SHORT_CLICKED || event == LV_EVENT_LONG_PRESSED_REPEAT) {
      widget->OpDownBtnPressed();
    }
  }
}

ScoreCounter::ScoreCounter(lv_font_t& font) : myValue {0}, opValue {0}, font {font}} {
}

void ScoreCounter::MyUpBtnPressed() {
  myValue++;
  UpdateLabel();

  if (ValueChangedHandler != nullptr) {
    ValueChangedHandler(userData);
  }
};

void ScoreCounter::MyMyDownBtnPressed() {
  myValue--;
  UpdateLabel();

  if (ValueChangedHandler != nullptr) {
    ValueChangedHandler(userData);
  }
};

void ScoreCounter::OpUpBtnPressed() {
  opValue++;
  UpdateLabel();

  if (ValueChangedHandler != nullptr) {
    ValueChangedHandler(userData);
  }
};

void ScoreCounter::OpDownBtnPressed() {
  opValue--;
  UpdateLabel();

  if (ValueChangedHandler != nullptr) {
    ValueChangedHandler(userData);
  }
};


void ScoreCounter::HideControls() {
  lv_obj_set_hidden(myupBtn, true);
  lv_obj_set_hidden(myDownBtn, true);
  lv_obj_set_hidden(opupBtn, true);
  lv_obj_set_hidden(opdownBtn, true);myUpBtn
  lv_obj_set_hidden(upperLine, true);
  lv_obj_set_hidden(lowerLine, true);
  lv_obj_set_style_local_bg_opa(counterContainer, LV_OBJ_PART_MAIN, LV_STATE_DEFAULT, LV_OPA_TRANSP);
}
void ScoreCounter::ShowControls() {
  lv_obj_set_hidden(myUpBtn, false);
  lv_obj_set_hidden(myDownBtn, false);
  lv_obj_set_hidden(opupBtn, false);
  lv_obj_set_hidden(opdownBtn, false);
  lv_obj_set_hidden(upperLine, false);
  lv_obj_set_hidden(lowerLine, false);
  lv_obj_set_style_local_bg_opa(counterContainer, LV_OBJ_PART_MAIN, LV_STATE_DEFAULT, LV_OPA_COVER);
}

void ScoreCounter::UpdateLabel() {


  if (pointMode)
  {
    if (myValue <= 3 && opValue <= 3) {
      lv_label_set_text_fmt(myScore, "%.*i", false, myvalue * 15);
      lv_label_set_text_fmt(opScore, "%.*i", false, opvalue * 15);
    }
    else {
      int diff = abs(myValue - opValue);
      lv_label_set_text(myScore, "-");
      lv_label_set_text(opScore, "-");

      if (diff <= 1) {
        // show advantage
        if (myValue > opValue) {
          lv_label_set_text(myScore, "Ad", false);
        } else {
          lv_label_set_text(opScore, "Ad", false);
        }
      } else {
        // show winner
        if (myValue > opValue) {
          lv_label_set_text(myScore, "Wi", false);
        } else {
          lv_label_set_text(opScore, "Wi", false);
        }
      }
    }
  } else {
    lv_label_set_text_fmt(myScore, "%.*i", false, myvalue);
    lv_label_set_text_fmt(opScore, "%.*i", false, opvalue);
  }
}

// Value is kept between 0 and 23, but the displayed value is converted to 12-hour.
// Make sure to set the max and min values to 0 and 23. Otherwise behaviour is undefined
void ScoreCounter::EnablePointMode() {
  pointMode = true;
}

void ScoreCounter::SetValueChangedEventCallback(void* userData, void (*handler)(void* userData)) {
  this->userData = userData;
  this->ValueChangedHandler = handler;
}

void ScoreCounter::Create() {
  counterContainer = lv_obj_create(lv_scr_act(), nullptr);
  lv_obj_set_style_local_bg_color(counterContainer, LV_BTN_PART_MAIN, LV_STATE_DEFAULT, Colors::bgAlt);

  myScore = lv_label_create(counterContainer, nullptr);
  lv_obj_set_style_local_text_font(myScore, LV_LABEL_PART_MAIN, LV_STATE_DEFAULT, &font);
  lv_obj_align(myScore, nullptr, LV_ALIGN_CENTER, 0, 0);
  lv_obj_set_auto_realign(myScore, true);

  static constexpr uint8_t padding = 5;
  const uint8_t width = std::max(lv_obj_get_width(myScore) + padding * 2, 58);
  static constexpr uint8_t btnHeight = 50;
  const uint8_t containerHeight = btnHeight * 2 + lv_obj_get_height(myScore) + padding * 2;

  opScore = lv_label_create(counterContainer, nullptr);
  lv_obj_set_style_local_text_font(opScore, LV_LABEL_PART_MAIN, LV_STATE_DEFAULT, &font);
  lv_obj_align(opScore, nullptr, LV_ALIGN_CENTER, width, 0);
  lv_obj_set_auto_realign(opScore, true);

  lv_obj_set_size(counterContainer, width, containerHeight);

  UpdateLabel();

  myUpBtn = lv_btn_create(counterContainer, nullptr);
  lv_obj_set_style_local_bg_color(myUpBtn, LV_BTN_PART_MAIN, LV_STATE_DEFAULT, Colors::bgAlt);
  lv_obj_set_size(myUpBtn, width, btnHeight);
  lv_obj_align(myUpBtn, nullptr, LV_ALIGN_IN_TOP_MID, 0, 0);
  myUpBtn->user_data = this;
  lv_obj_set_event_cb(myUpBtn, MyUpBtnEventHandler);

  lv_obj_t* upLabel = lv_label_create(myUpBtn, nullptr);
  lv_obj_set_style_local_text_font(upLabel, LV_LABEL_PART_MAIN, LV_STATE_DEFAULT, &jetbrains_mono_42);
  lv_label_set_text_static(upLabel, "+");
  lv_obj_align(upLabel, nullptr, LV_ALIGN_CENTER, 0, 0);

  myDownBtn = lv_btn_create(counterContainer, nullptr);
  lv_obj_set_style_local_bg_color(myDownBtn, LV_BTN_PART_MAIN, LV_STATE_DEFAULT, Colors::bgAlt);
  lv_obj_set_size(myDownBtn, width, btnHeight);
  lv_obj_align(myDownBtn, nullptr, LV_ALIGN_IN_BOTTOM_MID, 0, 0);
  myDownBtn->user_data = this;
  lv_obj_set_event_cb(myDownBtn, MyDownBtnEventHandler);

  lv_obj_t* downLabel = lv_label_create(myDownBtn, nullptr);
  lv_obj_set_style_local_text_font(downLabel, LV_LABEL_PART_MAIN, LV_STATE_DEFAULT, &jetbrains_mono_42);
  lv_label_set_text_static(downLabel, "-");
  lv_obj_align(downLabel, nullptr, LV_ALIGN_CENTER, 0, 0);

  linePoints[0] = {0, 0};
  linePoints[1] = {width, 0};

  opUpBtn = lv_btn_create(counterContainer, nullptr);
  lv_obj_set_style_local_bg_color(opUpBtn, LV_BTN_PART_MAIN, LV_STATE_DEFAULT, Colors::bgAlt);
  lv_obj_set_size(opUpBtn, width, btnHeight);
  lv_obj_align(opUpBtn, nullptr, LV_ALIGN_IN_TOP_MID, width, 0);
  opUpBtn->user_data = this;
  lv_obj_set_event_cb(opUpBtn, OpUpBtnEventHandler);

  lv_obj_t* opUpLabel = lv_label_create(opUpBtn, nullptr);
  lv_obj_set_style_local_text_font(opUpLabel, LV_LABEL_PART_MAIN, LV_STATE_DEFAULT, &jetbrains_mono_42);
  lv_label_set_text_static(opUpLabel, "+");
  lv_obj_align(opUpLabel, nullptr, LV_ALIGN_CENTER, width, 0);

  opDownBtn = lv_btn_create(counterContainer, nullptr);
  lv_obj_set_style_local_bg_color(opDownBtn, LV_BTN_PART_MAIN, LV_STATE_DEFAULT, Colors::bgAlt);
  lv_obj_set_size(opDownBtn, width, btnHeight);
  lv_obj_align(opDownBtn, nullptr, LV_ALIGN_IN_BOTTOM_MID, width, 0);
  opDownBtn->user_data = this;
  lv_obj_set_event_cb(opDownBtn, OpDownBtnEventHandler);

  lv_obj_t* opDownLabel = lv_label_create(opDownBtn, nullptr);
  lv_obj_set_style_local_text_font(opDownLabel, LV_LABEL_PART_MAIN, LV_STATE_DEFAULT, &jetbrains_mono_42);
  lv_label_set_text_static(opDownLabel, "-");
  lv_obj_align(opDownLabel, nullptr, LV_ALIGN_CENTER, width, 0);

  auto LineCreate = [&]() {
    lv_obj_t* line = lv_line_create(counterContainer, nullptr);
    lv_line_set_points(line, linePoints, 2);
    lv_obj_set_style_local_line_width(line, LV_LINE_PART_MAIN, LV_STATE_DEFAULT, 1);
    lv_obj_set_style_local_line_color(line, LV_LINE_PART_MAIN, LV_STATE_DEFAULT, LV_COLOR_WHITE);
    lv_obj_set_style_local_line_opa(line, LV_LINE_PART_MAIN, LV_STATE_DEFAULT, LV_OPA_20);
    return line;
  };

  myUpperLine = LineCreate();
  lv_obj_align(upperLine, myUpBtn, LV_ALIGN_OUT_BOTTOM_MID, 0, 0);

  myLowerLine = LineCreate();
  lv_obj_align(lowerLine, myDownBtn, LV_ALIGN_OUT_TOP_MID, 0, -1);


  opUpperLine = LineCreate();
  lv_obj_align(opUpperLine, myUpBtn, LV_ALIGN_OUT_BOTTOM_MID, width, 0);

  oplowerLine = LineCreate();
  lv_obj_align(oplowerLine, myDownBtn, LV_ALIGN_OUT_TOP_MID, width, -1);
}
