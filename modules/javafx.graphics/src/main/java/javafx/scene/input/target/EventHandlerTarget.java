package javafx.scene.input.target;

import javafx.event.Event;
import javafx.event.EventHandler;
import javafx.event.EventType;

public interface EventHandlerTarget {

    <T extends Event> void addEventHandler(EventType<T> eventType, EventHandler<? super T> eventHandler);

    <T extends Event> void removeEventHandler(EventType<T> eventType, EventHandler<? super T> eventHandler);

}
