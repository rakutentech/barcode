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

import android.graphics.Canvas;
import android.graphics.Color;
import android.graphics.Paint;
import android.graphics.PorterDuff;
import android.graphics.PorterDuffXfermode;
import android.graphics.RectF;
import android.support.annotation.Nullable;
import android.util.Log;

import java.io.ByteArrayOutputStream;

import jp.co.rakuten.esd.barcode.Barcode;

/**
 * Shape, which is used by {@link Barcode} to draw itself.
 */
class Code128Shape extends Barcode.BarcodeShape {

    private final String LOG_TAG = "Code128Shape";

    // 2 is for actual bars, because there is no strict limitation for barcode height.
    private final int MINIMAL_CODE_HEIGHT = 2;

    private Paint mInnerPaint;

    static {
        System.loadLibrary("barcode-code128");
    }

    private native void encode(@Nullable final byte[] payload);

    // Keep in mind, name of this variable can be changed only with corresponding changes in native code.
    private byte[] mEncodedBytes;

    // Keep in mind, name of this variable can be changed only with corresponding changes in native code.
    private int mWidth;

    /**
     * Creates an instance of Code128Shape with encoded payload as 1D Code128 barcode
     *
     * @param payload Payload, that will be encoded
     */
    Code128Shape(final String payload) {
        super();

        // mEncodedBytes and mWidth variables will be initialised in native code
        try {
            byte[] latinPayload = payload.getBytes("ISO-8859-1");

            ByteArrayOutputStream bos = new ByteArrayOutputStream(latinPayload.length + 1);
            bos.write(latinPayload);
            bos.write(0);

            encode(bos.toByteArray());
        } catch (Exception e) {
            Log.e(LOG_TAG, e.getMessage());
        }

        mInnerPaint = new Paint();
        mInnerPaint.setColor(Color.BLACK); // Default is black

        // Blending mode is SRC_OVER
        mInnerPaint.setXfermode(new PorterDuffXfermode(PorterDuff.Mode.SRC_OVER));
    }

    /**
     * Obtain {@link Paint} object, that is used for bars drawing.
     *
     * @return Paint object
     */
    Paint getBarcodeInnerPaint() {
        return mInnerPaint;
    }

    @Override
    public void draw(Canvas canvas, Paint paint) {
        super.draw(canvas, paint);

        if (mEncodedBytes != null && mWidth > 0) {

            float xScaleCoef = (canvas.getWidth() - paint.getStrokeWidth() * 2) / mWidth;
            RectF lineRect = new RectF(paint.getStrokeWidth(), paint.getStrokeWidth(),
                    paint.getStrokeWidth(), canvas.getHeight() - paint.getStrokeWidth());

            for (int i = 0; i < mEncodedBytes.length; i++) {
                if (i > 0) {
                    lineRect.left += mEncodedBytes[i - 1] * xScaleCoef;
                }
                lineRect.right += mEncodedBytes[i] * xScaleCoef;
                if (i % 2 == 0) {
                    canvas.drawRect(lineRect, mInnerPaint);
                }
            }
        }
    }

    @Override
    public int getMinimumHeight() {
        return MINIMAL_CODE_HEIGHT;
    }

    @Override
    public int getMinimumWidth() {
        return mWidth;
    }
}
