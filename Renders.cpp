#include "Game.h"
#include <algorithm>

// All render functions are here

void Game::renderCreditsMenu()
{
	constexpr float listTop = 155.f;
	constexpr float listBottom = 710.f;
	constexpr float lineHeight = 43.f;
	const float visibleHeight = listBottom - listTop;
	const float contentHeight = static_cast<float>(this->creditLines.size()) * lineHeight;
	const float maxScroll = std::max(0.f, contentHeight - visibleHeight);
	const float selectedPosition = static_cast<float>(this->selectedCreditLine) * lineHeight;
	const float scrollOffset = std::clamp(selectedPosition - visibleHeight / 2.f, 0.f, maxScroll);

	this->window->draw(this->startMenuBackground);
	this->window->draw(this->pausesettingsBackground);
	this->window->draw(this->creditsTitle);

	for (std::size_t i = 0; i < this->creditLines.size(); ++i)
	{
		const float y = listTop + static_cast<float>(i) * lineHeight - scrollOffset;
		if (y < listTop || y > listBottom - lineHeight)
		{
			continue;
		}

		const bool isHeading = this->creditLines[i].url.empty();
		this->creditLineText.setString(this->creditLines[i].label);
		this->creditLineText.setCharacterSize(isHeading ? 32 : 27);
		this->creditLineText.setStyle(isHeading ? sf::Text::Bold : sf::Text::Regular);
		if (!isHeading && this->creditLineText.getGlobalBounds().width > 900.f)
		{
			this->creditLineText.setCharacterSize(22);
		}
		this->creditLineText.setFillColor(
			static_cast<int>(i) == this->selectedCreditLine ? sf::Color::Yellow : sf::Color::White
		);
		this->creditLineText.setPosition(
			this->window->getSize().x / 2.f - this->creditLineText.getGlobalBounds().width / 2.f,
			y
		);
		this->window->draw(this->creditLineText);
	}

	this->window->draw(this->creditsStatusText);
	this->window->draw(this->creditsInstructionsText);
}

void Game::renderGUI()
{
	this->window->draw(this->pointText);
	this->window->draw(this->coinText);
	this->window->draw(this->killCounterText);
	//this->window->draw(this->playerHpBarBack);
	//this->window->draw(this->playerHpBar);
	if (!this->hideDamageAndFireRate)
	{
		this->window->draw(this->damageText);
		this->window->draw(this->fireRateText);
	}
	this->window->draw(this->timerText);
	this->window->draw(this->playerHealthBar);
	this->window->draw(this->shieldIcon);
	this->window->draw(this->shieldText);
}

void Game::renderWorld()
{

	this->window->draw(this->stageBackground);
	this->window->draw(this->stageBackground2);
}

void Game::renderGameElements()
{
	// Draw game elements
	this->window->draw(this->line1, 2, sf::Lines);
	this->window->draw(this->line2, 2, sf::Lines);
	this->window->draw(this->line3, 2, sf::Lines);
	this->window->draw(this->line4, 2, sf::Lines);

	for (auto* bullet : this->bullets)
	{
		bullet->render(this->window);
	}

	for (auto* enemy : this->enemies)
	{
		enemy->render(*this->window);
	}

	for (auto* item : this->items)
	{
		item->render(*this->window);
	}

	this->player->render(*this->window);
	this->renderGUI();
}

