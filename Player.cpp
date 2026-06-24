#include "Player.h"

void Player::initializeVariables()
{
    // Parameters initialization
    this->movementSpeed = 10.f;
    this->damage = 1.f;

    this->invincible = false;
    this->invincibilityDuration = 1.f;
    this->invincibilityTimer = 0.0f;

    this->bulletsPerSecond = 2.5f;
    this->attackCooldownMax = 60.f / this->bulletsPerSecond;
    this->attackCooldown = this->attackCooldownMax;

    if(this->difficulty == 0)
    {
        this->hpMax = 10;
        this->hp = this->hpMax;
    }

    if(this->difficulty == 1)
    {
        this->hpMax = 5;
        this->hp = this->hpMax;
    }

    if (this->difficulty == 2)
    {
        this->hpMax = 3;
        this->hp = this->hpMax;
    }

    this->shieldActive = false;
    this->shieldDuration = 4.0f;
    this->shieldTimer = 0.0f;

    this->damageMAX = false;
    this->fireRateMAX = false;
}

void Player::initializeTexture()
{
    // Load texture
    if (!this->shipFull.loadFromFile("Textures/Mainshipfix.png"))
    {
        std::cout << "TEXTURE::MAIN_SHIP::FAILED_TO_LOAD" << "\n";
    }

    if (!this->shipDamaged.loadFromFile("Textures/Mainshipdamage1.png"))
    {
        std::cout << "TEXTURE::MAIN_SHIP_DAMAGED_1::FAILED_TO_LOAD" << "\n";
    }

    if (!this->shipVeryDamaged.loadFromFile("Textures/Mainshipdamage2.png"))
    {
        std::cout << "TEXTURE::MAIN_SHIP_DAMAGED_2::FAILED_TO_LOAD" << "\n";
    }

    if (!this->shipEngine1.loadFromFile("Textures/Mainshipengine.png"))
    {
        std::cout << "TEXTURE::MAIN_SHIP_ENGINE::FAILED_TO_LOAD" << "\n";
    }

    if (!this->shipEngine1Fire.loadFromFile("Animations/Fireidle.png"))
    {
        std::cout << "TEXTURE::MAIN_SHIP_ENGINE_FIRE::FAILED_TO_LOAD" << "\n";
    }

    if (!this->shieldTexture.loadFromFile("Animations/Shield.png"))
    {
        std::cout << "TEXTURE::MAIN_SHIP_ENGINE_FIRE::FAILED_TO_LOAD" << "\n";
    }
}

void Player::initializeSprite()
{
    // Set texture to sprite
    this->ship.setTexture(this->shipFull);

    this->engine.setTexture(this->shipEngine1);

    // Resize
    this->ship.scale(2.25f, 2.25f);
    this->ship.setPosition(765.5f, 660.f);

    this->engine.setScale(2.25f, 2.25f);

    this->fire.setTexture(this->shipEngine1Fire);
    this->fireFrame = sf::IntRect(0, 0, 48, 48);
    this->fire.setTextureRect(this->fireFrame);
    this->fire.setScale(2.25f, 2.25f);
    this->fire.setColor(sf::Color::Color(230, 230, 250));

    this->shield.setTexture(this->shieldTexture);
    this->shieldFrame = sf::IntRect(0, 0, 64, 64);
    this->shield.setTextureRect(this->shieldFrame);
    this->shield.setScale(2.25f, 2.25f);
}

void Player::initializeAnimation()
{
    this->currentFrame = 0;
    this->animationTimer = 0.f;
    this->animationSpeed = 0.1f;

    this->currentFrameShield = 0;
    this->animationTimerShield = 0.f;
    this->animationSpeedShield = 0.075f;
}

