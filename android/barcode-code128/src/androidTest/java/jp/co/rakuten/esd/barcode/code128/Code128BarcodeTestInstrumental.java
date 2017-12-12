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

import android.graphics.Bitmap;
import android.graphics.Canvas;
import android.graphics.Color;
import android.graphics.Rect;
import android.support.test.filters.SmallTest;
import android.support.test.runner.AndroidJUnit4;

import org.junit.Before;
import org.junit.Test;
import org.junit.runner.RunWith;

import java.nio.Buffer;
import java.nio.ByteBuffer;
import java.nio.ByteOrder;
import java.nio.IntBuffer;

import jp.co.rakuten.esd.barcode.Barcode;

import static junit.framework.Assert.assertTrue;

@RunWith(AndroidJUnit4.class)
@SmallTest
public class Code128BarcodeTestInstrumental {

    private final int BP = Color.BLACK;
    private final int TP = Color.TRANSPARENT;

    private final int[] R_LETTER_PATTERN_PIXEL_ARRAY = {
            BP, BP, TP, BP, TP, TP, BP, TP, TP, TP, TP, BP, BP, TP, TP, TP,
            BP, TP, BP, BP, BP, TP, BP, BP, TP, BP, BP, BP, TP, BP, TP, TP,
            TP, BP, BP, TP, TP, TP, BP, BP, BP, TP, BP, TP, BP, BP,

            BP, BP, TP, BP, TP, TP, BP, TP, TP, TP, TP, BP, BP, TP, TP, TP,
            BP, TP, BP, BP, BP, TP, BP, BP, TP, BP, BP, BP, TP, BP, TP, TP,
            TP, BP, BP, TP, TP, TP, BP, BP, BP, TP, BP, TP, BP, BP
    };

    private final int[] NUMBER_20_PATTERN_PIXEL_ARRAY = {
            BP, BP, TP, BP, TP, TP, BP, BP, BP, TP, TP, BP, BP, TP, TP, BP,
            TP, TP, BP, BP, BP, TP, BP, BP, TP, TP, BP, BP, BP, TP, BP, TP,
            TP, BP, BP, TP, TP, TP, BP, BP, BP, TP, BP, TP, BP, BP,

            BP, BP, TP, BP, TP, TP, BP, BP, BP, TP, TP, BP, BP, TP, TP, BP,
            TP, TP, BP, BP, BP, TP, BP, BP, TP, TP, BP, BP, BP, TP, BP, TP,
            TP, BP, BP, TP, TP, TP, BP, BP, BP, TP, BP, TP, BP, BP
    };

    private final int[] NUMBER_20_R_LETTER_PATTERN_PIXEL_ARRAY = {
            BP, BP, TP, BP, TP, TP, BP, BP, BP, TP, TP, BP, BP, TP, TP, BP,
            TP, TP, BP, BP, BP, TP, BP, TP, BP, BP, BP, BP, TP, BP, BP, BP,
            TP, BP, BP, TP, TP, TP, BP, TP, BP, BP, BP, TP, BP, TP, BP, TP,
            TP, BP, BP, TP, TP, TP, TP, BP, BP, TP, TP, TP, BP ,BP, BP, TP,
            BP, TP, BP, BP,

            BP, BP, TP, BP, TP, TP, BP, BP, BP, TP, TP, BP, BP, TP, TP, BP,
            TP, TP, BP, BP, BP, TP, BP, TP, BP, BP, BP, BP, TP, BP, BP, BP,
            TP, BP, BP, TP, TP, TP, BP, TP, BP, BP, BP, TP, BP, TP, BP, TP,
            TP, BP, BP, TP, TP, TP, TP, BP, BP, TP, TP, TP, BP ,BP, BP, TP,
            BP, TP, BP, BP
    };

    private final int[] R_LETTER_NUMBER_20_PATTERN_PIXEL_ARRAY = {
            BP, BP, TP, BP, TP, TP, BP, TP, TP, TP, TP, BP, BP, TP, TP, TP,
            BP, TP, BP, BP, BP, TP, BP, BP, TP, TP, BP, BP, BP, TP, TP, BP,
            TP, BP, TP, TP, BP, BP, BP, TP, BP, BP, TP, TP, BP, BP, TP, TP,
            TP, BP, BP, TP, BP, BP, TP, BP, BP, TP, TP, TP, BP ,BP, BP, TP,
            BP, TP, BP, BP,

            BP, BP, TP, BP, TP, TP, BP, TP, TP, TP, TP, BP, BP, TP, TP, TP,
            BP, TP, BP, BP, BP, TP, BP, BP, TP, TP, BP, BP, BP, TP, TP, BP,
            TP, BP, TP, TP, BP, BP, BP, TP, BP, BP, TP, TP, BP, BP, TP, TP,
            TP, BP, BP, TP, BP, BP, TP, BP, BP, TP, TP, TP, BP ,BP, BP, TP,
            BP, TP, BP, BP,
    };

