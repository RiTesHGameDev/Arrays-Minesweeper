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
		const float board_width = 866.0f;
		const float board_height = 1080.0f;
		const float board_position = 530.0f;

		const std::string board_texture_path = "assets/textures/board.png";
		sf::Texture board_texture;
		sf::Sprite board_sprite;

		static const int number_of_rows = 9;
		static const int number_of_columns = 9;

		Cell* cell[number_of_rows][number_of_columns];

		const float horizontal_cell_padding = 115.0f;
		const float vertical_cell_paddling = 329.0f;

		std::default_random_engine random_engine;
		std::random_device random_device;

		static const int mines_count = 9;

		void Initialize_Board_Image();
		void Initialize();
		void Create_Board();

		float Get_Cell_Width_In_Board()const;
		float Get_Cell_Height_In_Board()const;

		void Populate_Board();
		void Populate_Mines();
		void Initialize_Variables();

		int Count_Mines_Around(sf::Vector2i cell_position);
		void Populate_Cells();
		bool Is_Valid_Cell_Position(sf::Vector2i cell_position);
	public:
		Board();
		void Render(sf::RenderWindow& window);
	};
}