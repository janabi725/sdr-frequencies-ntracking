#include <stdlib.h>
#include <stdio.h>
#include <rtl-sdr.h>

#define FREQUENCY 1090000000
#define SAMPLE_RATE 2000000
#define BUFFER_SIZE 16 * 1024

int main() {
    int device_index = 0;
    rtlsdr_dev_t *device = NULL;
    int r;

    // 1. Zähle wie viele Sticks da sind
    int device_count = rtlsdr_get_device_count();

    if (device_count == 0)  {
        printf("Da geht goi nix Chefe\n");
        return -1;
    }
    printf("Gefunden: %d Geräte()\n", device_count);
    printf("Öffene Geräte\n");
    // Öffne den Stick 
    int device_open = rtlsdr_open(&device, device_index);

    if (device_open < 0) {
        printf("Geht ned offe\n");
        return -1;
    }
    printf("Es lässt sich öffen\n");

    //Richtige Frequenz setzen
    int device_fr = rtlsdr_set_center_freq(device, FREQUENCY);

    printf("Frequenz Status: %d\n", device_fr);

    //Sample Rate setzen

    int device_sr = rtlsdr_set_sample_rate(device, SAMPLE_RATE);

    printf("Sample Rate Status: %d\n" , device_sr);

    //Buffer resetten

    rtlsdr_reset_buffer(device);



    // Buffer konfigurieren
    uint8_t buffer[16 * 1024];

   
    int bytes_gelesen;
    
    int c = 0;
    int status = 0;
    while(1) {
    
    status = rtlsdr_read_sync(device, buffer, BUFFER_SIZE, &bytes_gelesen);

    for (int i = 0; i < BUFFER_SIZE; i++)
        {   if(buffer[i] > 120)
            {
            printf("Starkes Signal mit %d\n", buffer[i]);
            }

            else if (buffer[i] < 108)
            { 
                printf("Schwaches Signal mit %d\n", buffer [i]);
            }

            
        
        
        };
        c++; 
        if (c > 1000){break;};
        
    } 
    rtlsdr_close(device);
    return 0; 
    

}