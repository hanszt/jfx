package javafx.scene.input.target;

import javafx.beans.property.ObjectProperty;
import javafx.event.EventHandler;
import javafx.scene.input.ScrollEvent;

public interface ScrollEventTarget {

    void setOnScrollStarted(EventHandler<? super ScrollEvent> value);

    EventHandler<? super ScrollEvent> getOnScrollStarted();

    ObjectProperty<EventHandler<? super ScrollEvent>> onScrollStartedProperty();

    ObjectProperty<EventHandler<? super ScrollEvent>> onScrollProperty();

    EventHandler<? super ScrollEvent> getOnScroll();

    void setOnScroll(EventHandler<? super ScrollEvent> scrollEvent);

    void setOnScrollFinished(EventHandler<? super ScrollEvent> value);

    EventHandler<? super ScrollEvent> getOnScrollFinished();

    ObjectProperty<EventHandler<? super ScrollEvent>> onScrollFinishedProperty();

}
