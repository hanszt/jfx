package javafx.scene.input.target;

import javafx.beans.property.ObjectProperty;
import javafx.event.EventHandler;
import javafx.scene.input.ContextMenuEvent;

public interface ContextMenuEventTarget {

    void setOnContextMenuRequested(EventHandler<? super ContextMenuEvent> value);

    EventHandler<? super ContextMenuEvent> getOnContextMenuRequested();

    ObjectProperty<EventHandler<? super ContextMenuEvent>> onContextMenuRequestedProperty();
}
