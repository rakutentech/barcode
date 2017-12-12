/*
 * Copyright 2017 Rakuten, Inc.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

package jp.co.rakuten.esd.barcode;

import android.graphics.Paint;
import android.graphics.drawable.ShapeDrawable;
import android.graphics.drawable.shapes.RectShape;

/**
 * Abstract class, that provides common interface for all types of barcode.
 */
public abstract class Barcode extends ShapeDrawable {

    /**
     * Abstract class, that describes Shapes that should be used by barcode to draw itself.
     * Has to be implemented for each concrete barcode class.
     */
    public static abstract class BarcodeShape extends RectShape {

        /**
         * Get minimum width for correct barcode drawing. Drawing barcode with value less than this
         * will make barcode unreadable for scanners
         *
         * @return  width in pixels
         */
        public abstract int getMinimumWidth();

        /**
         * Get minimum height for correct barcode drawing. Drawing barcode with value less than this
         * will make barcode unreadable for scanners
         *
         * @return  height in pixels
         */
        public abstract int getMinimumHeight();
    }

    /**
     * Obtain {@link Paint} object that is used for drawing bars.
     *
     * @return Paint object
     */
    public abstract Paint getInnerPaint();

    @Override
    public int getIntrinsicWidth() {
        BarcodeShape shape = getShape();
        return shape == null ? -1 : shape.getMinimumWidth();
    }

    @Override
    public int getIntrinsicHeight() {
        BarcodeShape shape = getShape();
        return shape == null ? -1 : shape.getMinimumHeight();
    }

    @Override
    public BarcodeShape getShape() {
        return (BarcodeShape) super.getShape();
    }
}


