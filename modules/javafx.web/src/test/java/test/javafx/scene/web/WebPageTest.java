/*
 * Copyright (c) 2011, 2024, Oracle and/or its affiliates. All rights reserved.
 * DO NOT ALTER OR REMOVE COPYRIGHT NOTICES OR THIS FILE HEADER.
 *
 * This code is free software; you can redistribute it and/or modify it
 * under the terms of the GNU General Public License version 2 only, as
 * published by the Free Software Foundation.  Oracle designates this
 * particular file as subject to the "Classpath" exception as provided
 * by Oracle in the LICENSE file that accompanied this code.
 *
 * This code is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License
 * version 2 for more details (a copy is included in the LICENSE file that
 * accompanied this code).
 *
 * You should have received a copy of the GNU General Public License version
 * 2 along with this work; if not, write to the Free Software Foundation,
 * Inc., 51 Franklin St, Fifth Floor, Boston, MA 02110-1301 USA.
 *
 * Please contact Oracle, 500 Oracle Parkway, Redwood Shores, CA 94065 USA
 * or visit www.oracle.com if you need additional information or have any
 * questions.
 */

package test.javafx.scene.web;

import com.sun.webkit.WebPage;
import com.sun.webkit.WebPageShim;
import javafx.scene.web.WebEngineShim;

import static org.junit.jupiter.api.Assertions.assertEquals;
import static org.junit.jupiter.api.Assertions.assertNull;
import static org.junit.jupiter.api.Assertions.assertThrows;
import org.junit.jupiter.api.Test;

public class WebPageTest extends TestBase {

    final static String PLAIN = "<html><head></head><body></body></html>";
    final static String HTML  = "<html><head></head><body><p>Test</p></body></html>";
    final static String XML   = "<?xml version='1.0'?><root></root>";
    final static String PTAG = "<p></p>";
    final static String IFRAME = "<iframe src=''> </iframe>";

    @Test public void testGetHtml() throws Exception {
        WebPage page = WebEngineShim.getPage(getEngine());

        loadContent(HTML);
        assertEquals(HTML, getHtml(page), "HTML document");

        // With XML document, getHtml() should return null
        loadContent(XML, "application/xml");
        assertNull(getHtml(page), "XML document");

        loadContent("");
        assertEquals(PLAIN, getHtml(page), "Empty document");

        loadContent("", "text/plain");
        assertEquals(PLAIN, getHtml(page), "Empty text/plain document");
    }

    private String getHtml(final WebPage page) throws Exception {
        return submit(() -> page.getHtml(page.getMainFrame()));
    }

    @Test public void testGetHtmlIllegalFrameId() {
        WebPage page = WebEngineShim.getPage(getEngine());
        assertEquals(null, page.getHtml(1));
    }

    @Test public void testFrameCount() {
        final WebPage page = WebEngineShim.getPage(getEngine());

        // load content with single iframe, which leads to two frame
        loadContent(PTAG + IFRAME);
        submit(() -> {
            assertEquals(2, WebPageShim.getFramesCount(page), "Expected two frames : ");
        });

        // load content with only one element which leads to single frame
        loadContent(PTAG);
        submit(() -> {
            assertEquals(1, WebPageShim.getFramesCount(page), "Expected single frame : ");
        });
    }

    // JDK-8196011
    @Test public void testICUTagParse() {
        load(WebPageTest.class.getClassLoader().getResource(
                "test/html/icutagparse.html").toExternalForm());
    }

    @Test
    public void testGetClientTextLocationFromNonEventThread() {
        assertThrows(IllegalStateException.class, () -> {
            WebPage page = WebEngineShim.getPage(getEngine());
            page.getClientTextLocation(0);
        });
    }

    @Test
    public void testGetClientLocationOffsetFromNonEventThread() {
        assertThrows(IllegalStateException.class, () -> {
            WebPage page = WebEngineShim.getPage(getEngine());
            page.getClientLocationOffset(0, 0);
        });
    }
}
