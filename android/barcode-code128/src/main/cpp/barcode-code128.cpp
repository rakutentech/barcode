/**
 * Barcode 128 Intermediate layer to be called from Java.
 *
 * @author "Rakuten Ecosystem Mobile" <ecosystem-mobile@mail.rakuten.com>
 */

#include <jni.h>
#include <stdint.h>
#include <string.h>

#include "bar128encode.h"

#define DEFAULT_BARCODE_BUFFER_ARRAY_LENGTH 1024

static char barcodeBufferArray[DEFAULT_BARCODE_BUFFER_ARRAY_LENGTH];


extern "C" void Java_jp_co_rakuten_esd_barcode_code128_Code128Shape_encode(JNIEnv *env,
                                                                           jobject thiz,
                                                                           jbyteArray payload) {
    if (payload == NULL)
        return;

    jbyte* payloadArray = env->GetByteArrayElements(payload, NULL);

    unsigned int width = bar128encode(reinterpret_cast<const char*>(payloadArray),
                                      barcodeBufferArray, sizeof(barcodeBufferArray));

    env->ReleaseByteArrayElements(payload, payloadArray, JNI_ABORT);

    jbyteArray barcodeArray = NULL;
    if (width) {
        size_t actualBarcodeArraySize = strlen(barcodeBufferArray);

        jsize barcodeArrayLength = static_cast<jsize> (actualBarcodeArraySize);

        barcodeArray = env->NewByteArray(barcodeArrayLength);
        env->SetByteArrayRegion(barcodeArray, 0, barcodeArrayLength,
                                reinterpret_cast<const jbyte *>(barcodeBufferArray));

    }

    // set mEncodedBytes array class variable
    jclass objClass = env->GetObjectClass(thiz);
    jfieldID barcodeArrayFieldId = env->GetFieldID(objClass, "mEncodedBytes", "[B");

    env->SetObjectField(thiz, barcodeArrayFieldId, barcodeArray);

    // set mWidth class variable
    jfieldID widthFieldId = env->GetFieldID(objClass, "mWidth", "I");

    env->SetIntField(thiz, widthFieldId, width);
}