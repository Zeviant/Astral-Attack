#include "Game.h"
#include <SFML/Window/Clipboard.hpp>
#include <Windows.h>
#include <shellapi.h>

namespace
{
	bool openCreditLink(const std::string& url)
	{
		const HINSTANCE result = ShellExecuteA(nullptr, "open", url.c_str(), nullptr, nullptr, SW_SHOWNORMAL);
		return reinterpret_cast<INT_PTR>(result) > 32;
	}
}

// Handle inputs in main menu
void Game::handleMainMenuInput(const sf::Event& ev)
{
	if (ev.key.code == sf::Keyboard::Up)
	{
		if (this->selectedMenuItem > 0)
		{
			this->menuSound.play();
			this->selectedMenuItem--;
		}
	}
	if (ev.key.code == sf::Keyboard::Down)
	{
		if (this->selectedMenuItem < 6)
		{
			this->menuSound.play();
			this->selectedMenuItem++;
		}
	}
	if (ev.key.code == sf::Keyboard::Return)
	{
		switch (this->selectedMenuItem)
		{
		case 0:
			this->initializeMusic();
			this->initializePlayer();
			this->gameState = GAMEPLAY;
			this->menuMusic.stop();
			this->clock.restart();
			this->elapsedTime = 0;
			this->minutes = 0;
			this->seconds = 0;
			break;
		case 1:
			this->gameState = SHOP;
			this->selectedMenuItem = 0;
			break;
		case 2:
			this->prevgameState = this->gameState;
			this->gameState = SETTINGS;
			this->selectedMenuItem = 0;
			break;
		case 3:
			this->gameState = TUTORIAL;
			this->selectedMenuItem = 0;
			break;
		case 4:
			this->gameState = CREDITS;
			this->selectedMenuItem = 0;
			break;
		case 5:
			this->gameState = DIFFICULTY;
			this->currentSelection = 0;
			break;
		case 6:
			this->window->close();
			break;
		default:
			break;
		}
	}
	if (ev.key.code == sf::Keyboard::Escape)
	{
		this->quitConfirmationScreenActive = true;
		this->selectedMenuItem = 0;
	}
}

// Handle inputs in tutorial menu
void Game::handleTutorialMenuInput(const sf::Event& ev)
{
	if (ev.key.code == sf::Keyboard::Escape)
	{
		this->gameState = MAIN_MENU;
		this->selectedMenuItem = 0;
	}

	if (ev.key.code == sf::Keyboard::Return)
	{
		this->gameState = MAIN_MENU;
		this->selectedMenuItem = 0;
	}

	if (ev.key.code == sf::Keyboard::Enter)
	{
		this->gameState = MAIN_MENU;
		this->selectedMenuItem = 0;
	}
}

// Handle quit menu
void Game::handleQuitConfirmationInput(const sf::Event& ev)
{
	if (ev.key.code == sf::Keyboard::Up)
	{
		if (this->selectedMenuItem > 0)
		{
			this->menuSound.play();
			this->selectedMenuItem--;
		}
	}
	if (ev.key.code == sf::Keyboard::Down)
	{
		if (this->selectedMenuItem < 1)
		{
			this->menuSound.play();
			this->selectedMenuItem++;
		}
	}
	if (ev.key.code == sf::Keyboard::Return)
	{
		switch (this->selectedMenuItem)
		{
		case 0:
			this->window->close();
			break;
		case 1:
			this->quitConfirmationScreenActive = false;
			this->selectedMenuItem = 0;
			break;
		}
	}
	if (ev.key.code == sf::Keyboard::Escape)
	{
		this->quitConfirmationScreenActive = false;
	}
}

