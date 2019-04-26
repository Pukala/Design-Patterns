#include <iostream>

class Gun
{
public:
  virtual void fire() = 0;
};

class AK47 : public Gun
{
public:
  void fire() override
  {
     std::cout << "tu tu tu tu tu\n";
  }
};

class CreatorGun
{
public:
  virtual Gun* createGun() = 0;
};

class CreatorAK46 : public CreatorGun
{
public:
  Gun* createGun() override
  {
    return new AK47();
  }
};

int main()
{
  CreatorGun* creator = new CreatorAK46();
  Gun* gun = creator->createGun();

  gun->fire();
  delete creator;
  delete gun;
}
