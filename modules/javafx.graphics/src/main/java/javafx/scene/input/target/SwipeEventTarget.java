package javafx.scene.input.target;

import javafx.beans.property.ObjectProperty;
import javafx.event.EventHandler;
import javafx.scene.input.SwipeEvent;

public interface SwipeEventTarget {

    void setOnSwipeUp(EventHandler<? super SwipeEvent> value);

    EventHandler<? super SwipeEvent> getOnSwipeUp();

    ObjectProperty<EventHandler<? super SwipeEvent>> onSwipeUpProperty();

    void setOnSwipeDown(EventHandler<? super SwipeEvent> value);

    EventHandler<? super SwipeEvent> getOnSwipeDown();

    ObjectProperty<EventHandler<? super SwipeEvent>> onSwipeDownProperty();

    void setOnSwipeLeft(EventHandler<? super SwipeEvent> value);

    EventHandler<? super SwipeEvent> getOnSwipeLeft();

    ObjectProperty<EventHandler<? super SwipeEvent>> onSwipeLeftProperty();

    void setOnSwipeRight(EventHandler<? super SwipeEvent> value);

    EventHandler<? super SwipeEvent> getOnSwipeRight();

    ObjectProperty<EventHandler<? super SwipeEvent>> onSwipeRightProperty();
}
