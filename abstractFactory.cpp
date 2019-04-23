#include <iostream>
#include <string>

// ----------------------------------------> INTERFACES

class Bottle
{
public:
  virtual Bottle *createButtle() = 0;
  virtual ~Bottle() = default;
};

class Alcohol
{
public:
  virtual Alcohol *createAlcohol() = 0;
  virtual ~Alcohol() = default;
};

class Drink
{
public:
  void sell()
  {
    std::cout << "SOLD.\n";
  }
  virtual ~Drink()
  {
    delete alcohol;
    delete bottle;
  }

protected:
  Alcohol *alcohol;
  Bottle *bottle;
  virtual void assembling() = 0;
};

class AlcoholFactory
{
public:
  virtual Bottle *makeBottle() = 0;
  virtual Alcohol *makeAlcohol() = 0;
  ~AlcoholFactory() = default;
};

// <------------------------------------- INTERFACES

// -------------------------------------- PRODUCTS

class VodkaBottle : public Bottle
{
public:
  VodkaBottle() { name = "VODKA BUTTLE"; }
  Bottle *createButtle() override
  {
    std::cout << "Has been created " << name << std::endl;
    return new VodkaBottle();
  }

private:
  std::string name;
};

class AlcoholVodka : public Alcohol
{
public:
  AlcoholVodka() { name = "VODKA ALCOHOL"; }
  Alcohol *createAlcohol() override
  {
    std::cout << "Has been created " << name << std::endl;
    return new AlcoholVodka();
  }

private:
  std::string name;
};

class BeerBottle : public Bottle
{
public:
  BeerBottle() { name = "BEER BUTTLE"; }
  Bottle *createButtle() override
  {
    std::cout << "Has been created " << name << std::endl;
    return new BeerBottle();
  }

private:
  std::string name;
};

class AlcoholBeer : public Alcohol
{
public:
  AlcoholBeer() { name = "BEER ALCOHOL"; }
  Alcohol *createAlcohol() override
  {
    std::cout << "Has been created " << name << std::endl;
    return new AlcoholBeer();
  }

private:
  std::string name;
};

// <-------------------------------------  PRODUCTS

// -------------------------------------> SPECIFIC FACTORY

class VodkaFactory : public AlcoholFactory
{
public:
  Bottle *makeBottle() override
  {
    return new VodkaBottle();
  }
  Alcohol *makeAlcohol() override
  {
    return new AlcoholVodka();
  }
};

class BeerFactory : public AlcoholFactory
{
public:
  Bottle *makeBottle() override
  {
    return new BeerBottle();
  }
  Alcohol *makeAlcohol() override
  {
    return new AlcoholBeer();
  }
};

// <-------------------------------- SPECIFIC FACTORY

// ---------------------------------> SPECIFIC PRODUCTS

class Finlandia : public Drink
{
public:
  explicit Finlandia(VodkaFactory *vodkaFactory) : factory(vodkaFactory)
  {
    assembling();
  }

private:
  void assembling()
  {
    alcohol = factory->makeAlcohol();
    alcohol = alcohol->createAlcohol();

    bottle = factory->makeBottle();
    bottle = bottle->createButtle();
  }

  AlcoholFactory *factory;
};

class Tyskie : public Drink
{
public:
  explicit Tyskie(BeerFactory *beerFactory) : factory(beerFactory)
  {
    assembling();
  }

private:
  void assembling()
  {
    alcohol = factory->makeAlcohol();
    alcohol = alcohol->createAlcohol();

    bottle = factory->makeBottle();
    bottle = bottle->createButtle();
  }

  AlcoholFactory *factory;
};

// <------------------------------------ SPECIFIC PRODUCTS

class Factory
{
public:
  Drink *sellDrink(std::string type)
  {
    Drink *drink = makeDrink(type);
    drink->sell();
    return drink;
  }

private:
  Drink *makeDrink(std::string type)
  {
    Drink *drink;
    if (type == "VODKA")
    {
      drink = new Finlandia(new VodkaFactory());
    }
    else
    {
      drink = new Tyskie(new BeerFactory());
    }
    return drink;
  }
};

int main()
{
  Factory *alcoholFactory = new Factory();
  Drink *vodka = alcoholFactory->sellDrink("VODKA");
  Drink *beer = alcoholFactory->sellDrink("BEER");

  delete vodka;
  delete beer;
  delete alcoholFactory;
}