 /*
Ce programme s'appuie sur le travail mené par Giles Booth (http://www.suppertime.co.uk/blogmywiki/2012/10/howtopoems/) 
et la dadaist poetry box réalisée par robottini (http://robottini.altervista.org/dadaist-poetry-box)
Ce programme est placé sous licence Creative Commons NC-BY-SA : https://creativecommons.org/licenses/by-nc-sa/2.0/fr/
julanimtic : http://blog.animtic.fr
 
 Boîte à histoires V1.1 05-03-2016
*/

#include <avr/pgmspace.h> // appel de la bibliothèque pour stocker les données sur la mémoire flash de la carte

//placez ici le titre de l'oeuvre
const char string_0[] PROGMEM = "Viens  \n";   
const char string_1[] PROGMEM = "La langue du Youshlaouna \n";
const char string_2[] PROGMEM = "Il est tres chouette votre theatre \n";
const char string_3[] PROGMEM = "Quelle chance \n";

// placez le texte de votre histoire/poème ici
// le texte doit être sur une seule ligne, voir le wiki du projet pour le formatage du texte et des caractères spéciaux
const char string_4[] PROGMEM = "Ma main paume vers le sol,\n tombe de bas en haut.\n Ma main paume vers le ciel, \n se replie vers moi. \n Mes doigts se replient \n sur ma main.\n Ma main se replie \n sur elle-meme. \n Mon index se replie sur \n mon poing ferme.\n Mon coude se replie. \n Ma tete dodeline. \n Mes yeux roulent. \n";   
const char string_5[] PROGMEM = "La langue du Youshlaouna. \n La langue du Chiang-ien.  \n La langue du Choubouloutone.  \n La langue du Touroukoukoulou. \n La langue du : Kana:Kana. \n La langue du Tchigatchigatchiga \n La langue du rororo, \n du Bleubleubleu, \n du Fleufleufleu. \n La langue du C est bon \n c est bon \n c est bon. \n";
const char string_6[] PROGMEM = "Bonjour tout le monde.\n Je suis tres content pour vous \n vous rencontrer jourdhui. \n Bon… Je tsui je vous remercie. \n Et tres bonne je suis tres chouette \n votrou… votrou… voutrou… theatre. \n Je vous remercie et bonn journée en r voir. \n";
const char string_7[] PROGMEM = "Quelle chance d etre \n au pays vertueux \n des droits de l’homme, \n  baigne dans la lumiere \n de l esprit des hauts nivellateurs \n tel mon bon docteur  \n Joseph Ignace Guillotin. \n Chacun est libre \n de s exprimer comme il peut \n pourvu qu il ne blesse \n physiquement \n quand la propriete chaque jour \n offense la pauvrete \n des sous-pauvres \n dans un air sature d azote.\n";

//fin du mode histoire


// Tableau des textes

const char* const string_table[] PROGMEM = {string_0, string_1,string_2,string_3,}; // si besoin compléter les valeurs string manquantes 
const char* const string_table1[] PROGMEM = {string_4, string_5,string_6, string_7,}; // si mode cadavre exquis commentez pour désactiver

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

chiffreal = random(0,4); // sélectionne un string entre 0 et 4 

  {
    strcpy_P(buffer, (char*)pgm_read_word(&(string_table[chiffreal]))); // copie le string sélectionné aléatoirement de la table string_table
    printer.println(buffer); //imprime le string situé dans le buffer de la carte
    delay( 1000 ); // patiente une seconde
   }
  }

  void vers2 () {
  {
    strcpy_P(buffer, (char*)pgm_read_word(&(string_table1[chiffreal]))); // copie le string sélectionné aléatoirement de la table string_table1
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
//    vers3(); // en fonction du nombre d'éléments à afficher décommentez cette ligne. Si vous souhaitez afficher plus d'éléments pensez à créer la fonction correspondante plus haut (ex ici void vers4)
    printer.feed(1);
    printer.println("Laurent Colomb \n Vocabul\x82s"); // placez ici votre signature
    printer.boldOff(); // fin du texte en gras
    printer.feed(2);
  printer.sleep(); //met en sommeil l'imprimante
    
  } 
  else {
    // éteins la led et ne fais rien 
    digitalWrite(ledPin, LOW);


 }
  
 }
