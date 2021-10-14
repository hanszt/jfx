package javafx.scene.input.target;

import javafx.beans.property.ObjectProperty;
import javafx.event.EventDispatcher;

public interface EventDispatcherTarget {

    void setEventDispatcher(EventDispatcher eventDispatcher);

    EventDispatcher getEventDispatcher();

    ObjectProperty<EventDispatcher> eventDispatcherProperty();
}
