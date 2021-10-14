package javafx.scene.input.target;

import javafx.beans.property.ObjectProperty;
import javafx.event.EventHandler;
import javafx.scene.input.RotateEvent;

public interface RotateEventTarget {

    void setOnRotationStarted(EventHandler<? super RotateEvent> value);

    EventHandler<? super RotateEvent> getOnRotationStarted();

    ObjectProperty<EventHandler<? super RotateEvent>> onRotationStartedProperty();

    void setOnRotate(EventHandler<? super RotateEvent> value);

    EventHandler<? super RotateEvent> getOnRotate();

    ObjectProperty<EventHandler<? super RotateEvent>> onRotateProperty();

    void setOnRotationFinished(EventHandler<? super RotateEvent> value);

    EventHandler<? super RotateEvent> getOnRotationFinished();

    ObjectProperty<EventHandler<? super RotateEvent>> onRotationFinishedProperty();
}
