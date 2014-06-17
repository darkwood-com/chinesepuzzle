package com.darkwood.chinesepuzzle;

import org.cocos2dx.lib.Cocos2dxActivity;
import org.cocos2dx.lib.Cocos2dxGLSurfaceView;
import android.os.Build;

public class AppActivity extends Cocos2dxActivity {
    public Cocos2dxGLSurfaceView onCreateView() {
        Cocos2dxGLSurfaceView view = new Cocos2dxGLSurfaceView(this);

        if (isAndroidEmulatorRunning())
            view.setEGLConfigChooser(8 , 8, 8, 8, 16, 0);
        else
            view.setEGLConfigChooser(8 , 8, 8, 8, 16, 8);

        return view;
    }

    private final static boolean isAndroidEmulatorRunning() {
        String model = Build.MODEL;
        String product = Build.PRODUCT;
        boolean isEmulator = false;
        if (product != null) {
            isEmulator = product.equals("sdk") || product.contains("_sdk") || product.contains("sdk_");
        }
        return isEmulator;
   }
}
