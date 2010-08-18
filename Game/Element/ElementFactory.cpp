#include "ElementFactory.h"
#include <sstream>

class QueryCallback : public b2QueryCallback
{
    public:
        QueryCallback(const b2Vec2& point)
        {
            m_point = point;
            m_fixture = NULL;

        }


        bool ReportFixture(b2Fixture* fixture)
        {
            b2Body* body = fixture->GetBody();
            if (body->GetType() == b2_dynamicBody) {
                bool inside = fixture->TestPoint(m_point);
                if (inside) {
                    m_fixture = fixture;
                    return false;
                }
            }
            return true;
        }

        b2Vec2 m_point;
        b2Fixture* m_fixture;
};


ElementFactory::ElementFactory() : _mouseJoint(NULL), _groundBody(NULL) {
}

ElementFactory::~ElementFactory() {
}

void ElementFactory::Init(sf::RenderWindow *application, b2World *world) {
    _mouseJoint=NULL;
    _groundBody=NULL;
    images_path = "ressources/images/";
    _world  = world;
    _app    = application;
    _font   = RessourceManager::Instance()->GetFont("ressources/fonts/gilligan.ttf");

    _world->SetContactListener(this);

    b2BodyDef bodyDef;
	_groundBody = _world->CreateBody(&bodyDef);
}

void ElementFactory::PreSolve(b2Contact* contact, const b2Manifold* oldManifold){
   // Logger::Instance()->log("PreSolve ");
}

void ElementFactory::Delete() {
    for (unsigned int i=0 ; i < _tabElem.size() ; i++) {
        delete _tabElem[i];
    }
    _tabElem.clear();
    _clock.Reset();
}

sf::Vector2f ElementFactory::loadBase(std::string background, std::string base, sf::Vector2f& dimension, std::string limite, float limite_y) {
    if (background != "") {
        if (_img_back.LoadFromFile(images_path + "backgrounds/" + background)) {
            _sprite_back.SetImage(_img_back);
            _sprite_back.Resize(_app->GetWidth(), _app->GetHeight());
            Logger::Instance()->log("Background loaded");
        } else {
            Logger::Instance()->log("Background not found");
        }
    } else {
        Logger::Instance()->log("Background not found");
    }

    if (_img_base.LoadFromFile(images_path + base)) {
        _sprite_base.SetImage(_img_base);
        _sprite_base.Resize(dimension.x, dimension.y);
        _sprite_base.SetPosition(_app->GetWidth()/2 - dimension.x/2, _app->GetHeight() - 100);
        Logger::Instance()->log("Base loaded");
    } else {
        Logger::Instance()->log("Base not found");
    }

    if (_img_limite.LoadFromFile(images_path + limite)) {
        _sprite_limite.SetImage(_img_limite);
        _sprite_limite.SetCenter(_img_limite.GetWidth()/2, _img_limite.GetHeight()/2);
        _sprite_limite.SetPosition(_app->GetWidth() - _img_limite.GetWidth()/2, _sprite_base.GetPosition().y - limite_y);
        Logger::Instance()->log("Limit loaded");
    } else {
        Logger::Instance()->log("Limit not found");
    }

    if (_img_current.LoadFromFile(images_path + "current.png")) {
        _sprite_current.SetImage(_img_current);
        _sprite_current.SetCenter(_img_current.GetWidth()/2, _img_current.GetHeight()/2);
        _sprite_current.SetPosition(_app->GetWidth() - _img_limite.GetWidth()/2, _sprite_base.GetPosition().y);
    } else {
        Logger::Instance()->log("current.png not found");
    }

	b2BodyDef baseBodyDef;
	baseBodyDef.position.Set((_app->GetWidth()/2), 90);
	b2Body* baseBody = _world->CreateBody(&baseBodyDef);
	b2PolygonShape baseBox;
	baseBox.SetAsBox(dimension.x / 2.0f, 10.0f);
	baseBody->CreateFixture(&baseBox, 0.0f);

	return _sprite_base.GetPosition();
}

void ElementFactory::add(std::string type, sf::Vector2f& position, float& angle, std::string file, float* fixture) {
    position.x = _sprite_base.GetPosition().x + position.x;
    position.y = _sprite_base.GetPosition().y - position.y;

    if (type == "Square" or type == "Rectangle") {
        Square *elem = new Square(position, angle, file, *_world, fixture, _app);
        _tabElem.push_back(elem);
    } else if (type == "Circle") {
        Circle *elem = new Circle(position, angle, file, *_world, fixture, _app);
        _tabElem.push_back(elem);
    } else if (type == "Triangle") {
        Triangle *elem = new Triangle(position, angle, file, *_world, fixture, _app);
        _tabElem.push_back(elem);
    }
}

