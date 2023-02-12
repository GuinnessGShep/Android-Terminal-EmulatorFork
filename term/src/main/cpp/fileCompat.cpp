/*
 * Copyright (C) 2012 Steven Luo
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#define LOG_TAG "FileCompat"

#include <unistd.h>

#include "fileCompat.h"

static jboolean testExecute(JNIEnv *env, jobject clazz, jstring jPathString)
{
    const char *pathname;
    int result;

    /* XXX We should convert CESU-8 to UTF-8 to deal with potential non-BMP
       chars in pathname */
    pathname = env->GetStringUTFChars(jPathString, nullptr);

    result = access(pathname, X_OK);

    env->ReleaseStringUTFChars(jPathString, pathname);
    return (result == 0);
}

extern "C"
JNIEXPORT jboolean JNICALL
Java_jackpal_androidterm_compat_FileCompat_00024Api8OrEarlier_testExecute(JNIEnv *env, jclass clazz,
                                                                          jstring pathName) {
    return testExecute(env, clazz, pathName);
}