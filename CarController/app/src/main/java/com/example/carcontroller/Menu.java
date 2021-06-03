package com.example.carcontroller;

import androidx.appcompat.app.AppCompatActivity;

import android.content.Intent;
import android.os.Bundle;
import android.view.View;
import android.widget.Button;

import static com.example.carcontroller.Bluetooth_connection.EXTRA_DEVICE_ADDRESS;

public class Menu extends AppCompatActivity {

    Button car,ultra;

    //An EXTRA to take the device MAC to the next activity
    public static String EXTRA_DEVICE_ADDRESS;
    // MAC-address of Bluetooth module
    public String newAddress = null;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_menu);

        car = findViewById(R.id.car);
        ultra = findViewById(R.id.ultra);

        Intent intent = getIntent();
        newAddress = intent.getStringExtra(Bluetooth_connection.EXTRA_DEVICE_ADDRESS);


        car.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                Intent i = new Intent(Menu.this, MainActivity.class);
                i.putExtra(EXTRA_DEVICE_ADDRESS, newAddress);
                startActivity(i);
            }
        });

        ultra.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                Intent i = new Intent(Menu.this, maze_activity.class);
                i.putExtra(EXTRA_DEVICE_ADDRESS, newAddress);
                startActivity(i);
            }
        });



    }
}