// Constructors
Player::Player(int difficulty)
{
    this->difficulty = difficulty;
    this->initializeVariables();
    this->initializeTexture();
    this->initializeSprite();
    this->initializeAnimation();

    this->engine.setPosition(
        this->ship.getPosition().x + this->ship.getGlobalBounds().width / 2 - this->engine.getGlobalBounds().width / 2,
        this->ship.getPosition().y + this->ship.getGlobalBounds().height - 81.f
    );

    this->fire.setPosition(
        this->engine.getPosition().x + this->engine.getGlobalBounds().width / 2 - this->fire.getGlobalBounds().width / 2,
        this->engine.getPosition().y + this->engine.getGlobalBounds().height - 101.f
    );

    this->shield.setPosition(
        this->ship.getPosition().x + this->ship.getGlobalBounds().width / 2 - this->shield.getGlobalBounds().width / 2,
        this->ship.getPosition().y + this->ship.getGlobalBounds().height - 90.f
    );

}

Player::~Player()
{
}

// Getters

const sf::Vector2f& Player::getPos() const
{
    return this->ship.getPosition();
}

const sf::FloatRect Player::getBounds() const
{
    return this->ship.getGlobalBounds();
}

const sf::FloatRect Player::getHitbox() const
{
    const sf::FloatRect bounds = this->ship.getGlobalBounds();
    constexpr float horizontalReduction = 0.15f;
    constexpr float verticalReduction = 0.05f;

    const float horizontalInset = bounds.width * horizontalReduction / 2.f;
    const float verticalInset = bounds.height * verticalReduction / 2.f;

    return sf::FloatRect(
        bounds.left + horizontalInset,
        bounds.top + verticalInset,
        bounds.width * (1.f - horizontalReduction),
        bounds.height * (1.f - verticalReduction)
    );
}

const int& Player::getHp() const
{
    return this->hp;
}

const int& Player::getHpMax() const
{
    return this->hpMax;
}

const float& Player::getMoveSpeed() const
{
    return this->movementSpeed;
}

const float& Player::getDamage() const
{
    return this->damage;
}

const float& Player::getAttackCooldown() const
{
    return this->attackCooldownMax;
}

const float& Player::getBulletsPerSecond() const
{
    return this->bulletsPerSecond;
}

const bool Player::getFireRateMAX() const
{
    return fireRateMAX;
}

const bool Player::getDamageMAX() const
{
    return damageMAX;
}

// Player movement 
void Player::move(const float dirX, const float dirY)
{
    this->ship.move(dirX, dirY);

    this->engine.setPosition(
        this->ship.getPosition().x + this->ship.getGlobalBounds().width / 2 - this->engine.getGlobalBounds().width / 2,
        this->ship.getPosition().y + this->ship.getGlobalBounds().height - 81.f
    );

    this->fire.setPosition(
        this->engine.getPosition().x + this->engine.getGlobalBounds().width / 2 - this->fire.getGlobalBounds().width / 2,
        this->engine.getPosition().y + this->engine.getGlobalBounds().height - 101.f
    );

    this->shield.setPosition(
        this->ship.getPosition().x + this->ship.getGlobalBounds().width / 2 - this->shield.getGlobalBounds().width / 2,
        this->ship.getPosition().y + this->ship.getGlobalBounds().height - 90.f
    );
}

// Attack cooldown handling
const bool Player::canAttack()
{
    if (this->attackCooldown >= this->attackCooldownMax)
    {
        this->attackCooldown = 0.f;
        return true;
    }

    return false;
}

// Player position setters (mostly unused, made to accept both a vector and (x,y))

void Player::setPosition(const sf::Vector2f pos)
{
    this->ship.setPosition(pos);

    this->engine.setPosition(
        this->ship.getPosition().x + this->ship.getGlobalBounds().width / 2 - this->engine.getGlobalBounds().width / 2,
        this->ship.getPosition().y + this->ship.getGlobalBounds().height - 81.f
    );

    this->fire.setPosition(
        this->engine.getPosition().x + this->engine.getGlobalBounds().width / 2 - this->fire.getGlobalBounds().width / 2,
        this->engine.getPosition().y + this->engine.getGlobalBounds().height - 101.f
    );

    this->shield.setPosition(
        this->ship.getPosition().x + this->ship.getGlobalBounds().width / 2 - this->shield.getGlobalBounds().width / 2,
        this->ship.getPosition().y + this->ship.getGlobalBounds().height - 90.f
    );
}

