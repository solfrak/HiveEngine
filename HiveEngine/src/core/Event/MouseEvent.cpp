#include "MouseEvent.h"
#include "EventVisitor.h"

void hive::MouseMotionEvent::process(EventVisitor &visitor)
{
    visitor.handle(*this);
}

void hive::MouseButtonEvent::process(EventVisitor &visitor)
{
    visitor.handle(*this);
}
