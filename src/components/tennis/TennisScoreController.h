#include <cstdint>

namespace Pinetime {
  namespace Controllers {
    class TennisScoreController {
    public:
      TennisScoreController();

      void Init();
      uint8_t MyScore() const {
        return myScore;
      }
      uint8_t OpScore() const {
        return opScore;
      }

    private:
      Controllers::TennisScoreController& tennisScoreController;
      uint8_t myScore = 0;
      uint8_t opScore = 0;
    };
  }
}
