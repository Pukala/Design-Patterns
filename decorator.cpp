#include <iostream>


class IGun
{
public:
	void virtual fire() = 0;
	virtual ~IGun() = default;
};

class Ak47 : public IGun
{
public:
	void fire() override
	{
		std::cout << "Ak45 shooting\n";
	}
};

class DecoratorGun : public IGun
{
public:
	explicit DecoratorGun(IGun& gun) : gun(gun)
	{
	}
	void fire() override
	{
		gun.fire();
	}
private:
	IGun& gun;
};

class Ak47WithKnife : public DecoratorGun
{
public:
	Ak47WithKnife(IGun& gun) : DecoratorGun(gun)
	{
	}
	void fire() override
	{
		DecoratorGun::fire();
		std::cout << "Knife is using to cut opponents\n";
	}
};

int main()
{
	IGun* gun = new Ak47();
	gun->fire();

	gun = new Ak47WithKnife(*gun);
	gun->fire();
	
	delete gun;
}