// Handle inputs in credits menu
void Game::handleCreditsMenuInput(const sf::Event& ev)
{
	if (ev.key.code == sf::Keyboard::Up)
	{
		for (int i = this->selectedCreditLine - 1; i >= 0; --i)
		{
			if (!this->creditLines[static_cast<std::size_t>(i)].url.empty())
			{
				this->selectedCreditLine = i;
				this->creditsStatusText.setString("");
				this->menuSound.play();
				break;
			}
		}
	}

	if (ev.key.code == sf::Keyboard::Down)
	{
		for (std::size_t i = static_cast<std::size_t>(this->selectedCreditLine + 1); i < this->creditLines.size(); ++i)
		{
			if (!this->creditLines[i].url.empty())
			{
				this->selectedCreditLine = static_cast<int>(i);
				this->creditsStatusText.setString("");
				this->menuSound.play();
				break;
			}
		}
	}

	if (ev.key.code == sf::Keyboard::Return || ev.key.code == sf::Keyboard::Enter)
	{
		const std::string& url = this->creditLines[static_cast<std::size_t>(this->selectedCreditLine)].url;
		sf::Clipboard::setString(sf::String::fromUtf8(url.begin(), url.end()));
		this->creditsStatusText.setString("Copied to clipboard!");
		openCreditLink(url);
	}

	if (ev.key.code == sf::Keyboard::Escape)
	{
		this->gameState = MAIN_MENU;
		this->selectedMenuItem = 0;
		this->selectedCreditLine = 1;
		this->creditsStatusText.setString("");
	}
}

