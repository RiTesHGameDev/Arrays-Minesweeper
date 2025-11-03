#include "../../header/GameLoop/Gameplay/Board.h"
#include "../../header/GameLoop/Gameplay/GameplayManager.h"
#include <iostream>

namespace Gameplay
{
	Board::Board(GameplayManager* gameplay_manager)
	{
		Initialize(gameplay_manager);
	}
	void Board::Initialize(GameplayManager* gameplay_manager)
	{
		Initialize_Board_Image();
		Initialize_Variables(gameplay_manager);
		Create_Board();
	}
	void Board::Initialize_Variables(GameplayManager* gameplayManager)
	{
		this->gameplay_manager = gameplayManager;
		//funtion to initialize random engine
		random_engine.seed(random_device());
		board_state = BoardState::FIRST_CELL;
	}
	void Board::Initialize_Board_Image()
	{
		if (!board_texture.loadFromFile(board_texture_path))
		{
			std::cerr << "Failed to load board texture" << std::endl;
		}
		board_sprite.setTexture(board_texture);
		board_sprite.setPosition(board_position,0);
		board_sprite.setScale(board_width / board_texture.getSize().x,
			board_height / board_texture.getSize().y);
	}
	void Board::Create_Board()
	{
		float cell_width = Get_Cell_Width_In_Board();
		float cell_height = Get_Cell_Height_In_Board();

		for(int row = 0; row < number_of_rows; ++row)
		{
			for (int col = 0; col < number_of_columns; ++col)
			{
				cell[row][col] = new Cell(cell_width, cell_height, sf::Vector2i(row,col),this);
			}
		}
	}
	float Board::Get_Cell_Width_In_Board()const
	{
		return (board_width - horizontal_cell_padding) / number_of_columns;
	}
	float Board::Get_Cell_Height_In_Board()const
	{
		return (board_height - vertical_cell_paddling) / number_of_rows;
	}
	void Board::Render(sf::RenderWindow& window)
	{
		window.draw(board_sprite);
		for (int row = 0; row < number_of_rows; ++row)
		{
			for (int col = 0; col < number_of_columns;++col)
			{
				cell[row][col]->Render(window);

			}
		}
	}
	void Board::Populate_Board(sf::Vector2i cell_position)
	{
		Populate_Mines(cell_position);
		Populate_Cells();
	}
	void Board::Populate_Mines(sf::Vector2i first_cell_position)
	{
		std::uniform_int_distribution<int>x_dist(0, number_of_columns - 1);
		std::uniform_int_distribution<int>y_dist(0,number_of_rows - 1);

		int mine_placed = 0;

		while (mine_placed < mines_count)
		{
			int x = x_dist(random_engine);
			int y = y_dist(random_engine);

			if (Is_Valid_Mine_Position(first_cell_position, x, y))
				continue;

			cell[x][y]->Set_Cell_Type(CellType::MINE);
			++mine_placed;
		}
	}
	void Board::Populate_Cells()
	{
		for (int row = 0;row < number_of_rows;++row)
		{
			for (int col = 0;col < number_of_columns;++col)
			{
				if (cell[row][col]->Get_Cell_Type() != CellType::MINE)
				{
					int mines_around = Count_Mines_Around(sf::Vector2i(row, col));
					cell[row][col]->Set_Cell_Type(static_cast<CellType>(mines_around));
				}
			}
		}
	}
	int Board::Count_Mines_Around(sf::Vector2i cell_position)
	{
		int mines_around = 0;

		for (int a = -1;a <= 1; ++a)
		{
			for (int b = -1;b <= 1;++b)
			{
				//skipping the current cell as need to count mines around current cell
				if ((a == 0 && b == 0) ||
					!Is_Valid_Cell_Position(sf::Vector2i(cell_position.x + a, cell_position.y + b)))
				
					continue;
				//checking and counting mines
				if (cell[cell_position.x + a][cell_position.y + b]->Get_Cell_Type() == CellType::MINE)
				{
					mines_around++;
				}
			}
		}
		return mines_around;
	}
	bool Board::Is_Valid_Cell_Position(sf::Vector2i cell_position)
	{
		return(cell_position.x >= 0 && cell_position.y >= 0 &&
			cell_position.x < number_of_columns && cell_position.y < number_of_rows);
	}
	bool Board::Is_Valid_Mine_Position(sf::Vector2i first_cell_position, int x, int y)
	{
		return (x == first_cell_position.x && y == first_cell_position.y) || 
			cell[x][y]->Get_Cell_Type() == CellType::MINE;
	}
	void Board::Update(Event::EventPollingManager& event_manager, const sf::RenderWindow& window)
	{
		for (int row = 0;row < number_of_rows;++row)
		{
			for (int col = 0;col < number_of_columns;++col)
			{
				cell[row][col]->Update(event_manager, window);
			}
		}
	}
	void Board::On_Cell_Button_Clicked(sf::Vector2i cell_position,
		Buttons::MouseButtonType mouse_button_type)
	{
		if(mouse_button_type == MouseButtonType::LEFT_MOUSE_BUTTON)
		{ 
			Sound::SoundManager::PlaySound(Sound::SoundType::BUTTON_CLICK);
			Open_Cell(cell_position);//open the cell when left clicked
		}
		else if (mouse_button_type == MouseButtonType::RIGHT_MOUSE_BUTTON)
		{
			Sound::SoundManager::PlaySound(Sound::SoundType::FLAG);
			Toggle_Flag(cell_position);
		}
	}
	void Board::Open_Cell(sf::Vector2i cell_position)
	{
		if (!cell[cell_position.x][cell_position.y]->Can_Open_Call())
			return;
		if (board_state == BoardState::FIRST_CELL)
		{
			Populate_Board(cell_position);
			board_state = BoardState::PLAYING;
		}
		Process_Cell_Type(cell_position);
	}
	void Board::Toggle_Flag(sf::Vector2i cell_position)
	{
		cell[cell_position.x][cell_position.y]->Toggle_Flag();
		flagged_cells += (cell[cell_position.x][cell_position.y]->Get_Cell_State() == CellState::FLAGGED)?1:-1;
	}
	void Board::Process_Cell_Type(sf::Vector2i cell_position)
	{
		switch (cell[cell_position.x][cell_position.y]->Get_Cell_Type())
		{
		case CellType::EMPTY:
			Process_Empty_Cell(cell_position);
			break;
		case CellType::MINE:
			Process_Mine_Cell(cell_position);
			break;
		default:
			cell[cell_position.x][cell_position.y]->Open();
			break;
		}
	}
	void Board::Process_Empty_Cell(sf::Vector2i cell_position)
	{
		CellState cell_state = cell[cell_position.x][cell_position.y]->Get_Cell_State();
		switch (cell_state)
		{
		case CellState::OPEN:
			return;
		default:
			cell[cell_position.x][cell_position.y]->Open();

			//checking neighbors
			for (int a = -1;a <= 1;++a)
			{
				for (int b = -1;b <= 1;++b)
				{
					//storing neighbor cell's position
					sf::Vector2i next_cell_position = sf::Vector2i(cell_position.x + a, cell_position.y + b);
					
					//skip current cell and invalid positions
					if (a == 0 && b == 0 || !Is_Valid_Cell_Position(next_cell_position))
					{
						continue;
					}

					//flagged cell state
					CellState next_cell_state = cell[cell_position.x][cell_position.y]->Get_Cell_State();
					if (next_cell_state == CellState::FLAGGED)
					{
						Toggle_Flag(next_cell_position);
					}

					//Opening neighbots cell
					Open_Cell(next_cell_position);
				}
			}
		}
	}
	void Board::Process_Mine_Cell(sf::Vector2i cell_position)
	{
		gameplay_manager->Set_Game_Result(GameResult::LOST);
	}
	void Board::Reveal_All_Mines()
	{
		for (int row = 0;row < number_of_rows;++row)
		{
			for (int col = 0;col < number_of_columns;++col)
			{
				if (cell[row][col]->Get_Cell_Type() == CellType::MINE)
				{
					cell[row][col]->Set_Cell_State(CellState::OPEN);
				}
			}
		}
	}
	void Board::Flag_All_Mines()
	{
		for (int row = 0;row < number_of_rows;++row)
		{
			for (int col = 0; col < number_of_columns; ++col)
			{
				if (cell[row][col]->Get_Cell_Type() == CellType::MINE &&
					cell[row][col]->Get_Cell_State() != CellState::FLAGGED)
				{
					cell[row][col]->Set_Cell_State(CellState::FLAGGED);
				}
			}
		}
	}
	bool Board::Are_All_Cells_Open()
	{
		int total_cells = number_of_columns * number_of_rows;
		int open_cell = 0;

		for (int row = 0; row < number_of_rows; ++row)
		{
			for (int col = 0; col < number_of_columns; ++col)
			{
				if (cell[row][col]->Get_Cell_State() == CellState::OPEN &&
					cell[row][col]->Get_Cell_Type() != CellType::MINE)
				{
					open_cell++;
				}
			}
		}
		return open_cell == (total_cells - mines_count);
	}
	int Board::Get_Remaining_Mines_Counts()const
	{
		return mines_count - flagged_cells;
	}
	BoardState Board::Get_Board_State()const
	{
		return board_state;
	}
	void Board::Set_Board_State(BoardState state)
	{
		board_state = state;
	}
}