void Player::setPosition(const float x, const float y)
{
    this->ship.setPosition(x, y);

    this->engine.setPosition(
        this->ship.getPosition().x + this->ship.getGlobalBounds().width / 2 - this->engine.getGlobalBounds().width / 2,
        this->ship.getPosition().y + this->ship.getGlobalBounds().height - 81.f
    );

    this->fire.setPosition(
        this->engine.getPosition().x + this->engine.getGlobalBounds().width / 2 - this->fire.getGlobalBounds().width / 2,
        this->engine.getPosition().y + this->engine.getGlobalBounds().height - 101.f
    );

    this->shield.setPosition(
        this->ship.getPosition().x + this->ship.getGlobalBounds().width / 2 - this->shield.getGlobalBounds().width / 2,
        this->ship.getPosition().y + this->ship.getGlobalBounds().height - 90.f
    );
}

// Setters

void Player::setHp(const int newhp)
{
    this->hp = newhp;

    if (this->hp > hpMax)
    {
        this->hp = hpMax;
    }
    updateSprite();
}

void Player::loseHp(const int value)
{
    if (!invincible)
    {
        this->hp = this->hp - value;
        if (this->hp < 0)
        {
            this->hp = 0;
        }
        startInvincibility();
    }

    this->updateSprite();
    
}

void Player::setDamage(const float val)
{
    this->damage = val;
}

// Invincibility frame handling

bool Player::isInvincible() const
{
    return invincible;
}

void Player::startInvincibility()
{
    invincible = true;
    invincibilityTimer = 0.0f;
}

// Stat upgrades

void Player::upgradeDamage()
{
    this->damage = this->damage + 0.25f;
    if(this->damage >= 4.0)
    {
        this->damage = 4.0;
        this->damageMAX = true;
    }
    std::cout << this->damage << "\n";
}

void Player::upgradeAttackSpeed()
{
    this->bulletsPerSecond = this->bulletsPerSecond + 0.25f;
    if(this->bulletsPerSecond >= 5.f)
    {
        this->bulletsPerSecond = 5.f;
        this->fireRateMAX = true;
    }

    this->attackCooldownMax = 60.f / this->bulletsPerSecond;
}

// Load saved ship color

void Player::setShipColor(int c)
{
    switch (c)
    {
    case 0:
        this->ship.setColor(sf::Color(255, 255, 255));
        break;
    case 1:
        this->ship.setColor(sf::Color(40, 132, 203));
        break;
    case 2:
        this->ship.setColor(sf::Color(53, 83, 10));
        break;
    case 3:
        this->ship.setColor(sf::Color(255, 177, 0));
        break;
    case 4:
        this->ship.setColor(sf::Color(153, 102, 255));
        break;
    case 5:
        this->ship.setColor(sf::Color(212, 44, 77));
        break;
    case 6:
        this->ship.setColor(sf::Color(65, 65, 65));
        break;
    }
}

// Load saved fire color

void Player::setFireColor(int c)
{
    switch (c)
    {
    case 0:
        if (!this->shipEngine1Fire.loadFromFile("Animations/Fireidle.png"))
        {
            std::cout << "TEXTURE::MAIN_SHIP_ENGINE_FIRE::FAILED_TO_LOAD" << "\n";
        }
        break;
    case 1:
        if (!this->shipEngine1Fire.loadFromFile("Animations/Fireidleyellow.png"))
        {
            std::cout << "TEXTURE::MAIN_SHIP_ENGINE_FIRE::FAILED_TO_LOAD" << "\n";
        }
        break;
    case 2:
        if (!this->shipEngine1Fire.loadFromFile("Animations/Fireidlegreen.png"))
        {
            std::cout << "TEXTURE::MAIN_SHIP_ENGINE_FIRE::FAILED_TO_LOAD" << "\n";
        }
        break;
    case 3:
        if (!this->shipEngine1Fire.loadFromFile("Animations/Fireidlewhite.png"))
        {
            std::cout << "TEXTURE::MAIN_SHIP_ENGINE_FIRE::FAILED_TO_LOAD" << "\n";
        }
        break;
    }
}

