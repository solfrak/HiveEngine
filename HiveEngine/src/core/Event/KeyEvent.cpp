//
// Created by samuel on 10/02/25.
//

#include "KeyEvent.h"

#include "EventVisitor.h"

void hive::KeyEvent::process(hive::EventVisitor &visitor)
{
    visitor.handle(*this);
}
