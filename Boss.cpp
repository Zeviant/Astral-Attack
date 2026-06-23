#include "Boss.h"
#include <iostream>
#include <algorithm>

// Boss class definition
Boss::Boss(float initialHealth, float initialMoveSpeed, int type)
    : health(initialHealth), moveSpeed(initialMoveSpeed), isMovingInLoop(false), angle(0.f), isDefeated(false), defeatTimer(0.f), volumeSFX(50.f)
{
    this->type = type;

    // Load textures
    if (type == 1) {
        if (!this->bossTexture.loadFromFile("Textures/Boss1.png"))
        {
            std::cout << "TEXTURE::BOSS::FAILED_TO_LOAD" << std::endl;
        }
    }

    if(type == 2)
    {
        if (!this->bossTexture.loadFromFile("Textures/Boss2.png"))
        {
            std::cout << "TEXTURE::BOSS2::FAILED_TO_LOAD" << std::endl;
        }
        
    }

    if (type == 3)
    {
        if (!this->bossTexture.loadFromFile("Textures/Boss3.png"))
        {
            std::cout << "TEXTURE::BOSS3::FAILED_TO_LOAD" << std::endl;
        }


    }

    if (type == 1) {
        if (!this->bossFire.loadFromFile("Animations/Bossfireidle.png"))
        {
            std::cout << "TEXTURE::BOSS_ENGINE_FIRE::FAILED_TO_LOAD" << "\n";
        }
    }

    if(type == 2)
    {
        if (!this->bossFire.loadFromFile("Animations/Boss2fireidle.png"))
        {
            std::cout << "TEXTURE::BOSS2_ENGINE_FIRE::FAILED_TO_LOAD" << "\n";
        }
    }

    if (type == 3)
    {
        if (!this->bossFire.loadFromFile("Animations/Boss3fireidle.png"))
        {
            std::cout << "TEXTURE::BOSS3_ENGINE_FIRE::FAILED_TO_LOAD" << "\n";
        }
    }

    // TO BE IMPLEMENTED --
    if (!this->defeatAnimation.loadFromFile("Animations/bossDefeat.png"))
    {
        std::cout << "TEXTURE::BOSS_ENGINE_FIRE::FAILED_TO_LOAD" << "\n";
    }

    // Set textures and scales
    bossSprite.setTexture(bossTexture);
    bossSprite.setScale(3.0f, 3.0f);

    if (type == 1) {
        bossSprite.rotate(180.f);
    }
    if (type == 3)
    {
        bossSprite.setScale(4.0f, 4.0f);

    }

    // Boss position and movement initialization
    startPosition = sf::Vector2f(400.f, -250.f); // Start just above the screen
    bossSprite.setPosition(startPosition);
    loopCenter = sf::Vector2f(600.f, 300.f); // Center of the loop
    loopRadius = 200.f; // Radius of the loop

    // Engine fire animation
    this->fire.setTexture(this->bossFire);
    this->fireFrame = sf::IntRect(0, 0, 128, 128);
    this->fire.setTextureRect(this->fireFrame);
    this->fire.setScale(3.0f, 3.0f);
    if (type == 1) {
        this->fire.rotate(180.f);
    }

    if (type == 1) {
        this->fire.setPosition(
            this->bossSprite.getPosition().x + this->bossSprite.getGlobalBounds().width / 2 - this->fire.getGlobalBounds().width / 2,
            this->bossSprite.getPosition().y + this->bossSprite.getGlobalBounds().height - 100.f
        );
    }

    if(type == 2)
    {
        this->fire.setPosition(
            this->bossSprite.getPosition().x + this->bossSprite.getGlobalBounds().width / 2 - this->fire.getGlobalBounds().width / 2,
            this->bossSprite.getPosition().y + this->bossSprite.getGlobalBounds().height - 1000.f
        );
    }

    if(type == 3)
    {
        this->fire.setPosition(
            this->bossSprite.getPosition().x + this->bossSprite.getGlobalBounds().width / 2 - this->fire.getGlobalBounds().width / 2,
            this->bossSprite.getPosition().y + this->bossSprite.getGlobalBounds().height - 1000.f
        );
        this->fire.setScale(4.0f,4.0f);
    
    }

    // Animation
    this->currentFrame = 0;
    this->animationTimer = 0.f;
    this->animationSpeed = 0.1f; // Speed of the animation

    // Boss movement parameters
    this->movingDown = true;
    this->Xincrease = 0.f;
    this->Yincrease = 0.f;

    // SFX
    if (!this->dirSwapBuffer.loadFromFile("Sounds/Dirchange.wav"))
    {
        std::cout << "SOUND::DIRCHANGE::FAILED_TO_LOAD" << "\n";
    }
    this->dirSwapSound.setBuffer(this->dirSwapBuffer);

    this->dirSwapSound.setVolume(this->volumeSFX);
}

