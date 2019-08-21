#include "Animation.h"

class PlayerAnimation : public Animation {
private:
  Texture2D spriteSheet;
public:
  PlayerAnimation();
  void play(AnimationState animation, Direction direction) override;
  void changeAnimationTo(AnimationState animation) override;
};