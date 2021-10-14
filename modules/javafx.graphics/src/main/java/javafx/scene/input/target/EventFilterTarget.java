package javafx.scene.input.target;

import javafx.event.Event;
import javafx.event.EventHandler;
import javafx.event.EventType;

public interface EventFilterTarget {

    <T extends Event> void addEventFilter(EventType<T> eventType, EventHandler<? super T> eventHandler);

    <T extends Event> void removeEventFilter(EventType<T> eventType, EventHandler<? super T> eventHandler);
}
