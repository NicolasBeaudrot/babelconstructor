#ifndef h__imagemanager_hpp__
#define h__imagemanager_hpp__
#include "Singleton.h"
#include <map>
#include <SFML/Graphics.hpp>
/*
* Class RessourceManager
* Manage ressources creation for better use of memory
* @author : Adrian Gaudebert - adrian.gaudebert@gmail.com
            Nicolas Beaudrot - nicolas.beaudrot@gmail.com
*/
class RessourceManager : public CSingleton<RessourceManager>
{
  private:
    friend class CSingleton<RessourceManager>;

    RessourceManager();

    virtual ~RessourceManager();

    std::map<std::string, sf::Image*> Images;

    std::map<std::string, sf::Font*> Fonts;

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

    /**
    *Get a sf::Font from a file name
    * @param ImageLink File name of the font
    * @return Pointer to the sf::Font
    */
    sf::Font *GetFont(const std::string &FontLink);
};
#endif
