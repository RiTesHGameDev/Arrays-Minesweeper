#pragma once
#include <SFML/Graphics.hpp>
#include <random>
#include "../../header/GameLoop/Gameplay/Cell.h"
#include "../../header/Event/EventPollingManager.h"

namespace Gameplay
{
	class GameplayManager;
	enum class BoardState
	{
		FIRST_CELL,
		PLAYING,
		COMPLETED
	};
	class Board
	{
	private:
		BoardState board_state;
		GameplayManager* gameplay_manager;
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
		void Initialize(GameplayManager* gameplay_manager);
		void Create_Board();

		float Get_Cell_Width_In_Board()const;
		float Get_Cell_Height_In_Board()const;

		void Populate_Board(sf::Vector2i cell_position);
		void Populate_Mines(sf:: Vector2i first_cell_position);
		void Initialize_Variables(GameplayManager* gameplay_manager);

		int Count_Mines_Around(sf::Vector2i cell_position);
		void Populate_Cells();
		bool Is_Valid_Cell_Position(sf::Vector2i cell_position);

		int flagged_cells;
		void Open_Cell(sf::Vector2i cell_position);
		void Toggle_Flag(sf::Vector2i cell_position);

		void Process_Cell_Type(sf::Vector2i cell_Position);
		void Process_Empty_Cell(sf::Vector2i cell_Position);
		void Process_Mine_Cell(sf::Vector2i cell_position);

		bool Is_Valid_Mine_Position(sf::Vector2i first_cell_position, int x, int y);
	public:
		Board(GameplayManager* gameplay_manager);
		int Get_Remaining_Mines_Counts()const;
		BoardState Get_Board_State()const;
		bool Are_All_Cells_Open();
		void Flag_All_Mines();
		void Set_Board_State(BoardState state);
		void Reveal_All_Mines();
		void On_Cell_Button_Clicked(sf::Vector2i cell_position, UIElements::Buttons::MouseButtonType mouse_button_type);
		void Render(sf::RenderWindow& window);
		void Update(Event::EventPollingManager& event_Manager, const sf::RenderWindow& window);
	};
}