Boss::~Boss()
{
}

// Boss sprite bounds getter
const sf::FloatRect Boss::getBounds() const
{
    sf::FloatRect originalBounds = this->bossSprite.getGlobalBounds();
    float shrinkFactor = 0.75f; // Shrink the hitbox by 22.5%
    float widthReduction = originalBounds.width * (1 - shrinkFactor);
    float heightReduction = originalBounds.height * (1 - shrinkFactor);

    sf::FloatRect smallerBounds(
        originalBounds.left + widthReduction / 2, // Center the hitbox
        originalBounds.top + heightReduction / 2, // Center the hitbox
        originalBounds.width * shrinkFactor,      // Shrink the width
        originalBounds.height * shrinkFactor      // Shrink the height
    );

    return smallerBounds;
}

// Position getter
const sf::Vector2f& Boss::getPos() const
{
    return this->bossSprite.getPosition();
}

// Hp getter
const float Boss::getHp() const
{
    return this->health;
}

// Spawn function
void Boss::spawn(sf::Vector2f position, sf::Vector2f loopLocation)
{
    bossSprite.setPosition(position);
    loopCenter = loopLocation;

    isMovingInLoop = false; // Start with coming down or up
    isDefeated = false;
    defeatTimer = 0.f;
}

// Animation
void Boss::updateAnimation()
{
    if (type == 1) {
        this->animationTimer += this->animationSpeed;
        if (this->animationTimer >= 1.f)
        {
            this->animationTimer = 0.f;
            this->currentFrame++;
            if (this->currentFrame >= 8)
            {
                this->currentFrame = 0;
            }
            this->fireFrame.left = this->currentFrame * 128;
            this->fire.setTextureRect(this->fireFrame);
        }
    }

    if(type == 2)
    {
        this->animationTimer += this->animationSpeed;
        if (this->animationTimer >= 1.f)
        {
            this->animationTimer = 0.f;
            this->currentFrame++;
            if (this->currentFrame >= 12)
            {
                this->currentFrame = 0;
            }
            this->fireFrame.left = this->currentFrame * 128;
            this->fire.setTextureRect(this->fireFrame);
        }
    
    }

    if(type == 3)
    {
        this->animationTimer += this->animationSpeed;
        if (this->animationTimer >= 1.f)
        {
            this->animationTimer = 0.f;
            this->currentFrame++;
            if (this->currentFrame >= 8)
            {
                this->currentFrame = 0;
            }
            this->fireFrame.left = this->currentFrame * 128;
            this->fire.setTextureRect(this->fireFrame);
        }
    
    
    }
}

// Boss spawning and defeat animation
void Boss::update(float deltaTime)
{
    // Fall off screen if defeated
    if (isDefeated)
    {
        updateDefeatedState(deltaTime);
        return;
    }

    this->updateAnimation();
    if (!isMovingInLoop)
    {
        // Move slowly down/up to the loop center
        sf::Vector2f currentPosition = bossSprite.getPosition();
        sf::Vector2f direction = loopCenter - currentPosition;
        float distance = moveSpeed * deltaTime;
        if (distance >= std::sqrt(direction.x * direction.x + direction.y * direction.y))
        {
            isMovingInLoop = true;
        }
        else
        {
            direction = distance * direction / std::sqrt(direction.x * direction.x + direction.y * direction.y);
            bossSprite.move(direction);
        }
    }
    else
    {
        moveInLoop(deltaTime);
    }

    this->dirSwapSound.setVolume(this->volumeSFX);
}

