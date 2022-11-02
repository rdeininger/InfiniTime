#include "TennisScore.h"
#include "displayapp/DisplayApp.h"

using namespace Pinetime::Applications::Screens;

TennisScore::TennisScore(DisplayApp* app) : Screen(app)
{
  Widgets::ScoreBoard board = Widgets::ScoreBoard();
  int offset = board.Width * -1;

  lv_obj_t* container = gameBoard.Create((char*)"Game");
  lv_obj_align(container, nullptr, LV_ALIGN_IN_LEFT_MID, padding,0);

  int rPad = padding *-1;
  container = set3Board.Create((char*)"3");
  lv_obj_align(container, nullptr, LV_ALIGN_IN_RIGHT_MID, rPad ,0);
  container = set2Board.Create((char*)"2");
  lv_obj_align(container, nullptr, LV_ALIGN_IN_RIGHT_MID, offset+rPad,0);
  offset += offset;
  container = set1Board.Create((char*)"1");
  lv_obj_align(container, nullptr, LV_ALIGN_IN_RIGHT_MID, offset+rPad,0);

  int plusSize = LV_HOR_RES * 0.5 - (padding *2);
  int minusSize = LV_HOR_RES * 0.4 - (padding *2);

  auto BtnCreate = [&](lv_obj_t *parent, char * text, int width, int height, lv_color_t color)
  {
    lv_obj_t* btn = lv_btn_create(parent, nullptr);
    lv_obj_set_height(btn, height);
    lv_obj_set_width(btn, width);
    lv_obj_t* btnLabel = lv_label_create(btn, nullptr);
    lv_obj_align(btnLabel, nullptr, LV_ALIGN_CENTER, 0, 0);
    lv_label_set_text_static(btnLabel, text);
    lv_obj_set_style_local_bg_color(btn, LV_BTN_PART_MAIN, LV_STATE_DEFAULT, color);


    return btn;
  };

  int negPad = padding *-1;
  lv_obj_t* topUpBtn = BtnCreate(lv_scr_act(), "+", plusSize, btnHeight, LV_COLOR_LIME);
  //lv_obj_set_event_cb(myUpBtn, lap_event_handler);
  lv_obj_align(topUpBtn, lv_scr_act(), LV_ALIGN_IN_TOP_LEFT, padding, padding);

  lv_obj_t* topDownBtn = BtnCreate(lv_scr_act(), "-", minusSize, btnHeight, LV_COLOR_RED);
  //lv_obj_set_event_cb(myUpBtn, lap_event_handler);
  lv_obj_align(topDownBtn, lv_scr_act(), LV_ALIGN_IN_TOP_RIGHT, negPad, padding);

   lv_obj_t* bottomUpBtn = BtnCreate(lv_scr_act(), "+", plusSize, btnHeight, LV_COLOR_LIME);
  //lv_obj_set_event_cb(myUpBtn, lap_event_handler);
  lv_obj_align(bottomUpBtn, lv_scr_act(), LV_ALIGN_IN_BOTTOM_LEFT, padding, negPad);

  lv_obj_t* bottomDownBtn = BtnCreate(lv_scr_act(), "-", minusSize, btnHeight, LV_COLOR_RED);
  //lv_obj_set_event_cb(myUpBtn, lap_event_handler);
  lv_obj_align(bottomDownBtn, lv_scr_act(), LV_ALIGN_IN_BOTTOM_RIGHT, negPad, negPad);

}

TennisScore::~TennisScore() {
  lv_obj_clean(lv_scr_act());
}
