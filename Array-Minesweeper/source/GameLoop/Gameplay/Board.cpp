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
		Create_Board();
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

		cell = new Cell(cell_width, cell_height, sf::Vector2i(0, 0));
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
		cell->Render(window);
	}
}