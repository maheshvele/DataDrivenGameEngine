#pragma once
#include <SFML/Graphics.hpp>
#include <string>
#include <vector>
#include <memory>

namespace Library
{
	class TetrominoRender
	{
	public:
		/*
		Each of these types are associated with the textures we need for the game
		*/
		enum class TextureType 
		{
			Invalid = -1,
			HideUIPowerup1,
			HideUIPowerup2,
			HideUIPowerup3,
			HideUIPowerup4,
			BackgroundMainMenu,
			BackgroundLevelSelector,
			Level1Background,
			Level2Background,
			Level3Background,
			Level4Background,
			Level5Background,
			Level6Background,
			Level7Background,
			Level8Background,
			SelectedBackground,
			WinScreenBackground,
			GreenBlock,
			PinkBlock,
			BlueBlock,
			YellowBlock,
			PurpleBlock,
			OrangeBlock,
			YellowArrow,
			PurpleArrow,
			BoardUI,
			NextThreeUI,
			NextUI,
			PowerUpUI,
			BottomUI,
			Player1Win,
			Player1Lose,
			Player2Win,
			Player2Lose,
			PowerUp1,
			PowerUp2,
			PowerUp3,
			PowerUp4,
			Max
		};

		/*
		Returns the instance of this singleton class
		*/
		static TetrominoRender* GetInstance();
		~TetrominoRender();

		/*
			@brief Method to render a sprite on the screen.
			@param window reference to the render window
			@param type the type of texture you want to render
			@param position the position on where on the window to draw the sprite
			@return void
		*/
		void RenderOnScreen(sf::RenderWindow& window, TextureType type, const sf::Vector2f& position, const sf::Vector2f& scale = sf::Vector2f(1.0f, 1.0f), bool flipHorizontal = false, float opacity = 1.0f );

		/*
		@brief Method to render a an animation frame on the screen.
		@param window reference to the render window
		@param type the type of texture you want to render
		@param position the position on where on the window to draw the animation frame
		@return void
		*/
		void TetrominoRender::RenderFrame(sf::RenderWindow& window, std::int32_t frameNum, const sf::Vector2f& position, const sf::Vector2f& scale);

		/*
			@brief Method to render text on the screen
			@param window reference to the render window
			@param reference to the string to render
			@param position the position on where on the window to draw the text
			@param textSize the size of the text, defaulted to 50
			@param color the color of the text, defaulted to white
		*/
		void RenderTextOnScreen(sf::RenderWindow& window, const std::string& text, const sf::Vector2f& position, std::uint32_t textSize = 50, sf::Color color = sf::Color::White);

		sf::Vector2u GetSpriteDimensions(TextureType type);
	private:
		class InstancePtr
		{
			friend TetrominoRender;
		public:
			InstancePtr()
				: mInstance(new TetrominoRender()){}
			~InstancePtr(){ delete mInstance; }
			TetrominoRender* Get(){ return mInstance; }
		private:
			TetrominoRender* mInstance;
		};

		TetrominoRender();
		static InstancePtr sInstance;

		void LoadAllTextures();

		static const std::string mPaths[];
		static const std::string mAnimationPaths[];
		sf::Texture* mTextures;
		sf::Texture* mAnimationTextures;
		sf::Font mFont;

		static const std::uint32_t numAnimationFrames;
	};
}
