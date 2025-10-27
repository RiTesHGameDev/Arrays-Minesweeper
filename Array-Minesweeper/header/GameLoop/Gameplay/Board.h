#pragma once
#include <SFML/Graphics.hpp>

namespace Gameplay
{
	class Board
	{
	private:
		const float board_width = 866.0f;
		const float board_height = 1080.0f;
		const float board_position = 530.0f;

		const std::string board_texture_path = "assets/textures/board.png";
		sf::Texture board_texture;
		sf::Sprite board_sprite;

		void Initialize_Board_Image();
		void Initialize();

	public:
		Board();
		void Render(sf::RenderWindow& window);
	};
}