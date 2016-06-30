#include "pch.h"
#include "TetrominoRender.h"

namespace Library
{
	const std::uint32_t TetrominoRender::numAnimationFrames = 32;

	const std::string TetrominoRender::mPaths[] { 
		"Sprites/hideBoardPowerup1.png",
		"Sprites/hideBoardPowerup2.png",
		"Sprites/hideBoardPowerup3.png",
		"Sprites/hideBoardPowerup4.png",
		"Sprites/MainMenu.png",
		"Sprites/MenuSelector.png",
		"Sprites/background.png",
		"Sprites/background1.png",
		"Sprites/background2.png",
		"Sprites/background3.png",
		"Sprites/background4.png",
		"Sprites/background5.png",
		"Sprites/background6.png",
		"Sprites/background7.png",
		"Sprites/backgroundSelected.png",
		"Sprites/WinPage.png",
		"Sprites/green_32.png",
		"Sprites/pink_32.png",
		"Sprites/blue_32.png",
		"Sprites/yellow_32.png",
		"Sprites/purple_32.png",
		"Sprites/orange_32.png",
		"Sprites/yellow_arrow.png",
		"Sprites/purple_arrow.png",
		"Sprites/board.png",
		"Sprites/coming_up_board_three.png",
		"Sprites/coming_up_board.png",
		"Sprites/power_up_board.png",
		"Sprites/bar_at_bottom_board.png",
		"Sprites/Win_Paul.png",
		"Sprites/Lose_Paul.png",
		"Sprites/Win_Tom.png",
		"Sprites/Lose_Tom.png",
		"Sprites/TopFour.png",
		"Sprites/Splat.png",
		"Sprites/Holes.png",
		"Sprites/PushUp.png",
		"Fonts/8bit16.ttf" };

	const std::string TetrominoRender::mAnimationPaths[] {
		"Sprites/IntroAnimation/TetrisIntro_Frame01.png",
		"Sprites/IntroAnimation/TetrisIntro_Frame02.png",
		"Sprites/IntroAnimation/TetrisIntro_Frame03.png",
		"Sprites/IntroAnimation/TetrisIntro_Frame04.png",
		"Sprites/IntroAnimation/TetrisIntro_Frame05.png",
		"Sprites/IntroAnimation/TetrisIntro_Frame06.png",
		"Sprites/IntroAnimation/TetrisIntro_Frame07.png",
		"Sprites/IntroAnimation/TetrisIntro_Frame08.png",
		"Sprites/IntroAnimation/TetrisIntro_Frame09.png",
		"Sprites/IntroAnimation/TetrisIntro_Frame10.png",
		"Sprites/IntroAnimation/TetrisIntro_Frame11.png",
		"Sprites/IntroAnimation/TetrisIntro_Frame12.png",
		"Sprites/IntroAnimation/TetrisIntro_Frame13.png",
		"Sprites/IntroAnimation/TetrisIntro_Frame14.png",
		"Sprites/IntroAnimation/TetrisIntro_Frame15.png",
		"Sprites/IntroAnimation/TetrisIntro_Frame16.png",
		"Sprites/IntroAnimation/TetrisIntro_Frame17.png",
		"Sprites/IntroAnimation/TetrisIntro_Frame18.png",
		"Sprites/IntroAnimation/TetrisIntro_Frame19.png",
		"Sprites/IntroAnimation/TetrisIntro_Frame20.png",
		"Sprites/IntroAnimation/TetrisIntro_Frame21.png",
		"Sprites/IntroAnimation/TetrisIntro_Frame22.png",
		"Sprites/IntroAnimation/TetrisIntro_Frame23.png",
		"Sprites/IntroAnimation/TetrisIntro_Frame24.png",
		"Sprites/IntroAnimation/TetrisIntro_Frame25.png",
		"Sprites/IntroAnimation/TetrisIntro_Frame26.png",
		"Sprites/IntroAnimation/TetrisIntro_Frame27.png",
		"Sprites/IntroAnimation/TetrisIntro_Frame28.png",
		"Sprites/IntroAnimation/TetrisIntro_Frame29.png",
		"Sprites/IntroAnimation/TetrisIntro_Frame30.png",
		"Sprites/IntroAnimation/TetrisIntro_Frame31.png",
		"Sprites/IntroAnimation/TetrisIntro_Frame32.png"
	};

	TetrominoRender::InstancePtr TetrominoRender::sInstance;

	TetrominoRender::TetrominoRender()
	{
		mTextures = new sf::Texture[(uint32_t)TextureType::Max];
		mAnimationTextures = new sf::Texture[numAnimationFrames];
		LoadAllTextures();
	}

	void TetrominoRender::LoadAllTextures()
	{

		for (std::uint32_t i = 0; i < (uint32_t)TextureType::Max; ++i)
		{
			if (!mTextures[i].loadFromFile(mPaths[i]))
			{
				throw std::exception(("There was problem with loading the texture at the path: " + mPaths[i]).c_str());
			}
		}
		if (!mFont.loadFromFile(mPaths[(uint32_t)TextureType::Max]))
		{
			throw std::exception(("There was problem with loading the texture at the path: " + mPaths[(uint32_t)TextureType::Max]).c_str());
		}
		for (std::uint32_t i = 0; i < numAnimationFrames; ++i)
		{
			if (!mAnimationTextures[i].loadFromFile(mAnimationPaths[i]))
			{
				throw std::exception(("There was problem with loading the texture at the path: " + mAnimationPaths[i]).c_str());
			}
		}
	}

	sf::Vector2u TetrominoRender::GetSpriteDimensions(TextureType type)
	{
		return mTextures[(uint32_t)type].getSize();
	}

	TetrominoRender* TetrominoRender::GetInstance()
	{
		if (!sInstance.Get())
		{
			sInstance = InstancePtr();
		}
		return sInstance.Get();
	}

	TetrominoRender::~TetrominoRender()
	{
		delete[] mTextures;
		delete[] mAnimationTextures;
	}

	void TetrominoRender::RenderOnScreen(sf::RenderWindow& window, TextureType type, const sf::Vector2f& position, const sf::Vector2f& scale, bool flipHorizontal, float opacity)
	{
		sf::Sprite sprite;
		sprite.setTexture(mTextures[(uint32_t)type]);
		sprite.setPosition(position);

		if (flipHorizontal)
		{
			sprite.setOrigin((float)mTextures[(uint32_t)type].getSize().x, 0.0f);
			sprite.setScale(sf::Vector2f(-1.0f, 1.0f));
		}
		else
		{
			sprite.setScale(scale);
		}

		if (opacity > 1.0f)
		{
			opacity = 1.f;
		}
		else if (opacity < 0.f)
		{
			opacity = 0.f;
		}

		opacity *= 255;
		sprite.setColor(sf::Color(255, 255, 255, (sf::Uint8)opacity));

		window.draw(sprite);
	}

	void TetrominoRender::RenderFrame(sf::RenderWindow& window, std::int32_t frameNum, const sf::Vector2f& position, const sf::Vector2f& scale)
	{
		sf::Sprite sprite;
		sprite.setTexture(mAnimationTextures[frameNum]);
		sprite.setPosition(position);

		sprite.setScale(scale);

		window.draw(sprite);
	}

	void TetrominoRender::RenderTextOnScreen(sf::RenderWindow& window, const std::string& t, const sf::Vector2f& position, std::uint32_t textSize, sf::Color color)
	{
		sf::Text text;
		text.setFont(mFont);
		text.setString(t);
		text.setCharacterSize(textSize);
		text.setColor(color);
		text.setPosition(position);
		window.draw(text);
	}
}
