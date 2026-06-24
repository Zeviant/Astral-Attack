#include "Enemy.h"

void Enemy::initializeVariables()
{
	this->type = 1;
	this->hp = 0;
	this->damage = 1;
	this->points = 5;
	this->speed = 10.f;

	this->meteorSpeedIncrease = 0.f;

	// Initialize animation variables
	this->animationTimer = 0.f;
	this->animationInterval = 0.5f;
	this->currentFrame = 0;
}


void Enemy::initializeTextures()
{
	this->textures["SMALLENEMY"] = new sf::Texture();
	if (!this->textures["SMALLENEMY"]->loadFromFile("Textures/Smallenemyf1.png"))
	{
		std::cout << "TEXTURE::SMALL_ENEMY::FAILED_TO_LOAD" << "\n";
	}

	this->textures["SMALLENEMY2"] = new sf::Texture();
	if (!this->textures["SMALLENEMY2"]->loadFromFile("Textures/Smallenemyf2.png"))
	{
		std::cout << "TEXTURE::SMALL_ENEMY::FAILED_TO_LOAD" << "\n";
	}

	this->textures["MEDIUMENEMY"] = new sf::Texture();
	if (!this->textures["MEDIUMENEMY"]->loadFromFile("Textures/Mediumenemyf1.png"))
	{
		std::cout << "TEXTURE::MEDIUM_ENEMY::FAILED_TO_LOAD" << "\n";
	}

	this->textures["MEDIUMENEMY2"] = new sf::Texture();
	if (!this->textures["MEDIUMENEMY2"]->loadFromFile("Textures/Mediumenemyf2.png"))
	{
		std::cout << "TEXTURE::MEDIUM_ENEMY::FAILED_TO_LOAD" << "\n";
	}

	this->textures["BIGENEMY"] = new sf::Texture();
	if (!this->textures["BIGENEMY"]->loadFromFile("Textures/Bigenemyf1.png"))
	{
		std::cout << "TEXTURE::BIG_ENEMY::FAILED_TO_LOAD" << "\n";
	}

	this->textures["BIGENEMY2"] = new sf::Texture();
	if (!this->textures["BIGENEMY2"]->loadFromFile("Textures/Bigenemyf2.png"))
	{
		std::cout << "TEXTURE::BIG_ENEMY::FAILED_TO_LOAD" << "\n";
	}

	this->textures["METEOR"] = new sf::Texture();
	if (!this->textures["METEOR"]->loadFromFile("Textures/Meteor.png"))
	{
		std::cout << "TEXTURE::METEOR::FAILED_TO_LOAD" << "\n";
	}

	this->textures["STAGE2ENEMY1"] = new sf::Texture();
	if(!this->textures["STAGE2ENEMY1"]->loadFromFile("Textures/Stage2e1.png"))
	{
		std::cout << "TEXTURE::STAGE2ENEMY1::FAILED_TO_LOAD" << "\n";
	}

	this->textures["STAGE2ENEMY2"] = new sf::Texture();
	if (!this->textures["STAGE2ENEMY2"]->loadFromFile("Textures/Stage2e2.png"))
	{
		std::cout << "TEXTURE::STAGE2ENEMY2::FAILED_TO_LOAD" << "\n";
	}

	this->textures["STAGE2ENEMY3"] = new sf::Texture();
	if (!this->textures["STAGE2ENEMY3"]->loadFromFile("Textures/Stage2e3.png"))
	{
		std::cout << "TEXTURE::STAGE2ENEMY3::FAILED_TO_LOAD" << "\n";
	}

	this->textures["STAGE2ENEMY4"] = new sf::Texture();
	if (!this->textures["STAGE2ENEMY4"]->loadFromFile("Textures/Stage2e4.png"))
	{
		std::cout << "TEXTURE::STAGE2ENEMY4::FAILED_TO_LOAD" << "\n";
	}

	this->textures["STAGE2ENEMY5"] = new sf::Texture();
	if (!this->textures["STAGE2ENEMY5"]->loadFromFile("Textures/Stage2e5.png"))
	{
		std::cout << "TEXTURE::STAGE2ENEMY5::FAILED_TO_LOAD" << "\n";
	}

	this->textures["STAGE2ENEMY6"] = new sf::Texture();
	if (!this->textures["STAGE2ENEMY6"]->loadFromFile("Textures/Stage2e6.png"))
	{
		std::cout << "TEXTURE::STAGE2ENEMY6::FAILED_TO_LOAD" << "\n";
	}

	this->textures["STAGE3ENEMY1"] = new sf::Texture();
	if (!this->textures["STAGE3ENEMY1"]->loadFromFile("Textures/Stage3e1.png"))
	{
		std::cout << "TEXTURE::STAGE3ENEMY1::FAILED_TO_LOAD" << "\n";
	}

	this->textures["STAGE3ENEMY2"] = new sf::Texture();
	if (!this->textures["STAGE3ENEMY2"]->loadFromFile("Textures/Stage3e2.png"))
	{
		std::cout << "TEXTURE::STAGE3ENEMY2::FAILED_TO_LOAD" << "\n";
	}

	this->textures["STAGE3ENEMY3"] = new sf::Texture();
	if (!this->textures["STAGE3ENEMY3"]->loadFromFile("Textures/Stage3e3.png"))
	{
		std::cout << "TEXTURE::STAGE3ENEMY3::FAILED_TO_LOAD" << "\n";
	}

	this->textures["STAGE3ENEMY4"] = new sf::Texture();
	if (!this->textures["STAGE3ENEMY4"]->loadFromFile("Textures/Stage3e4.png"))
	{
		std::cout << "TEXTURE::STAGE3ENEMY4::FAILED_TO_LOAD" << "\n";
	}

	this->textures["STAGE3ENEMY5"] = new sf::Texture();
	if (!this->textures["STAGE3ENEMY5"]->loadFromFile("Textures/Stage3e5.png"))
	{
		std::cout << "TEXTURE::STAGE3ENEMY5::FAILED_TO_LOAD" << "\n";
	}

	this->textures["STAGE3ENEMY6"] = new sf::Texture();
	if (!this->textures["STAGE3ENEMY6"]->loadFromFile("Textures/Stage3e6.png"))
	{
		std::cout << "TEXTURE::STAGE3ENEMY6::FAILED_TO_LOAD" << "\n";
	}

	if (!this->bomberFireTexture.loadFromFile("Animations/Bomberfire.png"))
	{
		std::cout << "TEXTURE::BOMBER_FIRE::FAILED_TO_LOAD" << "\n";
	}

	if (!this->frigateFireTexture.loadFromFile("Animations/Frigatefire.png"))
	{
		std::cout << "TEXTURE::FRIGATE_FIRE::FAILED_TO_LOAD" << "\n";
	}

	if (!this->scoutFireTexture.loadFromFile("Animations/Scoutfire.png"))
	{
		std::cout << "TEXTURE::SCOUT_FIRE::FAILED_TO_LOAD" << "\n";
	}

	if (!this->fighterFireTexture.loadFromFile("Animations/Fighterfire.png"))
	{
		std::cout << "TEXTURE::FIGHTER_FIRE::FAILED_TO_LOAD" << "\n";
	}

	if (!this->supportFireTexture.loadFromFile("Animations/Supportfire.png"))
	{
		std::cout << "TEXTURE::SUPPORT_FIRE::FAILED_TO_LOAD" << "\n";
	}

	if (!this->torpedoFireTexture.loadFromFile("Animations/Torpedofire.png"))
	{
		std::cout << "TEXTURE::TORPEDO_FIRE::FAILED_TO_LOAD" << "\n";
	}

	if (!this->deathBeamTexture.loadFromFile("Animations/Deathbeam.png"))
	{
		std::cout << "TEXTURE::DEATHBEAM::FAILED_TO_LOAD" << "\n";
	}

	if (!this->stage3e1FireTexture.loadFromFile("Animations/Stage3e1fire.png"))
	{
		std::cout << "TEXTURE::STAGE3_E1_FIRE::FAILED_TO_LOAD" << "\n";
	}


	if (!this->stage3e2FireTexture.loadFromFile("Animations/Stage3e2fire.png"))
	{
		std::cout << "TEXTURE::STAGE3_E2_FIRE::FAILED_TO_LOAD" << "\n";
	}

	if (!this->stage3e3FireTexture.loadFromFile("Animations/Stage3e3fire.png"))
	{
		std::cout << "TEXTURE::STAGE3_E3_FIRE::FAILED_TO_LOAD" << "\n";
	}

	if (!this->stage3e4FireTexture.loadFromFile("Animations/Stage3e4fire.png"))
	{
		std::cout << "TEXTURE::STAGE3_E4_FIRE::FAILED_TO_LOAD" << "\n";
	}

	if (!this->stage3e5FireTexture.loadFromFile("Animations/Stage3e5fire.png"))
	{
		std::cout << "TEXTURE::STAGE3_E5_FIRE::FAILED_TO_LOAD" << "\n";
	}

	if (!this->stage3e6FireTexture.loadFromFile("Animations/Stage3e6fire.png"))
	{
		std::cout << "TEXTURE::STAGE3_E6_FIRE::FAILED_TO_LOAD" << "\n";
	}

	if (!this->deathBeam2Texture.loadFromFile("Animations/Deathbeam2.png"))
	{
		std::cout << "TEXTURE::DEATHBEAM2::FAILED_TO_LOAD" << "\n";
	}
}


