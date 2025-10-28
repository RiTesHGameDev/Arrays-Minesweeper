#pragma once
#include <SFML/Graphics.hpp>
#include <random>
#include "../../header/GameLoop/Gameplay/Cell.h"
#include "../../header/Event/EventPollingManager.h"

namespace Gameplay
{
	class Board
	{
	private:
		Cell* cell;
		const float board_width = 866.0f;
		const float board_height = 1080.0f;
		const float board_position = 530.0f;

		const std::string board_texture_path = "assets/textures/board.png";
		sf::Texture board_texture;
		sf::Sprite board_sprite;

		static const int number_of_rows = 9;
		static const int number_of_columns = 9;

		const float horizontal_cell_padding = 115.0f;
		const float vertical_cell_paddling = 329.0f;

		void Initialize_Board_Image();
		void Initialize();
		void Create_Board();

		float Get_Cell_Width_In_Board()const;
		float Get_Cell_Height_In_Board()const;
	public:
		Board();
		void Render(sf::RenderWindow& window);
	};
}