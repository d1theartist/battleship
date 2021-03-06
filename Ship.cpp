#include "Ship.h"
#include <string>
#include <iostream>

using namespace std;

// Constructors
Ship::Ship()
{
    name = "";
    size = 0;
    alive = false;
    hitbox = NULL;
    position.xCoord = 0;
    position.yCoord = 0;
}

Ship::Ship(string shipName, int shipSize)
{
    name = shipName;
    size = shipSize;
    alive = true;
    hitbox = new bool[size];                          // Create a hitbox the size of the ship
    for(int i = 0; i<size; i++)                              // Turn all spaces in hitbox to true
        hitbox[i] = true;

    position.xCoord = 0;
    position.yCoord = 0;
}

// copy constructor
Ship::Ship(const Ship& origShip)
{
    name = origShip.name;
    size = origShip.size;
    alive = origShip.alive;
    hitbox = new bool[size];
    for(int i = 0; i < size; i++)       // deep copy dynamic data
        hitbox[i] = origShip.hitbox;

    position.xCoord = origShip.position.xCoord;
    position.yCoord = origShip.position.yCoord;
}

// Assignment operator
Ship& Ship::operator=(const Ship& origShip)
{
    if(this != &origShip)
    {
        if(hitbox != NULL)
            delete [] hitbox;

        name = origShip.name;
        size = origShip.size;
        alive = origShip.alive;
        hitbox = new bool[size];
        for(int i = 0; i < size; i++)       // deep copy dynamic data
            hitbox[i] = origShip.hitbox;

        position.xCoord = origShip.position.xCoord;
        position.yCoord = origShip.position.yCoord;
    }
    return *this;


}

ostream& operator<<(ostream& out, const Ship& myShip)
{
    out<<endl;
    out<<"Ship name: "<<myShip.name<<endl
        <<"Ship size: "<<myShip.size<<endl
        <<"Ship position: ("<<myShip.position.xCoord<<", "<<myShip.position.yCoord<<")"<<endl
        <<"Ship orientation: ";
    if(myShip.orientation == Ship::vertical)
        out<<"vertical."<<endl;
    else
        out<<"horizontal."<<endl;
    out<<"Ship alive: ";
    if(myShip.alive)
        out<<"true"<<endl;
    else
        out<<"false"<<endl;
    if(myShip.hitbox!= nullptr)
    {
        for(int i = 0; i < myShip.size; i++)
        {
            if(myShip.hitbox[i] == true)
                out<<"#";
            else
                out<<"*";
        }
    }
    return out;
}

bool Ship::operator==(const Ship &other)
{
    //cout<<"Name: "<<name<<"<- "<<endl;
    //cout<<"Name: "<<other.name<<"<- "<<endl;

    if(other.name.compare(name) !=  0 )
    {
        cout<<"strings are not equal"<<endl;
        return false;
    }

    //cout<<"Name check"<<endl;
    //if(other.orientation != orientation)
       // return false;
    //cout<<"orientation check"<<endl;
    if(other.position.xCoord != position.xCoord)
        return false;
    //cout<<"x check"<<endl;
    if(other.position.yCoord != position.yCoord)
        return false;
    //cout<<"y check"<<endl;
    if(other.size != size )
        return false;
   // cout<<"ALL checks"<<endl;

    return true;

}

// destructor
Ship::~Ship()
{
    delete [] hitbox;   // deallocate dynamic data
}

// set's ship's position
void Ship::setPosition(Coordinate coord, Orientation ori)
{
    position = coord;
    orientation = ori;
}

// update ship with attack data
void Ship::onHit(Coordinate atkCoord)
{
    if(orientation == vertical)
        hitbox[atkCoord.yCoord - position.yCoord] = false;
    else if(orientation == horizontal)
        hitbox[atkCoord.xCoord - position.xCoord] = false;
    setAlive();
}

// returns true if any of the hitboxes for the ship are still active (true)
// POST: set's Ship::alive
void Ship::setAlive()
{
    bool lives = false;                                 // Start off with ship being dead
    for(int i = 0; i<size; i++)                  // For each space the ship takes up
    {
        if(hitbox[i]== true)                     // If any of the hitboxes for the ship are alive the ship is alive
            lives = true;
    }
    alive = lives;
}

bool Ship::getAlive() const
{
    return alive;
}

void Ship::print() const
{
    cout<<endl;
    cout<<"Ship name: "<<name<<endl
        <<"Ship size: "<<size<<endl
        <<"Ship position: ("<<position.xCoord<<", "<<position.yCoord<<")"<<endl
        <<"Ship orientation: ";
    if(orientation == vertical)
        cout<<"vertical."<<endl;
    else
        cout<<"horizontal."<<endl;
    cout<<"Ship alive: ";
    if(alive)
        cout<<"true"<<endl;
    else
        cout<<"false"<<endl;
    if(hitbox!= NULL)
    {
        for(int i = 0; i < size; i++)
        {
            if(hitbox[i] == true)
                cout<<"#";
            else
                cout<<"*";
        }
    }
    cout<<endl;
    cout<<endl;
}

int Ship::getSize() const
{
    return size;
}

string Ship::getName() const
{
    return name;
}

Ship::Orientation Ship::getOrientation() const
{
    return orientation;
}

Coordinate Ship::getPosition() const
{
    return position;
}