void Game::renderDifficultyMenu()
{

	this->easyText.setFillColor(sf::Color(255, 255, 255, 128)); // Semi-transparent white
	this->easyText.setOutlineColor(sf::Color(0, 255, 0, 128));  // Semi-transparent green
	this->normalText.setFillColor(sf::Color(255, 255, 255, 128)); // Semi-transparent white
	this->normalText.setOutlineColor(sf::Color(255, 255, 0, 128)); // Semi-transparent yellow

	if(gameData.normalVictory == true)
	{
		if (this->incognitoFlag == false) 
		{
			this->hardText.setString("HELL");
			this->hardText.setPosition(
				this->window->getSize().x / 2.f - this->hardText.getGlobalBounds().width / 2.f,
				400.f
			);
			this->incognitoFlag = true;
		}
	this->hardText.setFillColor(sf::Color(255, 255, 255, 128)); // Semi-transparent white
	this->hardText.setOutlineColor(sf::Color(255, 0, 0, 128));  // Semi-transparent red
	}
	else
	{
	this->hardText.setFillColor(sf::Color(255, 255, 255, 60));
	this->hardText.setOutlineColor(sf::Color(255, 255, 255, 60));
	}

	this->returnText.setFillColor(sf::Color(255, 255, 255, 128)); // Semi-transparent white
	this->returnText.setOutlineColor(sf::Color(255, 255, 255, 128)); // Semi-transparent white

	switch(currentSelection)
	{
	case 0:

		this->easyText.setFillColor(sf::Color(255, 255, 255, 255)); // Semi-transparent white
		this->easyText.setOutlineColor(sf::Color(0, 255, 0, 255));  // Semi-transparent green
		break;

	case 1:
		this->normalText.setFillColor(sf::Color(255, 255, 255, 255)); // Semi-transparent white
		this->normalText.setOutlineColor(sf::Color(255, 255, 0, 255)); // Semi-transparent yellow
		break;

	case 2:
		if (gameData.normalVictory == true) {
			this->hardText.setFillColor(sf::Color(255, 255, 255, 255)); // Semi-transparent white
			this->hardText.setOutlineColor(sf::Color(255, 0, 0, 255));  // Semi-transparent red
		}
		else
		{
			this->hardText.setFillColor(sf::Color(255, 255, 255, 255));
			this->hardText.setOutlineColor(sf::Color(255, 255, 255, 255));
		}
		break;

	case 3:
		this->returnText.setFillColor(sf::Color(255, 255, 255, 255)); // Semi-transparent white
		this->returnText.setOutlineColor(sf::Color(255, 255, 255, 255)); // Semi-transparent white
		break;
	}

	switch(this->difficulty)
	{
	case 0:
		this->currentText.setString("Difficulty: Easy");
		break;
	case 1:
		this->currentText.setString("Difficulty: Normal");
		break;
	case 2:
		this->currentText.setString("Difficulty: HELL");
		break;
	default:
		this->currentText.setString("Difficulty: uwu");
		break;
	}

	// Draw menu items
	this->window->draw(this->startMenuBackground);
	this->window->draw(pausesettingsBackground);
	this->window->draw(this->easyText);
	this->window->draw(this->normalText);
	this->window->draw(this->hardText);
	this->window->draw(this->returnText);
	this->window->draw(this->currentText);

}

void Game::renderExplosion(sf::RenderTarget& target)
{
	for (size_t i = 0; i < this->explosions.size(); ++i) {
		this->explosions[i]->render(target);
	}
}

void Game::renderStartMenu()
{
	this->window->draw(this->startMenuBackground);

	// Reset the color of all menu items
	this->playText.setFillColor(sf::Color::White);
	this->shopText.setFillColor(sf::Color::White);
	this->settingsText.setFillColor(sf::Color::White);
	this->creditsText.setFillColor(sf::Color::White);
	this->quitText.setFillColor(sf::Color::White);
	this->resetText.setFillColor(sf::Color::White); 
	this->tutorialText.setFillColor(sf::Color::White);

	// Highlight the selected menu item
	if (!this->quitConfirmationScreenActive)
	{
		switch (this->selectedMenuItem)
		{
		case 0:
			this->playText.setFillColor(sf::Color::Yellow);
			break;

		case 1:
			this->shopText.setFillColor(sf::Color::Yellow);
			break;

		case 2:
			this->settingsText.setFillColor(sf::Color::Yellow);
			break;

		case 3:
			this->tutorialText.setFillColor(sf::Color::Yellow);
			break;
		case 4:
			this->creditsText.setFillColor(sf::Color::Yellow);
			break;
		case 5:
			this->resetText.setFillColor(sf::Color::Yellow);
			break;
		case 6:
			this->quitText.setFillColor(sf::Color::Yellow);
			break;
		}
	}

	// Draw menu items
	this->window->draw(this->tutorialText);
	this->window->draw(this->resetText);
	this->window->draw(this->gameTitle);
	this->window->draw(this->playText);
	this->window->draw(this->shopText);
	this->window->draw(this->settingsText);
	this->window->draw(this->creditsText);
	this->window->draw(this->quitText);
	std::stringstream ss2;
	ss2 << "Coins: " << this->gameData.coins << "$";
	this->coinAmount.setString(ss2.str());
	this->window->draw(this->coinAmount);
	std::stringstream ss5;
	ss5 << "High Score: " << this->gameData.highScore;
	this->menuHighScore.setString(ss5.str());
	this->window->draw(this->menuHighScore);

	if (this->quitConfirmationScreenActive)
	{
		this->renderQuitConfirmationMenu();
	}
}

