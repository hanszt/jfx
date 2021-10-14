package javafx.scene.input.target;

import javafx.beans.property.ObjectProperty;
import javafx.event.EventHandler;
import javafx.scene.input.DragEvent;
import javafx.scene.input.Dragboard;
import javafx.scene.input.TransferMode;

public interface DragEventTarget {

    void setOnDragEntered(EventHandler<? super DragEvent> value);

    EventHandler<? super DragEvent> getOnDragEntered();

    ObjectProperty<EventHandler<? super DragEvent>> onDragEnteredProperty();

    void setOnDragExited(EventHandler<? super DragEvent> value);

    EventHandler<? super DragEvent> getOnDragExited();

    ObjectProperty<EventHandler<? super DragEvent>> onDragExitedProperty();

    void setOnDragOver(EventHandler<? super DragEvent> value);

    EventHandler<? super DragEvent> getOnDragOver();

    ObjectProperty<EventHandler<? super DragEvent>> onDragOverProperty();

    void setOnDragDropped(EventHandler<? super DragEvent> value);

    EventHandler<? super DragEvent> getOnDragDropped();

    ObjectProperty<EventHandler<? super DragEvent>> onDragDroppedProperty();

    void setOnDragDone(EventHandler<? super DragEvent> value);

    EventHandler<? super DragEvent> getOnDragDone();

    ObjectProperty<EventHandler<? super DragEvent>> onDragDoneProperty();

    Dragboard startDragAndDrop(TransferMode... value);

    void startFullDrag();

}
