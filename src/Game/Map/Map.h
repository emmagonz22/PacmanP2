#include "Player.h"

class Map{
    public:
      Map(EntityManager*);
      void addBlock(Block*);
      void addEntity(Entity*);             //Add getter
      void setPlayer(Player*); //player setter
      Player* getPlayer(); //player getter
      int getHealthMap(); //health getter
      void tick();
      void render();
      void keyPressed(int key);
		  void mousePressed(int x, int y, int button);
		  void keyReleased(int key);
      void setHealthMap(int); //health setter
      virtual void setScore(int); //score setter
      virtual int getScore(); //score getter

    private:
      EntityManager *entityManager;
      Player *player;
};