#pragma once
#include "Player.h"
#include "Bullet.h"
#include "Enemy.h"
#include "Item.h"
#include "Boss.h"
#include "Explosion.h"
#include "gameData.h"
#include <map>
#include <string>
#include <sstream>
#include <iostream>
#include <iomanip>
#include <random>

// Possible gamestates
enum GameState
{
    MAIN_MENU,
    GAMEPLAY,
    PAUSED,
    TUTORIAL,
    SHOP,
    CREDITS,
    SETTINGS,
    DIFFICULTY,
    DEATH_ANIMATION,
    GAME_OVER,
    END
};

// GAME ENGINE
class Game
{
private:
    // Window
    sf::RenderWindow* window;
    sf::VideoMode videoMode;
    sf::View view;

    // Resources
    std::map<std::string, sf::Texture*> textures;
    std::vector<Bullet*> bullets;
    float bulletSpeed;

    // GUI
    sf::Font font;
    sf::Text pointText;
    sf::Text startText; 
    sf::Text coinText;
    sf::Text killCounterText;
    sf::Text shieldText;

    sf::Font titleFont;
    sf::Text gameTitle;
    sf::Text pauseTitle;
    sf::Text settingsTitle;
    sf::Text shopTitle;
    sf::Text creditsTitle;

    // Timer GUI
    sf::Text timerText;
    sf::Clock clock;
    float elapsedTime; // Elapsed time in seconds
    int seconds;
    int minutes;

    // World
    sf::Texture startMenuTexture;
    sf::Sprite startMenuBackground;

    sf::Texture stageBackgroundTexture;
    sf::Texture stage2BackgroundTexture;
    sf::Texture stage3BackgroundTexture;
    sf::Sprite stageBackground;
    sf::Sprite stageBackground2;

    float backgroundScrollSpeed;

    // Menu Backgrounds
    sf::Texture gameOverBackgroundTexture;
    sf::Sprite gameOverBackground;

    // Systems
    unsigned points;
    unsigned enemyKillCounter;
    unsigned bombs;
    int lastKillThreshold;
    int difficulty;

    // Spawnrates
    float enemySpawnRate;
    float meteorSpawnRate;
    float horizontalEnemySpawnRate;
    float deathBeamSpawnRate;
    float healthItemSpawnRate;
    float dpsItemSpawnRate;

    // Player
    Player* player;
    void setBulletColor(int c);

    // Player GUI
    sf::Sprite playerHealthBar;
    sf::Sprite shieldIcon;
    sf::RectangleShape playerHpBar;
    sf::RectangleShape playerHpBarBack;
    // Enemies
    float spawnTimer;
    float spawnTimerMax;
    float horizontalSpawnTimer;
    float horizontalSpawnTimerMax;
    float meteorSpawnTimer;
    float meteorSpawnTimerMax;
    float tripleMeteorChance;
    float doubleMeteorChance;
    float deathBeamSpawnTimer;
    float deathBeamSpawnTimerMax;

    std::vector<Enemy*> enemies;

    // Explosions
    std::vector<Explosion*> explosions;

    // Boss
    Boss* boss;
    float bossAttackCooldown;
    float bossAttackCooldownMax;
    bool startShooting;
    bool bossDefeated;

    // Items
    float healthItemSpawnTimer;
    float healthItemSpawnTimerMax;
    float dpsItemSpawnTimer;
    float dpsItemSpawnTimerMax;

    std::vector<Item*> items;

    // Sound Settings
    float soundfxVolume;
    float musicVolume;

    // Sound effects
    sf::SoundBuffer laserBuffer;
    sf::Sound laserSound;

    sf::SoundBuffer menuClick;
    sf::Sound menuSound;

    sf::SoundBuffer playerHitBuffer;
    sf::Sound playerHit;

    sf::SoundBuffer alienHitBuffer;
    sf::Sound alienHit;

    sf::SoundBuffer pauseBuffer;
    sf::Sound pauseSound;

    sf::SoundBuffer healBuffer;
    sf::Sound healSound;

    sf::SoundBuffer powerUpBuffer;
    sf::Sound powerUpSound;

    sf::SoundBuffer swooshBuffer;
    sf::Sound swooshSound;

    sf::SoundBuffer clangBuffer;
    sf::Sound clangHit;

    sf::SoundBuffer criticalBuffer;
    sf::Sound criticalHit;

    sf::SoundBuffer explosionBuffer;
    sf::Sound explosionSound;

