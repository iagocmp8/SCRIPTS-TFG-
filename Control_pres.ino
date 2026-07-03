#define PT100_PIN 36  
#define PG0029BEN_PIN 17
#define RREF 9150
#define ADC_MAX 4095  
#define V_REF 3.293
int contador = 0;      
float suma_temp = 0;         
float media_temp = 0; 
float suma_preas = 0;         
float media_preas = 0; 
  
void setup() {
    Serial.begin(115200);
}

void loop() {
    int adcValue_temp = analogRead(PT100_PIN); 
    float voltage = (adcValue_temp / (float)ADC_MAX) * V_REF+0.025; 
//float resistance = (voltage * RREF) / (V_REF - voltage);
    float resistance = RREF*(V_REF-voltage)/voltage;
    float temperature = (resistance - 1000.0) / 3.85; 

    int adcValue_preas = analogRead(PG0029BEN_PIN);
    float voltage_arduino = (adcValue_preas / (float)ADC_MAX) * V_REF+0.025; 
    float voltage_real = voltage_arduino*(10)/V_REF;
    float preassure=pow(10, 1.667 * voltage_real - 11.33);
  
    Serial.print("ADC Value Temp: ");
    Serial.print(adcValue_temp);
    Serial.print(" | Voltage: ");
    Serial.print(voltage, 3);
    Serial.print("V | Resistance: ");
    Serial.print(resistance, 2);
    Serial.print(" Ω | Temperature: ");
    Serial.print(temperature, 2);
    Serial.println(" °C");

    Serial.print("ADC Value Preas: ");
    Serial.print(adcValue_preas);
    Serial.print(" | Preassure: ");
    Serial.print(preassure, 2);
    Serial.println(" mbar");
    Serial.println(" ");

    suma_temp += temperature;
    contador++;
    if (contador == 10) {       
    media_temp = suma_temp / 10.0;  
    media_preas = suma_preas / 10.0;      
    Serial.print("-------------------------------------------------------------*-------------------------------------------------------------\n");
    Serial.print("Avg Temperature : ");
    Serial.print(media_temp, 2);
    Serial.println(" °C");
    Serial.print("Avg Preassure   : ");
    Serial.print(media_preas, 2);
    Serial.println(" mbar");
    Serial.println("-------------------------------------------------------------*-------------------------------------------------------------\n");

    // reiniciamos acumuladores
    contador = 0;
    suma_temp = 0;
    suma_preas = 0;
    }

    delay(1000); 
}
