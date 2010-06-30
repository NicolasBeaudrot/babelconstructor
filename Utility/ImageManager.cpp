/*
* Class ImageManager
* Manage sf::Image creation for better use of memory
* @author : Adrian Gaudebert - adrian.gaudebert@gmail.com
*/

#include "ImageManager.h"

/* -------------------------- */
/* ImageManager::ImageManager */
/* -------------------------- */
ImageManager::ImageManager()
{

}

/* --------------------------- */
/* ImageManager::~ImageManager */
/* --------------------------- */
ImageManager::~ImageManager()
{
  //On détruit toutes les images restantes
  std::map<std::string, sf::Image*>::iterator it;
  for(it = Images.begin(); it != Images.end(); it++)
  {
    delete it->second;
  }
}

/* ------------------------- */
/* ImageManager::SearchImage */
/* ------------------------- */
bool ImageManager::SearchImage(const std::string &ImageLink, sf::Image* &ImgTemp)
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
/* ImageManager::CreateImage */
/* ------------------------- */
sf::Image *ImageManager::CreateImage(const std::string &ImageLink)
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
/* ImageManager::GetImage */
/* ---------------------- */
sf::Image *ImageManager::GetImage(const std::string &ImageLink)
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
/* ImageManager::DeleteImage */
/* ------------------------- */
void ImageManager::DeleteImage(sf::Image &Img)
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
/* ImageManager::DeleteImage */
/* ------------------------- */
void ImageManager::DeleteImage(const std::string& ImageLink)
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
