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

package jp.co.rakuten.esd.barcode.code128;

import android.graphics.Color;
import android.graphics.Paint;
import android.graphics.PorterDuff;
import android.graphics.PorterDuffXfermode;

import jp.co.rakuten.esd.barcode.Barcode;

/**
 * Concrete implementation of {@link Barcode} supporting Code128 Type B,C generation
 */
public class Code128Barcode extends Barcode {

    /**
     * Constructs instance of Barcode drawable.
     *
     * @param payload Payload that will be encoded. While no size limit is enforced,
     *                keep in mind that barcodes that are too dense or too wide may require
     *                a high-resolution, wide-angle scanner and not work with common, cheaper hardware.
     *                For those, a good limit is probably around 48.
     */
    public Code128Barcode(String payload) {
        Code128Shape shape = new Code128Shape(payload);
        setShape(shape);

        // By default background of barcode is transparent
        getPaint().setColor(Color.TRANSPARENT);

        // Blending mode is SRC_OVER
        getPaint().setXfermode(new PorterDuffXfermode(PorterDuff.Mode.SRC_OVER));
    }

    @Override
    public Paint getInnerPaint() {
        return getShape().getBarcodeInnerPaint();
    }

    @Override
    public Code128Shape getShape() {
        return (Code128Shape) super.getShape();
    }
}