// Handle inputs in shop menu
void Game::handleShopMenuInput(const sf::Event& ev)
{
	if (ev.key.code == sf::Keyboard::Escape)
	{
		this->gameState = MAIN_MENU;
	}
	if (ev.key.code == sf::Keyboard::Up)
	{
		if (this->selectedMenuItem > 0)
		{
			this->menuSound.play();
			this->selectedMenuItem--;
		}
	}
	if (ev.key.code == sf::Keyboard::Down)
	{
		if (this->selectedMenuItem < 3)
		{
			this->menuSound.play();
			this->selectedMenuItem++;
		}
	}
	if (this->selectedMenuItem != 3)
	{
		if (ev.key.code == sf::Keyboard::Left)
		{
			if (this->shopselectedMenuItem > 0)
			{
				this->menuSound.play();
				this->shopselectedMenuItem--;
			}
		}
		if (ev.key.code == sf::Keyboard::Right)
		{
			if (this->shopselectedMenuItem < 5)
			{
				this->menuSound.play();
				this->shopselectedMenuItem++;
			}
		}
	}
	if (ev.key.code == sf::Keyboard::Return)
	{
		switch (this->selectedMenuItem)
		{
		case 0:
			switch (this->shopselectedMenuItem)
			{
			case 0:
				gameData.equipedbullet = 0;
				updateGameData(gameData);
				setBulletColor(gameData.equipedbullet);
				this->equipSound.play();
				break;
			case 1:
				if (gameData.bluebullet == "ACQUIRED")
				{
					gameData.equipedbullet = 1;
					updateGameData(gameData);
					setBulletColor(gameData.equipedbullet);
					this->equipSound.play();
				}
				else if (gameData.bluebullet == "NULL" && gameData.coins >= 5000)
				{
					gameData.bluebullet = "ACQUIRED";
					gameData.coins -= 5000;
					this->buySound.play();
				}
				else
				{
					this->noMoneySound.play();
				}
				break;
			case 2:
				if (gameData.greenbullet == "ACQUIRED")
				{
					gameData.equipedbullet = 2;
					updateGameData(gameData);
					setBulletColor(gameData.equipedbullet);
					this->equipSound.play();
				}
				else if (gameData.greenbullet == "NULL" && gameData.coins >= 5000)
				{
					gameData.greenbullet = "ACQUIRED";
					gameData.coins -= 5000;
					this->buySound.play();
				}
				else
				{
					this->noMoneySound.play();
				}
				break;
			case 3:
				if (gameData.yellowbullet == "ACQUIRED")
				{
					gameData.equipedbullet = 3;
					updateGameData(gameData);
					setBulletColor(gameData.equipedbullet);
					this->equipSound.play();
				}
				else if (gameData.yellowbullet == "NULL" && gameData.coins >= 5000)
				{
					gameData.yellowbullet = "ACQUIRED";
					gameData.coins -= 5000;
					this->buySound.play();
				}
				else
				{
					this->noMoneySound.play();
				}
				break;
			case 4:
				if (gameData.purplebullet == "ACQUIRED")
				{
					gameData.equipedbullet = 4;
					updateGameData(gameData);
					setBulletColor(gameData.equipedbullet);
					this->equipSound.play();
				}
				else if (gameData.purplebullet == "NULL" && gameData.coins >= 5000)
				{
					gameData.purplebullet = "ACQUIRED";
					gameData.coins -= 5000;
					this->buySound.play();
				}
				else
				{
					this->noMoneySound.play();
				}
				break;
			case 5:
				if (gameData.whitebullet == "ACQUIRED")
				{
					gameData.equipedbullet = 5;
					updateGameData(gameData);
					setBulletColor(gameData.equipedbullet);
					this->equipSound.play();
				}
				else if (gameData.whitebullet == "NULL" && gameData.coins >= 5000)
				{
					gameData.whitebullet = "ACQUIRED";
					gameData.coins -= 5000;
					this->buySound.play();
				}
				else
				{
					this->noMoneySound.play();
				}
				break;
			}
			break;
		case 1:
			switch (this->shopselectedMenuItem)
			{
			case 0:
				gameData.equipedship = 0;
				updateGameData(gameData);
				this->player->setShipColor(gameData.equipedship);
				this->player->setFireColor(gameData.equipedfire);
				this->setBulletColor(gameData.equipedbullet);
				this->equipSound.play();
				break;
			case 1:
				if (gameData.blueship == "ACQUIRED")
				{
					gameData.equipedship = 1;
					updateGameData(gameData);
					this->player->setShipColor(gameData.equipedship);
					this->equipSound.play();
				}
				else if (gameData.blueship == "NULL" && gameData.coins >= 10000)
				{
					gameData.blueship = "ACQUIRED";
					gameData.coins -= 10000;
					this->buySound.play();
				}
				else
				{
					this->noMoneySound.play();
				}
				break;
			case 2:
				if (gameData.greenship == "ACQUIRED")
				{
					gameData.equipedship = 2;
					updateGameData(gameData);
					this->player->setShipColor(gameData.equipedship);
					this->equipSound.play();
				}
				else if (gameData.greenship == "NULL" && gameData.coins >= 10000)
				{
					gameData.greenship = "ACQUIRED";
					gameData.coins -= 10000;
					this->buySound.play();
				}
				else
				{
					this->noMoneySound.play();
				}
				break;
			case 3:
				if (gameData.yellowship == "ACQUIRED")
				{
					gameData.equipedship = 3;
					updateGameData(gameData);
					this->player->setShipColor(gameData.equipedship);
					this->equipSound.play();
				}
				else if (gameData.yellowship == "NULL" && gameData.coins >= 10000)
				{
					gameData.yellowship = "ACQUIRED";
					gameData.coins -= 10000;
					this->buySound.play();
				}
				else
				{
					this->noMoneySound.play();
				}
				break;
			case 4:
				if (gameData.purpleship == "ACQUIRED")
				{
					gameData.equipedship = 4;
					updateGameData(gameData);
					this->player->setShipColor(gameData.equipedship);
					this->equipSound.play();
				}
				else if (gameData.purpleship == "NULL" && gameData.coins >= 10000)
				{
					gameData.purpleship = "ACQUIRED";
					gameData.coins -= 10000;
					this->buySound.play();
				}
				else
				{
					this->noMoneySound.play();
				}
				break;
			case 5:
				if (gameData.redship == "ACQUIRED")
				{
					gameData.equipedship = 5;
					updateGameData(gameData);
					this->player->setShipColor(gameData.equipedship);
					this->equipSound.play();
				}
				else if (gameData.redship == "NULL" && gameData.coins >= 10000)
				{
					gameData.redship = "ACQUIRED";
					gameData.coins -= 10000;
					this->buySound.play();
				}
				else
				{
					this->noMoneySound.play();
				}
				break;
			}
			break;
		case 2:
			switch (this->shopselectedMenuItem)
			{
			case 0:
				gameData.equipedfire = 0;
				updateGameData(gameData);
				this->player->setFireColor(gameData.equipedfire);
				this->equipSound.play();
				break;
			case 1:
				if (this->gameData.yellowfire == "ACQUIRED")
				{
					gameData.equipedfire = 1;
					updateGameData(gameData);
					this->player->setFireColor(gameData.equipedfire);
					this->equipSound.play();
				}
				else if (this->gameData.yellowfire == "NULL" && gameData.coins >= 5000)
				{
					gameData.yellowfire = "ACQUIRED";
					gameData.coins -= 5000;
					this->buySound.play();
				}
				else
				{
					this->noMoneySound.play();
				}
				break;
			case 2:
				if (this->gameData.greenfire == "ACQUIRED")
				{
					gameData.equipedfire = 2;
					updateGameData(gameData);
					this->player->setFireColor(gameData.equipedfire);
					this->equipSound.play();
				}
				else if (this->gameData.greenfire == "NULL" && gameData.coins >= 5000)
				{
					gameData.greenfire = "ACQUIRED";
					gameData.coins -= 5000;
					this->buySound.play();
				}
				else
				{
					this->noMoneySound.play();
				}
				break;
			case 3:
				if (this->gameData.blackship == "ACQUIRED")
				{
					gameData.equipedship = 6;
					updateGameData(gameData);
					this->player->setShipColor(gameData.equipedship);
					this->equipSound.play();
				}
				break;
			case 4:
				if (gameData.blackbullet == "ACQUIRED")
				{
					gameData.equipedbullet = 6;
					updateGameData(gameData);
					setBulletColor(gameData.equipedbullet);
					this->equipSound.play();
				}
				break;
			case 5:
				if (this->gameData.whitefire == "ACQUIRED")
				{
					gameData.equipedfire = 3;
					updateGameData(gameData);
					this->player->setFireColor(gameData.equipedfire);
					this->equipSound.play();
				}
				break;
			}
			break;
		case 3:
			this->gameState = MAIN_MENU;
			this->selectedMenuItem = 0;
			break;
		default:
			break;
		}

		this->updateShopUnlocks();
		updateGameData(this->gameData);
	}
}

