
/**** Widerstandswerte in Ohm ****/
#define PT1000_R1 3300.0
#define PT1000_R2 3300.0
#define PT1000_R3 680.0
#define PT1000_R4 10000.0
#define PT1000_R5 10000.0
#define PT1000_R6 43000.0
#define PT1000_R7 43000.0

#define PT1000_Versorgung 4.98
#define PT1000_Aufloesung 256
#define PT1000_Koeffizient_A (0.00390802)
#define PT1000_Koeffizient_B (-0.0000005802)
#define PT1000_Vergleichspannung ((PT1000_Versorgung*PT1000_R3)/(PT1000_R3+PT1000_R2))

uint8_t temperatur_Soll;
uint16_t sollWertADC;

/*** Umrechnen von Temperatur in Bitwert ***/
uint16_t PT1000berechnen(uint8_t temperatur)
{

  /********************************************************************************************/
  /*                                  !!!!!!!!Wichtig!!!!!!!!                                 */
  /*                            Geht nur bei Temperaturen über 0°C                            */
  /********************************************************************************************/


  float widerstandswert;
  float spannungsabfall_PT;
  float ausgangsspannungOPV;
  uint16_t wertADC;


  widerstandswert = (1000 * (1 + PT1000_Koeffizient_A * temperatur + PT1000_Koeffizient_B * temperatur * temperatur));                                                                      // Widerstandswert berechnen
  spannungsabfall_PT = ((PT1000_Versorgung * widerstandswert) / (PT1000_R1 + widerstandswert));                                                                                             // Spannugsabfall über PT1000 berechnen
  ausgangsspannungOPV = (spannungsabfall_PT * ((PT1000_R5 + PT1000_R7) / PT1000_R5) * (PT1000_R6 / (PT1000_R4 + PT1000_R6)) - (PT1000_Vergleichspannung * (PT1000_R7 / PT1000_R5)));        // Ausgangsspannung des Differenzverstärkers berechnen
  wertADC = ((ausgangsspannungOPV * PT1000_Aufloesung) / PT1000_Versorgung - 1);                                                                                                            // Wert des ADC berechnen


  Serial.println("Zwischenergebnisse: ");
  Serial.println("");
  Serial.print("Widerstandswert in Ohm: ");
  Serial.println(widerstandswert);
  Serial.print("Spannungsabfall PT1000 in V: ");
  Serial.println(spannungsabfall_PT);
  Serial.print("Ausgang OPV in V: ");
  Serial.println(ausgangsspannungOPV);
  Serial.println("");

  return wertADC;
}
void setup()
{
  Serial.begin(9600);

  temperatur_Soll = 200;
  
  Serial.print("Temperatur in °C: ");
  Serial.println(temperatur_Soll);

  sollWertADC = PT1000berechnen(temperatur_Soll);

  Serial.print("Wert ADC: ");
  Serial.println(sollWertADC);
}

void loop()
{

}
