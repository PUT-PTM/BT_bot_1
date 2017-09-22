package com.example.ania.jamnik;
import android.bluetooth.BluetoothAdapter;
import android.bluetooth.BluetoothDevice;
import android.bluetooth.BluetoothSocket;
import android.content.Intent;
import android.os.Bundle;
import android.support.v7.app.AppCompatActivity;
import android.view.MotionEvent;
import android.view.View;
import android.widget.Button;
import android.widget.Toast;
import java.io.IOException;
import java.io.OutputStream;
import java.util.Set;
import java.util.UUID;

public class MainActivity extends AppCompatActivity {
    /***************************************************************************************
     * 1 - ADRES MAC BLUETOOTH
     * 1 - MAC ADDRESS OF BLUETOOTH MODULE IN MACHINE
     *
     * 2 - PORT UUID, DOMYŚLNA WARTOŚĆ
     * 2 - PORT UUID, DEFAULT NUMBER
     *
     * 3 - DEKLARACJE: URZĄDZENIE BLUETOOTH, GNIAZDO I STRUMIEŃ WYSYŁANIA DANYCH
     * 3 - DECLARATION: BLUETOOTH DEVICE, SOCKET AND OUTPUT STREAM (WITH THIS ONE WE SEND
     *     COMMAND TO OUR MACHINE)
     *
     * 4 - DEKLARACJE PRZYCISKÓW: PRZÓD, TYŁ, LEWA, PRAWA, OD POŁĄCZENIA Z BLUETOOTH
     * 4 - DECLARATION OF BUTTONS: FORWARD, REVERSE, LEFT, RIGHT, BLUETOOTH CONNECTION
     *
     */
    //1
    private final String ADRES_MAC_BLUETOOTH = "30:14:12:26:09:64";
    //2
    private final UUID PORT_UUID = UUID.fromString("00001101-0000-1000-8000-00805f9b34fb");
    //3
    private BluetoothDevice urzadzenie;
    private BluetoothSocket gniazdo;
    private OutputStream outputStream;
    //4
    Button przod, tyl, prawa, lewa, polaczBluetooth;


    /***************************************************************************************
     * SEKCJA ONCREATE
     * ONCREATE SECTION
     *
     * 1 - DEFINICJE PRZYCISKÓW, MUSZĄ BYĆ W TEJ SEKCJI!!!
     * 1 - DEFINITIONS OF BUTTONS, THEY MUST BY IN THIS SECTION
     *
     * 2 - KAŻDY PRZYCISK (OPRÓCZ POŁĄCZENIA Z BLUETOOTH) JEST USTAWIONY W TAKI SPOSÓB,
     *     ZE KIEDY GO PRZYCISKAMY TO WYSYŁANY JEST SYGNAŁ O JEŹDZIE POJAZDEM W DANYM KIERUNKU,
     *     A KIEDY GO PUŚCIMY TO WYSYŁANY JEST SYGNAŁ ZATRZYMANIA
     * 2 - ALL BUTTONS (WITHOUT BLUETOOTH CONNECTION) ARE IN CONFIGURATION: WHEN WE PRESS THE BUTTON,
     *     APPLICATION SEND COMMAND TO MACHINE AND WE CAN DRIVE, WHEN WE RELEASE, APP SEND SIGNAL TO STOP MACHINE
     *
     * 3 - PRZYCISK POŁĄCZENIA Z MODUŁEM
     * 3 - BUTTON OF BLUETOOTH CONNECTION
     *
     */
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        //1
        przod = (Button) findViewById(R.id.przod);
        tyl = (Button) findViewById(R.id.tyl);
        prawa = (Button) findViewById(R.id.prawa);
        lewa = (Button) findViewById(R.id.lewa);
        polaczBluetooth = (Button) findViewById(R.id.polacz);

