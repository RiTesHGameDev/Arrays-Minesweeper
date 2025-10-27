#pragma once
#include "../../header/GameLoop/Gameplay/Board.h"
#include "SFML/Graphics.hpp"

namespace Gameplay
{
	class GameplayManager
	{
	private:
		const float background_aplha = 85.0f;

		sf::Texture background_texture;
		sf::Sprite background_sprite;
		std::string background_texture_path = "assets/textures/minsweeper_bg.png";
		Board* board;

		void Initialize();
		void Initialize_Variables();
		void Initialize_Background_Image();

	public:
		GameplayManager();
		~GameplayManager();
		void Render(sf::RenderWindow& window);
	};
}