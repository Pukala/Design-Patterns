/*
    Oddziela tworzenie zlozonego obiektu od jego reprezentacji,
    dzieki czemu ten sam proces konstrukcji moze prowadzic do
    powstania roznych reprezentacji.

    Budowniczego powinno sie stosowac gdy:
    -tworzenie zlozonego obiektu powinno byc niezalezne od skladnikow
     i sposobu jego tworzenia

    -kiedy proces konstrukcji musi umozliwic tworzenie roznych
     reprezentacji generowanego obiektu

    Konsekwencje:
    -Mozliwosc modyfikowania wewnetrznej reprezentacji produktu
    -Odizolowanie reprezentacji od kodu sluzacego do tworzenia
     produktu
    -Wieksza kontrola nad procesem tworzenia
*/

#include <iostream>
#include <string>

enum class Doors
{
  scissorDoors,
  suicideDoors,
  swanDoor
};
enum class Engine
{
  diesel,
  petrol,
  turbo
};
enum class Color
{
  red,
  black,
  white
};

class Car // PRODUCT
{
public:
  void createDoors(Doors d)
  {
    doors = d;
  }
  void createEngine(Engine e)
  {
    engine = e;
  }
  void paintBody(Color c)
  {
    color = c;
  }
  void describeTheCar()
  {
    std::cout << "doors = " << static_cast<int>(doors) << std::endl;
    std::cout << "engine = " << static_cast<int>(engine) << std::endl;
    std::cout << "color = " << static_cast<int>(color) << std::endl;
  }

private:
  Doors doors;
  Engine engine;
  Color color;
};

class CarBuilder // builder
{

public:
  virtual ~CarBuilder() = default;

  virtual void createDoors() = 0;
  virtual void createEngine() = 0;
  virtual void paintBody() = 0;

  void newCar()
  {
    car = new Car();
  }

  Car getCar()
  {
    return *car;
  }

protected:
  Car *car;
};

class SportCarBuilder : public CarBuilder // specific builder
{
public:
  SportCarBuilder() : CarBuilder()
  {
  }

  void createDoors() override
  {
    car->createDoors(Doors::scissorDoors);
  }
  void createEngine() override
  {
    car->createEngine(Engine::turbo);
  }
  void paintBody() override
  {
    car->paintBody(Color::red);
  }
};

class LuxuryCarBuilder : public CarBuilder // konkretny budowniczy
{
public:
  LuxuryCarBuilder() : CarBuilder()
  {
  }

  void createDoors() override
  {
    car->createDoors(Doors::suicideDoors);
  }
  void createEngine() override
  {
    car->createEngine(Engine::petrol);
  }
  void paintBody() override
  {
    car->paintBody(Color::white);
  }
};

class Director // director
{
public:
  void choseBuilder(CarBuilder *b)
  {
    builder = b;
  }

  Car getCar()
  {
    return builder->getCar();
  }

  void build()
  {
    builder->newCar();
    builder->createDoors();
    builder->createEngine();
    builder->paintBody();
  }

private:
  CarBuilder *builder;
};

int main()
{
  Director *director = new Director();

  CarBuilder *sportBuilder = new SportCarBuilder();

  director->choseBuilder(sportBuilder);
  director->build();
  Car bmw = director->getCar();

  bmw.describeTheCar();
}