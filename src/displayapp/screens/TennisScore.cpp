#include "TennisScore.h"
#include "displayapp/DisplayApp.h"

using namespace Pinetime::Applications::Screens;

TennisScore::TennisScore(DisplayApp* app) : Screen(app)
{
  scoreCounter.Create();
  lv_obj_align(scoreCounter.GetObject(), nullptr, LV_ALIGN_IN_TOP_LEFT, 0, 0);
  scoreCounter.EnablePointMode();
}

TennisScore::~TennisScore() {
  lv_obj_clean(lv_scr_act());
}