Enemy::Enemy(float pos_x, float pos_y, int type)
{
	this->initializeVariables();
	this->initializeTextures();

	switch(type)
	{
	case 1:
		this->enemyOne.setTexture(*this->textures["SMALLENEMY"]);
		this->enemyOne.setScale(2.75f, 2.75f);

		this->enemyOne.setPosition(pos_x, pos_y);

		this->type = type;
		this->hp = 1.f;
		this->damage = 1;
		this->points = 100;
		this->speed = 6.0f;
		break;

	case 2:
		this->enemyOne.setTexture(*this->textures["MEDIUMENEMY"]);
		this->enemyOne.scale(2.75f, 2.75f);

		this->enemyOne.setPosition(pos_x, pos_y);

		this->type = type;
		this->hp = 1.5f;
		this->damage = 1;
		this->points = 250;
		this->speed = 5.5f;
		break;

	case 3:
		this->enemyOne.setTexture(*this->textures["BIGENEMY"]);
		this->enemyOne.scale(2.75f, 2.75f);

		this->enemyOne.setPosition(pos_x, pos_y);

		this->type = type;
		this->hp = 3.f;
		this->damage = 1;
		this->points = 500;
		this->speed = 5.0f;
		break;

	case 4:
		this->enemyOne.setTexture(*this->textures["METEOR"]);

		this->enemyOne.setPosition(pos_x, pos_y);
		this->enemyOne.setScale(2.25f, 2.25f);

		this->type = type;
		this->hp = 100;
		this->damage = 1;
		this->points = 0;

		this->speed = 7.5f + meteorSpeedIncrease;

		break;

	case 5:
		this->enemyOne.setTexture(*this->textures["STAGE2ENEMY1"]);
		this->enemyOne.scale(2.75f, 2.75f);

		this->enemyOne.setPosition(pos_x, pos_y);

		this->type = type;
		this->hp = 8.5f;
		this->damage = 1;
		this->points = 500; 
		this->speed = 6.5f;

		this->bomberFire.setTexture(this->bomberFireTexture);
		this->bomberfireFrame = sf::IntRect(0, 0, 64, 64);
		this->bomberFire.setTextureRect(this->bomberfireFrame);
		this->bomberFire.setScale(2.75f, 2.75f);
		this->bomberFire.setPosition(this->enemyOne.getPosition().x - (this->textures["STAGE2ENEMY1"]->getSize().x / 2) * 2.75f, this->enemyOne.getPosition().y - (this->textures["STAGE2ENEMY1"]->getSize().y) * 2.75f + 45.f);
		this->bomberCurrentFrame = 0;
		this->bomberAnimationTimer = 0.f;
		this->bomberAnimationSpeed = 0.1f;
		break;

	case 6:
		this->enemyOne.setTexture(*this->textures["STAGE2ENEMY2"]);
		this->enemyOne.scale(2.75f, 2.75f);

		this->enemyOne.setPosition(pos_x, pos_y);

		this->type = type;
		this->hp = 4.5f;
		this->damage = 1;
		this->points = 200;
		this->speed = 7.5f;

		this->scoutFire.setTexture(this->scoutFireTexture);
		this->scoutFireFrame = sf::IntRect(0, 0, 64, 64);
		this->scoutFire.setTextureRect(this->scoutFireFrame);
		this->scoutFire.setScale(2.75f, 2.75f);
		this->scoutFire.setPosition(this->enemyOne.getPosition().x - (this->textures["STAGE2ENEMY2"]->getSize().x / 2) * 2.75f, this->enemyOne.getPosition().y - (this->textures["STAGE2ENEMY2"]->getSize().y) * 2.75f - 50.f);
		this->scoutCurrentFrame = 0;
		this->scoutAnimationTimer = 0.f;
		this->scoutAnimationSpeed = 0.1f;
		break;

	case 7:
		this->enemyOne.setTexture(*this->textures["STAGE2ENEMY3"]);
		this->enemyOne.scale(2.75f, 2.75f);

		this->enemyOne.setPosition(pos_x, pos_y);

		this->type = type;
		this->hp = 11.5f;
		this->damage = 1;
		this->points = 1000;
		this->speed = 4.0f;

		this->frigateFire.setTexture(this->frigateFireTexture);
		this->frigateFireFrame = sf::IntRect(0, 0, 64, 64);
		this->frigateFire.setTextureRect(this->frigateFireFrame);
		this->frigateFire.setScale(2.75f, 2.75f);
		this->frigateFire.setPosition(this->enemyOne.getPosition().x - (this->textures["STAGE2ENEMY3"]->getSize().x / 2) * 2.75f, this->enemyOne.getPosition().y - (this->textures["STAGE2ENEMY3"]->getSize().y) * 2.75f - 50.f);
		this->frigateCurrentFrame = 0;
		this->frigateAnimationTimer = 0.f;
		this->frigateAnimationSpeed = 0.1f;
		break;

	case 8:
		this->enemyOne.setTexture(*this->textures["STAGE2ENEMY4"]);
		this->enemyOne.scale(2.75f, 2.75f);

		this->enemyOne.setPosition(pos_x, pos_y);

		this->type = type;
		this->hp = 1.f;
		this->damage = 1;
		this->points = 100;
		this->speed = 13.5f;

		this->fighterFire.setTexture(this->fighterFireTexture);
		this->fighterFrame = sf::IntRect(0, 0, 64, 64);
		this->fighterFire.setTextureRect(this->fighterFrame);
		this->fighterFire.setScale(2.75f, 2.75f);
		this->fighterFire.setPosition(this->enemyOne.getPosition().x - (this->textures["STAGE2ENEMY4"]->getSize().x / 2) * 2.75f, this->enemyOne.getPosition().y - (this->textures["STAGE2ENEMY4"]->getSize().y) * 2.75f - 50.f);
		this->fighterCurrentFrame = 0;
		this->fighterAnimationTimer = 0.f;
		this->fighterAnimationSpeed = 0.1f;
		break;

	case 9:
		this->enemyOne.setTexture(*this->textures["STAGE2ENEMY5"]);
		this->enemyOne.scale(2.75f, 2.75f);

		this->enemyOne.setPosition(pos_x, pos_y);

		this->type = type;
		this->hp = 3.f;
		this->damage = 1;
		this->points = 500;
		this->speed = 3.0f;

		this->supportFire.setTexture(this->supportFireTexture);
		this->supportFrame = sf::IntRect(0, 0, 64, 64);
		this->supportFire.setTextureRect(this->supportFrame);
		this->supportFire.setScale(2.5f, 2.5f);
		this->supportFire.rotate(90);
		this->supportFire.setPosition(this->enemyOne.getPosition().x - (this->textures["STAGE2ENEMY5"]->getSize().x / 2) * 2.75f, this->enemyOne.getPosition().y - (this->textures["STAGE2ENEMY5"]->getSize().y) * 2.75f + 45.f);
		this->supportCurrentFrame = 0;
		this->supportAnimationTimer = 0.f;
		this->supportAnimationSpeed = 0.1f;

		break;

	case 10:
		this->enemyOne.setTexture(*this->textures["STAGE2ENEMY6"]);
		this->enemyOne.scale(2.75f, 2.75f);

		this->enemyOne.setPosition(pos_x, pos_y);

		this->type = type;
		this->hp = 2.f;
		this->damage = 1;
		this->points = 500;
		this->speed = 3.5f;

		this->torpedoFire.setTexture(this->torpedoFireTexture);
		this->torpedoFrame = sf::IntRect(0, 0, 64, 64);
		this->torpedoFire.setTextureRect(this->torpedoFrame);
		this->torpedoFire.setScale(2.75f, 2.75f);
		this->torpedoFire.rotate(270);
		this->torpedoFire.setPosition(this->enemyOne.getPosition().x - (this->textures["STAGE2ENEMY6"]->getSize().x / 2) * 2.75f, this->enemyOne.getPosition().y - (this->textures["STAGE2ENEMY6"]->getSize().y) * 2.75f + 45.f);
		this->torpedoCurrentFrame = 0;
		this->torpedoAnimationTimer = 0.f;
		this->torpedoAnimationSpeed = 0.1f;
		break;

	case 11:
		this->enemyOne.setTexture(deathBeamTexture);
		this->enemyOne.scale(2.75f, 2.75f);

		this->enemyOne.setPosition(pos_x, pos_y);

		this->type = type;
		this->hp = 100.f;
		this->damage = 1;
		this->points = 0;
		this->speed = 7.f;

		this->deathBeamFrame = sf::IntRect(0, 0, 18, 950);
		this->enemyOne.setTextureRect(this->deathBeamFrame);
		this->enemyOne.setScale(2.75f, 2.75f);
		this->enemyOne.setPosition(this->enemyOne.getPosition().x - (deathBeamTexture.getSize().x / 2) * 2.75f, this->enemyOne.getPosition().y - (deathBeamTexture.getSize().y) * 2.75f + 45.f);
		this->deathBeamCurrentFrame = 0;
		this->deathBeamAnimationTimer = 0.f;
		this->deathBeamAnimationSpeed = 0.1f;
		break;

	case 12:
		this->enemyOne.setTexture(*this->textures["STAGE3ENEMY1"]);
		this->enemyOne.scale(2.75f, 2.75f);

		this->enemyOne.setPosition(pos_x, pos_y);

		this->type = type;
		this->hp = 5.f;
		this->damage = 1;
		this->points = 500;
		this->speed = 14.f;

		this->stage3e1Fire.setTexture(this->stage3e1FireTexture);
		this->stage3e1Frame = sf::IntRect(0, 0, 64, 64);
		this->stage3e1Fire.setTextureRect(this->stage3e1Frame);
		this->stage3e1Fire.setScale(2.75f, 2.75f);
		this->stage3e1Fire.setPosition(this->enemyOne.getPosition().x - (this->textures["STAGE3ENEMY1"]->getSize().x / 2) * 2.75f, this->enemyOne.getPosition().y - (this->textures["STAGE3ENEMY1"]->getSize().y) * 2.75f + 45.f);
		this->stage3e1CurrentFrame = 0;
		this->stage3e1AnimationTimer = 0.f;
		this->stage3e1AnimationSpeed = 0.1f;
		break;

	case 13:
		this->enemyOne.setTexture(*this->textures["STAGE3ENEMY2"]);
		this->enemyOne.scale(2.75f, 2.75f);

		this->enemyOne.setPosition(pos_x, pos_y);

		this->type = type;
		this->hp = 12.f;
		this->damage = 1;
		this->points = 1500;
		this->speed = 10.0f;

		this->stage3e2Fire.setTexture(this->stage3e2FireTexture);
		this->stage3e2Frame = sf::IntRect(0, 0, 64, 64);
		this->stage3e2Fire.setTextureRect(this->stage3e2Frame);
		this->stage3e2Fire.setScale(2.75f, 2.75f);
		this->stage3e2Fire.setPosition(this->enemyOne.getPosition().x - (this->textures["STAGE3ENEMY2"]->getSize().x / 2) * 2.75f, this->enemyOne.getPosition().y - (this->textures["STAGE3ENEMY2"]->getSize().y) * 2.75f + 45.f);
		this->stage3e2CurrentFrame = 0;
		this->stage3e2AnimationTimer = 0.f;
		this->stage3e2AnimationSpeed = 0.1f;
		break;

	case 14:
		this->enemyOne.setTexture(*this->textures["STAGE3ENEMY3"]);
		this->enemyOne.scale(2.75f, 2.75f);

		this->enemyOne.setPosition(pos_x, pos_y);

		this->type = type;
		this->hp = 12.f;
		this->damage = 1;
		this->points = 1000;
		this->speed = 9.f;

		this->stage3e3Fire.setTexture(this->stage3e3FireTexture);
		this->stage3e3Frame = sf::IntRect(0, 0, 64, 64);
		this->stage3e3Fire.setTextureRect(this->stage3e3Frame);
		this->stage3e3Fire.setScale(2.75f, 2.75f);
		this->stage3e3Fire.setPosition(this->enemyOne.getPosition().x - (this->textures["STAGE3ENEMY3"]->getSize().x / 2) * 2.75f, this->enemyOne.getPosition().y - (this->textures["STAGE3ENEMY3"]->getSize().y) * 2.75f + 45.f);
		this->stage3e3CurrentFrame = 0;
		this->stage3e3AnimationTimer = 0.f;
		this->stage3e3AnimationSpeed = 0.1f;
		break;

	case 15:
		this->enemyOne.setTexture(*this->textures["STAGE3ENEMY4"]);
		this->enemyOne.scale(2.75f, 2.75f);

		this->enemyOne.setPosition(pos_x, pos_y);

		this->type = type;
		this->hp = 16.f;
		this->damage = 1;
		this->points = 4000;
		this->speed = 6.5f;

		this->stage3e4Fire.setTexture(this->stage3e4FireTexture);
		this->stage3e4Frame = sf::IntRect(0, 0, 64, 64);
		this->stage3e4Fire.setTextureRect(this->stage3e4Frame);
		this->stage3e4Fire.setScale(2.75f, 2.75f);
		this->stage3e4Fire.setPosition(this->enemyOne.getPosition().x - (this->textures["STAGE3ENEMY4"]->getSize().x / 2) * 2.75f, this->enemyOne.getPosition().y - (this->textures["STAGE3ENEMY4"]->getSize().y) * 2.75f + 45.f);
		this->stage3e4CurrentFrame = 0;
		this->stage3e4AnimationTimer = 0.f;
		this->stage3e4AnimationSpeed = 0.1f;
		break;
		
	case 16:
		this->enemyOne.setTexture(*this->textures["STAGE3ENEMY5"]);
		this->enemyOne.scale(2.75f, 2.75f);

		this->enemyOne.setPosition(pos_x, pos_y);

		this->type = type;
		this->hp = 4.f;
		this->damage = 1;
		this->points = 1000;
		this->speed = 4.5f;

		this->stage3e5Fire.setTexture(this->stage3e5FireTexture);
		this->stage3e5Frame = sf::IntRect(0, 0, 64, 64);
		this->stage3e5Fire.setTextureRect(this->stage3e5Frame);
		this->stage3e5Fire.setScale(2.75f, 2.75f);
		this->stage3e5Fire.rotate(90);
		this->stage3e5Fire.setPosition(this->enemyOne.getPosition().x - (this->textures["STAGE3ENEMY5"]->getSize().x / 2) * 2.75f + 50.f, this->enemyOne.getPosition().y - (this->textures["STAGE3ENEMY5"]->getSize().y) * 2.75f + 35.f);
		this->stage3e5CurrentFrame = 0;
		this->stage3e5AnimationTimer = 0.f;
		this->stage3e5AnimationSpeed = 0.1f;
		break;

	case 17:
		this->enemyOne.setTexture(*this->textures["STAGE3ENEMY6"]);
		this->enemyOne.scale(2.75f, 2.75f);

		this->enemyOne.setPosition(pos_x, pos_y);

		this->type = type;
		this->hp = 4.f;
		this->damage = 1;
		this->points = 1000;
		this->speed = 4.f;

		this->stage3e6Fire.setTexture(this->stage3e6FireTexture);
		this->stage3e6Frame = sf::IntRect(0, 0, 64, 64);
		this->stage3e6Fire.setTextureRect(this->stage3e6Frame);
		this->stage3e6Fire.setScale(2.75f, 2.75f);
		this->stage3e6Fire.rotate(270);
		this->stage3e6Fire.setPosition(this->enemyOne.getPosition().x - (this->textures["STAGE3ENEMY6"]->getSize().x / 2) * 2.75f + 50.f, this->enemyOne.getPosition().y - (this->textures["STAGE3ENEMY6"]->getSize().y) * 2.75f + 35.f);
		this->stage3e6CurrentFrame = 0;
		this->stage3e6AnimationTimer = 0.f;
		this->stage3e6AnimationSpeed = 0.1f;
		break;

	case 18:
		this->enemyOne.setTexture(deathBeam2Texture);
		this->enemyOne.scale(2.75f, 2.75f);

		this->enemyOne.setPosition(pos_x, pos_y);

		this->type = type;
		this->hp = 100.f;
		this->damage = 1;
		this->points = 0;
		this->speed = 6.0f;

		this->deathBeam2Frame = sf::IntRect(0, 0, 18, 950);
		this->enemyOne.setTextureRect(this->deathBeam2Frame);
		this->enemyOne.setScale(2.75f, 2.75f);
		this->enemyOne.setPosition(this->enemyOne.getPosition().x - (deathBeam2Texture.getSize().x / 2) * 2.75f, this->enemyOne.getPosition().y - (deathBeam2Texture.getSize().y) * 2.75f + 45.f);
		this->deathBeam2CurrentFrame = 0;
		this->deathBeam2AnimationTimer = 0.f;
		this->deathBeam2AnimationSpeed = 0.1f;
		break;

	}

}