void Game::renderTutorialMenu()
{
	this->window->draw(pausesettingsBackground);
	this->window->draw(tutorialTitle);
	this->window->draw(keybindingsExplanation);
	this->window->draw(returnfromcreditsText);
}

void Game::renderShopMenu()
{
	this->window->draw(this->startMenuBackground);
	this->window->draw(this->pausesettingsBackground);
	this->window->draw(this->shopTitle);
	std::stringstream ss2;
	ss2 << "Coins: " << this->gameData.coins << "$";
	this->coinAmount.setString(ss2.str());
	this->window->draw(this->coinAmount);
	this->returnfromshopText.setFillColor(sf::Color::White);
	this->redbulletSelect.setOutlineColor(sf::Color::White);
	this->bluebulletSelect.setOutlineColor(sf::Color::White);
	this->greenbulletSelect.setOutlineColor(sf::Color::White);
	this->yellowbulletSelect.setOutlineColor(sf::Color::White);
	this->purplebulletSelect.setOutlineColor(sf::Color::White);
	this->whitebulletSelect.setOutlineColor(sf::Color::White);
	this->normalshipSelect.setOutlineColor(sf::Color::White);
	this->greenshipSelect.setOutlineColor(sf::Color::White);
	this->blueshipSelect.setOutlineColor(sf::Color::White);
	this->yellowshipSelect.setOutlineColor(sf::Color::White);
	this->purpleshipSelect.setOutlineColor(sf::Color::White);
	this->redshipSelect.setOutlineColor(sf::Color::White);
	this->normalfireSelect.setOutlineColor(sf::Color::White);
	this->yellowfireSelect.setOutlineColor(sf::Color::White);
	this->greenfireSelect.setOutlineColor(sf::Color::White);
	this->blackshipSelect.setOutlineColor(sf::Color::White);
	this->blackbulletSelect.setOutlineColor(sf::Color::White);
	this->whitefireSelect.setOutlineColor(sf::Color::White);
	renderEquiped();

	switch (this->selectedMenuItem)
	{
	case 0:
		switch (this->shopselectedMenuItem)
		{
		case 0:
			this->redbulletSelect.setOutlineColor(sf::Color::Yellow);
			this->objectPrice.setString("Acquired");
			break;
		case 1:
			this->bluebulletSelect.setOutlineColor(sf::Color::Yellow);
			this->objectPrice.setString("Price: 5000$");
			if (gameData.bluebullet == "ACQUIRED")
			{
				this->objectPrice.setString("Acquired");
			}
			break;
		case 2:
			this->greenbulletSelect.setOutlineColor(sf::Color::Yellow);
			this->objectPrice.setString("Price: 5000$");
			if (gameData.greenbullet == "ACQUIRED")
			{
				this->objectPrice.setString("Acquired");
			}
			break;
		case 3:
			this->yellowbulletSelect.setOutlineColor(sf::Color::Yellow);
			this->objectPrice.setString("Price: 5000$");
			if (gameData.yellowbullet == "ACQUIRED")
			{
				this->objectPrice.setString("Acquired");
			}
			break;
		case 4:
			this->purplebulletSelect.setOutlineColor(sf::Color::Yellow);
			this->objectPrice.setString("Price: 5000$");
			if (gameData.purplebullet == "ACQUIRED")
			{
				this->objectPrice.setString("Acquired");
			}
			break;
		case 5:
			this->whitebulletSelect.setOutlineColor(sf::Color::Yellow);
			this->objectPrice.setString("Price: 5000$");
			if (gameData.whitebullet == "ACQUIRED")
			{
				this->objectPrice.setString("Acquired");
			}
			break;
		}
		break;
	case 1:
		switch (this->shopselectedMenuItem)
		{
		case 0:
			this->normalshipSelect.setOutlineColor(sf::Color::Yellow);
			this->objectPrice.setString("Acquired");
			break;
		case 1:
			this->blueshipSelect.setOutlineColor(sf::Color::Yellow);
			this->objectPrice.setString("Price: 10000$");
			if (gameData.blueship == "ACQUIRED")
			{
				this->objectPrice.setString("Acquired");
			}
			break;
		case 2:
			this->greenshipSelect.setOutlineColor(sf::Color::Yellow);
			this->objectPrice.setString("Price: 10000$");
			if (gameData.greenship == "ACQUIRED")
			{
				this->objectPrice.setString("Acquired");
			}
			break;
		case 3:
			this->yellowshipSelect.setOutlineColor(sf::Color::Yellow);
			this->objectPrice.setString("Price: 10000$");
			if (gameData.yellowship == "ACQUIRED")
			{
				this->objectPrice.setString("Acquired");
			}
			break;
		case 4:
			this->purpleshipSelect.setOutlineColor(sf::Color::Yellow);
			this->objectPrice.setString("Price: 10000$");
			if (gameData.purpleship == "ACQUIRED")
			{
				this->objectPrice.setString("Acquired");
			}
			break;
		case 5:
			this->redshipSelect.setOutlineColor(sf::Color::Yellow);
			this->objectPrice.setString("Price: 10000$");
			if (gameData.redship == "ACQUIRED")
			{
				this->objectPrice.setString("Acquired");
			}
			break;
		}
		break;
	case 2:
		switch (this->shopselectedMenuItem)
		{
		case 0:
			this->normalfireSelect.setOutlineColor(sf::Color::Yellow);
			this->objectPrice.setString("Acquired");
			break;
		case 1:
			this->yellowfireSelect.setOutlineColor(sf::Color::Yellow);
			this->objectPrice.setString("Price: 5000$");
			if (gameData.yellowfire == "ACQUIRED")
			{
				this->objectPrice.setString("Acquired");
			}
			break;
		case 2:
			this->greenfireSelect.setOutlineColor(sf::Color::Yellow);
			this->objectPrice.setString("Price: 5000$");
			if (gameData.greenfire == "ACQUIRED")
			{
				this->objectPrice.setString("Acquired");
			}
			break;
		case 3:
			this->blackshipSelect.setOutlineColor(sf::Color::Yellow);
			this->objectPrice.setString("Beat the game");
			if (gameData.blackship == "ACQUIRED")
			{
				this->objectPrice.setString("Acquired");
			}
			break;
		case 4:
			this->blackbulletSelect.setOutlineColor(sf::Color::Yellow);
			this->objectPrice.setString("Buy all shop items");
			if (gameData.blackbullet == "ACQUIRED")
			{
				this->objectPrice.setString("Acquired");
			}
			break;
		case 5:
			this->whitefireSelect.setOutlineColor(sf::Color::Yellow);
			this->objectPrice.setString(
				gameData.normalVictory ? "Beat the game in HELL mode" : "Beat the game in ??? mode"
			);
			if (gameData.whitefire == "ACQUIRED")
			{
				this->objectPrice.setString("Acquired");
			}
			break;
		}
		break;
	case 3:
		this->returnfromshopText.setFillColor(sf::Color::Yellow);
		break;
	}
	this->objectPrice.setPosition(
		this->window->getSize().x / 2.f - this->objectPrice.getGlobalBounds().width / 2.f,
		this->window->getSize().y / 2.f - this->objectPrice.getGlobalBounds().height / 2.f - 250.f
	);
	this->window->draw(this->objectPrice);
	this->window->draw(this->redbulletSelect);
	this->window->draw(this->bluebulletSelect);
	this->window->draw(this->greenbulletSelect);
	this->window->draw(this->yellowbulletSelect);
	this->window->draw(this->purplebulletSelect);
	this->window->draw(this->whitebulletSelect);
	this->window->draw(this->normalshipSelect);
	this->window->draw(this->greenshipSelect);
	this->window->draw(this->blueshipSelect);
	this->window->draw(this->yellowshipSelect);
	this->window->draw(this->purpleshipSelect);
	this->window->draw(this->redshipSelect);
	this->window->draw(this->normalfireSelect);
	this->window->draw(this->yellowfireSelect);
	this->window->draw(this->greenfireSelect);
	this->window->draw(this->blackshipSelect);
	this->window->draw(this->blackbulletSelect);
	this->window->draw(this->whitefireSelect);
	this->window->draw(this->returnfromshopText);
}

