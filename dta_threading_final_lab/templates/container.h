#pragma once

#include "../actors/actor.h"
#include <SFML/Graphics.hpp>
#include <vector>
#include <algorithm>

template<typename T>
struct is_pointer { static const bool value = false; };

template<typename T>
struct is_pointer<T*> { static const bool value = true; };

template <typename T>
class ActorContainer
{
private:
    std::vector<T> _container;

    void _removeFinished()
    {
        std::vector<T> pointerCopy;

        std::copy_if(_container.begin(), _container.end(), std::back_inserter(pointerCopy), [](const T item) {
            auto object = item;
            return object->finished();
        });

        _container.erase(std::remove_if(
            _container.begin(),
            _container.end(),
            [](T item) {
                auto object = item;
                return object->finished();
            }
        ), _container.end());

        for (auto &object : pointerCopy)
            delete object;
    }

public:
    ActorContainer() = default;

    ~ActorContainer()
    {
        if (is_pointer<T>::value)
        {
            for(auto &object : _container)
                delete object;
        }
    }

    T& operator[](unsigned int index) { return _container[index]; }

    void push(T object)
    {
        _container.push_back(object);
    }

    void draw(float deltaTime)
    {
        if(!_container.empty())
            _removeFinished();

        for (auto &object : _container)
            object->draw(deltaTime);
    }
};