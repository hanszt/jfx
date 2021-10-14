package javafx.scene.input.target;

import javafx.beans.property.ObjectProperty;
import javafx.event.EventHandler;
import javafx.scene.input.MouseEvent;

public interface MouseEventTarget {

    ObjectProperty<EventHandler<? super MouseEvent>> onMousePressedProperty();

    EventHandler<? super MouseEvent> getOnMousePressed();

    void setOnMousePressed(EventHandler<? super MouseEvent> eventHandler);

    void setOnMouseClicked(EventHandler<? super MouseEvent> value);

    EventHandler<? super MouseEvent> getOnMouseClicked();

    ObjectProperty<EventHandler<? super MouseEvent>> onMouseClickedProperty();

    ObjectProperty<EventHandler<? super MouseEvent>> onMouseDraggedProperty();

    EventHandler<? super MouseEvent> getOnMouseDragged();

    void setOnMouseDragged(EventHandler<? super MouseEvent> eventHandler);

    ObjectProperty<EventHandler<? super MouseEvent>> onMouseReleasedProperty();

    EventHandler<? super MouseEvent> getOnMouseReleased();

    void setOnMouseReleased(EventHandler<? super MouseEvent> eventHandler);

    ObjectProperty<EventHandler<? super MouseEvent>> onDragDetectedProperty();

    EventHandler<? super MouseEvent> getOnDragDetected();

    void setOnDragDetected(EventHandler<? super MouseEvent> value);

    void setOnMouseEntered(EventHandler<? super MouseEvent> value);

    EventHandler<? super MouseEvent> getOnMouseEntered();

    ObjectProperty<EventHandler<? super MouseEvent>> onMouseEnteredProperty();

    void setOnMouseExited(EventHandler<? super MouseEvent> value);

    EventHandler<? super MouseEvent> getOnMouseExited();

    ObjectProperty<EventHandler<? super MouseEvent>> onMouseExitedProperty();

    ObjectProperty<EventHandler<? super MouseEvent>> onMouseMovedProperty();

    EventHandler<? super MouseEvent> getOnMouseMoved();

    void setOnMouseMoved(EventHandler<? super MouseEvent> value);
}
