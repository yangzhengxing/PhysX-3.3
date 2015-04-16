package com.nvidia.physx.samples;

import android.app.NativeActivity;
import android.content.res.Configuration;
import android.graphics.PixelFormat;
import android.os.Bundle;
import android.view.View;
import android.view.Window;
import android.view.WindowManager;
import android.util.Log;

public class SamplesActivity extends NativeActivity
{
 protected void onCreate (Bundle savedInstanceState)
 {	
  getWindow().setFlags(WindowManager.LayoutParams.FLAG_FULLSCREEN, 
						WindowManager.LayoutParams.FLAG_FULLSCREEN); 
  super.onCreate(savedInstanceState);
 }
}