void Boss::setVolumeSFX(float volume)
{
    volumeSFX = std::clamp(volume, 0.f, 100.f);
}

// Player pos receiver (Necessary for thid boss)
void Boss::receivePos(sf::Vector2f pos)
{
    playerPos = pos;
}

void Boss::updateDefeatedState(float deltaTime)
{
    defeatTimer += deltaTime;

    if (defeatTimer >= 2.5f)
    {
        // After 3 seconds, make the boss fall off the screen slowly
        bossSprite.move(0, moveSpeed * deltaTime + 5.f);
    }

}

// Render
void Boss::render(sf::RenderTarget& target)
{

    if (!isDefeated)
    {
        target.draw(this->fire);
    }

    target.draw(bossSprite);
}

// Reduce health
void Boss::takeDamage(float damage)
{
    health -= damage;
    if (health <= 0 && !isDefeated)
    {
        isDefeated = true;
        defeatTimer = 0.f;
    }
    std::cout << "Health remaining: " << health <<"\n";
}

// Check if alive
bool Boss::isAlive() const
{
    return health > 0;
}

// Boss movement
void Boss::moveInLoop(float deltaTime)
{
    // First boss movement
    if (type == 1) {
        // Move in a circular loop
        angle += 0.5f * deltaTime;

        float x = loopCenter.x + (loopRadius + 50) * std::cos(angle);
        float y = loopCenter.y + loopRadius * std::sin(angle);

        bossSprite.setPosition(x, y);

        if (bossSprite.getPosition().y >= 900)
        {
            this->movingDown = false;
        }

        if (bossSprite.getPosition().y <= 200)
        {
            this->movingDown = true;
        }

        if (movingDown)
        {
            loopCenter.y++;
        }
        else
        {
            loopCenter.y--;
        }

        this->fire.setPosition(
            this->bossSprite.getPosition().x + this->bossSprite.getGlobalBounds().width / 2 - 17.f,
            this->bossSprite.getPosition().y + this->bossSprite.getGlobalBounds().height - 277.f
        );
    }
    // Second boss movement
    else if(type == 2)
    {
        static float timeElapsed = 0.0f;
        static float changeDirectionInterval = 25.0f;

        if (health <= 200)
        {
            Xincrease = Xincrease + 0.03f;
            Yincrease = Yincrease + 0.03f;
        }
        else if (health <= 10)
        {
            Xincrease = Xincrease + 0.25f;
            Yincrease = Yincrease + 0.25f;
        }
        else
        {
            Xincrease = Xincrease + 0.015f;
            Yincrease = Yincrease + 0.015f;
        }

        // Speed adjustment based on health
        float speedX = 100.0f + Xincrease; // Adjust horizontal speed
        float speedY = 55.0f + Yincrease;  // Adjust vertical speed

        std::cout << speedX << "\n";

        static float directionX = 1.0f;
        static float directionY = 1.0f;

        sf::Vector2f currentPosition = bossSprite.getPosition();

        // Change direction based on the timer
        timeElapsed += deltaTime;

        if (timeElapsed >= changeDirectionInterval - 4.f && timeElapsed <= changeDirectionInterval - 3.5f)
        {
            dirSwapSound.play();
        }

        if (timeElapsed >= changeDirectionInterval) {
            int dirRandomizer = rand() % 5;
            if(dirRandomizer == 0 or dirRandomizer == 1 or dirRandomizer == 2)
            {
                directionX = -directionX;
                directionY = -directionY;
            }
            if(dirRandomizer == 3)
            {
                directionX = directionX;
                directionY = -directionY;
            }
            if(dirRandomizer == 4)
            {
                directionX = -directionX;
                directionY = directionY;
            }
            timeElapsed = 0.0f; // Reset the timer
        }

        float newX = currentPosition.x + directionX * speedX * deltaTime;
        float newY = currentPosition.y + directionY * speedY * deltaTime;

        // Bounce off the screen edges
        if (newX < 0 || newX > 1000 - bossSprite.getGlobalBounds().width) 
        {
            directionX = -directionX;
        }
        if (newY < 0 || newY > 800 - bossSprite.getGlobalBounds().height) 
        {
            directionY = -directionY;
        }

        bossSprite.setPosition(
            std::clamp(newX, 0.0f, 1000.0f - bossSprite.getGlobalBounds().width),
            std::clamp(newY, 0.0f, 800.0f - bossSprite.getGlobalBounds().height)
        );

        this->fire.setPosition(
            this->bossSprite.getPosition().x + this->bossSprite.getGlobalBounds().width / 2 - 191.f,
            this->bossSprite.getPosition().y + this->bossSprite.getGlobalBounds().height - 340.f
        );
    }
    else if (type == 3)
    {
        static float time = 0.0f;
        static bool isCharging = false;
        static bool isReturning = false;
        static sf::Vector2f chargeDirection;
        static float chargeDistance = 0.0f;
        static float chargeSpeed = 300.0f;
        static sf::Vector2f targetPosition; // New target position for returning
        static float chargeTimer = 0.0f;
        float chargeCooldown = 12.5f;
        float A = 300.0f;
        float B = 100.0f;

        // Get the boss sprite dimensions
        float bossWidth = bossSprite.getGlobalBounds().width;
        float bossHeight = bossSprite.getGlobalBounds().height;

        if (!isCharging && !isReturning)
        {
            // Infinity shape movement pattern
            time += deltaTime;
            float x = loopCenter.x + A * std::sin(time);
            float y = loopCenter.y + B * std::sin(2 * time);
            targetPosition = sf::Vector2f(x, y);
            bossSprite.setPosition(targetPosition);
        }

        chargeTimer += deltaTime;

        if(health <= 100)
        {
            chargeCooldown = 10.f;
        }

        if (chargeTimer >= chargeCooldown && !isCharging && !isReturning)
        {
            // Start charging
            isCharging = true;
            chargeTimer = 0.0f;

            // Adjust the charge direction to aim from the center of the sprite
            sf::Vector2f bossCenter = bossSprite.getPosition() + sf::Vector2f(bossWidth / 2, bossHeight / 2);
            chargeDirection = playerPos - bossCenter;
            chargeDistance = std::sqrt(chargeDirection.x * chargeDirection.x + chargeDirection.y * chargeDirection.y);

            if (chargeDistance > 0.0f)
                chargeDirection /= chargeDistance;
        }

        if (isCharging)
        {
            sf::Vector2f chargeStep = chargeDirection * chargeSpeed * deltaTime;
            bossSprite.move(chargeStep);
            chargeDistance -= std::sqrt(chargeStep.x * chargeStep.x + chargeStep.y * chargeStep.y);

            if (chargeDistance <= 0.0f)
            {
                isCharging = false;
                isReturning = true;
            }
        }
        else if (isReturning)
        {
            sf::Vector2f currentPosition = bossSprite.getPosition();
            sf::Vector2f returnDirection = targetPosition - currentPosition;
            float returnDistance = std::sqrt(returnDirection.x * returnDirection.x + returnDirection.y * returnDirection.y);

            if (returnDistance > 0.0f)
                returnDirection /= returnDistance;

            float returnSpeed = 200.0f;
            sf::Vector2f returnStep = returnDirection * returnSpeed * deltaTime;
            bossSprite.move(returnStep);

            if (returnDistance <= std::sqrt(returnStep.x * returnStep.x + returnStep.y * returnStep.y))
            {
                isReturning = false;
                time = 0.0f; // Reset time to start infinity movement smoothly
            }
        }

        // Set fire position
        this->fire.setPosition(
            this->bossSprite.getPosition().x + bossWidth / 2 - 258.f,
            this->bossSprite.getPosition().y + bossHeight - 430.f
        );
    }

}
