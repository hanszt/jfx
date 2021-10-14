package test.javafx.scene.input.target;

import javafx.scene.Group;
import javafx.scene.Scene;
import javafx.scene.input.target.Interactable;
import javafx.scene.layout.VBox;

import static org.junit.Assert.*;

public class InteractableTest {

    @Test
    public void testInteractableCanBeUsedForBothNodeAndScene() {
        Scene scene = new Scene(new Group());
        VBox vBox = new VBox();
        setup(scene, vBox);

        assertTrue(scene.onMouseClickedProperty().isBound());
    }

    private void setup(Interactable interactable, Interactable reference) {
        interactable.onMouseClickedProperty().bind(reference.onMouseReleasedProperty());
    }
}