// Handle inputs in pause menu
void Game::handlePauseMenuInput(const sf::Event& ev)
{
	if (ev.key.code == sf::Keyboard::Up)
	{
		if (this->selectedMenuItem > 0)
		{
			this->menuSound.play();
			this->selectedMenuItem--;
		}
	}
	if (ev.key.code == sf::Keyboard::Down)
	{
		if (this->selectedMenuItem < 2)
		{
			this->menuSound.play();
			this->selectedMenuItem++;
		}
	}
	if (ev.key.code == sf::Keyboard::Return)
	{
		switch (this->selectedMenuItem)
		{
		case 0:
			this->gameState = GAMEPLAY;
			this->menuMusic.stop();
			this->stageMusic.play();
			this->selectedMenuItem = 0;
			break;
		case 1:
			this->prevgameState = this->gameState;
			this->gameState = SETTINGS;
			this->selectedMenuItem = 0;
			break;
		case 2:
			this->reset();
			this->gameState = MAIN_MENU;
			this->stageMusic.stop();
			this->menuMusic.play();
			this->selectedMenuItem = 0;
			break;
		default:
			break;
		}
	}
}

// Handle inputs in game over menu
void Game::handleGameOverMenuInput(const sf::Event& ev)
{
	if (ev.key.code == sf::Keyboard::Escape)
	{
		updateGameData(gameData);
		this->reset();
		this->gameState = MAIN_MENU;
		this->menuMusic.play();
		this->gameOverMusic.stop();
	}
	if (ev.key.code == sf::Keyboard::Return)
	{
		updateGameData(gameData);
		this->reset();
		this->gameState = MAIN_MENU;
		this->menuMusic.play();
		this->gameOverMusic.stop();
	}
}

