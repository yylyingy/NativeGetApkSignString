package io.yylyingy.github.libkeystoresign;

import android.content.Context;

/**
 * Created by Yangyl on 2017/4/6.
 */

public class Keysignlib {
    static {
        System.loadLibrary("sign-lib");
    }
    public static String getSignData(Context context){
        context = context.getApplicationContext();
        return signData(context);
    }
    private static native String signData(Context context);
}