Enemy::Enemy()
{
	initializeVariables();
}

Enemy::~Enemy()
{
}


const sf::FloatRect Enemy::getBounds() const
{

	return this->enemyOne.getGlobalBounds();
	
}

const int& Enemy::getPoints() const
{
	return this->points;
}

const int& Enemy::getDamage() const
{
	return this->damage;
}

const float& Enemy::getHp() const
{
	return this->hp;
}

const int& Enemy::getType() const
{
	return this->type;
}

void Enemy::reduceHp(const float value)
{
	this->hp = this->hp - value;

	if(this->hp < 0)
	{
		this->hp = 0;
	}
}

void Enemy::increaseMeteorSpeed(const float value)
{
	this->meteorSpeedIncrease = value;
}

const sf::Vector2f& Enemy::getPos() const
{
	return this->enemyOne.getPosition();
}

void Enemy::update()
{
	updateAnimation();
	updateBomberAnimation();
	updateFrigateAnimation();
	updateScoutAnimation();
	updateFighterAnimation();
	updateSupportAnimation();
	updateTorpedoAnimation();
	updateDeathBeamAnimation();
	updateStage3Enemy1();
	updateStage3Enemy2();
	updateStage3Enemy3();
	updateStage3Enemy4();
	updateStage3Enemy5();
	updateStage3Enemy6();

	if(this->type == 9 or this->type == 16)
	{
		this->enemyOne.move(this->speed, 0.f);
	}
	else if(this->type == 10 or this->type == 17)
	{
		this->enemyOne.move(-this->speed, 0.f);
	}
	else 
	{
		this->enemyOne.move(0.f, this->speed);
	}

}