void Game::renderEquiped()
{
	if (gameData.equipedbullet == 0)
	{
		this->redbulletSelect.setOutlineColor(sf::Color::Green);
	}
	else if (gameData.equipedbullet == 1)
	{
		this->bluebulletSelect.setOutlineColor(sf::Color::Green);
	}
	else if (gameData.equipedbullet == 2)
	{
		this->greenbulletSelect.setOutlineColor(sf::Color::Green);
	}
	else if (gameData.equipedbullet == 3)
	{
		this->yellowbulletSelect.setOutlineColor(sf::Color::Green);
	}
	else if (gameData.equipedbullet == 4)
	{
		this->purplebulletSelect.setOutlineColor(sf::Color::Green);
	}
	else if (gameData.equipedbullet == 5)
	{
		this->whitebulletSelect.setOutlineColor(sf::Color::Green);
	}
	else if (gameData.equipedbullet == 6)
	{
		this->blackbulletSelect.setOutlineColor(sf::Color::Green);
	}

	if (gameData.equipedship == 0)
	{
		this->normalshipSelect.setOutlineColor(sf::Color::Green);
	}
	else if (gameData.equipedship == 1)
	{
		this->blueshipSelect.setOutlineColor(sf::Color::Green);
	}
	else if (gameData.equipedship == 2)
	{
		this->greenshipSelect.setOutlineColor(sf::Color::Green);
	}
	else if (gameData.equipedship == 3)
	{
		this->yellowshipSelect.setOutlineColor(sf::Color::Green);
	}
	else if (gameData.equipedship == 4)
	{
		this->purpleshipSelect.setOutlineColor(sf::Color::Green);
	}
	else if (gameData.equipedship == 5)
	{
		this->redshipSelect.setOutlineColor(sf::Color::Green);
	}
	else if (gameData.equipedship == 6)
	{
		this->blackshipSelect.setOutlineColor(sf::Color::Green);
	}

	if (gameData.equipedfire == 0)
	{
		this->normalfireSelect.setOutlineColor(sf::Color::Green);
	}
	else if (gameData.equipedfire == 1)
	{
		this->yellowfireSelect.setOutlineColor(sf::Color::Green);
	}
	else if (gameData.equipedfire == 2)
	{
		this->greenfireSelect.setOutlineColor(sf::Color::Green);
	}
	else if (gameData.equipedfire == 3)
	{
		this->whitefireSelect.setOutlineColor(sf::Color::Green);
	}
}

