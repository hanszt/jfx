package javafx.scene.input.target;

import javafx.beans.property.ObjectProperty;
import javafx.event.EventHandler;
import javafx.scene.input.InputMethodEvent;

public interface InputMethodEventTarget {

    void setOnInputMethodTextChanged(EventHandler<? super InputMethodEvent> value);

    EventHandler<? super InputMethodEvent> getOnInputMethodTextChanged();

    ObjectProperty<EventHandler<? super InputMethodEvent>> onInputMethodTextChangedProperty();
}
