#ifndef TEXTURELOADER_HPP
#define TEXTURELOADER_HPP


class TextureLoader
{
public:
	bool loadTexture(std::string file_name);
	void updateTexture(std::string texture_name);
};

#endif
