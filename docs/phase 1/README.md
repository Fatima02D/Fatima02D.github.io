# Phase 1 — Base Hardware & Architecture Système

**Statut :** 🔄 En cours  
**Période :** Avril 2026  

---

## 🎯 Objectif de cette phase

Assembler et câbler tous les composants matériels du robot, valider chaque connexion, et préparer le système pour le premier test logiciel.

Cette phase est terminée quand :
- Le RPi démarre avec l'OS installé
- La communication I2C RPi → Hiwonder est validée
- Les moteurs répondent à une commande simple
- L'ESP32 reçoit les données de la manette Xbox

---

## 🛠️ Matériel de cette phase

| Composant | Quantité | 
|---|---|
| Châssis Hiwonder à chenilles | 1 |
| Raspberry Pi 4B 4GB | 1 | 
| ESP32 TTGO T-Display V1.1 | 1 | 
| Hiwonder Encoder Motor Module V1.4 | 1 | 
| HC-SR04 | 1 | 
| LiPo Zeee 7.4V 2200mAh | 1 | 
| Manette Xbox | 1 | 
| Micro SD 32GB | 1 | 
| Adaptateur XT30 → JST | 1 | 


---

## 🔌 Branchements effectués

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

*Note : gauche/droite à confirmer lors du premier test moteur*

### HC-SR04 → RPi
| HC-SR04 | RPi |
|---|---|
| VCC | Pin 2 (5V) |
| GND | Pin 9 (GND) |
| TRIG | Pin 11 (GPIO17) |
| ECHO | 1kΩ → Pin 13 (GPIO27) + 2kΩ → GND |

*Diviseur de tension nécessaire : HC-SR04 sort 5V, RPi GPIO accepte max 3.3V*

### ESP32 → RPi (UART) — À brancher
| ESP32 TTGO | RPi |
|---|---|
| GPIO17 (TX) | Pin 10 (RX) |
| GPIO2 (RX) | Pin 8 (TX) |
| GND | Pin 14 (GND) |

---

## ⚙️ Architecture système

```
Xbox Controller (Bluetooth)
        ↓
      ESP32 TTGO        ← Bluetooth + écran TFT 1.14"
        ↓ UART
   Raspberry Pi 4B      ← Cerveau central + ROS2 (phase 2+)
        ↓ I2C
  Hiwonder Encoder      ← Driver moteurs + lecture encodeurs
  Motor Module V1.4
      ↙        ↘
Moteur G       Moteur D
(M1)           (M2)

HC-SR04 → RPi Pin 11/13 (TRIG/ECHO)

Alimentation :
LiPo 7.4V → Hiwonder PWR (moteurs)
Powerbank USB-C → RPi (cerveau)
RPi USB-A → ESP32 (comm)
```

---

## 📋 Checklist Phase 1

**Hardware :**
- [x] Châssis assemblé
- [x] Moteurs sur M1 et M2
- [x] RPi → Hiwonder I2C câblé
- [x] HC-SR04 câblé avec diviseur tension
- [x] ESP32 → RPi UART câblé
- [x] LiPo → Hiwonder (adaptateur à acheter)
- [x] RPi fixé sur châssis (vis M2.5 à acheter)

**Logiciel :**
- [x] Micro SD achetée
- [x] Raspberry Pi OS 64-bit installé
- [x] SSH activé + WiFi configuré
- [x] Test I2C : `i2cdetect -y 1`
- [x] Adresse I2C Hiwonder confirmée

---

## 🔜 Prochaine phase

Phase 2 — Téléopération Xbox :
- Code ESP32 : réception manette Bluetooth
- Code RPi : envoi commandes via I2C vers Hiwonder
- Test moteurs gauche/droite
- Validation direction et vitesse
