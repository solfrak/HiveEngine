//
// Created by wstap on 7/30/2024.
//

#ifndef EVENTBUS_H
#define EVENTBUS_H
#include <queue>

#include "tree.h"
#include "core/events/Event.h"

namespace Lypo {

    class EventBus {
    public:
        EventBus(const EventBus&) = delete;
        EventBus& operator=(const EventBus&) = delete;

        static EventBus& getInstance()
        {
            static EventBus instance;
            return instance;
        }

        void addEventListener(IEventHandler* node) {
            eventBusTree_.push_back(node);
            updateBusPath();
        }

        void updateBusPath()
        {
            updateBfsPath();
        }


        void dispatch(Event* event)
        {
            for(IEventHandler* eventHandler : bfsOrder_)
                if(eventHandler != nullptr)
                    eventHandler->OnEvent(*event);
                else
                    if(event->handled) break;

        };

    private:
        EventBus() = default;
        ~EventBus() = default;

        void updateBfsPath() {
            std::vector<IEventHandler*> result;
            std::queue<IEventHandler*> q;

            for (IEventHandler* root : eventBusTree_) {
                q.push(root);
            }

            while (!q.empty()) {
                const int levelSize = q.size();

                for (int i = 0; i < levelSize; ++i) {
                    IEventHandler* node = q.front();
                    q.pop();
                    result.push_back(node);

                    for (IEventHandler* child : node->getChildren()) {
                        q.push(child);
                    }
                }

                result.push_back(nullptr);
            }

            std::cout << result.size();
            bfsOrder_ = result;
        }
        std::vector<IEventHandler*> eventBusTree_;
        std::vector<IEventHandler*> bfsOrder_;
    };

} // Lypo

#endif //EVENTBUS_H