void Game::renderQuitConfirmationMenu()
{
	this->window->draw(this->pausesettingsBackground);
	this->window->draw(this->pausesettingsBackground);
	this->yesCloseApplication.setFillColor(sf::Color::White);
	this->noKeepPlaying.setFillColor(sf::Color::White);

	switch (this->selectedMenuItem)
	{
	case 0:
		this->yesCloseApplication.setFillColor(sf::Color::Yellow);
		break;

	case 1:
		this->noKeepPlaying.setFillColor(sf::Color::Yellow);
		break;
	}

	this->window->draw(areYouSureQuestion);
	this->window->draw(yesCloseApplication);
	this->window->draw(noKeepPlaying);
}

void Game::renderPauseMenu()
{
	this->window->draw(this->pausesettingsBackground);
	// Reset the color of all menu items
	this->resumeText.setFillColor(sf::Color::White);
	this->pausesettingsText.setFillColor(sf::Color::White);
	this->mainmenuText.setFillColor(sf::Color::White);

	// Highlight the selected menu item
	switch (this->selectedMenuItem)
	{
	case 0:
		this->resumeText.setFillColor(sf::Color::Yellow);
		break;

	case 1:
		this->pausesettingsText.setFillColor(sf::Color::Yellow);
		break;

	case 2:
		this->mainmenuText.setFillColor(sf::Color::Yellow);
		break;
	}

	// Draw menu items
	this->window->draw(this->pauseTitle);
	this->window->draw(this->resumeText);
	this->window->draw(this->pausesettingsText);
	this->window->draw(this->mainmenuText);

}