// Handle inputs in settings menu
void Game::handleSettingsMenuInput(const sf::Event& ev)
{
	if (ev.key.code == sf::Keyboard::Escape)
	{
		this->gameState = this->prevgameState;
		this->selectedMenuItem = 0;
		if (this->prevgameState == GAMEPLAY)
		{
			this->stageMusic.play();
		}
	}
	if (ev.key.code == sf::Keyboard::Up)
	{
		if (this->selectedMenuItem > 0)
		{
			this->menuSound.play();
			this->selectedMenuItem--;
		}
	}
	if (ev.key.code == sf::Keyboard::Down)
	{
		if (this->selectedMenuItem < 4)
		{
			this->menuSound.play();
			this->selectedMenuItem++;
		}
	}
	switch (this->selectedMenuItem)
	{
	case 0:
		if (ev.key.code == sf::Keyboard::Left)
		{
			musicVolume = std::max(musicVolume - 0.5f, 0.0f);
			updateMusicVolume();
		}
		if (ev.key.code == sf::Keyboard::Right)
		{
			musicVolume = std::min(musicVolume + 0.5f, 10.0f);
			updateMusicVolume();
		}
		break;
	case 1:
		if (ev.key.code == sf::Keyboard::Left)
		{
			soundfxVolume = std::max(soundfxVolume - 0.5f, 0.0f);
			updateSoundFXVolume();
		}
		if (ev.key.code == sf::Keyboard::Right)
		{
			soundfxVolume = std::min(soundfxVolume + 0.5f, 10.0f);
			updateSoundFXVolume();
		}
		break;
	case 2:
		if (ev.key.code == sf::Keyboard::Left || ev.key.code == sf::Keyboard::Right || ev.key.code == sf::Keyboard::Return)
		{
			this->hideDamageAndFireRate = !this->hideDamageAndFireRate;
			this->menuSound.play();
		}
		break;
	case 3:
		if (ev.key.code == sf::Keyboard::Left || ev.key.code == sf::Keyboard::Right || ev.key.code == sf::Keyboard::Return)
		{
			this->playerStatsUpperRight = !this->playerStatsUpperRight;
			this->menuSound.play();
		}
		break;
	case 4:
		if (ev.key.code == sf::Keyboard::Return)
		{
			this->gameState = this->prevgameState;
			if (this->prevgameState == GAMEPLAY)
			{
				this->stageMusic.play();
			}
			this->selectedMenuItem = 0;
		}
		break;
	default:
		break;
	}
}

void Game::handleDifficultyMenuInput(const sf::Event& ev)
{

	if (ev.key.code == sf::Keyboard::Escape)
	{
		this->selectedMenuItem = 0;
		this->gameState = MAIN_MENU; // Return to main menu
	}

	if (ev.key.code == sf::Keyboard::Up)
	{
		if (this->currentSelection > 0)
		{
			this->menuSound.play();
			this->currentSelection--;
		}
	}
	if (ev.key.code == sf::Keyboard::Down)
	{
		if (this->currentSelection < 3)
		{
			this->menuSound.play();
			this->currentSelection++;
		}
	}
	if (ev.key.code == sf::Keyboard::Return)
	{
		switch (this->currentSelection)
		{
		case 0:
			this->difficultySetSound.play();
			this->difficulty = 0;
			std::cout << difficulty;
			break;
		case 1:
			this->difficultySetSound.play();
			this->difficulty = 1;
			std::cout << difficulty;
			break;
		case 2:
			if (gameData.normalVictory == true)
			{
			this->difficultySetSound.play();
				this->difficulty = 2;
				std::cout << difficulty;
			}
			else
			{
				this->noMoneySound.play();
			}
			break;
		case 3:
			this->selectedMenuItem = 0;
			this->gameState = MAIN_MENU;
		}
	}
}