void Enemy::updateAnimation()
{
	// Update animation timer
	this->animationTimer += 0.1f;

	if (this->animationTimer >= this->animationInterval)
	{
		// Reset timer
		this->animationTimer = 0.f;

		// Swap frames based on enemy type
		switch (this->type)
		{
		case 1:
			if (this->currentFrame == 0)
			{
				this->enemyOne.setTexture(*this->textures["SMALLENEMY2"]);
				this->currentFrame = 1;
			}
			else
			{
				this->enemyOne.setTexture(*this->textures["SMALLENEMY"]);
				this->currentFrame = 0;
			}
			break;

		case 2:
			if (this->currentFrame == 0)
			{
				this->enemyOne.setTexture(*this->textures["MEDIUMENEMY2"]);
				this->currentFrame = 1;
			}
			else
			{
				this->enemyOne.setTexture(*this->textures["MEDIUMENEMY"]);
				this->currentFrame = 0;
			}
			break;

		case 3:
			if (this->currentFrame == 0)
			{
				this->enemyOne.setTexture(*this->textures["BIGENEMY2"]);
				this->currentFrame = 1;
			}
			else
			{
				this->enemyOne.setTexture(*this->textures["BIGENEMY"]);
				this->currentFrame = 0;
			}
			break;

		default:
			break;
		}
	}
}

