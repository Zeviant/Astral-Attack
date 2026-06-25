#include "Game.h"

// Game events & progression
void Game::updateDifficulty()
{
	// Debug stage
	if(Stage == 0)
	{
		this->meteorSpawnRate = 5.0f;
	}

	// Stage 1 events
	if (Stage == 1) {

		if (elapsedTime >= 2.f && elapsedTime <= 3.f)
		{
			if(difficulty == 0)
			{
				this->enemySpawnRate = 1.5f;
			}

			if(difficulty == 2)
			{
				this->enemySpawnRate = 2.56f;
				this->meteorSpawnRate = 0.3f;
			}
		}

		if (elapsedTime >= 30.f && elapsedTime <= 31.f)
		{
			if(difficulty == 0)
			{
				this->meteorSpawnRate = 0.15f;
			}


			if(difficulty == 1)
			{
				this->meteorSpawnRate = 0.3f;
				this->doubleMeteorChance = 10;
			}
			
			if(difficulty == 2)
			{
				this->meteorSpawnRate = 0.55f;
				this->doubleMeteorChance = 25;
			}
			this->tripleMeteorChance = 0;
		}

		if (elapsedTime >= 60.f && elapsedTime <= 61.f)
		{
			if(difficulty == 0)
			{
				this->meteorSpawnRate = 0.3f;
				this->doubleMeteorChance = 10;
			}

			if(difficulty == 1)
			{
				this->meteorSpawnRate = 0.75f;
				this->doubleMeteorChance = 15;
			}

			if(difficulty == 2)
			{
				this->meteorSpawnRate = 0.85f;
				this->doubleMeteorChance = 30;
			}
		}

		if (elapsedTime >= 105.f && elapsedTime <= 106.f)
		{
			this->meteorSpawnRate = 0.f;
			this->doubleMeteorChance = 10;
			this->dpsItemSpawnRate = 0.f;
			this->enemySpawnRate = 0.f;
			this->backgroundScrollSpeed = 3.0f;
			cutscene = true;
		}

		// Boss spawn
		if (elapsedTime >= 110.f && elapsedTime <= 111.f)
		{
			if (!bossIsActive) {
				if (!this->stageMusic.openFromFile("Music/BossMusic.ogg"))
				{
					std::cout << "ERROR::BOSSMUSIC::FAILED_TO_LOAD" << "\n";
				}
				this->stageMusic.play();

				bossIsActive = true;
				this->boss->spawn(sf::Vector2f(603.f, -200.f), sf::Vector2f(603.f, 300.f));
			}
		}

		if (elapsedTime >= 112.f && elapsedTime <= 126.5f)
		{
			this->player->setAttackCooldown(0);
		}

		if (elapsedTime >= 126.5f && elapsedTime <= 128.f)
		{
			startShooting = true;
			cutscene = false;

			if(difficulty == 2)
			{
				this->meteorSpawnRate = 0.25f;
			}
		}

		if (((elapsedTime >= 158.f && elapsedTime <= 159.f && startShooting) or (this->boss->getHp() <= 50)) && checkerOne)
		{
			if(difficulty == 0)
			{
				this->bossAttackCooldownMax = 55.f;
			}

			if (difficulty == 1) 
			{
				this->meteorSpawnRate = 0.25f;
				this->bossAttackCooldownMax = 52.f;
			}

			if (difficulty == 2) 
			{
				this->meteorSpawnRate = 0.5f;
				this->bossAttackCooldownMax = 50.f;
			}

		}

		if (elapsedTime >= 195.f && elapsedTime <= 196.f && startShooting)
		{
			this->meteorSpawnRate = 0.8f;
			this->bossAttackCooldownMax = 30.f;

		}

		// Boss defeat rewards & start stage transition
		if (bossDefeated && checkerOne)
		{
			this->stageMusic.stop();
			this->explosionSound.play();
			this->startShooting = false;
			this->meteorSpawnRate = 0.f;
			this->timeStamp = elapsedTime;
			this->stageTransition = true;
			bossDefeated = false;
			if (difficulty == 0) {
				this->points = points + 25000;
				this->addCoins(250);
			}
			if (difficulty == 1)
			{
				this->points = points + 50000;
				this->addCoins(500);
			}
			if(difficulty == 2)
			{
				this->points = points + 75000;
				this->addCoins(750);
			}

			this->enemyKillCounter = enemyKillCounter + 50;
			checkerOne = false;
			this->backgroundScrollSpeed = 2.0f;
			cutscene = true;

		}

		if (elapsedTime >= timeStamp + 5.f && stageTransition)
		{
			this->healthItemSpawnRate = 0.5f;
			this->dpsItemSpawnRate = 1.5f;
			bossIsActive = false;
			stageTransition = false;
			victoryTune.play();
			stage1End = true;
			this->backgroundScrollSpeed = 1.f;
			this->meteorSpawnRate = 0.f;

			if (!this->stageMusic.openFromFile("Music/empty.mp3"))
			{
				std::cout << "ERROR::EMPTY::FAILED_TO_LOAD" << "\n";
			}
			this->stageMusic.play();
		}

		if (elapsedTime >= timeStamp + 10.f && checkerThree && stage1End)
		{
			this->healthItemSpawnRate = 0.f;
			this->dpsItemSpawnRate = 0.f;
			checkerThree = false;
			this->meteorSpawnRate = 0.f;

		}

		if (elapsedTime >= timeStamp + 13.f && checkerTwo && stage1End)
		{
			this->triggerFadeEffect();
			checkerTwo = false;
			this->meteorSpawnRate = 0.f;
			
		}

		if (elapsedTime >= timeStamp + 14.f && stage1End && checkerFour)
		{
			this->backgroundScrollSpeed = 75.f;
			this->meteorSpawnRate = 0.f;

		}

		if (elapsedTime >= timeStamp + 15.f && stage1End && checkerFour)
		{
			this->stageBackground.setTexture(this->stage2BackgroundTexture);
			this->stageBackground2.setTexture(this->stage2BackgroundTexture);
			this->stageBackground2.setPosition(0, this->stageBackground.getGlobalBounds().height);
			this->checkerFour = false;

		}

		// Stage transition complete
		if (elapsedTime >= timeStamp + 16.f && stage1End)
		{
			this->backgroundScrollSpeed = 1.5f;
			timeStamp2 = elapsedTime;
			stage1End = false;
			this->meteorSpawnRate = 0.f;
			bossDefeated = false;
			Stage = 2;


		}

		
	}

	// Stage 2 events
	if(Stage == 2)
	{
		if(elapsedTime >= timeStamp2 + 1.f  && elapsedTime <= timeStamp2 + 2.f)
		{
			checkerOne = true;
			checkerTwo = true;
			checkerThree = true;
			checkerFour = true;
			checkerFive = true;
			this->healthItemSpawnRate = 0.0167f;
			this->enemySpawnRate = 0.f;
			this->horizontalEnemySpawnRate = 0.f;
			this->meteorSpawnRate = 0.f;
			this->doubleMeteorChance = 0.f;
			this->tripleMeteorChance = 0.f;
			this->dpsItemSpawnRate = 0.075f;
			this->healthItemSpawnTimer = 0.f;
			this->boss = new Boss(375.f, 10.5f, 2);
			cutscene = false;
		}

		if(elapsedTime >= timeStamp2 + 7.f && checkerOne)
		{

			if(difficulty == 0)
			{
				this->enemySpawnRate = 1.35f;
				this->meteorSpawnRate = 0.25f;
				this->doubleMeteorChance = 10.f;
			}
			
			if(difficulty == 1)
			{
				this->enemySpawnRate = 2.0f;
				this->meteorSpawnRate = 0.25f;
				this->doubleMeteorChance = 25.f;
			}

			if(difficulty == 2)
			{
				this->enemySpawnRate = 2.0f;
				this->meteorSpawnRate = 0.35f;
				this->doubleMeteorChance = 35.f;
			}


			if (!this->stageMusic.openFromFile("Music/WithoutFear.ogg"))
			{
				std::cout << "ERROR::WITHOUT_FEAR_MUSIC::FAILED_TO_LOAD" << "\n";
			}
			this->stageMusic.play();
			checkerOne = false;

		}

		if (elapsedTime >= timeStamp2 + 31.f && elapsedTime <= timeStamp2 + 32.f)
		{
			if (difficulty == 0)
			{
				this->enemySpawnRate = 1.25f;
				this->horizontalEnemySpawnRate = 0.2f;
				this->meteorSpawnRate = 0.5f;
			}

			if (difficulty == 1) 
			{
				this->enemySpawnRate = 1.75f;
				this->horizontalEnemySpawnRate = 0.3f;
				this->meteorSpawnRate = 0.7f;
			}

			if (difficulty == 2)
			{
				this->enemySpawnRate = 1.9f;
				this->horizontalEnemySpawnRate = 0.4f;
				this->meteorSpawnRate = 0.8f;
			}
		}

		if (elapsedTime >= timeStamp2 + 55.f && checkerTwo)
		{
			if (difficulty == 0)
			{
				this->doubleMeteorChance = 20.f;
				this->horizontalEnemySpawnRate = 0.40f;
			
			}

			if (difficulty == 1) 
			{
				this->doubleMeteorChance = 40.f;
				this->horizontalEnemySpawnRate = 0.70f;
			}

			if (difficulty == 2)
			{
				this->doubleMeteorChance = 50.f;
				this->horizontalEnemySpawnRate = 0.80f;
			}
			checkerTwo = false;
		}

		if (elapsedTime >= timeStamp2 + 107.f && elapsedTime <= timeStamp2 + 108.f)
		{
			this->meteorSpawnRate = 0.f;
			this->horizontalEnemySpawnRate = 0.f;
			this->enemySpawnRate = 0.f;
			this->dpsItemSpawnRate = 0.f;
			cutscene = true;

		}

		// Boss spawn
		if (elapsedTime >= timeStamp2 + 112.f && checkerThree)
		{
			if (!bossIsActive) {
				if (!this->stageMusic.openFromFile("Music/BossMusic2.ogg"))
				{
					std::cout << "ERROR::BOSSMUSIC::FAILED_TO_LOAD" << "\n";
				}
				this->stageMusic.play();
				this->stageMusic.setLoop(true);

				bossIsActive = true;
				this->meteorSpawnRate = 0.f;
				this->doubleMeteorChance = 0.f;
				this->tripleMeteorChance = 0.f;

				this->boss->spawn(sf::Vector2f(387.5f, 1000.f), sf::Vector2f(387.5f, 600.f));
			}
			this->backgroundScrollSpeed = 3.0f;
			this->checkerThree = false;
			this->deathBeamSpawnTimer = 50.f;
			cutscene = false;
			this->updateSoundFXVolume();
		}

		if(bossIsActive && this->boss->getHp() <= 350 && !stageTransition)
		{
			if(difficulty == 0)
			{
				this->deathBeamSpawnRate = 0.05f;
				this->horizontalEnemySpawnRate = 0.04f;
			}
			if(difficulty == 1) 
			{
				this->deathBeamSpawnRate = 0.09f;
				this->horizontalEnemySpawnRate = 0.2f;
			}
			if(difficulty == 2)
			{
				this->deathBeamSpawnRate = 0.102f;
				this->horizontalEnemySpawnRate = 0.3f;
			}
		}

		if(bossIsActive && this->boss->getHp() <= 200 && !stageTransition)
		{
			if (difficulty == 0)
			{
				this->horizontalEnemySpawnRate = 0.1f;
			}
			if(difficulty == 1) 
			{
				this->deathBeamSpawnRate = 0.11f;
				this->horizontalEnemySpawnRate = 0.35f;
			}
			if(difficulty == 2)
			{
				this->deathBeamSpawnRate = 0.13f;
				this->horizontalEnemySpawnRate = 0.5f;
			}
		}

		if (bossIsActive && this->boss->getHp() <= 120 && !stageTransition)
		{
			if (difficulty == 2)
			{
				this->enemySpawnRate = 0.1f;
			}
		}

		// Boss defeated rewards
		if (bossDefeated && checkerFour)
		{
			this->stageMusic.stop();
			this->stageMusic.setLoop(false);
			this->explosionSound.play();
			this->meteorSpawnRate = 0.f;
			this->enemySpawnRate = 0.f;
			this->horizontalEnemySpawnRate = 0.f;
			this->deathBeamSpawnRate = 0.f;
			this->timeStamp = elapsedTime;
			this->stageTransition = true;
			bossDefeated = false;

			if (difficulty == 0)
			{
				this->points = points + 50000;
				this->addCoins(500);

			}

			if (difficulty == 1) 
			{
				this->points = points + 100000;
				this->addCoins(1000);
			}

			if (difficulty == 2)
			{
				this->points = points + 150000;
				this->addCoins(1500);
				this->enemyKillCounter = enemyKillCounter + 20;
			}


			this->enemyKillCounter = enemyKillCounter + 100;
			checkerFour = false;
			this->backgroundScrollSpeed = 2.0f;
			cutscene = true;

		}

		if (elapsedTime >= timeStamp + 5.f && stageTransition)
		{
			this->healthItemSpawnRate = 1.f;
			this->dpsItemSpawnRate = 3.0f;
			bossIsActive = false;
			stageTransition = false;
			victoryTune.play();
			stage2End = true;
			this->backgroundScrollSpeed = 1.f;
			this->meteorSpawnRate = 0.f;

			if (!this->stageMusic.openFromFile("Music/empty.mp3"))
			{
				std::cout << "ERROR::EMPTY::FAILED_TO_LOAD" << "\n";
			}
			this->stageMusic.play();
			this->stageMusic.setVolume(this->clampVolume(this->musicVolume * 12.f));
		}

		if (elapsedTime >= timeStamp + 10.f && checkerFive && stage2End)
		{
			this->healthItemSpawnRate = 0.f;
			this->dpsItemSpawnRate = 0.f;
			checkerFive = false;
			this->meteorSpawnRate = 0.f;

		}

		if (elapsedTime >= timeStamp + 13.f && checkerSix && stage2End)
		{
			this->triggerFadeEffect();
			checkerSix = false;
			this->meteorSpawnRate = 0.f;

		}

		if (elapsedTime >= timeStamp + 14.f && stage2End && checkerSeven)
		{
			this->backgroundScrollSpeed = 75.f;
			this->meteorSpawnRate = 0.f;

		}

		if (elapsedTime >= timeStamp + 15.f && stage2End && checkerSeven)
		{
			this->stageBackground.setTexture(this->stage3BackgroundTexture);
			this->stageBackground2.setTexture(this->stage3BackgroundTexture);
			this->stageBackground2.setPosition(0, this->stageBackground.getGlobalBounds().height);
			this->checkerFour = false;

		}

		// Stage transition
		if (elapsedTime >= timeStamp + 16.f && stage2End)
		{
			this->backgroundScrollSpeed = 1.5f;
			timeStamp2 = elapsedTime;
			stage2End = false;
			this->meteorSpawnRate = 0.f;
			this->bossDefeated = false;
			Stage = 3;



		}



	}
	
	// Stage 3 events
	if (Stage == 3)
	{
		if (elapsedTime >= timeStamp2 + 1.f && elapsedTime <= timeStamp2 + 2.f)
		{
			checkerOne = true;
			checkerTwo = true;
			checkerThree = true;
			checkerFour = true;
			checkerFive = true;
			checkerSix = true;
			this->healthItemSpawnRate = 0.0167f;
			this->enemySpawnRate = 0.f;
			this->horizontalEnemySpawnRate = 0.f;
			this->meteorSpawnRate = 0.f;
			this->doubleMeteorChance = 0.f;
			this->tripleMeteorChance = 0.f;
			this->healthItemSpawnTimer = 25.f;
			this->backgroundScrollSpeed = 2.0f;
			this->boss = new Boss(825.f, 10.f, 3);
			cutscene = false;
			
		}

		if (elapsedTime >= timeStamp2 + 6.f && checkerOne)
		{

			if (!this->stageMusic.openFromFile("Music/Aloneagainstenemy.ogg"))
			{
				std::cout << "ERROR::ALONE_MUSIC::FAILED_TO_LOAD" << "\n";
			}
			this->stageMusic.play();
			this->dpsItemSpawnRate = 0.08f;
			this->healthItemSpawnTimer = 0.f;

			if(difficulty == 0)
			{
				this->enemySpawnRate = 2.25f;
				this->horizontalEnemySpawnRate = 0.f;
			}

			if(difficulty == 1)
			{
				this->enemySpawnRate = 2.5f;
				this->horizontalEnemySpawnRate = 0.f;
			}

			if (difficulty == 2)
			{
				this->enemySpawnRate = 2.5f;
				this->horizontalEnemySpawnRate = 0.5f;
			}
			this->meteorSpawnRate = 0.25f;
			this->doubleMeteorChance = 25.f;


			checkerOne = false;
		}

		if(elapsedTime >= timeStamp2 + 20.f && elapsedTime <= timeStamp2 + 21.f)
		{
			this->enemySpawnRate = 0.25f;
			if (difficulty == 0)
			{
				this->meteorSpawnRate = 1.75f;
				this->doubleMeteorChance = 40.f;
				this->tripleMeteorChance = 0.f;
			
			}

			if (difficulty == 1) 
			{
				this->meteorSpawnRate = 2.0f;
				this->doubleMeteorChance = 50.f;
				this->tripleMeteorChance = 0.f;
			}
			if(difficulty == 2)
			{
				this->meteorSpawnRate = 2.35f;
				this->doubleMeteorChance = 55.f;
				this->tripleMeteorChance = 0.f;
			}
			this->horizontalSpawnTimer = 0.f;
		}

		if(elapsedTime >= timeStamp2 + 30.f && elapsedTime <= timeStamp2 + 31.f)
		{
			if (difficulty == 0)
			{
				this->enemySpawnRate = 1.0f;
				this->meteorSpawnRate = 0.5f;
				this->doubleMeteorChance = 90.f;
				this->horizontalEnemySpawnRate = 0.75f;
			}

			if (difficulty == 1)
			{
				this->enemySpawnRate = 1.25f;
				this->meteorSpawnRate = 0.75f;
				this->doubleMeteorChance = 90.f;
				this->horizontalEnemySpawnRate = 0.75f;
			}

			if (difficulty == 2)
			{
				this->enemySpawnRate = 1.35f;
				this->meteorSpawnRate = 0.8f;
				this->doubleMeteorChance = 90.f;
				this->horizontalEnemySpawnRate = 0.8f;
			}

		}

		if(elapsedTime >= timeStamp2 + 65.f && elapsedTime <= timeStamp2 + 66.f)
		{
			if(difficulty == 0)
			{
				this->enemySpawnRate = 0.9f;
				this->deathBeamSpawnRate = 0.08f;
				this->doubleMeteorChance = 0.f;
				this->horizontalEnemySpawnRate = 0.8f;
			}

			if(difficulty == 1)
			{
				this->enemySpawnRate = 1.0f;
				this->deathBeamSpawnRate = 0.10f;
				this->doubleMeteorChance = 0.f;
				this->horizontalEnemySpawnRate = 1.0f;
			}

			if (difficulty == 2)
			{
				this->enemySpawnRate = 1.25f;
				this->deathBeamSpawnRate = 0.11f;
				this->doubleMeteorChance = 0.f;
				this->horizontalEnemySpawnRate = 1.1f;
			}

		}


		if (elapsedTime >= timeStamp2 + 86.f && elapsedTime <= timeStamp2 + 87.f)
		{
			this->deathBeamSpawnRate = 0.f;
		}

		if (elapsedTime >= timeStamp2 + 89.f && elapsedTime <= timeStamp2 + 90.f)
		{
			this->horizontalEnemySpawnRate = 0.1f;
			this->enemySpawnRate = 0.0f;
			this->doubleMeteorChance = 0.f;
		}

		if (elapsedTime >= timeStamp2 + 90.f && elapsedTime <= timeStamp2 + 91.f)
		{

			if(difficulty == 0)
			{
				this->meteorSpawnRate = 2.f;
				this->doubleMeteorChance = 45.f;
			
			}

			if(difficulty == 1)
			{
				this->meteorSpawnRate = 2.25f;
				this->doubleMeteorChance = 50.f;
			}


			if (difficulty == 2)
			{
				this->meteorSpawnRate = 2.3f;
				this->doubleMeteorChance = 55.f;
				this->horizontalEnemySpawnRate = 0.3f;
				this->enemySpawnRate = 0.3f;
			}


		}

		if (elapsedTime >= timeStamp2 + 105.f && elapsedTime <= timeStamp2 + 106.f)
		{
			this->meteorSpawnRate = 0.f;
			this->doubleMeteorChance = 0.f;
			this->tripleMeteorChance = 0.f;
			this->deathBeamSpawnRate = 0.f;
			this->enemySpawnRate = 0.f;
			this->horizontalEnemySpawnRate = 0.f;
			cutscene = true;

		}

		if(elapsedTime >= timeStamp2 + 109.8f && checkerFour)
		{
			if (!this->stageMusic.openFromFile("Music/Theendp1.wav"))
			{
				std::cout << "ERROR::BOSSMUSIC::FAILED_TO_LOAD" << "\n";
			}
			this->stageMusic.play();
			this->stageMusic.setVolume(this->clampVolume(this->musicVolume * 20.f));

			this->backgroundScrollSpeed = 4.0f;
			checkerFour = false;
		}

		if(elapsedTime >= timeStamp2 + 110.f && elapsedTime <= timeStamp2 + 125.f)
		{
			this->player->setAttackCooldown(0);
		}

		// Boss spawn
		if (elapsedTime >= timeStamp2 + 115.f && checkerTwo)
		{
			if (!bossIsActive) {
				bossIsActive = true;
				this->meteorSpawnRate = 0.f;
				this->doubleMeteorChance = 0.f;
				this->tripleMeteorChance = 0.f;
				dpsItemSpawnRate = 0.f;
				healthItemSpawnRate = 0.04f;
				this->deathBeamSpawnTimer = 55.f;

				this->boss->spawn(sf::Vector2f(355.f, -400.f), sf::Vector2f(355.f, -100.f));
			}
			
			this->checkerTwo = false;
		}

		if (elapsedTime >= timeStamp2 + 125.f && checkerThree)
		{
	
			if (!this->stageMusic.openFromFile("Music/Theendp2.wav"))
				{
				std::cout << "ERROR::BOSSMUSIC::FAILED_TO_LOAD" << "\n";
			}
			this->stageMusic.play();
			this->stageMusic.setVolume(this->clampVolume(this->musicVolume * 20.f));
			this->stageMusic.setLoop(true);

			this->cutscene = false;
			this->checkerThree = false;
		}

		if (bossIsActive && boss->getHp() <= 800 && boss->getHp() >= 700)
		{
			this->deathBeamSpawnRate = 0.06f;
			this->enemySpawnRate = 0.25f;
			this->horizontalEnemySpawnRate = 0.35f;
		}

		if (bossIsActive && boss->getHp() <= 700 && boss->getHp() >= 600)
		{
			this->meteorSpawnRate = 0.25f;
		}


		if(bossIsActive && boss->getHp() <= 600 && boss->getHp() >= 500)
		{
			this->enemySpawnRate = 0.5f;
		}

		if(bossIsActive && boss->getHp() <= 500 && boss->getHp() >= 400)
		{
			this->horizontalEnemySpawnRate = 0.5f;
		}

		if (bossIsActive && boss->getHp() <= 400 && boss->getHp() >= 300)
		{
			if(difficulty == 2)
			{
				this->enemySpawnRate = 0.7f;
			}

		}

		if (bossIsActive && boss->getHp() <= 200 && boss->getHp() >= 150)
		{
			if (difficulty == 1 or difficulty == 2)
			{
				this->deathBeamSpawnRate = 0.12f;
			}
		}

		if (bossIsActive && boss->getHp() <= 150 && boss->getHp() >= 50)
		{
			if (difficulty == 1 or difficulty == 2)
			{
				this->horizontalEnemySpawnRate = 1.0f;
			}

		}

		if (bossDefeated && checkerFive)
		{
			this->stageMusic.setLoop(false);
			this->stageMusic.stop();
			this->explosionSound.play();
			this->meteorSpawnRate = 0.f;
			this->horizontalEnemySpawnRate = 0.f;
			this->deathBeamSpawnRate = 0.f;
			this->enemySpawnRate = 0.f;
			this->timeStamp = elapsedTime;
			bossDefeated = false;

			if(this->difficulty == 0)
			{
				this->points = points + 125000;
				this->addCoins(1250);
			}

			if(this->difficulty == 1)
			{
				this->points = points + 250000;
				this->addCoins(2500);
			}

			if(this->difficulty == 2)
			{
				this->points = points + 500000;
				this->addCoins(5000);
			}

			this->gameData.gameCompleted = true;
			if (this->difficulty == 1)
			{
				this->gameData.normalVictory = true;
			}
			if (this->difficulty == 2)
			{
				this->gameData.hellVictory = true;
			}
			this->updateShopUnlocks();
			updateGameData(this->gameData);


			this->enemyKillCounter = enemyKillCounter + 200;
			checkerFive = false;
			this->backgroundScrollSpeed = 2.0f;
			cutscene = true;

		}

		if (elapsedTime >= timeStamp + 5.f && checkerFive == false && checkerSix)
		{
			if (!this->endMusic.openFromFile("Music/Bravery.ogg"))
			{
				std::cout << "ERROR::BRAVERY::FAILED_TO_LOAD" << "\n";
			}
			this->endMusic.setVolume(this->clampVolume(this->musicVolume * 20.f));
			this->endMusic.play();

			checkerSix = false;
			this->healthItemSpawnRate = 1.0f;
		}

		if(elapsedTime >= timeStamp + 22.f && checkerFive == false && checkerSeven)
		{
			this->triggerFadeEffect();

			checkerSeven = false;
		}

		// Game end
		if(elapsedTime >= timeStamp + 25.f && checkerFive == false)
		{
			cutscene = false;
			this->hellBonusPending = (this->difficulty == 2);
			this->endScreenEnterReleased = false;
			gameState = END;
		}


	}
}
