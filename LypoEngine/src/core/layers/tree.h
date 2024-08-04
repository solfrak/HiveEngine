//
// Created by wstap on 7/29/2024.
//

#ifndef TREE_H
#define TREE_H
#include <iostream>

#include "core/events/Event.h"

namespace Lypo {
    class RealNode : public IEventHandler
    {
    public:
        explicit RealNode(const int value)
            : value_(value) {}

        void OnEvent(Event &event) override
        {
            // std::cout << "Event " << value_ << std::endl;

            if(value_ == 111)
                event.handled = true;
        };
    private:
        int value_;
    };


} // Lypo

#endif //TREE_H