void Enemy::updateBomberAnimation()
{
	if (this->type == 5)
	{
		this->bomberAnimationTimer += 0.025f;

		if (this->bomberAnimationTimer >= this->bomberAnimationSpeed)
		{
			// Reset timer
			this->bomberAnimationTimer = 0.f;

			// Update frame
			this->bomberCurrentFrame++;
			if (this->bomberCurrentFrame >= 10)
				this->bomberCurrentFrame = 0;

			// Set texture rect
			this->bomberfireFrame.left = this->bomberCurrentFrame * 64;
			this->bomberFire.setTextureRect(this->bomberfireFrame);
			this->bomberFire.setPosition(this->enemyOne.getPosition().x - (this->textures["STAGE2ENEMY1"]->getSize().x / 2)*2.75f, this->enemyOne.getPosition().y - (this->textures["STAGE2ENEMY1"]->getSize().y)*2.75f + 55.f); 
		}
	}
}



void Enemy::updateScoutAnimation()
{
	if (this->type == 6)
	{
		this->scoutAnimationTimer += 0.04f;

		if (this->scoutAnimationTimer >= this->scoutAnimationSpeed)
		{
			// Reset timer
			this->scoutAnimationTimer = 0.f;

			// Update frame
			this->scoutCurrentFrame++;
			if (this->scoutCurrentFrame >= 10)
				this->scoutCurrentFrame = 0;

			// Set texture rect
			this->scoutFireFrame.left = this->scoutCurrentFrame * 64;
			this->scoutFire.setTextureRect(this->scoutFireFrame);
			this->scoutFire.setPosition(this->enemyOne.getPosition().x - (this->textures["STAGE2ENEMY2"]->getSize().x / 2) * 2.75f - 17.f, this->enemyOne.getPosition().y - (this->textures["STAGE2ENEMY2"]->getSize().y) * 2.75f + 18.f);
		}
	}
}