    sf::SoundBuffer bossLaserBuffer;
    sf::Sound bossLaser;

    sf::SoundBuffer shieldBuffer;
    sf::Sound shield;

    sf::SoundBuffer levelUpBuffer;
    sf::Sound levelup;

    sf::SoundBuffer buySoundBuffer;
    sf::Sound buySound;

    sf::SoundBuffer noMoneyBuffer;
    sf::Sound noMoneySound;

    sf::SoundBuffer equipBuffer;
    sf::Sound equipSound;
    
    sf::SoundBuffer deathbeamSoundBuffer;
    sf::Sound deathbeamSound;

    sf::SoundBuffer difficultySetBuffer;
    sf::Sound difficultySetSound;

    // Music
    sf::Music stageMusic;
    sf::Music menuMusic;
    sf::Music gameOverMusic;
    sf::Music victoryTune;
    sf::Music endMusic;

    // Line Mechanic
    sf::Vertex line1[2];
    sf::Vertex line2[2];
    sf::Vertex line3[2];
    sf::Vertex line4[2];
    int lane;
    int laneRandomizer;
    float lanePos;
    bool leftKeyPressed;
    bool rightKeyPressed;
    float horizontalPos;

    int line1Pos;
    int line2Pos;
    int line3Pos;
    int line4Pos;

    // Game states
    GameState gameState; 
    GameState prevgameState;

    // Private functions

    // Initializers
    void initialize();
    void initializeWindow();
    void initializeStage();
    void initializeLines();
    void initializeTextures();
    void initializeSounds();
    void initializeMusic();
    void initializeGUI();
    void initializeBackground();
    void initializeSystems();
    void initializeMenuBackgrounds();
    void initializeGameData();

    void initializeStartMenu();
    void initializeQuitConfirmationMenu();
    void initializeShopMenu();
    void initializePauseMenu();
    void initializeTutorialMenu();
    void initializeDifficultyMenu();
    void initializeGameOverMenu();
    void initializeEndScreen();
    void initializeSettingsMenu();
    void initializeCreditsMenu();
    void initializeSoundFXVolume();
    void initializeMusicVolume();
    void initializeEnemy();
    void initializeSpawnRates();
    void initializePlayerHealthBar();
    void initializeShieldDisplay();
    void initializeItems();
    void initializePlayer();
    float clampVolume(float volume) const;
    void updateShopUnlocks();

    // Game menu input handling
    void handleCreditsMenuInput(const sf::Event& ev);
    void handleMainMenuInput(const sf::Event& ev);
    void handleTutorialMenuInput(const sf::Event& ev);
    void handleQuitConfirmationInput(const sf::Event& ev);
    void handleShopMenuInput(const sf::Event& ev);
    void handlePauseMenuInput(const sf::Event& ev);
    void handleDifficultyMenuInput(const sf::Event& ev);
    void handleGameOverMenuInput(const sf::Event& ev);
    void handleSettingsMenuInput(const sf::Event& ev);

    // Main Menu options
    sf::Text playText;
    sf::Text shopText;
    sf::Text settingsText;
    sf::Text creditsText;
    sf::Text tutorialText;
    sf::Text quitText;
    sf::Text resetText;
    sf::Text menuHighScore;
    bool quitConfirmationScreenActive;
    sf::Text areYouSureQuestion;
    sf::Text yesCloseApplication;
    sf::Text noKeepPlaying;
    sf::Text congratText;

    // Shop Menu options
    sf::Text objectPrice;
    sf::Text coinAmount;
    sf::Text returnfromshopText;
    sf::RectangleShape redbulletSelect;
    sf::Texture redbullet;
    sf::RectangleShape bluebulletSelect;
    sf::Texture bluebullet;
    sf::RectangleShape greenbulletSelect;
    sf::Texture greenbullet;
    sf::RectangleShape yellowbulletSelect;
    sf::Texture yellowbullet;
    sf::RectangleShape purplebulletSelect;
    sf::Texture purplebullet;
    sf::RectangleShape whitebulletSelect;
    sf::Texture whitebullet;
    sf::RectangleShape normalshipSelect;
    sf::Texture normalship;
    sf::RectangleShape greenshipSelect;
    sf::Texture greenship;
    sf::RectangleShape blueshipSelect;
    sf::Texture blueship;
    sf::RectangleShape yellowshipSelect;
    sf::Texture yellowship;
    sf::RectangleShape purpleshipSelect;
    sf::Texture purpleship;
    sf::RectangleShape redshipSelect;
    sf::Texture redship;
    sf::RectangleShape normalfireSelect;
    sf::Texture normalfire;
    sf::RectangleShape yellowfireSelect;
    sf::Texture yellowfire;
    sf::RectangleShape greenfireSelect;
    sf::Texture greenfire;
    sf::RectangleShape blackshipSelect;
    sf::Texture blackship;
    sf::RectangleShape blackbulletSelect;
    sf::Texture blackbullet;
    sf::RectangleShape whitefireSelect;
    sf::Texture whitefire;

