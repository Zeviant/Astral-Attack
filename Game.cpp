#include "Game.h"
#include <algorithm>

// All initializers
void Game::initialize()
{

	this->initializeWindow();
	this->initializeLines();
	this->initializeStage();
	this->initializeTextures();
	this->initializeSounds();
	this->initializeGameData();
	this->initializePlayer();
	this->initializeSpawnRates();
	this->initializeEnemy();
	this->initializeItems();
	this->initializeGUI();
	this->initializeStartMenu(); 
	this->initializeBackground();
	this->initializePlayerHealthBar();
	this->initializeSystems();
	this->initializePauseMenu();
	this->initializeGameOverMenu();
	this->initializeMenuBackgrounds();
	this->initializeSettingsMenu();
	this->initializeFadeEffects();
	this->initializeTutorialMenu();
	this->initializeDifficultyMenu();
	this->initializeShopMenu();
	this->initializeShieldDisplay();
	this->initializeMusicVolume();
	this->initializeSoundFXVolume();
	this->initializeCreditsMenu();
	this->initializeQuitConfirmationMenu();
	this->initializeEndScreen();

	this->gameState = MAIN_MENU; // Set initial game state to MAIN_MENU
	this->prevgameState = MAIN_MENU;
	this->selectedMenuItem = 0;  // Initialize the selected menu item to the first item
}

// Load saved bullet color
void Game::setBulletColor(int c)
{
	switch (c)
	{
	case 0:
		if (!this->textures["BULLET"]->loadFromFile("Textures/Redbulletrfix.png"))
		{
			std::cout << "TEXTURE::BULLET_RED::FAILED_TO_LOAD" << "\n";
		}
		break;
	case 1:
		if (!this->textures["BULLET"]->loadFromFile("Textures/Bluebulletfix.png"))
		{
			std::cout << "TEXTURE::BULLET_BLUE::FAILED_TO_LOAD" << "\n";
		}
		break;
	case 2:
		if(!this->textures["BULLET"]->loadFromFile("Textures/Greenbulletfix.png"))
		{
			std::cout << "TEXTURE::BULLET_GREEN::FAILED_TO_LOAD" << "\n";
		}
		break;
	case 3:
		if (!this->textures["BULLET"]->loadFromFile("Textures/Yellowbullet.png"))
		{
			std::cout << "TEXTURE::BULLET_YELLOW::FAILED_TO_LOAD" << "\n";
		}
		break;
	case 4:
		if (!this->textures["BULLET"]->loadFromFile("Textures/Purplebullet.png"))
		{
			std::cout << "TEXTURE::BULLET_PURPLE::FAILED_TO_LOAD" << "\n";
		}
		break;
	case 5:
		if (!this->textures["BULLET"]->loadFromFile("Textures/Whitebullet.png"))
		{
			std::cout << "TEXTURE::BULLET_WHITE::FAILED_TO_LOAD" << "\n";
		}
		break;
	case 6:
		if (!this->textures["BULLET"]->loadFromFile("Textures/Blackbullet.png"))
		{
			std::cout << "TEXTURE::BULLET_WHITE::FAILED_TO_LOAD" << "\n";
		}
		break;
	}
}

Game::Game()
{
	this->initialize();

}

// Destructor
Game::~Game()
{
	delete this->window;
	delete this->player;
	delete this->boss;

	// Delete textures
	for (auto& i : this->textures)
	{
		delete i.second; // Deletes second part of textures array, which is the actual texture (not the string portion)
	}

	// Delete bullets
	for (auto* i : this->bullets)
	{
		delete i;
	}

	for (auto* i : this->enemies)
	{
		delete i;
	}
}

// Public
void Game::run()
{
	while (this->window->isOpen())
	{
		// Game loop
		this->update();
		this->render();
	}
}

