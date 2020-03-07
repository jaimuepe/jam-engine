#ifndef TEXTURE2D_H
#define TEXTURE2D_H

namespace graphics
{

class Texture2D
{

public:

    unsigned int getID() const
    {
        return m_ID;
    }

    void generate(unsigned char* data, int width, int height, int nChannels);

    void bind() const;

    int getWidth() const
    {
        return m_width;
    }

    int getHeight() const
    {
        return m_height;
    }

    bool isValid() const
    {
        return m_ID > 0;
    }

private:

    unsigned int m_ID;

    int m_width;
    int m_height;
};

} // namespace graphics

#endif // TEXTURE2D_H
