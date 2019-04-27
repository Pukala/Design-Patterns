#include <iostream>
#include <array>

enum class TypeOfImage
{
	landscape, selfie
};

class Image
{
public:
	virtual void draw() = 0;
	static Image *findAndClone(TypeOfImage type)
	{
		for (auto i : prototypes)
		{
			if (i->getTypeOfImage() == type)
			{
				return i->clone();
			}
		}
		return nullptr;
	}
	virtual ~Image() = default;
protected:
	virtual TypeOfImage getTypeOfImage() = 0;
	virtual Image*  clone() = 0;
	static void addPrototype(Image* image)
	{
		prototypes[itr++] = image;
	}
private:
	static std::array<Image*, 10> prototypes;
	static int itr;
};
std::array<Image*, 10> Image::prototypes;
int Image::itr;

class LandscapePicture : public Image
{
public:
	TypeOfImage getTypeOfImage() override { return TypeOfImage::landscape; }
	void draw() override { std::cout << "LandscapePicture::draw " << id << std::endl; }
	Image* clone() override { return new LandscapePicture(1); }
protected:
	explicit LandscapePicture(int unusedValue)
	{
		id = counter++;
	}
private:
	static LandscapePicture landspacePicture;
	LandscapePicture()
	{
		addPrototype(this);
	}
	int id{};
	static int counter;
};

LandscapePicture LandscapePicture::landspacePicture;
int LandscapePicture::counter = 1;

class Selfie : public Image
{
public:
	TypeOfImage getTypeOfImage() override { return TypeOfImage::selfie; }
	void draw() override { std::cout << "Selfie::draw " << id << std::endl; }
	Image*  clone() { return new Selfie(1); }
protected:
	explicit Selfie(int unusedValue)
	{
		id = counter++;
	}
private:
	Selfie()
	{
		addPrototype(this);
	}
	static Selfie selfie;
	int id{};
	static int counter;
};

Selfie Selfie::selfie;
int Selfie::counter = 1;

int main()
{
	constexpr auto numOfImage{ 3u };
	std::array<TypeOfImage, numOfImage> input{ TypeOfImage::landscape, TypeOfImage::selfie, TypeOfImage::landscape };

	std::array<Image*, numOfImage> images;

	for (auto i = 0; i < numOfImage; i++)
	{
		images.at(i) = Image::findAndClone(input.at(i));
	}

	for (auto i = 0; i < numOfImage; i++)
	{
		images.at(i)->draw();
	}

	for (auto i = 0; i < numOfImage; i++)
	{
		delete images.at(i);
	}
}