void ElementFactory::move(const sf::Input& input) {

    if (_mouseJoint) {
        b2Vec2 p( _app->GetWidth() - input.GetMouseX(), _app->GetHeight() - input.GetMouseY());
        _mouseJoint->SetTarget(p);
	}
}

void ElementFactory::clic(const sf::Input& input) {

    if (input.GetMouseX() >= 0 && (unsigned)input.GetMouseX() <= _app->GetWidth()
        && input.GetMouseY() >= 0 && (unsigned)input.GetMouseY() <= _app->GetHeight()
        && !(input.GetMouseX() >= _sprite_base.GetPosition().x && input.GetMouseX() <= (_sprite_base.GetPosition().x + _img_base.GetWidth())
            && input.GetMouseY() >= _sprite_base.GetPosition().y && (unsigned)input.GetMouseY() <= _app->GetHeight())) {

        sf::Vector2f mouse = sf::Vector2f(input.GetMouseX(),input.GetMouseY());

        if (_mouseJoint) {
            //revert back the fixedRotation Attribute
            _mouseJoint->GetBodyB()->SetFixedRotation(false);
            _world->DestroyJoint(_mouseJoint);
            _mouseJoint = NULL;
        } else {

            // Query the world for overlapping shapes.
            // Did we click on a shape?
            b2Vec2 p(_app->GetWidth() - mouse.x, _app->GetHeight() - mouse.y);

            // Make a small box.
            b2AABB aabb;
            b2Vec2 d;
            d.Set(0.001f, 0.001f);
            aabb.lowerBound = p - d;
            aabb.upperBound = p + d;

            QueryCallback callback(p);
            _world->QueryAABB(&callback, aabb);

            if (callback.m_fixture) {
                b2Body* body = callback.m_fixture->GetBody();

                b2MouseJointDef md;
                md.bodyA = _groundBody;

                md.bodyB = body;
                md.target = p;
                md.dampingRatio = 1.0f;
                md.frequencyHz = 1.0f;
                md.maxForce = 1000.0f*body->GetMass();
               _mouseJoint = (b2MouseJoint*)_world->CreateJoint(&md);

               body->SetAwake(true);

               //Fixe the rotation
               body->SetFixedRotation(true);

            }
        }

        for(unsigned int i=0 ; i <  _tabElem.size() ; i++) {
            if(_mouseJoint) {
                _tabElem[i]->clic(_mouseJoint->GetBodyB());
            } else { // to deselect element
                _tabElem[i]->clic(NULL);
            }
        }
    }
}

bool ElementFactory::below() {
    for (unsigned int i=0 ; i < _tabElem.size() ; i++) {
        if (_tabElem[i]->below(_sprite_base.GetPosition().y + 10)) {
            return true;
        }
    }
    return false;
}

void ElementFactory::rotate(float value) {
    for (unsigned int i=0 ; i < _tabElem.size() ; i++) {
        _tabElem[i]->rotate( value);
    }
}

int ElementFactory::render(const sf::Input& input) {
    int ret = 0;
    float current_y = 800;
    bool tested = false;

    _app->Draw(_sprite_back);
    _app->Draw(_sprite_base);
    _app->Draw(_sprite_limite);
    ObstacleFactory::Instance()->render();

    for(unsigned int i=0 ; i <  _tabElem.size() ; i++) {
        _tabElem[i]->render(input);
        float tmp_y = _tabElem[i]->getYPosition();
        if(tmp_y < current_y) {
            current_y = tmp_y;
        }
        if (_tabElem[i]->test(_sprite_limite.GetPosition().y)) {
            tested = true;
        }
    }
    _sprite_current.SetY(current_y );
    _app->Draw(_sprite_current);

    if (tested) {
        float elapsedTime = _clock.GetElapsedTime();
        if(elapsedTime >= 2.5 && elapsedTime <= 5) {
            std::ostringstream oss;
            oss << floor(elapsedTime) - 1;
            std::string t = oss.str();
            sf::String time(t, *_font, 40);
            time.SetPosition(20,20);
            _app->Draw(time);
        }
        if (elapsedTime >= 5) {
            ret = 1;
            if (floor(elapsedTime) == 8) {
                ret = 2;
            }
        }
    } else {
        _clock.Reset();
    }

    return ret;
}
