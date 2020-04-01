#include "Rectangle.h"

Rectangle::Rectangle( float x, float y, float width, float height )
	: 
	x { x },
	y { y },
	width { width },
	height { height }
{
}

Rectangle::Rectangle( sf::Vector2f const & position, sf::Vector2f const & size )
	:
	x { position.x },
	y { position.y },
	width { size.x },
	height { size.y }
{
}

sf::Vector2f Rectangle::getPosition() const
{
	return sf::Vector2f( x, y );
}

sf::Vector2f Rectangle::getSize() const
{
	return sf::Vector2f( width, height );
}
