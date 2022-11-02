#include "TennisScore.h"
#include "displayapp/DisplayApp.h"

using namespace Pinetime::Applications::Screens;

static void topUpBtnEventHandler(lv_obj_t* obj, lv_event_t event) {
  if (event != LV_EVENT_CLICKED) {
    return;
  }
  auto* tennis = static_cast<TennisScore*>(obj->user_data);
  tennis->IncTop();
}

static void topDownBtnEventHandler(lv_obj_t* obj, lv_event_t event) {
  if (event != LV_EVENT_CLICKED) {
    return;
  }
  auto* tennis = static_cast<TennisScore*>(obj->user_data);
  tennis->DecTop();
}

static void bottomUpBtnEventHandler(lv_obj_t* obj, lv_event_t event) {
  if (event != LV_EVENT_CLICKED) {
    return;
  }
  auto* tennis = static_cast<TennisScore*>(obj->user_data);
  tennis->IncBottom();
}

static void bottomDownBtnEventHandler(lv_obj_t* obj, lv_event_t event) {
  if (event != LV_EVENT_CLICKED) {
    return;
  }
  auto* tennis = static_cast<TennisScore*>(obj->user_data);
  tennis->DecBottom();
}

TennisScore::TennisScore(DisplayApp* app): Screen(app)
{
  Widgets::ScoreBoard board = Widgets::ScoreBoard();
  int offset = board.Width * -1;

  lv_obj_t* container = gameBoard.Create(game);
  lv_obj_align(container, nullptr, LV_ALIGN_IN_LEFT_MID, padding,0);

  int rPad = padding *-1;
  container = set3Board.Create(set3);
  lv_obj_align(container, nullptr, LV_ALIGN_IN_RIGHT_MID, rPad ,0);
  container = set2Board.Create(set2);
  lv_obj_align(container, nullptr, LV_ALIGN_IN_RIGHT_MID, offset+rPad,0);
  offset += offset;
  container = set1Board.Create(set1);
  lv_obj_align(container, nullptr, LV_ALIGN_IN_RIGHT_MID, offset+rPad,0);

  int plusSize = LV_HOR_RES * 0.5 - (padding *2);
  int minusSize = LV_HOR_RES * 0.4 - (padding *2);

  auto BtnCreate = [&](lv_obj_t *parent, char * text, int width, int height, lv_color_t color)
  {
    lv_obj_t* btn = lv_btn_create(parent, nullptr);
    btn->user_data = this;
    lv_obj_set_height(btn, height);
    lv_obj_set_width(btn, width);
    lv_obj_t* btnLabel = lv_label_create(btn, nullptr);
    lv_obj_align(btnLabel, nullptr, LV_ALIGN_CENTER, 0, 0);
    lv_label_set_text_static(btnLabel, text);
    lv_obj_set_style_local_bg_color(btn, LV_BTN_PART_MAIN, LV_STATE_DEFAULT, color);

    return btn;
  };

  lv_color_t green = LV_COLOR_MAKE(0x0, 0xb0, 0x0);
  int negPad = padding *-1;
  lv_obj_t* topUpBtn = BtnCreate(lv_scr_act(), plus, plusSize, btnHeight, green);
  lv_obj_set_event_cb(topUpBtn, topUpBtnEventHandler);
  lv_obj_align(topUpBtn, lv_scr_act(), LV_ALIGN_IN_TOP_LEFT, padding, padding);

  lv_obj_t* topDownBtn = BtnCreate(lv_scr_act(), minus, minusSize, btnHeight, LV_COLOR_RED);
  lv_obj_set_event_cb(topDownBtn, topDownBtnEventHandler);
  lv_obj_align(topDownBtn, lv_scr_act(), LV_ALIGN_IN_TOP_RIGHT, negPad, padding);

  lv_obj_t* bottomUpBtn = BtnCreate(lv_scr_act(), plus, plusSize, btnHeight, green);
  lv_obj_set_event_cb(bottomUpBtn, bottomUpBtnEventHandler);
  lv_obj_align(bottomUpBtn, lv_scr_act(), LV_ALIGN_IN_BOTTOM_LEFT, padding, negPad);

  lv_obj_t* bottomDownBtn = BtnCreate(lv_scr_act(), minus, minusSize, btnHeight, LV_COLOR_RED);
  lv_obj_set_event_cb(bottomDownBtn, bottomDownBtnEventHandler);
  lv_obj_align(bottomDownBtn, lv_scr_act(), LV_ALIGN_IN_BOTTOM_RIGHT, negPad, negPad);

}

TennisScore::~TennisScore() {
  lv_obj_clean(lv_scr_act());
}

void TennisScore::IncTop() {
  if (isWin && scores[0] > scores[1]) {
    addToSet();
    return;
  }
  if (scores[0] < 99) {
    scores[0] += 1;
    updateGameText();
  }
}

void TennisScore::DecTop() {
  if (scores[0] > 0) {
    scores[0] -= 1;
    updateGameText();
  }
}

void TennisScore::IncBottom() {
  if (isWin && scores[1] > scores[0]) {
    addToSet();
    return;
  }
  if (scores[1] < 99) {
    scores[1] += 1;
    updateGameText();
  }
}

void TennisScore::DecBottom() {
  if (scores[1] > 0) {
    scores[1] -= 1;
    updateGameText();
  }
}

void TennisScore::addToSet() {
  if (scores[0] > scores[1]) {
      scores[currentSet*2]++;
  } else {
      scores[currentSet*2+1]++;
  }
  scores[0] = 0;
  scores[1] = 0;
  updateGameText();
  updateSetText();
}

void TennisScore::updateSetText() {
  set1Board.SetTopText(scores[2]);
  set1Board.SetBottomText(scores[3]);
  set2Board.SetTopText(scores[4]);
  set2Board.SetBottomText(scores[5]);
  set3Board.SetTopText(scores[6]);
  set3Board.SetBottomText(scores[7]);
}
void TennisScore::updateGameText() {

  uint8_t top = scores[0];
  uint8_t bottom = scores[1];

  uint8_t diff = std::abs(top-bottom);

  isWin = false;
  if (pointMode)
  {
    gameBoard.SetTopText(top);
    gameBoard.SetBottomText(bottom);
  } else {
    if (top <= 3 && bottom <= 3) {
      top = std::min(top * 15, 40);
      bottom = std::min(bottom * 15, 40);

      gameBoard.SetTopText(top);
      gameBoard.SetBottomText(bottom);
    }
    else {
      gameBoard.SetTopText(minus);
      gameBoard.SetBottomText(minus);

      if (diff < 2) {
        // show advantage
        if (top > bottom) {
          gameBoard.SetTopText(advantage);
        } else if (bottom > top)  {
          gameBoard.SetBottomText(advantage);
        }
      } else {
        // show winner
        isWin = true;
        if (top > bottom) {
          gameBoard.SetTopText(win);
        } else {
          gameBoard.SetBottomText(win);
        }
      }
    }

  }
}
