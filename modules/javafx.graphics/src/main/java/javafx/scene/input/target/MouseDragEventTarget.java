package javafx.scene.input.target;

import javafx.beans.property.ObjectProperty;
import javafx.event.EventHandler;
import javafx.scene.input.MouseDragEvent;

public interface MouseDragEventTarget {

    ObjectProperty<EventHandler<? super MouseDragEvent>> onMouseDragReleasedProperty();

    EventHandler<? super MouseDragEvent> getOnMouseDragReleased();

    void setOnMouseDragReleased(EventHandler<? super MouseDragEvent> value);

    ObjectProperty<EventHandler<? super MouseDragEvent>> onMouseDragEnteredProperty();

    EventHandler<? super MouseDragEvent> getOnMouseDragEntered();

    void setOnMouseDragEntered(EventHandler<? super MouseDragEvent> value);

    void setOnMouseDragExited(EventHandler<? super MouseDragEvent> value);

    EventHandler<? super MouseDragEvent> getOnMouseDragExited();

    ObjectProperty<EventHandler<? super MouseDragEvent>> onMouseDragExitedProperty();

    ObjectProperty<EventHandler<? super MouseDragEvent>> onMouseDragOverProperty();

    EventHandler<? super MouseDragEvent> getOnMouseDragOver();

    void setOnMouseDragOver(EventHandler<? super MouseDragEvent> value);

}
