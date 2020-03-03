#ifndef TEXTURE2D_H
#define TEXTURE2D_H

namespace Graphics
{

    class Texture2D
    {

    public:

        unsigned int ID;

        void generate(unsigned char* data, int width, int height, int nChannels);

        void bind() const;

        int getWidth() const
        {
            return width;
        }

        int getHeight() const
        {
            return height;
        }

    private:
        int width;
        int height;
    };
}
#endif // TEXTURE2D_H
