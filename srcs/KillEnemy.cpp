#include "KillEnemy.hpp"
#include "GameEntity.hpp"
#include "Scene.hpp"
#include <ncurses.h>
#include "KillPlayer.hpp"

void KillEnemy::start()
{
	this->_renderBehavior = entity()->getBehavior<RenderBehavior>();
	this->_interface = entity()->scene()->getEntity("interface")->getBehavior<InterfaceBehavior>();
}

void KillEnemy::update()
{
	RenderBehavior *rb;

	for (List<EntityPair>::const_iterator it = entity()->scene()->entities().begin();
			it != entity()->scene()->entities().end(); it = it->next())
	{
		if (it->value().b()->name().find("ent") == 0)
		{
			rb = it->value().b()->getBehavior<RenderBehavior>();
			if (this->_renderBehavior->collidesWith(rb))
			{
				entity()->scene()->destroy(it->value().b());
				entity()->scene()->destroy(entity());
				this->_interface->score += it->value().b()->getBehavior<KillPlayer>()->score;
			}
		}
	}
}
