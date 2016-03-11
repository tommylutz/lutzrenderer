class ImageInterface
{
public:
    virtual ~ImageInterface() = 0;
    virtual void set_pixel(int x, int y, unsigned char graylevel);
    
};
