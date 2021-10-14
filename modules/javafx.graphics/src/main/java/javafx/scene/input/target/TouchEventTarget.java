package javafx.scene.input.target;

import javafx.beans.property.ObjectProperty;
import javafx.event.EventHandler;
import javafx.scene.input.TouchEvent;

public interface TouchEventTarget {

    void setOnTouchPressed(EventHandler<? super TouchEvent> value);

    EventHandler<? super TouchEvent> getOnTouchPressed();

    ObjectProperty<EventHandler<? super TouchEvent>> onTouchPressedProperty();

    void setOnTouchMoved(EventHandler<? super TouchEvent> value);

    EventHandler<? super TouchEvent> getOnTouchMoved();

    ObjectProperty<EventHandler<? super TouchEvent>> onTouchMovedProperty();

    void setOnTouchReleased(EventHandler<? super TouchEvent> value);

    EventHandler<? super TouchEvent> getOnTouchReleased();

    ObjectProperty<EventHandler<? super TouchEvent>> onTouchReleasedProperty();

    void setOnTouchStationary(EventHandler<? super TouchEvent> value);

    EventHandler<? super TouchEvent> getOnTouchStationary();

    ObjectProperty<EventHandler<? super TouchEvent>> onTouchStationaryProperty();
}
