#ifndef IUPDATEABLECOMPONENT_H
#define IUPDATEABLECOMPONENT_H

class IUpdateableComponent
{

public:
    virtual void update(float deltaTime) = 0;
};

#endif // IUPDATEABLECOMPONENT_H
