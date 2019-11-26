#pragma once

class Actor
{
private:
    bool _finished = false;
public:
    virtual bool finished() { return _finished; }
    virtual void draw(float) {};
};