// Updates

void Player::updateAttackCooldown()
{
    if (this->attackCooldown < this->attackCooldownMax)
    {
        this->attackCooldown += 1.f;
    }
}

void Player::setAttackCooldown(float val)
{
    this->attackCooldown = val;
}

void Player::updateSprite()
{
    if(difficulty == 0)
    {
        if (this->hp == 5 or this->hp == 4 or this->hp == 3)
        {
            this->ship.setTexture(this->shipDamaged);
        }
        else if (this->hp <= 2)
        {
            this->ship.setTexture(this->shipVeryDamaged);
        }
        else
        {
            this->ship.setTexture(this->shipFull);
        }
    
    }

    if(difficulty == 1)
    {
        if (this->hp == 3 or this->hp == 2)
        {
            this->ship.setTexture(this->shipDamaged);
        }
        else if (this->hp <= 1)
        {
            this->ship.setTexture(this->shipVeryDamaged);
        }
        else
        {
            this->ship.setTexture(this->shipFull);
        }
    }

    if(difficulty == 2)
    {
        if(this->hp == 2)
        {
            this->ship.setTexture(this->shipDamaged);
        }
        else if(this->hp <= 1)
        {
            this->ship.setTexture(this->shipVeryDamaged);
        }
        else
        {
            this->ship.setTexture(this->shipFull);
        }
    }

}

void Player::updateAnimation()
{
    this->animationTimer += this->animationSpeed;
    if (this->animationTimer >= 1.f)
    {
        this->animationTimer = 0.f;
        this->currentFrame++;
        if (this->currentFrame >= 3)
        {
            this->currentFrame = 0;
        }
        this->fireFrame.left = this->currentFrame * 48;
        this->fire.setTextureRect(this->fireFrame);
    }

}

void Player::updateAnimationShield()
{
    if (this->shieldActive)
    {
        this->animationTimerShield += this->animationSpeedShield;
        if (this->animationTimerShield >= 1.f)
        {
            this->animationTimerShield = 0.f;
            this->currentFrameShield++;
            if (this->currentFrameShield >= 8)
            {
                this->currentFrameShield = 0;
            }
            this->shieldFrame.left = this->currentFrameShield * 64;
            this->shield.setTextureRect(this->shieldFrame);
        }
    }
}

void Player::update()
{
    this->updateAttackCooldown();
    this->updateAnimation();
    this->updateAnimationShield();

    if (this->isInvincible() && !this->shieldActive)
    {
        invincibilityTimer += 0.01667f;
        if (invincibilityTimer >= invincibilityDuration)
        {
            invincible = false;
        }
    }

    if (this->shieldActive)
    {
        this->shieldTimer += 0.01667f;
        if (this->shieldTimer >= this->shieldDuration)
        {
            this->shieldActive = false;
            this->invincible = false;

        }
    }
}

// Render

void Player::render(sf::RenderTarget& target)
{
    target.draw(this->fire);
    target.draw(this->engine);
    target.draw(this->ship);
    if (this->shieldActive) // Render shield only if active
    {
        target.draw(this->shield);
    }
}

// Shield mechanic

void Player::activateShield()
{
    if (!this->shieldActive) // Ensure shield can only be activated if not already active
    {
        this->shieldActive = true;
        this->shieldTimer = 0.0f;
        this->invincible = true;
    }
}