// Reset game
void Game::reset()
{  
	// Reset player stats
	delete player;
	delete boss;

	bossIsActive = false;
	this->cutscene = false;

	this->initializePlayer();
	this->initializeEnemy();
	this->initializeSpawnRates();
	this->backgroundScrollSpeed = 1.0f;
	this->initializeItems();
	this->initializeBackground();
	this->initializeStage();
	this->initializeSystems();
	this->lane = 4;
	this->stageMusic.setLoop(false);



	this->elapsedTime = 0.f;
	this->clock.restart();
	this->minutes = 0;
	this->seconds = 0;

	// Clear bullets
	for (auto* bullet : this->bullets)
	{
		delete bullet;
	}
	this->bullets.clear();

	// Clear enemies
	for (auto* enemy : this->enemies)
	{
		delete enemy;
	}
	this->enemies.clear();

	// Clear items
	for (auto* item : this->items)
	{
		delete item;
	}
	this->items.clear();


}

// Fade to black effect
void Game::triggerFadeEffect() {
	fadeState = FADING_OUT;
	fadeAlpha = 0.f;
	fadeClock.restart();
}

// Screen shake effect (for last boss)
void Game::applyScreenShake(float intensity)
{
	// Get the original center of the view
	sf::Vector2f originalCenter = this->window->getDefaultView().getCenter();

	// Apply a random offset
	float offsetX = static_cast<float>((rand() % 100 - 50) / 50.0f) * intensity;
	float offsetY = static_cast<float>((rand() % 100 - 50) / 50.0f) * intensity;

	// Create a temporary view with the new center
	sf::View tempView = this->window->getDefaultView();
	tempView.setCenter(originalCenter + sf::Vector2f(offsetX, offsetY));

	// Set the temporary view
	this->window->setView(tempView);
}

float Game::getSoundFx()
{
	return soundfxVolume;
}

float Game::clampVolume(float volume) const
{
	return std::clamp(volume, 0.f, 100.f);
}

void Game::updateShopUnlocks()
{
	bool saveChanged = false;

	if (this->gameData.gameCompleted && this->gameData.blackship != "ACQUIRED")
	{
		this->gameData.blackship = "ACQUIRED";
		saveChanged = true;
	}

	if (this->gameData.hellVictory && this->gameData.whitefire != "ACQUIRED")
	{
		this->gameData.whitefire = "ACQUIRED";
		saveChanged = true;
	}

	const bool allPurchasableItemsAcquired =
		this->gameData.bluebullet == "ACQUIRED" &&
		this->gameData.greenbullet == "ACQUIRED" &&
		this->gameData.yellowbullet == "ACQUIRED" &&
		this->gameData.purplebullet == "ACQUIRED" &&
		this->gameData.whitebullet == "ACQUIRED" &&
		this->gameData.blueship == "ACQUIRED" &&
		this->gameData.greenship == "ACQUIRED" &&
		this->gameData.yellowship == "ACQUIRED" &&
		this->gameData.purpleship == "ACQUIRED" &&
		this->gameData.redship == "ACQUIRED" &&
		this->gameData.yellowfire == "ACQUIRED" &&
		this->gameData.greenfire == "ACQUIRED";

	if (allPurchasableItemsAcquired && this->gameData.blackbullet != "ACQUIRED")
	{
		this->gameData.blackbullet = "ACQUIRED";
		saveChanged = true;
	}

	if (saveChanged)
	{
		updateGameData(this->gameData);
	}
}

// Check inputs & events
void Game::updatePollEvents()
{
	sf::Event ev;
	while (this->window->pollEvent(ev))
	{
		if (ev.type == sf::Event::Closed)
		{
			this->window->close();
		}
		if (ev.type == sf::Event::KeyPressed)
		{
			switch (this->gameState)
			{
			case MAIN_MENU:
				if (!this->quitConfirmationScreenActive)
				{
					handleMainMenuInput(ev);
				}
				else
				{
					handleQuitConfirmationInput(ev);
				}
				break;
			case PAUSED:
				handlePauseMenuInput(ev);
				break;
			case GAME_OVER:
				handleGameOverMenuInput(ev);
				break;
			case SHOP:
				handleShopMenuInput(ev);
				break;
			case SETTINGS:
				handleSettingsMenuInput(ev);
				break;
			case CREDITS:
				handleCreditsMenuInput(ev);
				break;
			case TUTORIAL:
				handleTutorialMenuInput(ev);
				break;
			case DIFFICULTY:
				handleDifficultyMenuInput(ev);
				break;
			default:
				break;
			}
		}
	}
}

