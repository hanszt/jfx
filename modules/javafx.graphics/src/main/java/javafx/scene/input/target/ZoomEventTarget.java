package javafx.scene.input.target;

import javafx.beans.property.ObjectProperty;
import javafx.event.EventHandler;
import javafx.scene.input.ZoomEvent;

public interface ZoomEventTarget {

    void setOnZoomStarted(EventHandler<? super ZoomEvent> value);

    EventHandler<? super ZoomEvent> getOnZoomStarted();

    ObjectProperty<EventHandler<? super ZoomEvent>> onZoomStartedProperty();

    void setOnZoom(EventHandler<? super ZoomEvent> value);

    EventHandler<? super ZoomEvent> getOnZoom();

    ObjectProperty<EventHandler<? super ZoomEvent>> onZoomProperty();

    void setOnZoomFinished(EventHandler<? super ZoomEvent> value);

    EventHandler<? super ZoomEvent> getOnZoomFinished();

    ObjectProperty<EventHandler<? super ZoomEvent>> onZoomFinishedProperty();
}
