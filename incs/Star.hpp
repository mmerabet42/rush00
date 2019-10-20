#ifndef STAR_HPP
# define STAR_HPP

# include "List.hpp"
# include "GameEntity.hpp"
# include "Behavior.hpp"

class Star : public Behavior
{
public:
  void start();
  void update();
  void set(int p_hauteur, int p_speed);

private:
	int reset;
  int hauteur;
  int speed;
};

#endif
