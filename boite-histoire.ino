
/*
 Ce programme s'appuie sur le travail mené par Giles Booth : 
 http://www.suppertime.co.uk/blogmywiki/2012/10/howtopoems/

 Ce programme est placé sous licence Creative Commons NC-BY-SA : https://creativecommons.org/licenses/by-nc-sa/2.0/fr/

 julanimtic http://blog.animtic.fr

 les textes proposés ici en exemple sont issus du domaine public.
 
 Boîte à histoires V1 28-05-2016

 */

 //une led est utilisée pour vérifier le bon fonctionnement du bouton. Ce n'est pas obligatoire. 
const int buttonPin = 2;     // le numéro de la broche utilisée par le bouton
const int ledPin =  13;      // le numéro de la broche utilisée par la led
int buttonState = 0;         // variable pour vérifier l'état du bouton 


//appel de la bibiothèque de l'imprimante, voir le tutoriel d'utilisation de l'imprimante sur adafruit : https://learn.adafruit.com/mini-thermal-receipt-printer
#include "Adafruit_Thermal.h"

#include "SoftwareSerial.h"
#define TX_PIN 6 
#define RX_PIN 5

SoftwareSerial mySerial(RX_PIN, TX_PIN); 
Adafruit_Thermal printer(&mySerial);    


//fonction intégrant les différents textes à imprimer
    void textes() {

  // placez le titre du texte 
  char* titre[]={"La Grenouille qui veut se faire aussi grosse que le Boeuf",};
  
  // placez le texte de votre histoire/poème ici
  // le texte doit être sur une seule ligne, voir le fichier readme pour le formatage du texte et des caractères spéciaux
  char* texte[]={"Une Grenouille vit un Boeuf\nQui lui sembla de belle taille.\nElle, qui n\x27\x82tait pas grosse en tout comme un oeuf,\nEnvieuse, s\x27\x82tend, et s\x27 enfle, et se travaille,\nPour \x82galer l\x27 animal en \ngrosseur,\nDisant : \x22Regardez bien, ma \nsoeur ;\nEst-ce assez ? dites-moi ;\n n\x27y suis-je point encore ?\n-Nenni. \n-M\x27y voici donc ? \n-Point du tout. \n-M\x27y voil\x85 ?\n- Vous n\x27 en approchez point.\x22 \nLa ch\x82tive pecore\nS\x27 enfla si bien qu\x27 elle creva.\nLe monde est plein de gens qui \nne sont pas plus sages :\nTout bourgeois veut b\x83tir comme les grands seigneurs,\nTout petit prince a des \nambassadeurs,\nTout marquis veut avoir des \npages.\x27",};

  // placez le nom des auteurs
  char* auteur[]={"Jean de LA FONTAINE",};

  int textesnum = random(2);  // Pour le chiffre n indiqué entre parenthèse, sélectionne un numéro de texte entre o et n-1. ici 7 
  // la valeur est définie une fois et sera réutilisée pour chacun des éléments à imprimer


  printer.boldOn(); //met le texte en gras 
  printer.feed(1); //passe 1 ligne sans imprimer (modifiez la valeur pour modifier l'espace
  printer.doubleHeightOn(); // met le texte en grand caractère
  printer.println(titre[textesnum]); // imprime le titre 
  printer.doubleHeightOff(); // fin du texte en grand caractère
  printer.boldOff(); // fin du texte en gras
  
  printer.feed(1);
  printer.println(texte[textesnum]); // imprime le texte

  printer.justify('R'); //texte aligné à droite
  printer.println(auteur[textesnum]); // imprime l'auteur
  printer.justify('L'); //texte aligné à gauche
  printer.feed(1); 
  printer.println("La petite boite \x85 histoire"); //placez ici votre signature
  printer.feed(3);
  
  delay(3000);   // pause de 3 secondes  (3000 milisecondes)    
}

//fin de la fonction textes

// décommentez la fonction suivante, en prenant soin de commenter la précédente, pour utiliser la boîte à histoire comme générateur de cadavres exquis.


/*
  void textes() {

  // placez le premier vers 
  char* vers1[]={"La Grenouille qui veut se faire aussi grosse que le Boeuf",};
  
  // placez le second vers
  // le texte doit être sur une seule ligne, voir le fichier readme pour le formatage du texte et des caractères spéciaux
  char* vers2[]={"Une Grenouille vit un Boeuf\nQui lui sembla de belle taille.\nElle, qui n\x27\x82tait pas grosse en tout comme un oeuf,\nEnvieuse, s\x27\x82tend, et s\x27 enfle, et se travaille,\nPour \x82galer l\x27 animal en \ngrosseur,\nDisant : \x22Regardez bien, ma \nsoeur ;\nEst-ce assez ? dites-moi ;\n n\x27y suis-je point encore ?\n-Nenni. \n-M\x27y voici donc ? \n-Point du tout. \n-M\x27y voil\x85 ?\n- Vous n\x27 en approchez point.\x22 \nLa ch\x82tive pecore\nS\x27 enfla si bien qu\x27 elle creva.\nLe monde est plein de gens qui \nne sont pas plus sages :\nTout bourgeois veut b\x83tir comme les grands seigneurs,\nTout petit prince a des \nambassadeurs,\nTout marquis veut avoir des \npages.\x27",};

  // placez le troisième vers
  char* vers3[]={"Jean de LA FONTAINE",};

  int vers1num = random(2);  // Pour le chiffre n indiqué entre parenthèse, sélectionne un numéro de texte entre o et n-1. ici 7 
  int vers2num = random(2);
  int vers3num = random(2);

  printer.feed(1); //passe 1 ligne sans imprimer (modifiez la valeur pour modifier l'espace
  printer.println(vers1[vers1num]); // imprime le premier vers
  
  printer.feed(1);
  printer.println(vers2[vers2num]); // imprime le second vers

  printer.println(vers3[vers3num]); // imprime le troisième vers
  printer.feed(2); 
  printer.println("La petite boite \x85 histoire"); //placez ici votre signature
  printer.feed(3);
  
  delay(3000);   // pause de 3 secondes  (3000 milisecondes)    
}
//fin de la fonction cadavre exquis

*/


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
    textes(); //lance la fonction textes (voir plus haut)
  printer.sleep(); //met en sommeil l'imprimante
    
  } 
  else {
    // éteins la led et ne fais rien 
    digitalWrite(ledPin, LOW);


 }
  
 }