void Enemy::updateFrigateAnimation()
{
	if (this->type == 7)
	{
		this->frigateAnimationTimer += 0.02f;

		if (this->frigateAnimationTimer >= this->frigateAnimationSpeed)
		{
			// Reset timer
			this->frigateAnimationTimer = 0.f;

			// Update frame
			this->frigateCurrentFrame++;
			if (this->frigateCurrentFrame >= 12)
				this->frigateCurrentFrame = 0;

			// Set texture rect
			this->frigateFireFrame.left = this->frigateCurrentFrame * 64;
			this->frigateFire.setTextureRect(this->frigateFireFrame);
			this->frigateFire.setPosition(this->enemyOne.getPosition().x - (this->textures["STAGE2ENEMY3"]->getSize().x / 2) * 2.75f + 16.f, this->enemyOne.getPosition().y - (this->textures["STAGE2ENEMY3"]->getSize().y) * 2.75f - 25.f);
		}
	}
}

void Enemy::updateFighterAnimation()
{
	if (this->type == 8)
	{
		this->fighterAnimationTimer += 0.04f;

		if (this->fighterAnimationTimer >= this->fighterAnimationSpeed)
		{
			// Reset timer
			this->fighterAnimationTimer = 0.f;

			// Update frame
			this->fighterCurrentFrame++;
			if (this->fighterCurrentFrame >= 10)
				this->fighterCurrentFrame = 0;

			// Set texture rect
			this->fighterFrame.left = this->fighterCurrentFrame * 64;
			this->fighterFire.setTextureRect(this->fighterFrame);
			this->fighterFire.setPosition(this->enemyOne.getPosition().x - (this->textures["STAGE2ENEMY4"]->getSize().x / 2) * 2.75f - 28.f, this->enemyOne.getPosition().y - (this->textures["STAGE2ENEMY4"]->getSize().y) * 2.75f - 35.f);
		}
	}
}

