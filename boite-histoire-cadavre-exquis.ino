 /*
Ce programme s'appuie sur le travail mené par Giles Booth (http://www.suppertime.co.uk/blogmywiki/2012/10/howtopoems/) 
et la dadaist poetry box réalisée par robottini (http://robottini.altervista.org/dadaist-poetry-box)
Ce programme est placé sous licence Creative Commons NC-BY-SA : https://creativecommons.org/licenses/by-nc-sa/2.0/fr/
julanimtic : http://blog.animtic.fr
 
 Boîte à histoires V1.1 05-03-2017
*/

#include <avr/pgmspace.h> // appel de la bibliothèque pour stocker les données sur la mémoire flash de la carte

const char string_0[] PROGMEM = "Sur la lune";   
const char string_1[] PROGMEM = "Au bord du monde";
const char string_2[] PROGMEM = "Au fond de l\x27ocean";
const char string_3[] PROGMEM = "Dans sa bulle";
const char string_4[] PROGMEM = "Sur une branche";
const char string_5[] PROGMEM = "Dans sa grotte";
const char string_6[] PROGMEM = "un crocodile";   
const char string_7[] PROGMEM = "un panda roux";
const char string_8[] PROGMEM = "un ornithorynque";
const char string_9[] PROGMEM = "une licorne";
const char string_10[] PROGMEM = "une chouette";
const char string_11[] PROGMEM = "une chauve-souris";
const char string_12[] PROGMEM = "r\x88ve d\x27";   
const char string_13[] PROGMEM = "s\x27 amuse avec";
const char string_14[] PROGMEM = "tombe amoureux(se) d\x27";
const char string_15[] PROGMEM = "part en voyage \x85 bord d\x27";
const char string_16[] PROGMEM = "jongle avec";
const char string_17[] PROGMEM = "r\x82pare";
const char string_18[] PROGMEM = "un parapluie.";   
const char string_19[] PROGMEM = "une toile d\x27 araignee.";
const char string_20[] PROGMEM = "un arc en ciel.";
const char string_21[] PROGMEM = "un balais volant.";
const char string_22[] PROGMEM = "une fleur.";
const char string_23[] PROGMEM = "un robot";

// Tableau des textes

const char* const string_table1[] PROGMEM = {string_0, string_1,string_2,string_3,string_4, string_5}; // si besoin compléter les valeurs string manquantes 
const char* const string_table2[] PROGMEM = {string_6, string_7,string_8, string_9,string_10, string_11}; 
const char* const string_table3[] PROGMEM = {string_12,string_13,string_14, string_15,string_16,string_17}; 
const char* const string_table4[] PROGMEM = {string_18,string_19,string_20, string_21,string_22,string_23};

char buffer[1040];    // assurez-vous que la valeur indiquée soit supérieure au nombre maximum de caractères d'un string

int chiffreal = 0; // définit le nom de la valeur aléatoire pour déterminer le texte à utiliser

//appel de la bibiothèque de l'imprimante, voir le tutoriel d'utilisation de l'imprimante sur adafruit : https://learn.adafruit.com/mini-thermal-receipt-printer
#include "Adafruit_Thermal.h"
#include "SoftwareSerial.h"
#define TX_PIN 6 
#define RX_PIN 5

SoftwareSerial mySerial(RX_PIN, TX_PIN); 
Adafruit_Thermal printer(&mySerial);    

 //une led est utilisée pour vérifier le bon fonctionnement du bouton. Ce n'est pas obligatoire. 
const int buttonPin = 2;     // le numéro de la broche utilisée par le bouton
const int ledPin =  13;      // le numéro de la broche utilisée par la led
int buttonState = 0;         // variable pour vérifier l'état du bouton 

//fonction intégrant les différents textes à imprimer appelés ici vers 1, vers 2, ...
void vers1 () {

chiffreal = random(0,5); // sélectionne un string entre 0 et 4 

  {
    strcpy_P(buffer, (char*)pgm_read_word(&(string_table1[chiffreal]))); // copie le string sélectionné aléatoirement de la table string_table
    printer.println(buffer); //imprime le string situé dans le buffer de la carte
    delay( 1000 ); // patiente une seconde
   }
  }

  void vers2 () {

chiffreal = random(0,5); // décommentez pour le mode cadavre exquis

  {
    strcpy_P(buffer, (char*)pgm_read_word(&(string_table2[chiffreal]))); // copie le string sélectionné aléatoirement de la table string_table1
    printer.println(buffer);
    delay( 1000 );
   }
  }

    void vers3 () {

chiffreal = random(0,5);// décommentez pour le mode cadavre exquis

  {
    strcpy_P(buffer, (char*)pgm_read_word(&(string_table3[chiffreal]))); 
    printer.println(buffer);
    delay( 1000 );

   }
  }
  
  void vers4 () {

chiffreal = random(0,5);// décommentez pour le mode cadavre exquis

  {
    strcpy_P(buffer, (char*)pgm_read_word(&(string_table4[chiffreal]))); 
    printer.println(buffer);
    delay( 1000 );

   }
  }


void setup() {
  // défini la broche de la led comme une sortie
  pinMode(ledPin, OUTPUT);
  // défini la broche du bouton comme une entrée
  pinMode(buttonPin, INPUT);
  // initialise l'imprimante
  mySerial.begin(19200);
  printer.begin();
}

void loop() {
  // vérifier l'état du bouton
  buttonState = digitalRead(buttonPin);

  // Si le bouton est pressé
  if (buttonState == HIGH) {
    // Allume la led
    digitalWrite(ledPin, HIGH);
    printer.wake(); //réveille l'imprimante
    printer.feed(1); // déroule le papier sans imprimer
    printer.boldOn(); // met le texte en gras
    vers1(); // imprime le premier texte
    vers2(); // imprime le second texte ...
    vers3();
    vers4(); // en fonction du nombre d'éléments à afficher décommentez cette ligne. Si vous souhaitez afficher plus d'éléments pensez à créer la fonction correspondante plus haut (ex ici void vers4)
    printer.feed(1);
    printer.println("La petite boite \x85 histoire"); // placez ici votre signature
    printer.boldOff(); // fin du texte en gras
    printer.feed(2);
    printer.sleep(); //met en sommeil l'imprimante
    
  } 
  else {
    // éteins la led et ne fais rien 
    digitalWrite(ledPin, LOW);


 }
  
}