// Updaters
void Game::update()
{
	this->updatePollEvents();
	this->updateTimer();

	if(this->gameState == MAIN_MENU)
	{
		this->updateTitleEffect();
		this->updateFadeEffect();
	}

	if (this->gameState == GAMEPLAY)
	{
		this->updateInput();
		this->player->update();
		this->updateCollision();
		this->updateBackground();
		this->updateBullets();
		this->updateGUI();
		this->updateItems();
		this->updateEnemies();
		this->updateCombat();
		this->updateDifficulty();
		this->updateExplosionEffect();
		this->updateHealthBar(this->player->getHp());

		if (bossIsActive)
		{
			this->updateBoss();
		}
		if (bossIsActive && Stage == 3)
		{
			boss->receivePos(this->player->getPos());
		}
		
		if (bossIsActive && boss->getHp() < 100 && boss->getHp() >= 1 && Stage == 3)
		{
			this->applyScreenShake(5.0f); // Adjust intensity as needed
		}

		this->updateFadeEffect();
	}
	if (this->gameState == DEATH_ANIMATION)
	{
		this->updateFadeEffect();
	}
	if (this->gameState == GAME_OVER)
	{
		this->updateFadeEffect();
	}
	if (this->gameState == END)
	{
		this->updateEndScreen();
	}
	if (this->gameState == HELL_BONUS_END)
	{
		this->updateHellBonusEndScreen();
	}
}

// Renders
void Game::render()
{
	this->window->clear();

	if (this->gameState == MAIN_MENU)
	{
		this->renderStartMenu(); // Render start menu if in MAIN_MENU state
	}

	if (this->gameState == GAMEPLAY)
	{
		this->renderWorld();
		this->renderGameElements();
		this->renderExplosion(*this->window);

		if(bossIsActive)
		{
			this->boss->render(*window);
		}
	}

	if (this->gameState == SHOP)
	{
		this->renderShopMenu();
	}

	if(this->gameState == GAME_OVER)
	{
		this->renderGameOverMenu();
	}

	if (this->gameState == PAUSED)
	{
		this->renderWorld();
		this->renderGameElements();

		if (bossIsActive) 
		{
			this->boss->render(*window);
		}
		this->renderPauseMenu();
		
	}

	if (this->gameState == SETTINGS && prevgameState == PAUSED)
	{
		this->renderWorld();
		this->renderGameElements();
		this->renderSettingsMenu();
	}

	if (this->gameState == SETTINGS && prevgameState == MAIN_MENU)
	{
		this->window->draw(this->startMenuBackground);
		this->renderSettingsMenu();
	}

	if (fadeState != NONE) {
		this->window->draw(fadeOverlay);
	}

	if (this->gameState == CREDITS)
	{
		this->renderCreditsMenu();
	}

	if (this->gameState == TUTORIAL)
	{
		this->window->draw(this->startMenuBackground);
		this->renderTutorialMenu();
	}

	if(this->gameState == DIFFICULTY)
	{
		this->updateDifficultyMenuEffect();
		this->renderDifficultyMenu();
	}

	if (this->gameState == DEATH_ANIMATION)
	{
		this->renderWorld();
		this->renderGameElements();
		this->renderExplosion(*this->window);

		if (bossIsActive)
		{
			this->boss->render(*window);
		}
		this->window->draw(fadeOverlay);
	
	}

	if(this->gameState == END)
	{
		this->renderEndScreen();
	}

	if (this->gameState == HELL_BONUS_END)
	{
		this->renderHellBonusEndScreen();
	}

	if(bossIsActive && Stage == 3)
	{
		this->window->setView(this->window->getDefaultView());
	}

	this->window->display();
}


