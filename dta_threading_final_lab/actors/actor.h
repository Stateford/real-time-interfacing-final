#pragma once

class Actor
{
protected:
    bool _finished = false;
public:
    virtual bool finished() { return _finished; }
    virtual void draw(float) {};
    virtual bool collision(const Actor& actor) const { return false; };
};