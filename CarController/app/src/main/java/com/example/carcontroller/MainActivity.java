package com.example.carcontroller;

import androidx.appcompat.app.AppCompatActivity;

import android.annotation.SuppressLint;
import android.bluetooth.BluetoothAdapter;
import android.bluetooth.BluetoothDevice;
import android.bluetooth.BluetoothSocket;
import android.content.Intent;
import android.os.Bundle;
import android.os.Handler;
import android.os.HandlerThread;
import android.os.Looper;
import android.view.MotionEvent;
import android.view.View;
import android.widget.Button;
import android.widget.ImageButton;
import android.widget.Toast;

import java.io.IOException;
import java.io.InputStream;
import java.io.OutputStream;
import java.util.UUID;

public class MainActivity extends AppCompatActivity {

    private BluetoothAdapter btAdapter = null;
    private BluetoothSocket btSocket = null;
    private OutputStream outStream = null;
    private InputStream inputStream = null;
    private int incomingBytes = 0;
    private byte[] buffer = null;
    private Handler handler = null;
    private Runnable runnable_Main = null;

    // UUID service - This is the type of Bluetooth device that the BT module is
    // It is very likely yours will be the same, if not google UUID for your manufacturer
    private static final UUID MY_UUID = UUID.fromString("00001101-0000-1000-8000-00805F9B34FB");

    // MAC-address of Bluetooth module
    public String newAddress = null;

    private Button servo1_L;
    private Button servo1_R;
    private Button servo2_L;
    private Button servo2_R;
    private Button servo3_L;
    private Button servo3_R;
    private Button servo4_L;
    private Button servo4_R;
    private Button servo5_L;
    private Button servo5_R;
    private Button servo6_L;
    private Button servo6_R;
    private ImageButton forward;
    private ImageButton backward;
    private ImageButton right;
    private ImageButton left;

    private String direction;
    private boolean stopThread = true;