void Enemy::updateSupportAnimation()
{
	if (this->type == 9)
	{
		this->supportAnimationTimer += 0.02f;

		if (this->supportAnimationTimer >= this->supportAnimationSpeed)
		{
			// Reset timer
			this->supportAnimationTimer = 0.f;

			// Update frame
			this->supportCurrentFrame++;
			if (this->supportCurrentFrame >= 10)
				this->supportCurrentFrame = 0;

			// Set texture rect
			this->supportFrame.left = this->supportCurrentFrame * 64;
			this->supportFire.setTextureRect(this->supportFrame);
			this->supportFire.setPosition(this->enemyOne.getPosition().x - (this->textures["STAGE2ENEMY5"]->getSize().x / 2) * 2.75f + 155.f, this->enemyOne.getPosition().y - (this->textures["STAGE2ENEMY5"]->getSize().y) * 2.75f + 42.5f);
		}
	}
}

void Enemy::updateTorpedoAnimation()
{
	if (this->type == 10)
	{
		this->torpedoAnimationTimer += 0.025f;

		if (this->torpedoAnimationTimer >= this->torpedoAnimationSpeed)
		{
			// Reset timer
			this->torpedoAnimationTimer = 0.f;

			// Update frame
			this->torpedoCurrentFrame++;
			if (this->torpedoCurrentFrame >= 10)
				this->torpedoCurrentFrame = 0;

			// Set texture rect
			this->torpedoFrame.left = this->torpedoCurrentFrame * 64;
			this->torpedoFire.setTextureRect(this->torpedoFrame);
			this->torpedoFire.setPosition(this->enemyOne.getPosition().x - (this->textures["STAGE2ENEMY6"]->getSize().x / 2) * 2.75f - 30.f, this->enemyOne.getPosition().y - (this->textures["STAGE2ENEMY6"]->getSize().y) * 2.75f + 327.f);
		}
	}
}

void Enemy::updateDeathBeamAnimation()
{
	if (this->type == 11)
	{
		this->deathBeamAnimationTimer += 0.03f;
		if (this->deathBeamAnimationTimer >= this->deathBeamAnimationSpeed)
		{
			// Reset timer
			this->deathBeamAnimationTimer = 0.f;

			// Update frame
			this->deathBeamCurrentFrame++;
			if (this->deathBeamCurrentFrame >= 4)
				this->deathBeamCurrentFrame = 0;

			// Set texture rect
			this->deathBeamFrame.left = this->deathBeamCurrentFrame * 18;
			this->enemyOne.setTextureRect(this->deathBeamFrame);
		}
	}
	else if(this->type == 18)
	{
		this->deathBeam2AnimationTimer += 0.03f;
		if (this->deathBeam2AnimationTimer >= this->deathBeam2AnimationSpeed)
		{
			// Reset timer
			this->deathBeam2AnimationTimer = 0.f;

			// Update frame
			this->deathBeam2CurrentFrame++;
			if (this->deathBeam2CurrentFrame >= 4)
				this->deathBeam2CurrentFrame = 0;

			// Set texture rect
			this->deathBeam2Frame.left = this->deathBeam2CurrentFrame * 18;
			this->enemyOne.setTextureRect(this->deathBeam2Frame);
		}
	
	}
}

void Enemy::updateStage3Enemy1()
{
	if (this->type == 12) 
	{
		this->stage3e1AnimationTimer += 0.1f;

		if (this->stage3e1AnimationTimer >= this->stage3e1AnimationSpeed)
		{
			// Reset timer
			this->stage3e1AnimationTimer = 0.f;

			// Update frame
			this->stage3e1CurrentFrame++;
			if (this->stage3e1CurrentFrame >= 8) 
				this->stage3e1CurrentFrame = 0;

			// Set texture rect
			this->stage3e1Frame.left = this->stage3e1CurrentFrame * 64;
			this->stage3e1Fire.setTextureRect(this->stage3e1Frame);
			this->stage3e1Fire.setPosition(this->enemyOne.getPosition().x - (this->textures["STAGE3ENEMY1"]->getSize().x / 2) * 2.75f, this->enemyOne.getPosition().y - (this->textures["STAGE3ENEMY1"]->getSize().y) * 2.75f + 38.f);
		}
	}

}

void Enemy::updateStage3Enemy2()
{
	if (this->type == 13)
	{
		this->stage3e2AnimationTimer += 0.1f; 

		if (this->stage3e2AnimationTimer >= this->stage3e2AnimationSpeed)
		{
			// Reset timer
			this->stage3e2AnimationTimer = 0.f;

			// Update frame
			this->stage3e2CurrentFrame++;
			if (this->stage3e2CurrentFrame >= 8) 
				this->stage3e2CurrentFrame = 0;

			// Set texture rect
			this->stage3e2Frame.left = this->stage3e2CurrentFrame * 64;
			this->stage3e2Fire.setTextureRect(this->stage3e2Frame);
			this->stage3e2Fire.setPosition(this->enemyOne.getPosition().x - (this->textures["STAGE3ENEMY2"]->getSize().x / 2) * 2.75f - 1.f, this->enemyOne.getPosition().y - (this->textures["STAGE3ENEMY2"]->getSize().y) * 2.75f + 50.f);
		}
	}
}

