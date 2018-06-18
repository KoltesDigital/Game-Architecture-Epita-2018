#pragma once

namespace engine
{
	namespace backend
	{
		struct Position
		{
			int row;
			int column;

			bool operator ==(const Position &other)
			{
				return row == other.row
					&& column == other.column;
			}
		};
	}
}
