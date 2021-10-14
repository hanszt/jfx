package javafx.scene.input.target;

import javafx.beans.property.ObjectProperty;
import javafx.event.EventHandler;
import javafx.scene.input.KeyEvent;

public interface KeyEventTarget {

    void setOnKeyPressed(EventHandler<? super KeyEvent> value);

    EventHandler<? super KeyEvent> getOnKeyPressed();

    ObjectProperty<EventHandler<? super KeyEvent>> onKeyPressedProperty();

    void setOnKeyReleased(EventHandler<? super KeyEvent> value);

    EventHandler<? super KeyEvent> getOnKeyReleased();

    ObjectProperty<EventHandler<? super KeyEvent>> onKeyReleasedProperty();

    void setOnKeyTyped(EventHandler<? super KeyEvent> value);

    EventHandler<? super KeyEvent> getOnKeyTyped();

    ObjectProperty<EventHandler<? super KeyEvent>> onKeyTypedProperty();
}