void Enemy::updateStage3Enemy3()
{
	
	if (this->type == 14)
	{
		this->stage3e3AnimationTimer += 0.1f;

		if (this->stage3e3AnimationTimer >= this->stage3e3AnimationSpeed)
		{
			// Reset timer
			this->stage3e3AnimationTimer = 0.f;

			// Update frame
			this->stage3e3CurrentFrame++;
			if (this->stage3e3CurrentFrame >= 8)
				this->stage3e3CurrentFrame = 0;

			// Set texture rect
			this->stage3e3Frame.left = this->stage3e3CurrentFrame * 64; 
			this->stage3e3Fire.setTextureRect(this->stage3e3Frame);
			this->stage3e3Fire.setPosition(this->enemyOne.getPosition().x - (this->textures["STAGE3ENEMY3"]->getSize().x / 2) * 2.75f + 71.f, this->enemyOne.getPosition().y - (this->textures["STAGE3ENEMY3"]->getSize().y) * 2.75f + 10.f);
		}
	}
}

void Enemy::updateStage3Enemy4()
{
	if (this->type == 15)
	{
		this->stage3e4AnimationTimer += 0.1f;

		if (this->stage3e4AnimationTimer >= this->stage3e4AnimationSpeed)
		{
			// Reset timer
			this->stage3e4AnimationTimer = 0.f;

			// Update frame
			this->stage3e4CurrentFrame++;
			if (this->stage3e4CurrentFrame >= 8)
				this->stage3e4CurrentFrame = 0;

			// Set texture rect
			this->stage3e4Frame.left = this->stage3e4CurrentFrame * 64;
			this->stage3e4Fire.setTextureRect(this->stage3e4Frame);
			this->stage3e4Fire.setPosition(this->enemyOne.getPosition().x - (this->textures["STAGE3ENEMY4"]->getSize().x / 2) * 2.75f + 38.f, this->enemyOne.getPosition().y - (this->textures["STAGE3ENEMY4"]->getSize().y) * 2.75f + 62.f);
		}
	}
}

void Enemy::updateStage3Enemy5()
{

	if (this->type == 16) {
		this->stage3e5AnimationTimer += 0.1f;

		if (this->stage3e5AnimationTimer >= this->stage3e5AnimationSpeed)
		{
			// Reset timer
			this->stage3e5AnimationTimer = 0.f;

			// Update frame
			this->stage3e5CurrentFrame++;
			if (this->stage3e5CurrentFrame >= 8)
				this->stage3e5CurrentFrame = 0;

			// Set texture rect
			this->stage3e5Frame.left = this->stage3e5CurrentFrame * 64;
			this->stage3e5Fire.setTextureRect(this->stage3e5Frame);
			this->stage3e5Fire.setPosition(this->enemyOne.getPosition().x - (this->textures["STAGE3ENEMY5"]->getSize().x / 2) * 2.75f + 176.f, this->enemyOne.getPosition().y - (this->textures["STAGE3ENEMY5"]->getSize().y) * 2.75f + 44.f);
		}
	}
}

void Enemy::updateStage3Enemy6()
{
	if(this->type == 17)
	{
		this->stage3e6AnimationTimer += 0.1f;

		if (this->stage3e6AnimationTimer >= this->stage3e6AnimationSpeed)
		{
			// Reset timer
			this->stage3e6AnimationTimer = 0.f;

			// Update frame
			this->stage3e6CurrentFrame++;
			if (this->stage3e6CurrentFrame >= 8)
				this->stage3e6CurrentFrame = 0;

			// Set texture rect
			this->stage3e6Frame.left = this->stage3e6CurrentFrame * 64;
			this->stage3e6Fire.setTextureRect(this->stage3e6Frame);
			this->stage3e6Fire.setPosition(this->enemyOne.getPosition().x - (this->textures["STAGE3ENEMY6"]->getSize().x / 2) * 2.75f - 25.f, this->enemyOne.getPosition().y - (this->textures["STAGE3ENEMY6"]->getSize().y) * 2.75f + 212.f);
		}
	
	}

}



void Enemy::render(sf::RenderTarget& target)
{

	if (this->type == 5)
	{
		target.draw(this->bomberFire);
	}

	if (this->type == 6)
	{
		target.draw(this->scoutFire);
	}

	if (this->type == 7)
	{
		target.draw(this->frigateFire);
	}

	if (this->type == 8)
	{
		target.draw(this->fighterFire);
	}

	if (this->type == 9)
	{
		target.draw(this->supportFire);
	}

	if (this->type == 10)
	{
		target.draw(this->torpedoFire);
	}

	if (this->type == 12)
	{
		target.draw(this->stage3e1Fire);
	}

	if (this->type == 13)
	{
		target.draw(this->stage3e2Fire);
	}

	if (this->type == 14)
	{
		target.draw(this->stage3e3Fire);
	}

	if (this->type == 15)
	{
		target.draw(this->stage3e4Fire);
	}

	if(this-> type == 16)
	{
		target.draw(this->stage3e5Fire);
	}

	if(this-> type == 17)
	{
		target.draw(this->stage3e6Fire);
	}

	target.draw(this->enemyOne);

}
