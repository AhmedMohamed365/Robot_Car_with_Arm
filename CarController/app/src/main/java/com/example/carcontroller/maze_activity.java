package com.example.carcontroller;

import androidx.appcompat.app.AppCompatActivity;

import android.annotation.SuppressLint;
import android.bluetooth.BluetoothAdapter;
import android.bluetooth.BluetoothDevice;
import android.bluetooth.BluetoothSocket;
import android.content.Intent;
import android.graphics.drawable.Drawable;
import android.os.Bundle;
import android.os.Handler;
import android.os.HandlerThread;
import android.os.Looper;
import android.view.MotionEvent;
import android.view.View;
import android.widget.ImageButton;
import android.widget.ImageView;
import android.widget.Toast;

import java.io.IOException;
import java.io.InputStream;
import java.io.OutputStream;
import java.util.UUID;

public class maze_activity extends AppCompatActivity {
    ImageView leftUltra, upUltra, rightUltra;
    private byte[] buffer = null;
    private HandlerThread handlerThread = null;
    private Handler handler = null;
    private Runnable runnable_Maze = null;

    private BluetoothAdapter btAdapter = null;
    private BluetoothSocket btSocket = null;
    private OutputStream outStream = null;
    private InputStream inputStream = null;
    private int incomingBytes = 0;

    public String newAddress ;
    private String direction;
    private boolean stopThread = true;

    private ImageButton forward;
    private ImageButton backward;
    private ImageButton right;
    private ImageButton left;


    private static final UUID MY_UUID = UUID.fromString("00001101-0000-1000-8000-00805F9B34FB");

    @SuppressLint("ClickableViewAccessibility")
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_maze_activity);

        btAdapter = BluetoothAdapter.getDefaultAdapter();
        checkBTState();


        leftUltra = findViewById(R.id.left_red);
        upUltra = findViewById(R.id.up_red);
        rightUltra = findViewById(R.id.right_red);

        forward = (ImageButton)findViewById(R.id.arrowUp);
        backward = (ImageButton)findViewById(R.id.arrowDown);
        right = (ImageButton)findViewById(R.id.arrowRight);
        left = (ImageButton)findViewById(R.id.arrowLeft);


        handlerThread = new HandlerThread("MazeHandlerThread");
        handlerThread.start();
        Looper looper = handlerThread.getLooper();
        handler = new Handler(looper);
        runnable_Maze = new Runnable() {
            @Override
            public void run() {
                System.out.println("run here");
                while (true) {

                    if (!stopThread) {
                        System.out.println(direction);
                        sendData(direction);
                    }

                    buffer = new byte[1024];
                    try {
                        if (inputStream != null)
                            incomingBytes = inputStream.read(buffer);
                    } catch (IOException e) {
                        System.out.println("Maze: Error in read buffer\n" + e.getMessage());
                        return;
                    }
                    if (incomingBytes > 0) {
                        String data = new String(buffer, 0, incomingBytes); 
                        System.out.println("Incoming data: " + data);
                        if(data.equals("q"))
                            upUltra.setImageResource(R.drawable.up_green);
                        else if(data.equals("a"))
                            upUltra.setImageResource(R.drawable.up_red);
                        else if(data.equals("w"))
                            rightUltra.setImageResource(R.drawable.right_green);
                        else if(data.equals("$"))
                            rightUltra.setImageResource(R.drawable.right_red);
                        else if(data.equals("e"))
                            leftUltra.setImageResource(R.drawable.left_green);
                        else if(data.equals("d"))
                            leftUltra.setImageResource(R.drawable.left_red);

                    }
                }
            }
        };
        handler.post(runnable_Maze);

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
            btSocket.close();
        } catch (Exception e) {
            Toast.makeText(getBaseContext(), "ERROR - Failed to close Bluetooth socket", Toast.LENGTH_SHORT).show();
        }
    }

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
}