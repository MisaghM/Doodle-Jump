#ifndef CONSTS_HPP_INCLUDE
#define CONSTS_HPP_INCLUDE

namespace consts {

//main-system
constexpr int WIN_WIDTH = 400, WIN_HEIGHT = 640;
constexpr char WIN_NAME[] = "Doodle Jump";
constexpr char FONT[] = "assets/MSComicSans.ttf";
constexpr char ICON[] = "assets/icon.png";

//InputManager
constexpr char RIGHT = 'd';
constexpr char LEFT = 'a';
constexpr char PAUSE = 'p';

//MenuScene
constexpr char MENU_COVER[] = "assets/covers/menu-cover.png";

//GameScene
constexpr char SEQ_FILE[] = "assets/sequence.txt";
constexpr char BACKGROUND_COVER[] = "assets/covers/background.png";
constexpr char TOPBAR_IMG[] = "assets/top-score.png";
constexpr char PAUSE_BTN_IMG[] = "assets/pause.png";

//PauseScene
constexpr char PAUSE_COVER[] = "assets/covers/pause-cover.png";

//GameoverScene
constexpr char GAMEOVER_COVER[] = "assets/covers/gameover-cover.png";

//Doodle
constexpr float DOODLE_VY = 0.7f; // pixels per miliseconds
constexpr float DOODLE_VY_SPRING = 1.3f;
constexpr float DOODLE_VX = 0.42f;
constexpr float G = 14 / 10000.0f;

constexpr char DOODLE_JUMP_SOUND[] = "assets/sounds/jump.wav";
constexpr char DOODLE_DEATH_SOUND[] = "assets/sounds/pada.mp3";
constexpr char DOODLE_JUMP_ON_ENEMY_SOUND[] = "assets/sounds/jumponmonster.mp3";
constexpr char DOODLE_HIT_BY_ENEMY_SOUND[] = "assets/sounds/monster-crash.mp3";

//PlatformBreakable
constexpr char PLAT_BREAK_SOUND[] = "assets/sounds/lomise.mp3";

//Spring
constexpr char SPRING_JUMP_SOUND[] = "assets/sounds/feder.mp3";

} // namespace consts

#endif //CONSTS_HPP_INCLUDE