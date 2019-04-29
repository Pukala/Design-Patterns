#include <iostream>

class Singleton
{
public:
	static Singleton* createSingleton()
	{
		if (instance == nullptr)
		{
			instance = new Singleton();
			return instance;
		}
		return instance;
	}
	Singleton(const Singleton&) = delete;
	Singleton(Singleton&&) = delete;
	Singleton &operator=(const Singleton&) = delete;
	Singleton &operator=(Singleton&&) = delete;
private:
	Singleton()
	{
		std::cout << "I HAVE CREATED OBJECT\n";
	}
	static Singleton *instance;
};

Singleton* Singleton::instance = nullptr;

int main()
{
	Singleton * s1 = Singleton::createSingleton();
	Singleton * s2 = Singleton::createSingleton();

	std::cout << "ADRES OF S1 = " << s1 << std::endl;
	std::cout << "ADRES OF S2 = " << s2 << std::endl;
}