    // Tutotial Menu
    sf::Text tutorialTitle;
    sf::Text keybindingsExplanation;

    // Pause Menu options
    sf::RectangleShape pausesettingsBackground;
    sf::Text resumeText;
    sf::Text pausesettingsText;
    sf::Text mainmenuText;

    // Credits Menu
    struct CreditLine
    {
        std::string label;
        std::string url;
    };

    sf::Text creditLineText;
    sf::Text creditsInstructionsText;
    sf::Text creditsStatusText;
    sf::Text returnfromcreditsText;
    std::vector<CreditLine> creditLines;
    int selectedCreditLine;

    // Difficulty menu
    sf::Text easyText;
    sf::Text normalText;
    bool incognitoFlag;
    sf::Text hardText;
    sf::Text returnText;
    sf::Text currentText;

    // Game Over menu options
    sf::Text gameOverText;
    sf::Text scoreAchieved;
    sf::Text lastHighScore;

    // Settings Menu options
    sf::Text musicvolumeText;
    sf::RectangleShape musicvolumeBorder;
    sf::RectangleShape musicvolumeIndicator;
    sf::Text soundfxText;
    sf::RectangleShape soundfxvolumeBorder;
    sf::RectangleShape soundfxvolumeIndicator;
    sf::Text backText;

    int selectedMenuItem;
    int shopselectedMenuItem = 0;
    int currentSelection = 0;

    // End menu
    sf::Texture earthTexture;
    sf::Sprite earthSprite;

    sf::IntRect earthFrame;
    int earthCurrentFrame;
    float earthAnimationTimer;
    float earthAnimationSpeed;

    sf::Texture endBackgroundTexture;
    sf::Sprite endBackground;

    // Flags
    bool bossIsActive;
    bool checkerOne;
    bool checkerTwo;
    bool checkerThree;
    bool checkerFour;
    bool checkerFive;
    bool checkerSix;
    bool checkerSeven;

    // Stages
    bool stageTransition;
    bool stage1End;
    bool stage2End;
    unsigned Stage;
    float timeStamp;
    float timeStamp2;
    bool cutscene;

    // Game Data
    GameData gameData;

    // Fade effect
    enum FadeState { NONE, FADING_OUT, BLACK_SCREEN, FADING_IN };
    FadeState fadeState;
    sf::RectangleShape fadeOverlay;
    float fadeAlpha;
    sf::Clock fadeClock;
    void initializeFadeEffects();

    // Title effect
    float titlePulseTime;
    float titleScaleFactor;
   
public:
    // Constructors
    Game();
    virtual ~Game();

    // Other functions
    void run();
    void reset();
    void triggerFadeEffect();
    void applyScreenShake(float intensity);
    float getSoundFx();

    // Updaters
    void updatePollEvents();
    void updateInput();

    void updateBackground();
    void updateGUI();
    void updateTimer();
    void updateBullets();
    void updateCollision();
    void updateSoundFXVolume();
    void updateMusicVolume();
    void updateEnemies();
    void updateItems();
    void updateCombat();
    void updateBoss();
    void updateHealthBar(int hp);
    void updateDifficulty();
    void updateFadeEffect();
    void updateExplosionEffect();
    void updateTitleEffect();
    void updateDifficultyMenuEffect();
    void updateEndScreen();


    void update();

    // Renders

    void renderCreditsMenu();
    void renderGUI();
    void renderWorld();
    void render();
    void renderStartMenu();
    void renderTutorialMenu();
    void renderShopMenu();
    void renderEquiped();
    void renderQuitConfirmationMenu();
    void renderPauseMenu();
    void renderSettingsMenu();
    void renderDifficultyMenu();
    void renderGameOverMenu();
    void renderEndScreen();
    void renderGameElements();
    void renderExplosion(sf::RenderTarget& target);
};
