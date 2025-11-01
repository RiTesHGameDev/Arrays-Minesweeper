#include "../../header/GameLoop/Gameplay/Board.h"
#include <iostream>

namespace Gameplay
{
	Board::Board()
	{
		Initialize();
	}
	void Board::Initialize()
	{
		Initialize_Board_Image();
		Initialize_Variables();
		Create_Board();

		Populate_Board();
	}
	void Board::Initialize_Variables()
	{
		//funtion to initialize random engine
		random_engine.seed(random_device());
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
	void Board::Populate_Board()
	{
		Populate_Mines();
		Populate_Cells();
	}
	void Board::Populate_Mines()
	{
		std::uniform_int_distribution<int>x_dist(0, number_of_columns - 1);
		std::uniform_int_distribution<int>y_dist(0,number_of_rows - 1);

		int mine_placed = 0;

		while (mine_placed < mines_count)
		{
			int x = x_dist(random_engine);
			int y = y_dist(random_engine);

			if (cell[x][y]->Get_Cell_Type()!= CellType::MINE)
			{
				cell[x][y]->Set_Cell_Type(CellType::MINE);
				++mine_placed;
			}
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
			Open_Cell(cell_position);//open the cell when left clicked
		}
		else if (mouse_button_type == MouseButtonType::RIGHT_MOUSE_BUTTON)
		{

		}
	}
	void Board::Open_Cell(sf::Vector2i cell_position)
	{
		if (!cell[cell_position.x][cell_position.y]->Can_Open_Call())
		{
			return;
		}
		cell[cell_position.x][cell_position.y]->Open();
	}
}