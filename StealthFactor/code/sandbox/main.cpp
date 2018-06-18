/*
struct Behavior
{
	virtual void move(x, y);
};

struct PlayerBehavior : Behavior
{

};

struct Pawn
{
	int x, y;
	std::unique_ptr<Behavior> behavior;

};

struct PlayerPawn : Pawn
{

};

struct EnemyPawn : Pawn
{
	Archetype &archetype;
};

struct Target
{
	int x, y;
};

struct Map
{
	int rows, columns;
	std::vector<Element *> elements;

	void serialize(...);
};

struct Grid
{
	Grid(Map &map) ...;

	int rows, columns;
	std::vector<Pawn> pawns;
	Target target;
};

TEST(GridTest, SimpleMove)
{
	XMLLoader ....
	Map map;
	map.serialize(loader);

	Grid grid{ map };
	auto player = grid.getPlayerPawn();
	EXPECT_EQ(sf::Vector2i{ 1, 2 }, player.getPosition());
	player.move(4, 6);
	EXPECT_EQ(sf::Vector2i{ 4, 6 }, player.getPosition());

}
*/
int main()
{

}