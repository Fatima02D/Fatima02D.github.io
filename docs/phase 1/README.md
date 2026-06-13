# Phase 1 — Base Hardware & Architecture Systeme

**Statut :** Complete
**Periode :** Avril — Juin 2026

---

## Objectif de cette phase

Assembler et cabler tous les composants materiels du robot, valider chaque connexion, et preparer le systeme pour le premier test logiciel.

Cette phase est terminee quand :
- Le RPi demarre avec l OS installe
- La communication I2C RPi → Hiwonder est validee
- Les moteurs repondent a une commande simple
- L ESP32 recoit les donnees de la manette Xbox

---

## Materiel de cette phase

| Composant | Quantite | Statut |
|---|---|---|
| Chassis Hiwonder a chenilles | 1 | Assemble |
| Raspberry Pi 4B 4GB | 1 | Operationnel |
| ESP32 TTGO T-Display V1.1 | 1 | En place |
| Hiwonder Encoder Motor Module V1.4 | 1 | Branche |
| HC-SR04 | 1 | Branche |
| LiPo Zeee 7.4V 2200mAh | 1 | Operationnelle |
| Manette Xbox | 1 | Disponible |
| Micro SD SanDisk 32GB | 1 | OS installe |
| Adaptateur Deans → JST | 1 | Branche |

---

## Branchements effectues

### RPi 4B → Hiwonder (I2C)

| RPi (pin physique) | Hiwonder |
|---|---|
| Pin 3 (SDA) | SDA |
| Pin 5 (SCL) | SCL |
| Pin 4 (5V) | 5V |
| Pin 6 (GND) | GND |

### Moteurs → Hiwonder

| Moteur | Port Hiwonder |
|---|---|
| Moteur gauche (JST 6 fils) | M1 |
| Moteur droit (JST 6 fils) | M2 |

### HC-SR04 → RPi

| HC-SR04 | RPi |
|---|---|
| VCC | Pin 2 (5V) |
| GND | Pin 9 (GND) |
| TRIG | Pin 11 (GPIO17) |
| ECHO | 1kΩ → Pin 13 (GPIO27) + 2kΩ → GND |

Diviseur de tension necessaire : HC-SR04 sort 5V, RPi GPIO accepte max 3.3V.

### ESP32 → RPi (UART)

| ESP32 TTGO | RPi |
|---|---|
| GPIO17 (TX) | Pin 10 (RX) |
| GPIO2 (RX) | Pin 8 (TX) |
| GND | Pin 14 (GND) |

---

## Architecture systeme

```
Xbox Controller (Bluetooth)
        |
      ESP32 TTGO        <- Bluetooth + ecran TFT 1.14"
        | UART
   Raspberry Pi 4B      <- Cerveau central + ROS2 (phase 2+)
        | I2C
  Hiwonder Encoder      <- Driver moteurs + lecture encodeurs
  Motor Module V1.4
      /        \
Moteur G       Moteur D
(M1)           (M2)

HC-SR04 → RPi Pin 11/13 (TRIG/ECHO)

Alimentation :
LiPo 7.4V → Hiwonder PWR (moteurs)
Powerbank USB-C → RPi (cerveau)
```

---

## Informations I2C

| Parametre | Valeur |
|---|---|
| Adresse Hiwonder | 0x34 |
| MOTOR_TYPE_ADDR | 20 |
| MOTOR_ENCODER_POLARITY_ADDR | 21 |
| MOTOR_FIXED_SPEED_ADDR | 51 |

Commandes moteurs (4 valeurs : M1, M2, M3, M4) :

```python
[100, 100, 0, 0]    # Avancer
[-100, -100, 0, 0]  # Reculer
[-100, 100, 0, 0]   # Tourner gauche
[100, -100, 0, 0]   # Tourner droite
[0, 0, 0, 0]        # Stop
```

---

## Checklist Phase 1

Hardware :
- [x] Chassis assemble
- [x] Moteurs sur M1 et M2
- [x] RPi → Hiwonder I2C cable
- [x] HC-SR04 cable avec diviseur tension
- [x] ESP32 → RPi UART cable
- [x] LiPo → Hiwonder branche
- [ ] RPi fixe sur chassis (vis M2.5 a acheter)

Logiciel :
- [x] Micro SD achetee
- [x] Raspberry Pi OS 64-bit installe
- [x] SSH active + WiFi configure
- [x] I2C active via raspi-config
- [x] Adresse I2C Hiwonder confirmee (0x34)
- [x] Test moteurs reussi — robot avance, recule, tourne

---

## Prochaine phase

Phase 2 — Teleoperation Xbox :
- Code ESP32 : reception manette Bluetooth
- Code RPi : envoi commandes via I2C vers Hiwonder
- Test moteurs gauche/droite
- Validation direction et vitesse
