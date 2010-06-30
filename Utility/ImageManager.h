#ifndef h__imagemanager_hpp__
#define h__imagemanager_hpp__
#include "Singleton.h"
#include <map>
#include <SFML/Graphics.hpp>
/*
* Class ImageManager
* Manage sf::Image creation for better use of memory
* @author : Adrian Gaudebert - adrian.gaudebert@gmail.com
*/
class ImageManager : public CSingleton<ImageManager>
{
  private:
    friend class CSingleton<ImageManager>;

    ImageManager();

    virtual ~ImageManager();

    std::map<std::string, sf::Image*> Images;

    /**
    * Search an Image in memory
    * @param ImageLink File name of the image
    * @param ImgTemp Output pointer to the sf::Image if found
    * @return Boolean, true if the sf::Image is found, false otherwise
    */
    bool SearchImage(const std::string &ImageLink, sf::Image* &ImgTemp);

    /**
    * Create a sf::Image from his file name
    * @param ImageLink File name of the image
    * @return Pointer to the sf::Image created, or NULL if failed
    */
    sf::Image *CreateImage(const std::string &ImageLink);

  public:
    /**
    * Get a sf::Image from a file name
    * @param ImageLink File name of the image
    * @return Pointer to the sf::Image
    */
    sf::Image *GetImage(const std::string &ImageLink);

    /**
    * Delete a sf::Image if already loaded
    * @param Img The sf::Image to destroy
    * @return None
    */
    void DeleteImage(sf::Image &Img);

    /**
    * Delete a sf::Image if already loaded
    * @param ImageLink File name of the image to destroy
    * @return None
    */
    void DeleteImage(const std::string& ImageLink);
};
#endif
