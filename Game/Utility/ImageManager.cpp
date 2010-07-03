/*
* Class RessourceManager
* Manage ressources creation for better use of memory
* @author : Adrian Gaudebert - adrian.gaudebert@gmail.com
            Nicolas Beaudrot - nicolas.beaudrot@gmail.com
*/

#include "ImageManager.h"

/* -------------------------- */
/* RessourceManager::RessourceManager */
/* -------------------------- */
RessourceManager::RessourceManager()
{

}

/* --------------------------- */
/* RessourceManager::~RessourceManager */
/* --------------------------- */
RessourceManager::~RessourceManager()
{
  //On détruit toutes les images restantes
  std::map<std::string, sf::Image*>::iterator it;
  for(it = Images.begin(); it != Images.end(); it++)
  {
    delete it->second;
  }
}

/* ------------------------- */
/* RessourceManager::SearchImage */
/* ------------------------- */
bool RessourceManager::SearchImage(const std::string &ImageLink, sf::Image* &ImgTemp)
{
  std::map<std::string, sf::Image*>::iterator it;

  it = Images.find(ImageLink);

  if(it == Images.end())
  {
    return false;
  }
  else
  {
    ImgTemp = it->second;
  }

  return true;
}

/* ------------------------- */
/* RessourceManager::CreateImage */
/* ------------------------- */
sf::Image *RessourceManager::CreateImage(const std::string &ImageLink)
{
  sf::Image *ImgTemp = new sf::Image();
  if(ImgTemp->LoadFromFile(ImageLink))
  {
    Images.insert(std::pair<std::string, sf::Image*>(ImageLink, ImgTemp));
    return ImgTemp;
  }
  else
  {
    delete ImgTemp;
  }

  return NULL;
}

/* ---------------------- */
/* RessourceManager::GetImage */
/* ---------------------- */
sf::Image *RessourceManager::GetImage(const std::string &ImageLink)
{
  sf::Image *ImgTemp;

  //Si l'image demandée n'existe pas déjà, on la créée
  if(!SearchImage(ImageLink, ImgTemp))
  {
    ImgTemp = CreateImage(ImageLink);
  }

  return ImgTemp;
}

/* ------------------------- */
/* RessourceManager::DeleteImage */
/* ------------------------- */
void RessourceManager::DeleteImage(sf::Image &Img)
{
  std::map<std::string, sf::Image*>::iterator it;

  //On cherche l'image demandée
  for(it = Images.begin(); it != Images.end(); it++)
  {
    //Si on la trouve, on la détruit et on la retire
    if(it->second == &Img)
    {
      delete &Img;
      Images.erase(it);
      break;
    }
  }
}

/* ------------------------- */
/* RessourceManager::DeleteImage */
/* ------------------------- */
void RessourceManager::DeleteImage(const std::string& ImageLink)
{
  std::map<std::string, sf::Image*>::iterator it;

  it = Images.find(ImageLink);

  if(it != Images.end())
  {
    if(it->second != NULL)
    {
      delete (it->second);
      Images.erase(it);
    }
  }
}

sf::Font *RessourceManager::GetFont(const std::string &FontLink) {
    sf::Font *FontTemp;
    std::map<std::string, sf::Font*>::iterator it;
    it = Fonts.find(FontLink);

    if(it == Fonts.end()) {
        FontTemp = new sf::Font();
        if(FontTemp->LoadFromFile(FontLink)) {
            Fonts.insert(std::pair<std::string, sf::Font*>(FontLink, FontTemp));
        }
    } else {
        FontTemp = it->second;
    }

    return FontTemp;
}
