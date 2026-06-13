# Phase 2 — Teleoperation Xbox

**Statut :** En cours
**Periode :** Juin 2026
**Prerequis :** Phase 1 complete — I2C RPi → Hiwonder fonctionnel

---

## Objectif de cette phase

Controler le robot a distance via la manette Xbox. L'ESP32 recoit les commandes Bluetooth de la manette et les transmet au RPi via UART. Le RPi envoie ensuite les commandes de vitesse a la Hiwonder via I2C.

Cette phase est terminee quand :
- L'ESP32 se connecte a la manette Xbox via Bluetooth
- Les joysticks controlent la vitesse et la direction des chenilles
- La latence commande → mouvement est inferieure a 100ms
- Le robot peut etre controle de facon fluide et predictible

---

## Architecture de communication

```
Manette Xbox (Bluetooth)
        |
      ESP32 TTGO        <- recoit joystick L/R, boutons
        | UART (GPIO17 TX → RPi Pin10 RX)
   Raspberry Pi 4B      <- decode commandes, calcule vitesses
        | I2C (0x34)
  Hiwonder Module       <- applique vitesses aux moteurs
        |
  Moteurs M1 / M2
```

---

## Branchements Phase 2

### ESP32 → RPi (UART)

| ESP32 TTGO | RPi |
|---|---|
| GPIO17 (TX) | Pin 10 (RX) |
| GPIO2 (RX) | Pin 8 (TX) |
| GND | Pin 14 (GND) |

Ces branchements s'ajoutent aux branchements I2C deja en place depuis la Phase 1.

---

## Stack logiciel

| Composant | Langage | Role |
|---|---|---|
| ESP32 | C++ (Arduino) | Reception Bluetooth Xbox + envoi UART |
| RPi | Python | Reception UART + envoi I2C Hiwonder |

---

## Mapping joystick → vitesse moteurs

Modele de controle differentiel (skid steering) :

```
Joystick gauche (axe Y) = vitesse lineaire (avant/arriere)
Joystick droit (axe X)  = vitesse angulaire (gauche/droite)

Moteur gauche = vitesse_lineaire - vitesse_angulaire
Moteur droit  = vitesse_lineaire + vitesse_angulaire
```

Valeurs joystick : -100 a +100
Valeurs moteur : -100 a +100

---

## Checklist Phase 2

Branchements :
- [ ] ESP32 TX → RPi Pin 10 (RX)
- [ ] ESP32 RX → RPi Pin 8 (TX)
- [ ] ESP32 GND → RPi Pin 14 (GND)

Logiciel ESP32 :
- [ ] Bibliotheque Xbox Bluetooth installee
- [ ] Connexion manette etablie
- [ ] Lecture joysticks fonctionnelle
- [ ] Envoi commandes via UART

Logiciel RPi :
- [ ] Reception UART fonctionnelle
- [ ] Decodage commandes joystick
- [ ] Envoi vitesses via I2C Hiwonder
- [ ] Test controle robot en temps reel

Validation :
- [ ] Joystick avant → robot avance
- [ ] Joystick arriere → robot recule
- [ ] Joystick droite → robot tourne droite
- [ ] Joystick gauche → robot tourne gauche
- [ ] Relacher joystick → robot s'arrete
- [ ] Latence < 100ms

---

## Prochaine phase

Phase 3 — Odometrie :
- Lecture des encodeurs moteurs via Hiwonder I2C
- Calcul position (x, y, theta) en temps reel
- Correction de trajectoire avec PID