    @SuppressLint("ClickableViewAccessibility")
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);


        //getting the bluetooth adapter value and calling checkBTstate function
        btAdapter = BluetoothAdapter.getDefaultAdapter();
        checkBTState();

        servo1_L = (Button)findViewById(R.id.servo6_1);
        servo1_R = (Button)findViewById(R.id.servo6_2);
        servo2_L = (Button)findViewById(R.id.servo2_1);
        servo2_R = (Button)findViewById(R.id.servo2_2);
        servo3_L = (Button)findViewById(R.id.servo4_1);
        servo3_R = (Button)findViewById(R.id.servo4_2);
        servo4_L = (Button)findViewById(R.id.servo4_1);
        servo4_R = (Button)findViewById(R.id.servo4_2);
        servo5_L = (Button)findViewById(R.id.servo2_1);
        servo5_R = (Button)findViewById(R.id.servo2_2);
        servo6_L = (Button)findViewById(R.id.servo6_1);
        servo6_R = (Button)findViewById(R.id.servo6_2);
        forward = (ImageButton)findViewById(R.id.uparrow);
        backward = (ImageButton)findViewById(R.id.downarrow);
        right = (ImageButton)findViewById(R.id.rightarrow);
        left = (ImageButton)findViewById(R.id.leftarrow);

        HandlerThread handlerThread = new HandlerThread("MainHandlerThread");
        handlerThread.start();
        Looper looper = handlerThread.getLooper();
        handler = new Handler(looper);
        runnable_Main =  new Runnable() {
            @Override
            public void run() {
                System.out.println("here run");
                while (true)
                {
                    if(!stopThread)
                    {
                        System.out.println(direction);
                        sendData(direction);
                    }
                }
            }
        };
        handler.post(runnable_Main);


        forward.setOnTouchListener(new View.OnTouchListener() {
            @Override
            public boolean onTouch(View v, MotionEvent event) {
                if(event.getAction() == MotionEvent.ACTION_DOWN)
                {
                    sendData("f");
                }
                if(event.getAction() == MotionEvent.ACTION_UP)
                {
                    sendData("s");
                }
                return true;
            }
        });

        backward.setOnTouchListener(new View.OnTouchListener() {
            @Override
            public boolean onTouch(View v, MotionEvent event) {
                if(event.getAction() == MotionEvent.ACTION_DOWN)
                {
                    sendData("b");
                }
                if(event.getAction() == MotionEvent.ACTION_UP)
                {
                    sendData("s");
                }
                return false;
            }
        });

        right.setOnTouchListener(new View.OnTouchListener() {
            @Override
            public boolean onTouch(View v, MotionEvent event) {

                if(event.getAction() == MotionEvent.ACTION_DOWN)
                {
                    sendData("r");
                }
                if(event.getAction() == MotionEvent.ACTION_UP)
                {
                    sendData("s");
                }
                return false;
            }
        });

        left.setOnTouchListener(new View.OnTouchListener() {
            @Override
            public boolean onTouch(View v, MotionEvent event) {
                if(event.getAction() == MotionEvent.ACTION_DOWN)
                {
                    sendData("l");
                }
                if(event.getAction() == MotionEvent.ACTION_UP)
                {
                    sendData("s");
                }
                return false;
            }
        });

        servo1_L.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                sendData("a");
            }
        });
        servo1_R.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                sendData("x");
            }
        });
        servo2_L.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                System.out.println("press");
                sendData("j");
            }
        });
        servo2_R.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                System.out.println("press");
                sendData("d");
            }
        });
        servo3_L.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                System.out.println("press");
                sendData("k");
            }
        });
        servo3_R.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                System.out.println("press");
                sendData("m");
            }
        });
        servo4_L.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                System.out.println("press");
                sendData("n");
            }
        });
        servo4_R.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                System.out.println("press");
                sendData("o");
            }
        });
        servo5_L.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                System.out.println("press");
                sendData("i");
            }
        });
        servo5_R.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                System.out.println("press");
                sendData("h");
            }
        });
        servo6_L.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                System.out.println("press");
                sendData("z");
            }
        });
        servo6_R.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                System.out.println("press");
                sendData("g");
            }
        });
    }

    @Override
    protected void onResume() {
        super.onResume();
        // connection methods are best here in case program goes into the background etc

        //Get MAC address from DeviceListActivity
        Intent intent = getIntent();
        newAddress = intent.getStringExtra(Menu.EXTRA_DEVICE_ADDRESS);

        // Set up a pointer to the remote device using its address.
        BluetoothDevice device = btAdapter.getRemoteDevice(newAddress);

        //Attempt to create a bluetooth socket for comms
        try {
            btSocket = device.createRfcommSocketToServiceRecord(MY_UUID);
        } catch (IOException e1) {
            Toast.makeText(getBaseContext(), "ERROR - Could not create Bluetooth socket", Toast.LENGTH_SHORT).show();
        }

        // Establish the connection.
        try {
            btSocket.connect();
        } catch (IOException e) {
            try {
                btSocket.close();        //If IO exception occurs attempt to close socket
            } catch (IOException e2) {
                Toast.makeText(getBaseContext(), "ERROR - Could not close Bluetooth socket", Toast.LENGTH_SHORT).show();
            }
        }

        // Create a data stream so we can talk to the device
        try {
            outStream = btSocket.getOutputStream();
        } catch (IOException e) {
            Toast.makeText(getBaseContext(), "ERROR - Could not create bluetooth outstream", Toast.LENGTH_SHORT).show();
        }
        //When activity is resumed, attempt to send a piece of junk data ('x') so that it will fail if not connected
        // i.e don't wait for a user to press button to recognise connection failure
        sendData("x");

        // Create a data stream to read incoming data
        try {
            inputStream = btSocket.getInputStream();
        } catch (IOException e) {
            System.out.println("Error in input stream");
        }
    }

    @Override
    public void onBackPressed() {
        super.onBackPressed();
        try {
            //handler.removeCallbacks(runnable_Main);
            handler.removeCallbacksAndMessages(null);
            btSocket.close();
        } catch (IOException e2) {
            Toast.makeText(getBaseContext(), "ERROR - Failed to close Bluetooth socket", Toast.LENGTH_SHORT).show();
        }
    }

    //takes the UUID and creates a comms socket
    private BluetoothSocket createBluetoothSocket(BluetoothDevice device) throws IOException {
        return device.createRfcommSocketToServiceRecord(MY_UUID);
    }

    //same as in device list activity
    private void checkBTState() {
        // Check device has Bluetooth and that it is turned on
        if (btAdapter == null) {
            Toast.makeText(getBaseContext(), "ERROR - Device does not support bluetooth", Toast.LENGTH_SHORT).show();
            finish();
        } else {
            if (btAdapter.isEnabled()) {
            } else {
                //Prompt user to turn on Bluetooth
                Intent enableBtIntent = new Intent(BluetoothAdapter.ACTION_REQUEST_ENABLE);
                startActivityForResult(enableBtIntent, 1);
            }
        }
    }

    // Method to send data
    private void sendData(String message) {
        byte[] msgBuffer = message.getBytes();
        System.out.println("data sent");

        try {
            //attempt to place data on the outstream to the BT device
            outStream.write(msgBuffer);
        } catch (IOException e) {
            //if the sending fails this is most likely because device is no longer there
            Toast.makeText(getBaseContext(), "ERROR - Device not found", Toast.LENGTH_SHORT).show();
            finish();
        }
    }
}