    private final int[] GS1_PATTERN_PIXEL_ARRAY = {
            BP, BP, TP, BP, TP, TP, BP, BP, BP, TP, TP, BP, BP, BP, BP, TP, BP, TP,
            BP, BP, BP, TP, BP, BP, TP, BP, BP, TP, TP, BP, BP, TP, TP, BP, TP,
            BP, BP, TP, TP, BP, BP, BP, TP, TP, BP, TP, TP, TP, BP, TP, BP, BP, TP, TP, TP,
            BP, BP, BP, TP, TP, TP, BP, TP, BP, BP, TP, BP, BP, TP, TP, TP, TP, BP, TP,
            BP, TP, TP, BP, BP, TP, BP, BP, TP, TP, BP, BP, TP, TP, BP, BP, TP,
            BP, BP, TP, TP, BP, BP, TP, TP, BP, BP, TP, BP, BP, TP, TP, BP, BP, TP, TP,
            BP, BP, TP, BP, BP, TP, TP, BP, BP, TP, TP, BP, BP, TP, TP, BP, BP, TP,
            BP, BP, TP, TP, BP, TP, TP, TP, BP ,TP, TP, BP, BP, TP, TP, BP ,BP, TP, TP, TP,
            BP, BP, BP, TP, BP, TP, BP, BP,

            BP, BP, TP, BP, TP, TP, BP, BP, BP, TP, TP, BP, BP, BP, BP, TP, BP, TP,
            BP, BP, BP, TP, BP, BP, TP, BP, BP, TP, TP, BP, BP, TP, TP, BP, TP,
            BP, BP, TP, TP, BP, BP, BP, TP, TP, BP, TP, TP, TP, BP, TP, BP, BP, TP, TP, TP,
            BP, BP, BP, TP, TP, TP, BP, TP, BP, BP, TP, BP, BP, TP, TP, TP, TP, BP, TP,
            BP, TP, TP, BP, BP, TP, BP, BP, TP, TP, BP, BP, TP, TP, BP, BP, TP,
            BP, BP, TP, TP, BP, BP, TP, TP, BP, BP, TP, BP, BP, TP, TP, BP, BP, TP, TP,
            BP, BP, TP, BP, BP, TP, TP, BP, BP, TP, TP, BP, BP, TP, TP, BP, BP, TP,
            BP, BP, TP, TP, BP, TP, TP, TP, BP ,TP, TP, BP, BP, TP, TP, BP ,BP, TP, TP, TP,
            BP, BP, BP, TP, BP, TP, BP, BP
    };

    @Before
    public void setUp() {

    }

    private void testBarcodeWithPattern(Barcode barcode, int[] pattern) {
        barcode.setBounds(new Rect(0, 0, barcode.getIntrinsicWidth(), barcode.getIntrinsicHeight()));

        // Check if barcode generated successfully
        assertTrue(barcode.getIntrinsicHeight() > 0);
        assertTrue(barcode.getIntrinsicWidth() == pattern.length /
                barcode.getIntrinsicHeight());

        Bitmap barcodeBitmap = Bitmap.createBitmap(barcode.getIntrinsicWidth(),
                barcode.getIntrinsicHeight(), Bitmap.Config.ARGB_8888);
        Canvas canvas = new Canvas(barcodeBitmap);

        barcode.draw(canvas);

        IntBuffer pixelBuffer = ByteBuffer.allocateDirect(barcodeBitmap.getByteCount())
                .order(ByteOrder.LITTLE_ENDIAN).asIntBuffer();
        barcodeBitmap.copyPixelsToBuffer(pixelBuffer);
        pixelBuffer.position(0);

        IntBuffer patternBuffer = IntBuffer.wrap(pattern);

        assertTrue(pixelBuffer.equals(patternBuffer));
    }

    @Test
    public void testBarcodeTypeC() {
        Barcode barcode = new Code128Barcode("R");
        testBarcodeWithPattern(barcode, R_LETTER_PATTERN_PIXEL_ARRAY);
    }

    @Test
    public void testBarcodeTypeB() {
        Barcode barcode = new Code128Barcode("20");
        testBarcodeWithPattern(barcode, NUMBER_20_PATTERN_PIXEL_ARRAY);
    }

    @Test
    public void testBarcodeTypeCB() {
        Barcode barcode = new Code128Barcode("20R");
        testBarcodeWithPattern(barcode, NUMBER_20_R_LETTER_PATTERN_PIXEL_ARRAY);
    }

    @Test
    public void testBarcodeTypeBC() {
        Barcode barcode = new Code128Barcode("R20");
        testBarcodeWithPattern(barcode, R_LETTER_NUMBER_20_PATTERN_PIXEL_ARRAY);
    }

    @Test
    public void testGS1() {
        Barcode barcode = new Code128Barcode("\u00f100123456780000000001");
        testBarcodeWithPattern(barcode, GS1_PATTERN_PIXEL_ARRAY);
    }
}
