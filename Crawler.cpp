#include "Crawler.h"

// allows non default values for Crawler
Crawler::Crawler(int id, Position position, Direction direction, int size, list<Position> path)
    :id(id), position(position), direction(direction), size(size), path(path)
{

}