        //2
        przod.setOnTouchListener(new View.OnTouchListener(){
            @Override
            public boolean onTouch(View v, MotionEvent event)
            {
                switch(event.getAction()){
                    case MotionEvent.ACTION_DOWN:
                        try{
                            outputStream.write('w');
                            outputStream.flush();
                        }
                        catch (IOException e){
                            Toast.makeText(getApplicationContext(), "Błąd wysyłania", Toast.LENGTH_SHORT).show();
                        }
                        break;
                    case MotionEvent.ACTION_UP:
                        try {
                            outputStream.write('x');
                            outputStream.flush();

                        }
                        catch(IOException e) {
                            Toast.makeText(getApplicationContext(), "Błąd wysyłania", Toast.LENGTH_SHORT).show();
                        }
                        break;
                    default:
                        break;
                }
                return false;
            }
        });
        tyl.setOnTouchListener(new View.OnTouchListener(){
            @Override
            public boolean onTouch(View v, MotionEvent event)
            {
                switch(event.getAction()){
                    case MotionEvent.ACTION_DOWN:
                        try{
                            outputStream.write('s');
                            outputStream.flush();
                        }
                        catch (IOException e){
                            Toast.makeText(getApplicationContext(), "Błąd wysyłania", Toast.LENGTH_SHORT).show();
                        }
                        break;
                    case MotionEvent.ACTION_UP:
                        try {
                            outputStream.write('x');
                            outputStream.flush();
                        }
                        catch(IOException e) {
                            Toast.makeText(getApplicationContext(), "Błąd wysyłania", Toast.LENGTH_SHORT).show();
                        }
                        break;
                }
                return false;
            }
        });
        lewa.setOnTouchListener(new View.OnTouchListener(){
            @Override
            public boolean onTouch(View v, MotionEvent event)
            {
                switch(event.getAction()){
                    case MotionEvent.ACTION_DOWN:
                        try{
                            outputStream.write('a');
                            outputStream.flush();
                        }
                        catch (IOException e){
                            Toast.makeText(getApplicationContext(), "Błąd wysyłania", Toast.LENGTH_SHORT).show();
                        }
                        break;
                    case MotionEvent.ACTION_UP:
                        try {
                            outputStream.write('x');
                            outputStream.flush();
                        }
                        catch(IOException e) {
                            Toast.makeText(getApplicationContext(), "Błąd wysyłania", Toast.LENGTH_SHORT).show();
                        }
                        break;
                }
                return false;
            }
        });
        prawa.setOnTouchListener(new View.OnTouchListener(){
            @Override
            public boolean onTouch(View v, MotionEvent event)
            {
                switch(event.getAction()){
                    case MotionEvent.ACTION_DOWN:
                        try{
                            outputStream.write('d');
                            outputStream.flush();
                        }
                        catch (IOException e){
                            Toast.makeText(getApplicationContext(), "Błąd wysyłania", Toast.LENGTH_SHORT).show();
                        }
                        break;
                    case MotionEvent.ACTION_UP:
                        try {
                            outputStream.write('x');
                            outputStream.flush();
                        }
                        catch(IOException e) {
                            Toast.makeText(getApplicationContext(), "Błąd wysyłania", Toast.LENGTH_SHORT).show();
                        }
                        break;
                }
                return false;
            }
        });
        //3
        polaczBluetooth.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                if(inicjalizujBluetooth()) {
                    polaczBluetooth();
                }
            }
        });

    }
    /***************************************************************************************
     * INICJALIZACJA BLUETOOTH
     * INITIALIZATION OF BLUETOOTH
     *
     * 1 - SPRAWDZA CZY TELEFON WSPIERA BLUETOOTH
     * 1 - CHECKING IF TELEPHONE HAS BLUETOOTH
     *
     * 2 - SPRAWDZA CZY BLUETOOTH JEST WŁĄCZONY, JEŻELI NIE, TO PROSI UŻYTKOWNIKA O WŁĄCZENIE
     * 2 - CHECKING IF BLUETOOTH IS SET UP, IF NOT - APP SEND REQUEST AND ASK USER TO SET IT UP
     *
     * 3 - SET (KOLEKCJA NIE PRZYJMUJĄCA DUPLIKATÓW) SPAROWNYCH URZĄDZEŃ
     * 3 - SET OF PAIR DEVICES
     *
     * 4 - SPRAWDZA CZY TELEFON I MODUŁ SĄ SPAROWANE, JEŻELI NIE TO PROSI O ICH SPAROWANIE
     * 4 - CHECKING IF TELEPHONE AND OUT MODULE ARE PAIR DEVICER, IF NOT APP SEND MESSAGE TO DO THIS
     *
     */
    public boolean inicjalizujBluetooth() {
        boolean znajdz = false;
        BluetoothAdapter bluetoothAdapter = BluetoothAdapter.getDefaultAdapter();
        //1
        if(bluetoothAdapter == null) {
            Toast.makeText(getApplicationContext(), "Telefon nie posiada bluetooth", Toast.LENGTH_LONG).show();
        }
        //2
        if(!bluetoothAdapter.isEnabled()) {
            Intent czyWlaczonyBluetooth = new Intent(BluetoothAdapter.ACTION_REQUEST_ENABLE);
            startActivityForResult(czyWlaczonyBluetooth,0);
            try {
                Thread.sleep(1000);
            }
            catch(InterruptedException e) {
                Toast.makeText(getApplicationContext(), "Błąd połączenia", Toast.LENGTH_LONG).show();
            }
        }
        //3
        Set<BluetoothDevice> sparowane = bluetoothAdapter.getBondedDevices();
        //4
        if(sparowane.isEmpty()){
            Toast.makeText(getApplicationContext(), "Najpierw sparuj urządzenia", Toast.LENGTH_LONG).show();
        }
        else {
            for(BluetoothDevice iterator : sparowane) {
                if(iterator.getAddress().equals(ADRES_MAC_BLUETOOTH)) {
                    urzadzenie = iterator;
                    znajdz = true;
                    break;
                }
            }
        }
        return znajdz;
    }

    /***************************************************************************************
     * POŁĄCZENIE Z BLUETOOTH
     * CONNECTION WITH BLUETOOTH
     *
     * 1 - STRUMIEŃ DANYCH WYJŚCIOWYCH ŁĄCZY SIĘ Z GNIAZDEM
     * 1 - OUTPUT STREAM IS CONNECT TO THE SOCKET
     *
     */
    public boolean polaczBluetooth() {
        boolean polaczony = true;
        try {
            gniazdo = urzadzenie.createRfcommSocketToServiceRecord(PORT_UUID);
            gniazdo.connect();
            Toast.makeText(getApplicationContext(),
                    "Połączenie z urządzeniem powiodło się", Toast.LENGTH_LONG).show();
        }
        catch(IOException e) {
            Toast.makeText(getApplicationContext(), "Błąd połączenia", Toast.LENGTH_LONG).show();
            polaczony = false;
        }
        //1
        if(polaczony){
            try{
                outputStream = gniazdo.getOutputStream();
            }
            catch(IOException e){
                Toast.makeText(getApplicationContext(), "Błąd połączenia z gniazdem", Toast.LENGTH_LONG).show();
            }
        }
        return polaczony;
    }
}