void Game::renderGameOverMenu()
{
	this->mainmenuText.setFillColor(sf::Color::Yellow);

	this->window->draw(this->gameOverBackground);
	this->window->draw(this->gameOverText);
	this->window->draw(this->mainmenuText);
	this->window->draw(this->scoreAchieved);
	this->window->draw(this->lastHighScore);
}

void Game::renderEndScreen()
{
	this->window->draw(this->endBackground);
	this->window->draw(this->congratText);
	this->window->draw(this->earthSprite);

}

void Game::renderHellBonusEndScreen()
{
	this->window->draw(this->hellBonusBackground);
}

void Game::renderSettingsMenu()
{
	this->window->draw(this->pausesettingsBackground);
	this->musicvolumeText.setFillColor(sf::Color::White);
	this->soundfxText.setFillColor(sf::Color::White);
	this->hideStatsText.setFillColor(sf::Color::White);
	this->statsPositionText.setFillColor(sf::Color::White);
	this->backText.setFillColor(sf::Color::White);
	this->musicvolumeBorder.setOutlineColor(sf::Color::White);
	this->musicvolumeIndicator.setFillColor(sf::Color(255, 255, 255, 75));
	this->soundfxvolumeBorder.setOutlineColor(sf::Color::White);
	this->soundfxvolumeIndicator.setFillColor(sf::Color(255, 255, 255, 75));

	this->hideStatsText.setString(
		this->hideDamageAndFireRate ? "Hide DMG & Bullets/s: ON" : "Hide DMG & Bullets/s: OFF"
	);
	this->hideStatsText.setPosition(
		this->window->getSize().x / 2.f - this->hideStatsText.getGlobalBounds().width / 2.f,
		this->window->getSize().y / 2.f - this->hideStatsText.getGlobalBounds().height / 2.f + 130.f
	);

	this->statsPositionText.setString(
		this->playerStatsUpperRight ? "Player Stats Position: Upper Right" : "Player Stats Position: Bottom Left"
	);
	this->statsPositionText.setPosition(
		this->window->getSize().x / 2.f - this->statsPositionText.getGlobalBounds().width / 2.f,
		this->window->getSize().y / 2.f - this->statsPositionText.getGlobalBounds().height / 2.f + 180.f
	);

	// Highlight the selected menu item
	switch (this->selectedMenuItem)
	{
	case 0:
		this->musicvolumeText.setFillColor(sf::Color::Yellow);
		this->musicvolumeBorder.setOutlineColor(sf::Color::Yellow);
		this->musicvolumeIndicator.setFillColor(sf::Color(255, 255, 0, 75));
		break;

	case 1:
		this->soundfxText.setFillColor(sf::Color::Yellow);
		this->soundfxvolumeBorder.setOutlineColor(sf::Color::Yellow);
		this->soundfxvolumeIndicator.setFillColor(sf::Color(255, 255, 0, 75));
		break;
	case 2:
		this->hideStatsText.setFillColor(sf::Color::Yellow);
		break;
	case 3:
		this->statsPositionText.setFillColor(sf::Color::Yellow);
		break;
	case 4:
		this->backText.setFillColor(sf::Color::Yellow);
		break;
	}

	// Draw menu items
	this->window->draw(this->settingsTitle);
	this->window->draw(this->musicvolumeText);
	this->window->draw(this->musicvolumeBorder);
	this->window->draw(this->musicvolumeIndicator);
	this->window->draw(this->soundfxText);
	this->window->draw(this->soundfxvolumeBorder);
	this->window->draw(this->soundfxvolumeIndicator);
	this->window->draw(this->hideStatsText);
	this->window->draw(this->statsPositionText);
	this->window->draw(this->backText);
}
